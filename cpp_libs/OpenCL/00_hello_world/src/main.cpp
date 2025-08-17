#define CL_HPP_TARGET_OPENCL_VERSION 300
#define CL_HPP_MINIMUM_OPENCL_VERSION 120

#include <iostream>
#include <vector>
#include <string>

#include <CL/opencl.hpp>

int main()
{
    try
    {
        // Get all available OpenCL platforms
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);

        if ( platforms.empty() )
        {
            std::cerr << "No OpenCL platforms found!" << std::endl;
            return -1;
        }

        std::cout << "Found " << platforms.size() << " OpenCL platform(s):" << std::endl;

        // Iterate through all platforms and their devices
        for ( size_t i = 0; i < platforms.size(); ++i )
        {
            auto& platform = platforms[i];

            // Get platform information
            std::string platform_name = platform.getInfo<CL_PLATFORM_NAME>();
            std::string platform_vendor = platform.getInfo<CL_PLATFORM_VENDOR>();
            std::string platform_version = platform.getInfo<CL_PLATFORM_VERSION>();

            std::cout << "\n--- Platform " << i << " ---" << std::endl;
            std::cout << "Name: " << platform_name << std::endl;
            std::cout << "Vendor: " << platform_vendor << std::endl;
            std::cout << "Version: " << platform_version << std::endl;

            // Get all devices for this platform
            std::vector<cl::Device> devices;
            platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

            std::cout << "Devices: " << devices.size() << std::endl;

            // Display information about each device
            for ( size_t j = 0; j < devices.size(); ++j )
            {
                auto& device = devices[j];

                std::string device_name = device.getInfo<CL_DEVICE_NAME>();
                std::string device_vendor = device.getInfo<CL_DEVICE_VENDOR>();
                cl_device_type device_type = device.getInfo<CL_DEVICE_TYPE>();
                cl_uint compute_units = device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
                cl_ulong global_mem_size = device.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>();

                std::cout << "  Device " << j << ":" << std::endl;
                std::cout << "    Name: " << device_name << std::endl;
                std::cout << "    Vendor: " << device_vendor << std::endl;
                std::cout << "    Type: ";

                // Decode device type
                if ( device_type & CL_DEVICE_TYPE_CPU )
                {
                    std::cout << "CPU ";
                }
                if ( device_type & CL_DEVICE_TYPE_GPU )
                {
                    std::cout << "GPU ";
                }
                if ( device_type & CL_DEVICE_TYPE_ACCELERATOR )
                {
                    std::cout << "Accelerator ";
                }
                std::cout << std::endl;

                std::cout << "    Compute Units: " << compute_units << std::endl;
                std::cout << "    Global Memory: " << (global_mem_size / (1024 * 1024)) << " MB" << std::endl;
            }
        }

        // Try to create a simple context with the first available device
        std::cout << "\n--- Testing Context Creation ---" << std::endl;

        // Get the first platform and its first device
        cl::Platform default_platform = platforms[0];
        std::vector<cl::Device> devices;
        default_platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

        if ( devices.empty() )
        {
            std::cerr << "No devices found on the default platform!" << std::endl;
            return -1;
        }

        cl::Device default_device = devices[0];
        std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << std::endl;

        // Create OpenCL context
        cl::Context context(default_device);
        std::cout << "✓ Context created successfully" << std::endl;

        // Create command queue
        cl::CommandQueue queue(context, default_device);
        std::cout << "✓ Command queue created successfully" << std::endl;

        std::cout << "\nOpenCL environment test completed successfully!" << std::endl;
        std::cout << "Your system is ready for OpenCL development." << std::endl;

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