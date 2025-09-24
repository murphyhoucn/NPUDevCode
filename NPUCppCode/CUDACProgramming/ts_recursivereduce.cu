#include <stdio.h>
#include <cuda_runtime.h>

#include "common/common.h"

// CPU
int RecursiveReduce(int *data, const int size)
{
    if (size == 1)
        return data[0];

    const int stride = size / 2;

    if (size % 2 == 1)
    {
        for (int i = 0; i < stride; i++)
            data[i] += data[i + stride];
        data[0] += data[size - 1];
    }
    else
    {
        for (int i = 0; i < stride; i++)
            data[i] += data[i + stride];
    }

    return RecursiveReduce(data, stride);
}

// 相邻配对-warmup
__global__ void WarmUp(int *g_idata, int *g_odata, unsigned int n)
{
    unsigned int tid = threadIdx.x;
    if (tid >= n)
        return;

    int *idata = g_idata + blockDim.x * blockIdx.x;

    for (int stride = 1; stride < blockDim.x; stride *= 2)
    {
        if ((tid % (2 * stride) == 0))
            idata[tid] += idata[tid + stride];

        __syncthreads(); // 同步
    }

    if (tid == 0)
        g_odata[blockIdx.x] = idata[0];
}

// 相邻配对
__global__ void ReduceNeighbored(int *g_idata, int *g_odata, unsigned int n)
{
    unsigned int tid = threadIdx.x;
    if (tid >= n)
        return;

    int *idata = g_idata + blockDim.x * blockIdx.x;

    for (int stride = 1; stride < blockDim.x; stride *= 2)
    {
        if ((tid % (2 * stride) == 0))
            idata[tid] += idata[tid + stride];

        __syncthreads(); // 同步
    }

    if (tid == 0)
        g_odata[blockIdx.x] = idata[0];
}

__global__ void ReduceNeighboredLess(int *g_idata, int *g_odata, unsigned int n)
{
    unsigned int tid = threadIdx.x;
    unsigned int idx = threadIdx.x + blockIdx.x * blockDim.x;

    int *idata = g_idata + blockDim.x * blockIdx.x;

    if (idx > n)
        return;

    for (int stride = 1; stride < blockDim.x; stride *= 2)
    {
        int index = 2 * stride * tid;
        if (index < blockDim.x)
            idata[index] += idata[index + stride];
        __syncthreads();
    }

    if (tid == 0)
        g_odata[blockIdx.x] = idata[0];
}

__global__ void ReduceInterleaved(int *g_idata, int *g_odata, unsigned int n)
{
    unsigned int tid = threadIdx.x;
    unsigned int idx = threadIdx.x + blockDim.x * blockIdx.x;

    int *idata = g_idata + blockDim.x * blockIdx.x;

    if (idx >= n)
        return;

    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1)
    {
        if (tid < stride)
            idata[tid] += idata[tid + stride];
        __syncthreads();
    }

    if (tid == 0)
        g_odata[blockIdx.x] = idata[0];
}

