#include <stdio.h>
#include <cuda_runtime.h>

#include "common/common.h"

__global__ void nesthelloworld(int iSize, int iDepth)
{
    unsigned int tid = threadIdx.x;
    printf("depth: %d, blockIdx.x: %d, threadIdx.x: %d\n", iDepth, blockIdx.x, threadIdx.x);
    if (iSize == 1)
        return;
    int nthread = (iSize >> 1);

    if (tid == 0 && nthread > 0)
    {
        nesthelloworld<<<1, nthread>>>(nthread, ++iDepth);
        printf("---> nested execution depth: %d\n", iDepth);
    }
}

int main()
{
    int size = 64;
    int block_x = 2;
    dim3 block(block_x, 1);
    dim3 grid((size - 1) / block.x + 1, 1);

    nesthelloworld<<<grid, block>>>(size, 0);
    cudaGetLastError();
    cudaDeviceReset();
    return 0;
}