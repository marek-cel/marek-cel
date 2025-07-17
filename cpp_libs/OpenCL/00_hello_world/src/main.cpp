#include <cstring>
#include <iostream>
#include <vector>

#include <CL/cl.h>

const char* kernelSource = R"CLC(
__kernel void hello(__global int* out) {
    out[0] = 42;
}
)CLC";

int main(int argc, char** argv)
{
    std::cout << "Hello, OpenCL!" << std::endl;

    cl_int err;

    // Step 1: Get platforms
    cl_uint numPlatforms = 0;
    err = clGetPlatformIDs(0, nullptr, &numPlatforms);
    if (err != CL_SUCCESS || numPlatforms == 0) {
        std::cerr << "Failed to find any OpenCL platforms." << std::endl;
        return 1;
    }
    std::vector<cl_platform_id> platforms(numPlatforms);
    clGetPlatformIDs(numPlatforms, platforms.data(), nullptr);

    // Step 2: Get a device
    cl_device_id device;
    err = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_DEFAULT, 1, &device, nullptr);
    if (err != CL_SUCCESS) {
        std::cerr << "Failed to get device ID." << std::endl;
        return 1;
    }

    // Step 3: Create context
    cl_context context = clCreateContext(nullptr, 1, &device, nullptr, nullptr, &err);

    // Step 4: Create command queue (or clCreateCommandQueueWithProperties for OpenCL 2.0+)
    cl_command_queue queue = clCreateCommandQueue(context, device, 0, &err);

    // Step 5: Create program
    const size_t sourceSize = std::strlen(kernelSource);
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSource, &sourceSize, &err);
    err = clBuildProgram(program, 1, &device, nullptr, nullptr, nullptr);
    if (err != CL_SUCCESS) {
        // Print build log
        char log[2048];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(log), log, nullptr);
        std::cerr << "Build failed:\n" << log << std::endl;
        return 1;
    }

    // Step 6: Create kernel
    cl_kernel kernel = clCreateKernel(program, "hello", &err);

    // Step 7: Create buffer
    cl_mem buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int), nullptr, &err);

    // Step 8: Set kernel argument
    clSetKernelArg(kernel, 0, sizeof(cl_mem), &buffer);

    // Step 9: Launch kernel
    size_t globalWorkSize = 1;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, nullptr, &globalWorkSize, nullptr, 0, nullptr, nullptr);

    // Step 10: Read result
    int result = 0;
    clEnqueueReadBuffer(queue, buffer, CL_TRUE, 0, sizeof(int), &result, 0, nullptr, nullptr);

    std::cout << "Result from OpenCL kernel: " << result << std::endl;

    // Cleanup
    clReleaseMemObject(buffer);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    return 0;
}