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

int main()
{
    int devidx = 0;
    cudaSetDevice(devidx);

    int n_element = 1 << 14;
    printf("Vector size = %d\n", n_element);

    size_t n_bytes = sizeof(int) * n_element;

    float *h_a = (float *)malloc(n_bytes);
    float *h_b = (float *)malloc(n_bytes);
    float *h_c = (float *)malloc(n_bytes);
    float *h_c_gpu = (float *)malloc(n_bytes);

    memset(h_c, 0, n_bytes);
    memset(h_c_gpu, 0, n_bytes);
    initialData(h_a, n_element);
    initialData(h_b, n_element);

    // float *d_a = nullptr, *d_b = nullptr, *d_c = nullptr;
    // CHECK(cudaMallocHost((float **)&d_a, n_bytes));
    // CHECK(cudaMallocHost((float **)&d_b, n_bytes));
    // CHECK(cudaMallocHost((float **)&d_c, n_bytes));

    float *d_a = nullptr, *d_b = nullptr, *d_c = nullptr;
    CHECK(cudaMalloc((float **)&d_a, n_bytes));
    CHECK(cudaMalloc((float **)&d_b, n_bytes));
    CHECK(cudaMalloc((float **)&d_c, n_bytes));

    CHECK(cudaMemcpy(d_a, h_a, n_bytes, cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(d_b, h_b, n_bytes, cudaMemcpyHostToDevice));

    dim3 block(1024);
    dim3 grid((n_element - block.x) / block.x + 1);

    SumArraysGPU<<<grid, block>>>(d_a, d_b, d_c);
    printf("Execution configuration<<<%d,%d>>>\n", grid.x, block.x);
    CHECK(cudaMemcpy(h_c_gpu, d_c, n_bytes, cudaMemcpyDeviceToHost));
    SumArrays(h_a, h_b, h_c, n_element);

    checkResult(h_c, h_c_gpu, n_element);
    cudaFreeHost(d_a);
    cudaFreeHost(d_b);
    cudaFreeHost(d_c);

    free(h_a);
    free(h_b);
    free(h_c);
    free(h_c_gpu);

    return 0;
}