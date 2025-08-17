#define CL_HPP_TARGET_OPENCL_VERSION 300
#define CL_HPP_MINIMUM_OPENCL_VERSION 120

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cstdint>

#include <CL/opencl.hpp>

// Configuration constants
constexpr uint32_t vector_size = 10;  // Number of dimensions for our vectors
constexpr uint32_t num_vectors = 1000000;  // Number of vector pairs to add for performance testing

// OpenCL kernel source code for vector addition
// This kernel will be executed in parallel on each compute unit
const char* vector_add_kernel_source = R"(
__kernel void vector_add(
    __global const float* a,     // Input vector A (read-only)
    __global const float* b,     // Input vector B (read-only)
    __global float* result,      // Output vector (write-only)
    const unsigned int count     // Number of elements to process
) {
    // Get the index of the current work-item (thread)
    int gid = get_global_id(0);

    // Make sure we don't go out of bounds
    if (gid < count) {
        // Perform the vector addition: result[i] = a[i] + b[i]
        result[gid] = a[gid] + b[gid];
    }
}
)";

// Function to find a specific device type (CPU or GPU)
cl::Device findDevice(bool run_on_gpu)
{
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    cl_device_type target_type = run_on_gpu ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU;

    // Search through all platforms for the desired device type
    for ( auto& platform : platforms )
    {
        std::vector<cl::Device> devices;
        try
        {
            platform.getDevices(target_type, &devices);
            if ( !devices.empty() )
            {
                // Return the first device of the requested type
                return devices[0];
            }
        }
        catch ( const std::exception& )
        {
            // This platform doesn't have devices of the requested type, continue searching
            continue;
        }
    }

    throw std::runtime_error("No suitable device found for the requested type");
}

// Function to generate random test data
std::vector<float> generateRandomVector(size_t size)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-100.0f, 100.0f);

    std::vector<float> vec(size);
    for ( size_t i = 0; i < size; ++i )
    {
        vec[i] = dis(gen);
    }
    return vec;
}

// Function to perform CPU-based vector addition for verification
std::vector<float> cpuVectorAdd(const std::vector<float>& a, const std::vector<float>& b)
{
    std::vector<float> result(a.size());
    for ( size_t i = 0; i < a.size(); ++i )
    {
        result[i] = a[i] + b[i];
    }
    return result;
}

// Function to verify results (compare OpenCL result with CPU result)
bool verifyResults(const std::vector<float>& opencl_result, const std::vector<float>& cpu_result, float tolerance = 0.001f)
{
    if ( opencl_result.size() != cpu_result.size() )
    {
        return false;
    }

    for (size_t i = 0; i < opencl_result.size(); ++i)
    {
        if (std::abs(opencl_result[i] - cpu_result[i]) > tolerance)
        {
            std::cout << "Mismatch at index " << i << ": OpenCL=" << opencl_result[i]
                      << ", CPU=" << cpu_result[i] << std::endl;
            return false;
        }
    }
    return true;
}

