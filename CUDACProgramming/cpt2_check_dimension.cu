// Code 2-2
#include <cuda_runtime.h>
#include <stdio.h>

__global__ void CheckIndex()
{
    // 核函数中，每个线程都输出自己的线程索引，块索引，块维度，网格维度
    printf("threadIdx: (%d, %d, %d) \t\
            blockIdx: (%d, %d, %d) \t\
            blockDim: (%d, %d, %d) \t\
            gridDim: (%d, %d, %d)\n",
           threadIdx.x, threadIdx.y, threadIdx.z,
           blockIdx.x, blockIdx.y, blockIdx.z,
           blockDim.x, blockDim.y, blockDim.z,
           gridDim.x, gridDim.y, gridDim.z);
}

int main()
{
    int n_element = 6;

    dim3 block = 3;
    dim3 grid = ((n_element + block.x - 1) / block.x);

    // 主机端，检查块和网格维度
    printf("grid.x =  %d, grid.y =  %d, grid.z =  %d\n", grid.x, grid.y, grid.z);
    printf("block.x = %d, block.y = %d, block.z = %d\n", block.x, block.y, block.z);

    CheckIndex<<<grid, block>>>();
    cudaDeviceReset();

    return 0;
}