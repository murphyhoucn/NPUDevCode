#include <stdio.h>
#include <cuda_runtime.h>

int main()
{
    int dev = 0;
    cudaDeviceProp dev_prop;
    cudaGetDeviceProperties(&dev_prop, dev);

    printf("Device %d : %s\n", dev, dev_prop.name);                                                     // GPU index and GPU Name
    printf("Number of multiprocessors: %d\n", dev_prop.multiProcessorCount);                            // SM
    printf("Total amount of constant memory: %4.2f KB\n", dev_prop.totalConstMem / 1024.0);             // Constant memory
    printf("Total amount of shared memory per block: %4.2f KB\n", dev_prop.sharedMemPerBlock / 1024.0); // Shared memory
    printf("Total number of registers available per block: %d\n", dev_prop.regsPerBlock);               // registers per block
    printf("Warp size: %d\n", dev_prop.warpSize);                                                       // warp size
    printf("Maximum number of threads per block: %d\n", dev_prop.maxThreadsPerBlock);
    printf("Maximum number of threads per multiprocessor: %d\n", dev_prop.maxThreadsPerMultiProcessor);
    printf("Maximum number of warps per multiprocessor: %d\n", dev_prop.maxThreadsPerMultiProcessor / 32);

    return EXIT_SUCCESS;
}