int main()
{
    // Configuration: Set this flag to choose between CPU and GPU execution
    bool run_on_gpu = true;  // Change to false to run on CPU

    try
    {
        std::cout << "=== OpenCL Vector Addition Demo ===" << std::endl;
        std::cout << "Vector dimensions: " << vector_size << std::endl;
        std::cout << "Number of vector pairs: " << num_vectors << std::endl;
        std::cout << "Total elements to process: " << (vector_size * num_vectors) << std::endl;
        std::cout << "Target device: " << (run_on_gpu ? "GPU" : "CPU") << std::endl << std::endl;

        // Step 1: Find and select the appropriate device
        std::cout << "--- Device Selection ---" << std::endl;
        cl::Device device = findDevice(run_on_gpu);
        std::string device_name = device.getInfo<CL_DEVICE_NAME>();
        std::string device_vendor = device.getInfo<CL_DEVICE_VENDOR>();
        cl_uint compute_units = device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();

        std::cout << "Selected device: " << device_name << std::endl;
        std::cout << "Vendor: " << device_vendor << std::endl;
        std::cout << "Compute units: " << compute_units << std::endl << std::endl;

        // Step 2: Create OpenCL context and command queue
        std::cout << "--- OpenCL Setup ---" << std::endl;
        cl::Context context(device);
        cl::CommandQueue queue(context, device);
        std::cout << "✓ Context and command queue created" << std::endl;

        // Step 3: Create and build the OpenCL program from source
        cl::Program::Sources sources;
        sources.push_back({vector_add_kernel_source, strlen(vector_add_kernel_source)});
        cl::Program program(context, sources);

        // Build the program for the selected device
        try
        {
            program.build({device});
            std::cout << "✓ OpenCL kernel compiled successfully" << std::endl;
        }
        catch ( const std::exception& )
        {
            // If build fails, show the build log for debugging
            std::string build_log = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);
            std::cerr << "Build failed! Build log:" << std::endl << build_log << std::endl;
            return -1;
        }

        // Step 4: Create the kernel object
        cl::Kernel kernel(program, "vector_add");
        std::cout << "✓ Kernel created" << std::endl << std::endl;

        // Step 5: Generate test data
        std::cout << "--- Test Data Generation ---" << std::endl;
        size_t total_elements = vector_size * num_vectors;

        std::vector<float> vector_a = generateRandomVector(total_elements);
        std::vector<float> vector_b = generateRandomVector(total_elements);
        std::vector<float> opencl_result(total_elements);

        std::cout << "✓ Generated " << total_elements << " random elements" << std::endl;

        // Step 6: Create OpenCL memory buffers
        std::cout << "--- Memory Buffer Creation ---" << std::endl;
        size_t buffer_size = total_elements * sizeof(float);

        // Create buffers on the device
        cl::Buffer buffer_a(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, buffer_size, vector_a.data());
        cl::Buffer buffer_b(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, buffer_size, vector_b.data());
        cl::Buffer buffer_result(context, CL_MEM_WRITE_ONLY, buffer_size);

        std::cout << "✓ Created device memory buffers (" << (buffer_size * 3 / 1024 / 1024) << " MB total)" << std::endl;

        // Step 7: Set kernel arguments
        kernel.setArg(0, buffer_a);      // Input vector A
        kernel.setArg(1, buffer_b);      // Input vector B
        kernel.setArg(2, buffer_result); // Output buffer
        kernel.setArg(3, static_cast<cl_uint>(total_elements)); // Element count

        std::cout << "✓ Kernel arguments set" << std::endl << std::endl;

        // Step 8: Execute the kernel
        std::cout << "--- OpenCL Kernel Execution ---" << std::endl;

        // Determine work group size based on device type
        size_t local_work_size;
        if ( run_on_gpu )
        {
            // For GPUs, use larger work groups (typically 64, 128, or 256)
            local_work_size = 256;
        }
        else
        {
            // For CPUs, use smaller work groups (typically 1, 4, or 8)
            local_work_size = 8;
        }

        // Calculate global work size (must be multiple of local work size)
        size_t global_work_size = ((total_elements + local_work_size - 1) / local_work_size) * local_work_size;

        std::cout << "Global work size: " << global_work_size << std::endl;
        std::cout << "Local work size: " << local_work_size << std::endl;
        std::cout << "Work groups: " << (global_work_size / local_work_size) << std::endl;

        // Execute the kernel and measure execution time
        auto start_time = std::chrono::high_resolution_clock::now();

        queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(global_work_size), cl::NDRange(local_work_size));
        queue.finish(); // Wait for completion

        auto end_time = std::chrono::high_resolution_clock::now();
        auto opencl_duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

        std::cout << "✓ Kernel execution completed" << std::endl;
        std::cout << "OpenCL execution time: " << opencl_duration.count() << " microseconds" << std::endl;

        // Step 9: Read results back from device
        queue.enqueueReadBuffer(buffer_result, CL_TRUE, 0, buffer_size, opencl_result.data());
        std::cout << "✓ Results copied back to host" << std::endl << std::endl;

        // Step 10: Verify results by comparing with CPU implementation
        std::cout << "--- Result Verification ---" << std::endl;

        // For verification, use smaller dataset to avoid long CPU computation
        size_t verify_elements = std::min(static_cast<size_t>(10000), total_elements);
        std::vector<float> cpu_a(vector_a.begin(), vector_a.begin() + verify_elements);
        std::vector<float> cpu_b(vector_b.begin(), vector_b.begin() + verify_elements);

        auto cpu_start = std::chrono::high_resolution_clock::now();
        std::vector<float> cpu_result = cpuVectorAdd(cpu_a, cpu_b);
        auto cpu_end = std::chrono::high_resolution_clock::now();
        auto cpu_duration = std::chrono::duration_cast<std::chrono::microseconds>(cpu_end - cpu_start);

        std::vector<float> opencl_verify(opencl_result.begin(), opencl_result.begin() + verify_elements);

        bool results_match = verifyResults(opencl_verify, cpu_result);
        std::cout << "CPU computation time (for " << verify_elements << " elements): "
                  << cpu_duration.count() << " microseconds" << std::endl;
        std::cout << "Results verification: " << (results_match ? "✓ PASSED" : "✗ FAILED") << std::endl;

        // Step 11: Display performance summary
        std::cout << "\n--- Performance Summary ---" << std::endl;
        std::cout << "Device: " << device_name << std::endl;
        std::cout << "Elements processed: " << total_elements << std::endl;
        std::cout << "OpenCL time: " << opencl_duration.count() << " μs" << std::endl;

        if ( verify_elements == total_elements )
        {
            double speedup = static_cast<double>(cpu_duration.count()) / opencl_duration.count();
            std::cout << "CPU time: " << cpu_duration.count() << " μs" << std::endl;
            std::cout << "Speedup: " << speedup << "x" << std::endl;
        }

        // Show some sample results
        std::cout << "\n--- Sample Results ---" << std::endl;
        for ( int i = 0; i < std::min(5, static_cast<int>(total_elements)); ++i )
        {
            std::cout << "Element " << i << ": " << vector_a[i] << " + " << vector_b[i]
                      << " = " << opencl_result[i] << std::endl;
        }

        std::cout << "\nDemo completed successfully!" << std::endl;

    }
    catch ( const std::exception& e )
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    catch (...)
    {
        std::cerr << "Unknown error occurred" << std::endl;
        return -1;
    }

    return 0;
}