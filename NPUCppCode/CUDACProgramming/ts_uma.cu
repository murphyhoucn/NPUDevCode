#include <stdio.h>
#include <cuda_runtime.h>
#include <string.h>
#include "common/common.h"

void SumArrays(float *a, float *b, float *c, const int size)
{
    for (int i = 0; i < size; i += 4)
    {
        c[i] = a[i] + b[i];
        c[i + 1] = a[i + 1] + b[i + 1];
        c[i + 2] = a[i + 2] + b[i + 2];
        c[i + 3] = a[i + 3] + b[i + 3];
    }
}

__global__ void SumArraysGPU(float *a, float *b, float *c)
{
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    c[idx] = a[idx] + b[idx];
}

int main(int argc, char **argv)
{
    int dev = 0;
    cudaSetDevice(dev);

    int power = 10;
    if (argc >= 2)
        power = atoi(argv[1]);
    int nElem = 1 << power;
    printf("Vector size:%d\n", nElem);
    int nByte = sizeof(float) * nElem;

    float *res_from_gpu_h = (float *)malloc(nByte);
    float *res_h = (float *)malloc(nByte);
    memset(res_h, 0, nByte);
    memset(res_from_gpu_h, 0, nByte);

    float *a_host, *b_host, *res_d;
    double iStart, iElaps;
    dim3 block(1024);
    dim3 grid(nElem / block.x);
    res_from_gpu_h = (float *)malloc(nByte);

    CHECK(cudaMallocManaged((float **)&a_host, nByte, cudaHostAllocMapped));
    CHECK(cudaMallocManaged((float **)&b_host, nByte, cudaHostAllocMapped));

    CHECK(cudaMalloc((float **)&res_d, nByte));

    initialData(a_host, nElem);
    initialData(b_host, nElem);

    //=============================================================//
    iStart = cpuSecond();
    SumArraysGPU<<<grid, block>>>(a_host, b_host, res_d); // 统一内存寻址  Uniform Memory Access
    CHECK(cudaMemcpy(res_from_gpu_h, res_d, nByte, cudaMemcpyDeviceToHost));
    iElaps = cpuSecond() - iStart;
    //=============================================================//
    printf("UMA memory elapsed %lf ms \n", iElaps);
    printf("Execution configuration<<<%d,%d>>>\n", grid.x, block.x);

    //-----------------------normal memory---------------------------
    //-----------------------normal memory---------------------------
    //-----------------------normal memory---------------------------
    //-----------------------normal memory---------------------------
    //-----------------------normal memory---------------------------
    //-----------------------normal memory---------------------------
    //-----------------------normal memory---------------------------
    //-----------------------normal memory---------------------------
    //-----------------------normal memory---------------------------
    //-----------------------normal memory---------------------------
    //-----------------------normal memory---------------------------
    //-----------------------normal memory---------------------------
    float *a_h_n = (float *)malloc(nByte);
    float *b_h_n = (float *)malloc(nByte);
    float *res_h_n = (float *)malloc(nByte);
    float *res_from_gpu_h_n = (float *)malloc(nByte);
    memset(res_h_n, 0, nByte);
    memset(res_from_gpu_h_n, 0, nByte);

    float *a_d_n, *b_d_n, *res_d_n;
    CHECK(cudaMalloc((float **)&a_d_n, nByte));
    CHECK(cudaMalloc((float **)&b_d_n, nByte));
    CHECK(cudaMalloc((float **)&res_d_n, nByte));

    initialData(a_h_n, nElem);
    initialData(b_h_n, nElem);
    //=============================================================//
    iStart = cpuSecond();
    CHECK(cudaMemcpy(a_d_n, a_h_n, nByte, cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(b_d_n, b_h_n, nByte, cudaMemcpyHostToDevice));
    SumArraysGPU<<<grid, block>>>(a_d_n, b_d_n, res_d_n);
    CHECK(cudaMemcpy(res_from_gpu_h, res_d, nByte, cudaMemcpyDeviceToHost));
    iElaps = cpuSecond() - iStart;
    //=============================================================//
    printf("device memory elapsed %lf ms \n", iElaps);
    printf("Execution configuration<<<%d,%d>>>\n", grid.x, block.x);
    //--------------------------------------------------------------------

    SumArrays(a_host, b_host, res_h, nElem);
    checkResult(res_h, res_from_gpu_h, nElem);

    cudaFreeHost(a_host);
    cudaFreeHost(b_host);
    cudaFree(res_d);
    free(res_h);
    free(res_from_gpu_h);

    cudaFree(a_d_n);
    cudaFree(b_d_n);
    cudaFree(res_d_n);

    free(a_h_n);
    free(b_h_n);
    free(res_h_n);
    free(res_from_gpu_h_n);
    return 0;
}