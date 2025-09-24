#include <stdio.h>
#include <cuda_runtime.h>

int main()
{
    int deviceCount = 0;
    cudaError_t error_id = cudaGetDeviceCount(&deviceCount);
    if (error_id != cudaSuccess)
    {
        printf("cudaGetDeviceCount returned %d\n -> %s\n", (int)error_id, cudaGetErrorString(error_id));
        printf("Result = FALL\n");
        exit(EXIT_FAILURE);
    }

    if (deviceCount == 0)
    {
        printf("There are no available device(s) that support CUDA\n");
    }
    else
    {
        printf("Detected %d CUDA Capable device(s)\n", deviceCount);
    }

    int dev = 0, driverVersion = 0, runtimeVersion = 0;
    cudaSetDevice(dev);
    cudaDeviceProp deviceProp;
    cudaGetDeviceProperties(&deviceProp, dev);
    printf("Device %d:\"%s\"\n", dev, deviceProp.name);

    cudaDriverGetVersion(&driverVersion);
    cudaRuntimeGetVersion(&runtimeVersion);

    printf("CUDA Driver Version / Runtime Version:       %d.%d / %d.%d\n", driverVersion / 1000, (driverVersion % 100) / 10, runtimeVersion / 1000, (runtimeVersion % 100) / 10);
    printf("CUDA Capability Major/Minor version number:  %d.%d\n", deviceProp.major, deviceProp.minor);
    printf("Total amount of global memory:               %.2f GBytes\n", (float)deviceProp.totalGlobalMem / pow(1024, 3));
    printf("GPU Clock rate:                              %.0f MHz (%0.2f GHz)\n", deviceProp.clockRate * 1e-3f, deviceProp.clockRate * 1e-6f);
    printf("Memory Bus width:                            %d-bits\n", deviceProp.memoryBusWidth);

    if (deviceProp.l2CacheSize)
        printf("L2 Cache Size:                               %d bytes (%f Mbytes)\n", deviceProp.l2CacheSize, deviceProp.l2CacheSize / 1024.0 / 1024.0);

    printf("Max Texture Dimension Size (x,y,z)           1D=(%d), 2D=(%d, %d), 3D=(%d, %d, %d)\n", deviceProp.maxTexture1D, deviceProp.maxTexture2D[0], deviceProp.maxTexture2D[1], deviceProp.maxTexture3D[0], deviceProp.maxTexture3D[1], deviceProp.maxTexture3D[2]);
    printf("Max Layered Texture Size (dim) x layers      1D=(%d) x %d, 2D=(%d, %d) x %d \n", deviceProp.maxTexture1DLayered[0], deviceProp.maxTexture1DLayered[1], deviceProp.maxTexture2DLayered[0], deviceProp.maxTexture2DLayered[1], deviceProp.maxTexture2DLayered[2]);

    printf("Total amount of constant memory              %lu bytes(%f kbytes)\n", deviceProp.totalConstMem, deviceProp.totalConstMem / 1024.0);                // 常量内存
    printf("Total amout of shared memory per block:      %ld bytes(%f kbytes)\n", deviceProp.sharedMemPerBlock, deviceProp.sharedMemPerBlock / 1024.0);        // 共享内存
    printf("Total amout of Register per SM:              %d bytes(%f kbytes)\n", deviceProp.regsPerMultiprocessor, deviceProp.regsPerMultiprocessor / 1024.0); // 寄存器

    printf("Wrap size:                                   %d\n", deviceProp.warpSize);
    printf("Maximum number of thread per multiprocesser  %d\n", deviceProp.maxThreadsPerMultiProcessor);
    printf("Maximum number of thread per block:          %d\n", deviceProp.maxThreadsPerBlock);
    printf("Maximum size of each dimension of a block:   %d x %d x %d\n", deviceProp.maxThreadsDim[0], deviceProp.maxThreadsDim[1], deviceProp.maxThreadsDim[2]);
    printf("Maximum size of each dimension of a grid:    %d x %d x %d\n", deviceProp.maxGridSize[0], deviceProp.maxGridSize[1], deviceProp.maxGridSize[2]);
    printf("Maximum memory pitch:                        %lu bytes\n", deviceProp.memPitch); // 最大连续线性内存

    printf("The number of multiprocessors(SM):           %d\n", deviceProp.multiProcessorCount);
    printf("Total amount of constant memeory:            %4.2f KB\n", deviceProp.totalConstMem / 1024.0);
    printf("Total amount of shared memeory per block:    %4.2f KB\n", deviceProp.sharedMemPerBlock / 1024.0);
    printf("Total num of registers available per block:  %f KB\n", deviceProp.regsPerBlock / 1024.0);

    printf("Bool: %d\n", deviceProp.localL1CacheSupported);
    printf("Bool: %d\n", deviceProp.globalL1CacheSupported);

    exit(EXIT_SUCCESS);
}

/*

GA 102 的手册
https://www.nvidia.com/content/PDF/nvidia-ampere-ga-102-gpu-architecture-whitepaper-v2.pdf

https://www.techpowerup.com/gpu-specs/geforce-rtx-3080.c3621
*/