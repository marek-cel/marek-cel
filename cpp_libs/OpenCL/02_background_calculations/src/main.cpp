#define CL_HPP_TARGET_OPENCL_VERSION 300
#define CL_HPP_MINIMUM_OPENCL_VERSION 120

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <random>
#include <cmath>
#include <iomanip>

#include <CL/opencl.hpp>

// Configuration constants
constexpr uint32_t NUM_BODIES = 1024;        // Number of particles in simulation
constexpr float SIMULATION_DT = 0.016f;      // Time step (60 FPS target)
constexpr float G_CONSTANT = 6.67430e-11f;   // Gravitational constant (scaled for demo)
constexpr float DAMPING = 0.999f;            // Velocity damping to prevent explosion
constexpr float SOFTENING = 0.1f;            // Softening parameter to avoid singularities
constexpr int SYNC_INTERVAL_MS = 33;         // Sync every ~30ms (30 FPS display)
constexpr int SIMULATION_STEPS_PER_SYNC = 2; // Multiple physics steps per display update

// Structure to represent a particle/body in our simulation
struct Body
{
    float x, y, z;        // Position
    float vx, vy, vz;     // Velocity
    float mass;           // Mass
    float padding;        // Align to 32 bytes for better GPU memory access
};

// OpenCL kernel for N-body gravitational simulation
const char* nbody_kernel_source = R"(
// Structure matching our C++ Body struct
typedef struct {
    float x, y, z;        // Position
    float vx, vy, vz;     // Velocity
    float mass;           // Mass
    float padding;        // Padding for alignment
} Body;

__kernel void update_bodies(
    __global Body* bodies,           // Array of all bodies
    const float dt,                  // Time step
    const float G,                   // Gravitational constant
    const float damping,             // Velocity damping factor
    const float softening,           // Softening parameter
    const unsigned int num_bodies    // Total number of bodies
) {
    // Get the index of the current work-item (which body we're updating)
    int i = get_global_id(0);

    // Make sure we don't go out of bounds
    if (i >= num_bodies) return;

    // Get the current body we're updating
    Body body = bodies[i];

    // Calculate gravitational forces from all other bodies
    float fx = 0.0f, fy = 0.0f, fz = 0.0f;

    for (int j = 0; j < num_bodies; j++) {
        if (i == j) continue; // Don't calculate force with itself

        Body other = bodies[j];

        // Calculate distance vector
        float dx = other.x - body.x;
        float dy = other.y - body.y;
        float dz = other.z - body.z;

        // Calculate distance squared with softening to avoid singularities
        float dist_sq = dx*dx + dy*dy + dz*dz + softening*softening;
        float dist = sqrt(dist_sq);

        // Calculate gravitational force magnitude: F = G * m1 * m2 / r^2
        float force_magnitude = G * body.mass * other.mass / dist_sq;

        // Normalize direction and apply force
        float inv_dist = 1.0f / dist;
        fx += force_magnitude * dx * inv_dist;
        fy += force_magnitude * dy * inv_dist;
        fz += force_magnitude * dz * inv_dist;
    }

    // Update velocity using F = ma, so a = F/m
    body.vx += (fx / body.mass) * dt;
    body.vy += (fy / body.mass) * dt;
    body.vz += (fz / body.mass) * dt;

    // Apply velocity damping to prevent system from exploding
    body.vx *= damping;
    body.vy *= damping;
    body.vz *= damping;

    // Update position using velocity
    body.x += body.vx * dt;
    body.y += body.vy * dt;
    body.z += body.vz * dt;

    // Write updated body back to global memory
    bodies[i] = body;
}
)";

class PhysicsSimulation
{
private:
    // OpenCL objects
    cl::Context context;
    cl::CommandQueue queue;
    cl::Program program;
    cl::Kernel kernel;
    cl::Buffer bodies_buffer;

    // Simulation data
    std::vector<Body> bodies;
    std::vector<Body> display_bodies;  // Copy for main thread display

