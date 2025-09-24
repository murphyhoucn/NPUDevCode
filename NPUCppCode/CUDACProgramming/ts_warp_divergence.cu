#include <stdio.h>
#include <cuda_runtime.h>
#include "common/common.h"

__global__ void WarmUp(float* C)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    float a = 0.0f, b = 0.0f;

    if((tid/warpSize) % 2 == 0) a = 100.0f;
    else b = 200.0f;

    C[tid] = a + b;
}

__global__ void MathKernek1(float* C)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    float a = 0.0f, b = 0.0f;

    if(tid % 2 == 0) a = 100.0f;
    else b = 200.0f;

    C[tid] = a + b;
}
__global__ void MathKernek2(float* C)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    float a = 0.0f, b = 0.0f;

    if((tid/warpSize) % 2 == 0) a = 100.0f;
    else b = 200.0f;

    C[tid] = a + b;
}
__global__ void MathKernek3(float* C)
{
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    float a = 0.0f, b = 0.0f;
    bool ipred = (tid % 2) == 0;

    if(ipred) a = 100.0f;
    else b = 200.0f;

    C[tid] = a + b;
}


int main(int argc, char** argv)
{
    int dev = 0;
    cudaDeviceProp deviceprop;
    cudaGetDeviceProperties(&deviceprop, dev);
    printf("Using Device %d:%s", dev, deviceprop.name);

    int datasize = 64;
    int blocksize = 64;

    if(argc > 1) datasize = atoi(argv[1]);
    if(argc > 2) blocksize = atoi(argv[2]);

    dim3 block(blocksize, 1);
    dim3 grid((datasize - 1) / block.x + 1, 1);
    printf("Execuation configuration(block, grid): (%d, %d)\n", block.x, grid.x);

    float* d_C;
    size_t nbytes = datasize * sizeof(float);
    float* h_C = (float*)malloc(nbytes);
    cudaMalloc((float**)&d_C, nbytes);

    // warmup kernel
    double t_start, t_elaps;
    cudaDeviceSynchronize();
    t_start = Seconds();
    WarmUp<<<grid, block>>>(d_C);
    cudaDeviceSynchronize();
    t_elaps = Seconds() - t_start;
    printf("WarmUp      <<<%d,%d>>> elaps %lf sec \n", grid.x, block.x, t_elaps);

    // 1
    cudaDeviceSynchronize();
    t_start = Seconds();
    MathKernek1<<<grid, block>>>(d_C);
    cudaDeviceSynchronize();
    t_elaps = Seconds() - t_start;
    printf("MathKernek1 <<<%d,%d>>> elaps %lf sec \n", grid.x, block.x, t_elaps);

    // 2
    cudaDeviceSynchronize();
    t_start = Seconds();
    MathKernek2<<<grid, block>>>(d_C);
    cudaDeviceSynchronize();
    t_elaps = Seconds() - t_start;
    printf("MathKernek2 <<<%d,%d>>> elaps %lf sec \n", grid.x, block.x, t_elaps);

    // 3
    cudaDeviceSynchronize();
    t_start = Seconds();
    MathKernek3<<<grid, block>>>(d_C);
    cudaDeviceSynchronize();
    t_elaps = Seconds() - t_start;
    printf("MathKernek3 <<<%d,%d>>> elaps %lf sec \n", grid.x, block.x, t_elaps);    
    
    free(h_C);
    cudaFree(d_C);
    cudaDeviceReset();
    
    return 0;
}