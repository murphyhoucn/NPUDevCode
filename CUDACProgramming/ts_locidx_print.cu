# include <stdio.h>
# include <cuda_runtime.h>
# include <stdlib.h>

#include "common/common.h"
__global__ void printThreadIdx(float* A, const int nx, const int ny)
{
    int ix = threadIdx.x + blockIdx.x * blockDim.x;
    int iy = threadIdx.y + blockIdx.y * blockDim.y;

    unsigned int idx = ix + nx * iy;
    printf("thread_id(%d,%d) block_id(%d,%d) coordinate(%d,%d) global index %2d ival %2f\n",threadIdx.x,threadIdx.y, blockIdx.x,blockIdx.y, ix,iy, idx, A[idx]);

}

int main()
{
    int dev_idx = 0;
    cudaSetDevice(dev_idx);

    srand((unsigned int)time(NULL));

    int nx = 8, ny=6;
    int nxy = nx * ny;
    size_t nBytes = nxy * sizeof(int);

    float* h_A = (float*)malloc(nBytes);

    for (int i = 0; i < nxy; i++)
    {
        h_A[i] = (float)rand() / RAND_MAX;
    }

    // 打印二维数组
    for (int i = 0; i < nxy; i++) 
    {
        printf("%f ", h_A[i]);
    }
    printf("\n");

    // device
    float* d_A = NULL;
    CHECK(cudaMalloc((void**)&d_A, nBytes));
    cudaMemcpy(d_A, h_A, nBytes, cudaMemcpyHostToDevice);

    dim3 block(4, 2);
    dim3 grid((nx - 1) / block.x + 1, (ny - 1) / block.y + 1);

    printThreadIdx<<<grid, block>>>(d_A, nx, ny);

    CHECK(cudaDeviceSynchronize());
    cudaFree(d_A);
    free(h_A);

    cudaDeviceReset();

    return 0;
}