    // Threading and synchronization
    std::thread simulation_thread;
    std::mutex data_mutex;
    std::atomic<bool> running{false};
    std::atomic<bool> simulation_ready{false};
    std::atomic<uint64_t> simulation_steps{0};
    std::atomic<double> avg_frame_time{0.0};

    // Performance tracking
    std::chrono::high_resolution_clock::time_point last_sync_time;
    std::chrono::high_resolution_clock::time_point simulation_start_time;

public:
    PhysicsSimulation(bool use_gpu = true)
    {
        initializeOpenCL(use_gpu);
        initializeBodies();
        setupOpenCLBuffers();
        last_sync_time = std::chrono::high_resolution_clock::now();
        simulation_start_time = last_sync_time;
    }

    ~PhysicsSimulation()
    {
        stop();
    }

    void initializeOpenCL(bool use_gpu)
    {
        std::cout << "--- Initializing OpenCL for Physics Simulation ---" << std::endl;

        // Find appropriate device
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);

        cl_device_type target_type = use_gpu ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU;
        cl::Device device;
        bool found = false;

        for ( auto& platform : platforms )
        {
            std::vector<cl::Device> devices;
            try
            {
                platform.getDevices(target_type, &devices);
                if ( !devices.empty() )
                {
                    device = devices[0];
                    found = true;
                    break;
                }
            }
            catch ( const std::exception& )
            {
                continue;
            }
        }

        if ( !found )
        {
            throw std::runtime_error("No suitable OpenCL device found");
        }

        std::string device_name = device.getInfo<CL_DEVICE_NAME>();
        std::cout << "Using device: " << device_name << std::endl;

        // Create context and command queue
        context = cl::Context(device);
        queue = cl::CommandQueue(context, device);

        // Build program
        cl::Program::Sources sources;
        sources.push_back({nbody_kernel_source, strlen(nbody_kernel_source)});
        program = cl::Program(context, sources);

