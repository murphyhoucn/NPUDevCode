// 习题 5
// Code 2-8
#include <cuda_runtime.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    printf("%s Starting...\n", argv[0]);

    // detect the cuda capabled devices
    int device_count = 0;
    cudaError_t error_id = cudaGetDeviceCount(&device_count);

    if (error_id != cudaSuccess)
    {
        printf("cudaGetDeviceCount returned %d\n -> %s\n", (int)error_id, cudaGetErrorString(error_id));
        printf("Result = FAIL\n");
        exit(EXIT_FAILURE);
    }

    if (device_count == 0)
    {
        printf("There are no available devices that support CUDA!\n");
    }
    else
    {
        printf("Detected %d CUDA Capable devices.\n", device_count);
    }

    int dev, driver_version = 0, runtime_version = 0;

    dev = 0;
    cudaSetDevice(dev);
    cudaDeviceProp device_prop;
    cudaGetDeviceProperties(&device_prop, dev);
    printf("Device %d: %s\n", dev, device_prop.name);

    cudaDriverGetVersion(&driver_version);
    cudaRuntimeGetVersion(&runtime_version);
    printf("CUDA Driver Version：%d.%d\n", driver_version / 1000, (driver_version % 100) / 10);
    printf("CUDA Runtime Version：%d.%d\n", runtime_version / 1000, (runtime_version % 100) / 10);

    printf("CUDA Capability Major/Minor version number: %d.%d\n", device_prop.major, device_prop.minor);

    printf("Total amount of global memory: %.2f MBytes (%llu bytes)\n", (float)device_prop.totalGlobalMem / (pow(1024.0, 0.3)), (unsigned long long)device_prop.totalGlobalMem);

    printf("GPU Clock rate: %.0f Mhz (%.2f Ghz)\n", device_prop.clockRate * 1e-3f, device_prop.clockRate * 1e-6f);
    printf("Memory Clock rate: %.0f Mhz\n", device_prop.memoryClockRate * 1e-3f);
    printf("Memory Bus Width: %d-bit\n", device_prop.memoryBusWidth);

    if (device_prop.l2CacheSize)
    {
        printf("L2 Cache Size %d bytes\n", device_prop.l2CacheSize);
    }

    printf("Max Texture Deimension Size (x, y, z): 1D = (%d), 2D = (%d, %d), 3D = (%d, %d, %d)\n", device_prop.maxTexture1D, device_prop.maxTexture2D[0], device_prop.maxTexture2D[1], device_prop.maxTexture3D[0], device_prop.maxTexture3D[1], device_prop.maxTexture3D[2]);
    printf("Max Layerd Texture Size (dim) x layers: 1D = (%d) x %d, 2D = (%d, %d) x %d\n", device_prop.maxTexture1DLayered[0], device_prop.maxTexture1DLayered[1], device_prop.maxTexture2DLayered[0], device_prop.maxTexture1DLayered[1], device_prop.maxTexture1DLayered[2]);

    printf("Total amount of constant memory: %lu bytes\n", device_prop.totalConstMem);
    printf("Total amount of shared memory per block: %lu bytes\n", device_prop.sharedMemPerBlock);
    printf("Total number of registers available per block: %d\n", device_prop.regsPerBlock);

    printf("Warp size: %d\n", device_prop.warpSize);
    printf("Maximum number of threads per multiprocessor: %d\n", device_prop.maxThreadsPerMultiProcessor);
    printf("Maximum number of threads per clock: %d\n", device_prop.maxThreadsPerBlock);
    printf("Maximum sizes of each dimension of a block: %d x %d x %d\n", device_prop.maxThreadsDim[0], device_prop.maxThreadsDim[1], device_prop.maxThreadsDim[2]);
    printf("Maximum sizes of each dimension of a grid: %d x %d x %d\n", device_prop.maxGridSize[0], device_prop.maxGridSize[1], device_prop.maxGridSize[2]);

    printf("Maximum memory pitch: %lu bytes\n", device_prop.memPitch);

    exit(EXIT_SUCCESS);
}

/*
Detected 8 CUDA Capable devices.
Device 0: NVIDIA GeForce RTX 3080
CUDA Driver Version：12.0
CUDA Runtime Version：11.3
CUDA Capability Major/Minor version number: 8.6
Total amount of global memory: 1311956992.00 MBytes (10495655936 bytes)
GPU Clock rate: 1710 Mhz (1.71 Ghz)
Memory Clock rate: 9501 Mhz
Memory Bus Width: 320-bit
L2 Cache Size 5242880 bytes
Max Texture Deimension Size (x, y, z): 1D = (131072), 2D = (131072, 65536), 3D = (16384, 16384, 16384)
Max Layerd Texture Size (dim) x layers: 1D = (32768) x 2048, 2D = (32768, 2048) x 32768
Total amount of constant memory: 65536 bytes
Total amount of shared memory per block: 49152 bytes
Total number of registers available per block: 65536
Warp size: 32
Maximum number of threads per multiprocessor: 1536
Maximum number of threads per clock: 1024
Maximum sizes of each dimension of a block: 1024 x 1024 x 64
Maximum sizes of each dimension of a grid: 2147483647 x 65535 x 65535
Maximum memory pitch: 2147483647 bytes
*/