int main(int argc, char **argv)
{
    int devidx = 0;
    cudaSetDevice(devidx);

    // bool bResult = false;

    // initialization

    int size = 1 << 24;
    printf("with array size %d  ", size);

    // execution configuration
    int blocksize = 1024;
    if (argc > 1)
    {
        blocksize = atoi(argv[1]);
    }
    dim3 block(blocksize, 1);
    dim3 grid((size - 1) / block.x + 1, 1);
    printf("grid %d block %d \n", grid.x, block.x);

    // allocate host memory
    size_t bytes = size * sizeof(int);
    int *idata_host = (int *)malloc(bytes);
    int *odata_host = (int *)malloc(grid.x * sizeof(int));
    int *tmp = (int *)malloc(bytes);

    // initialize the array
    initialData_int(idata_host, size);

    memcpy(tmp, idata_host, bytes);
    double iStart, iElaps;
    int gpu_sum = 0;

    // device memory
    int *idata_dev = NULL;
    int *odata_dev = NULL;
    CHECK(cudaMalloc((void **)&idata_dev, bytes));
    CHECK(cudaMalloc((void **)&odata_dev, grid.x * sizeof(int)));

    // cpu reduction
    int cpu_sum = 0;
    iStart = cpuSecond();
    // cpu_sum = recursiveReduce(tmp, size);
    for (int i = 0; i < size; i++)
        cpu_sum += tmp[i];
    printf("cpu sum:%d \n", cpu_sum);
    iElaps = cpuSecond() - iStart;
    printf("cpu reduce                 elapsed %lf ms cpu_sum: %d\n", iElaps, cpu_sum);

    // kernel 1:reduceNeighbored

    CHECK(cudaMemcpy(idata_dev, idata_host, bytes, cudaMemcpyHostToDevice));
    CHECK(cudaDeviceSynchronize());
    iStart = cpuSecond();
    WarmUp<<<grid, block>>>(idata_dev, odata_dev, size);
    cudaDeviceSynchronize();
    iElaps = cpuSecond() - iStart;
    cudaMemcpy(odata_host, odata_dev, grid.x * sizeof(int), cudaMemcpyDeviceToHost);
    gpu_sum = 0;
    for (int i = 0; i < grid.x; i++)
        gpu_sum += odata_host[i];
    printf("gpu warmup                 elapsed %lf ms gpu_sum: %d<<<grid %d block %d>>>\n",
           iElaps, gpu_sum, grid.x, block.x);

    // kernel 1:reduceNeighbored

    CHECK(cudaMemcpy(idata_dev, idata_host, bytes, cudaMemcpyHostToDevice));
    CHECK(cudaDeviceSynchronize());
    iStart = cpuSecond();
    ReduceNeighbored<<<grid, block>>>(idata_dev, odata_dev, size);
    cudaDeviceSynchronize();
    iElaps = cpuSecond() - iStart;
    cudaMemcpy(odata_host, odata_dev, grid.x * sizeof(int), cudaMemcpyDeviceToHost);
    gpu_sum = 0;
    for (int i = 0; i < grid.x; i++)
        gpu_sum += odata_host[i];
    printf("gpu reduceNeighbored       elapsed %lf ms gpu_sum: %d<<<grid %d block %d>>>\n",
           iElaps, gpu_sum, grid.x, block.x);

    // kernel 2:reduceNeighboredLess

    CHECK(cudaMemcpy(idata_dev, idata_host, bytes, cudaMemcpyHostToDevice));
    CHECK(cudaDeviceSynchronize());
    iStart = cpuSecond();
    ReduceNeighboredLess<<<grid, block>>>(idata_dev, odata_dev, size);
    cudaDeviceSynchronize();
    iElaps = cpuSecond() - iStart;
    cudaMemcpy(odata_host, odata_dev, grid.x * sizeof(int), cudaMemcpyDeviceToHost);
    gpu_sum = 0;
    for (int i = 0; i < grid.x; i++)
        gpu_sum += odata_host[i];
    printf("gpu reduceNeighboredLess   elapsed %lf ms gpu_sum: %d<<<grid %d block %d>>>\n",
           iElaps, gpu_sum, grid.x, block.x);

    // kernel 3:reduceInterleaved
    CHECK(cudaMemcpy(idata_dev, idata_host, bytes, cudaMemcpyHostToDevice));
    CHECK(cudaDeviceSynchronize());
    iStart = cpuSecond();
    ReduceInterleaved<<<grid, block>>>(idata_dev, odata_dev, size);
    cudaDeviceSynchronize();
    iElaps = cpuSecond() - iStart;
    cudaMemcpy(odata_host, odata_dev, grid.x * sizeof(int), cudaMemcpyDeviceToHost);
    gpu_sum = 0;
    for (int i = 0; i < grid.x; i++)
        gpu_sum += odata_host[i];
    printf("gpu reduceInterleaved      elapsed %lf ms gpu_sum: %d<<<grid %d block %d>>>\n",
           iElaps, gpu_sum, grid.x, block.x);
    // free host memory

    free(idata_host);
    free(odata_host);
    CHECK(cudaFree(idata_dev));
    CHECK(cudaFree(odata_dev));

    // reset device
    cudaDeviceReset();

    // check the results
    if (gpu_sum == cpu_sum)
    {
        printf("Test success!\n");
    }
    return EXIT_SUCCESS;
}