        try
        {
            program.build({device});
            std::cout << "✓ OpenCL kernel compiled successfully" << std::endl;
        }
        catch ( const std::exception& )
        {
            std::string build_log = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);
            std::cerr << "Build failed! Build log:" << std::endl << build_log << std::endl;
            throw;
        }

        // Create kernel
        kernel = cl::Kernel(program, "update_bodies");
        std::cout << "✓ Physics simulation kernel ready" << std::endl;
    }

    void initializeBodies()
    {
        std::cout << "--- Initializing " << NUM_BODIES << " Bodies ---" << std::endl;

        bodies.resize(NUM_BODIES);
        display_bodies.resize(NUM_BODIES);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> pos_dist(-10.0f, 10.0f);
        std::uniform_real_distribution<float> vel_dist(-1.0f, 1.0f);
        std::uniform_real_distribution<float> mass_dist(1.0f, 5.0f);

        // Create a central massive body for interesting dynamics
        bodies[0] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 50.0f, 0.0f};

        // Generate random bodies around the center
        for ( size_t i = 1; i < NUM_BODIES; ++i )
        {
            float x = pos_dist(gen);
            float y = pos_dist(gen);
            float z = pos_dist(gen);
            float mass = mass_dist(gen);

            // Give bodies some initial orbital velocity
            float r = std::sqrt(x*x + y*y + z*z);
            float orbital_speed = std::sqrt(G_CONSTANT * 50.0f / (r + 1.0f)) * 0.5f;

            bodies[i] = {
                x, y, z,
                -y * orbital_speed / r, x * orbital_speed / r, vel_dist(gen) * 0.1f,
                mass, 0.0f
            };
        }

        std::cout << "✓ Bodies initialized with orbital dynamics" << std::endl;
    }

    void setupOpenCLBuffers()
    {
        std::cout << "--- Setting up OpenCL Buffers ---" << std::endl;

        size_t buffer_size = sizeof(Body) * NUM_BODIES;

        // Create buffer and copy initial data
        bodies_buffer = cl::Buffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
                                   buffer_size, bodies.data());

        // Set kernel arguments
        kernel.setArg(0, bodies_buffer);
        kernel.setArg(1, SIMULATION_DT);
        kernel.setArg(2, G_CONSTANT);
        kernel.setArg(3, DAMPING);
        kernel.setArg(4, SOFTENING);
        kernel.setArg(5, static_cast<cl_uint>(NUM_BODIES));

        std::cout << "✓ OpenCL buffers created (" << (buffer_size / 1024) << " KB)" << std::endl;
    }

    void simulationLoop()
    {
        std::cout << "--- Starting Physics Simulation Thread ---" << std::endl;

        auto last_frame_time = std::chrono::high_resolution_clock::now();
        double frame_time_accumulator = 0.0;
        int frame_count = 0;

        // Simulation loop runs independently of display
        while ( running.load() )
        {
            auto frame_start = std::chrono::high_resolution_clock::now();

            // Run multiple simulation steps per iteration for better accuracy
            for ( int step = 0; step < SIMULATION_STEPS_PER_SYNC; ++step )
            {
                // Execute physics kernel
                size_t global_size = ((NUM_BODIES + 255) / 256) * 256; // Round up to multiple of 256
                size_t local_size = 256;

                queue.enqueueNDRangeKernel(kernel, cl::NullRange,
                                           cl::NDRange(global_size), cl::NDRange(local_size));
                queue.finish();

                simulation_steps.fetch_add(1);
            }

            // Periodically sync with main thread
            auto now = std::chrono::high_resolution_clock::now();
            auto sync_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_sync_time);

            if ( sync_elapsed.count() >= SYNC_INTERVAL_MS )
            {
                // Copy data back from GPU for display
                queue.enqueueReadBuffer(bodies_buffer, CL_TRUE, 0,
                                        sizeof(Body) * NUM_BODIES, bodies.data());

                // Thread-safe copy to display buffer
                {
                    std::lock_guard<std::mutex> lock(data_mutex);
                    display_bodies = bodies;
                    simulation_ready.store(true);
                }

                last_sync_time = now;
            }

            // Calculate average frame time for performance monitoring
            auto frame_end = std::chrono::high_resolution_clock::now();
            auto frame_duration = std::chrono::duration_cast<std::chrono::microseconds>(frame_end - frame_start);

            frame_time_accumulator += frame_duration.count();
            frame_count++;

            if ( frame_count >= 100 ) // Update average every 100 frames
            {
                avg_frame_time.store(frame_time_accumulator / frame_count);
                frame_time_accumulator = 0.0;
                frame_count = 0;
            }

            // Small sleep to prevent 100% CPU usage while maintaining responsiveness
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }

        std::cout << "Physics simulation thread terminated" << std::endl;
    }

    void start()
    {
        if ( running.load() ) return;

        running.store(true);
        simulation_thread = std::thread(&PhysicsSimulation::simulationLoop, this);

        std::cout << "✓ Physics simulation started" << std::endl;
    }

    void stop()
    {
        if ( !running.load() ) return;

        running.store(false);
        if ( simulation_thread.joinable() )
        {
            simulation_thread.join();
        }

        std::cout << "Physics simulation stopped" << std::endl;
    }

    // Get current simulation state (thread-safe)
    std::vector<Body> getCurrentState()
    {
        std::lock_guard<std::mutex> lock(data_mutex);
        return display_bodies;
    }

    // Get simulation statistics
    struct SimulationStats
    {
        uint64_t total_steps;
        double avg_frame_time_us;
        double simulation_time_s;
        double steps_per_second;
    };

    SimulationStats getStats() const
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto total_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - simulation_start_time);
        double time_s = total_time.count() / 1000.0;

        uint64_t steps = simulation_steps.load();

        return {
            steps,
            avg_frame_time.load(),
            time_s,
            steps > 0 ? steps / time_s : 0.0
        };
    }

    bool isReady() const
    {
        return simulation_ready.load();
    }
};

