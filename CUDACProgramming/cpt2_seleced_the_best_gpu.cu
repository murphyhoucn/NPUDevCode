// Code 2-9
#include <cuda_runtime.h>
#include <stdio.h>

int main()
{
    int num_device = 0;
    cudaGetDeviceCount(&num_device);

    if (num_device > 1)
    {
        int max_multiprocessors = 0, max_device = 0;
        for (int device = 0; device < num_device; ++device)
        {
            cudaDeviceProp device_prop;
            cudaGetDeviceProperties(&device_prop, device);

            if (max_multiprocessors < device_prop.multiProcessorCount)
            {
                max_multiprocessors = device_prop.multiProcessorCount;
                max_device = device;
            }
        }

        cudaSetDevice(max_device);
    }
    else
    {
        cudaSetDevice(0);
    }

    return 0;
}