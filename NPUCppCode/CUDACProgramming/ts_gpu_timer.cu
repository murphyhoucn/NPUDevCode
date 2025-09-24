# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <cuda_runtime.h>

// # include <time.h> //提供了处理日期和时间的标准函数和数据结构
# include <sys/time.h> // 通常用于获取更加精确的时间信息

void sumArrayOnHost(float *A, float *B, float *C, const int N)
{
    for (int i = 0; i < N; i++)
        C[i] = A[i] + B[i];
}

__global__ void sumArrayOnDevice(float *A, float *B, float *C, const int N)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N)
        C[i] = A[i] + B[i];
}

double cpuSecond()
{
  struct timeval tp;
  gettimeofday(&tp,NULL);
  return((double)tp.tv_sec+(double)tp.tv_usec*1e-6);
}

int main()
{
    int dev = 0;
    cudaSetDevice(dev);

    const int N = 1<<24;
    size_t size = N * sizeof(float);

    float *h_A = (float*)malloc(size);
    float *h_B = (float*)malloc(size);
    float *h_C = (float*)malloc(size);
    float *gpu_C = (float *)malloc(size);

    for (int i = 0; i < N; i++)
    {
        h_A[i] = 1.0f;
        h_B[i] = 2.0f;
    }
    
    memset(h_C, 0, size);
    memset(gpu_C, 0, size);

    float *d_A, *d_B, *d_C;
    cudaMalloc((void **)&d_A, size);
    cudaMalloc((void **)&d_B, size);
    cudaMalloc((void **)&d_C, size);

    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    double iStart, iElaps;
    iStart=cpuSecond();

    dim3 block(256);
    dim3 grid((N - 1) / block.x + 1);
    sumArrayOnDevice<<<grid,block>>>(d_A, d_B, d_C, N);
    cudaDeviceSynchronize();
    iElaps = cpuSecond() - iStart;

    cudaMemcpy(gpu_C, d_C, size, cudaMemcpyDeviceToHost);

    double iStart_cpu,iElaps_cpu;
    iStart_cpu = cpuSecond();
    sumArrayOnHost(h_A, h_B, h_C, N);
    iElaps_cpu = cpuSecond() - iStart_cpu;

    for (int i = 0; i < N; i++) {
        if (gpu_C[i] != h_C[i]) {
            printf("Error: gpu_C[%d] = %f != %f = h_C[%d]\n", i, gpu_C[i], h_C[i], i);
            exit(EXIT_FAILURE);
        }
    }

    printf("cup time cost: %f\ngpu time cost: %f\n", iElaps_cpu, iElaps);

    free(h_A);
    free(h_B);
    free(h_C);
    free(gpu_C);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
 
    return 0;
}