// Simple console-based visualization
void displaySimulation(const std::vector<Body>& bodies)
{
    // Clear screen (ANSI escape sequence)
    std::cout << "\033[2J\033[H";

    std::cout << "=== Real-time N-Body Gravitational Simulation ===" << std::endl;
    std::cout << "Bodies: " << bodies.size() << " | ";

    // Calculate system properties for display
    float total_kinetic = 0.0f;
    float center_x = 0.0f, center_y = 0.0f, center_z = 0.0f;
    float total_mass = 0.0f;

    for ( const auto& body : bodies )
    {
        float v_sq = body.vx*body.vx + body.vy*body.vy + body.vz*body.vz;
        total_kinetic += 0.5f * body.mass * v_sq;

        center_x += body.x * body.mass;
        center_y += body.y * body.mass;
        center_z += body.z * body.mass;
        total_mass += body.mass;
    }

    center_x /= total_mass;
    center_y /= total_mass;
    center_z /= total_mass;

    std::cout << "Total Kinetic Energy: " << std::fixed << std::setprecision(2) << total_kinetic << std::endl;
    std::cout << "Center of Mass: (" << center_x << ", " << center_y << ", " << center_z << ")" << std::endl;
    std::cout << std::endl;

    // Show positions of first 10 bodies for monitoring
    std::cout << "Sample Body Positions:" << std::endl;
    std::cout << "ID |      X |      Y |      Z |   Mass | Speed" << std::endl;
    std::cout << "---|--------|--------|--------|--------|--------" << std::endl;

    for ( int i = 0; i < std::min(10, static_cast<int>(bodies.size())); ++i )
    {
        const auto& b = bodies[i];
        float speed = std::sqrt(b.vx*b.vx + b.vy*b.vy + b.vz*b.vz);

        std::cout << std::setw(2) << i << " |"
                  << std::setw(7) << std::fixed << std::setprecision(2) << b.x << " |"
                  << std::setw(7) << std::fixed << std::setprecision(2) << b.y << " |"
                  << std::setw(7) << std::fixed << std::setprecision(2) << b.z << " |"
                  << std::setw(7) << std::fixed << std::setprecision(1) << b.mass << " |"
                  << std::setw(7) << std::fixed << std::setprecision(3) << speed << std::endl;
    }
}

int main()
{
    try
    {
        std::cout << "=== Real-time OpenCL Physics Simulation ===" << std::endl;
        std::cout << "Configuration:" << std::endl;
        std::cout << "- Bodies: " << NUM_BODIES << std::endl;
        std::cout << "- Time step: " << SIMULATION_DT << "s" << std::endl;
        std::cout << "- Sync interval: " << SYNC_INTERVAL_MS << "ms" << std::endl;
        std::cout << "- Steps per sync: " << SIMULATION_STEPS_PER_SYNC << std::endl;
        std::cout << std::endl;

        // Create and start simulation (use GPU by default)
        bool use_gpu = true;
        PhysicsSimulation simulation(use_gpu);
        simulation.start();

        std::cout << "\nPress Ctrl+C to stop simulation..." << std::endl;
        std::cout << "Waiting for simulation to start..." << std::endl;

        // Main display loop
        auto last_display_time = std::chrono::high_resolution_clock::now();

        while ( true )
        {
            // Check if we have new simulation data
            if ( simulation.isReady() )
            {
                auto current_bodies = simulation.getCurrentState();
                displaySimulation(current_bodies);

                // Display performance statistics
                auto stats = simulation.getStats();
                std::cout << std::endl << "=== Performance Statistics ===" << std::endl;
                std::cout << "Simulation time: " << std::fixed << std::setprecision(1) << stats.simulation_time_s << "s" << std::endl;
                std::cout << "Total simulation steps: " << stats.total_steps << std::endl;
                std::cout << "Steps per second: " << std::fixed << std::setprecision(1) << stats.steps_per_second << std::endl;
                std::cout << "Avg frame time: " << std::fixed << std::setprecision(1) << stats.avg_frame_time_us << " μs" << std::endl;

                std::cout << std::endl << "Press Ctrl+C to stop..." << std::endl;
            }

            // Sleep for display update interval
            std::this_thread::sleep_for(std::chrono::milliseconds(SYNC_INTERVAL_MS));
        }

    }
    catch ( const std::exception& e )
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}