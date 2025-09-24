# include <stdio.h>
# include <cuda_runtime.h>

# define CHECK(call) \
{\
    const cudaError_t error = call;\
    if (error != cudaSuccess)\
    {\
        printf("ERROR: %s:%d,", __FILE__, __LINE__);\
        printf("code:%d, resason:%s\n", error, cudaGetErrorString(error));\
        exit(1);\
    }\
}\


void sumArrayOnHost(float *A, float *B, float *C, const int N)
{
    for (int i = 0; i < N; i++)
        C[i] = A[i] + B[i];
}

__global__ void sumArrayOnDevice(float *A, float *B, float *C)
{
    int i = threadIdx.x;
    C[i] = A[i] + B[i];
}

int main()
{
    int dev = 0;
    cudaSetDevice(dev);

    const int N = 1024;
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
    CHECK(cudaMalloc((void **)&d_A, size));
    CHECK(cudaMalloc((void **)&d_B, size));
    CHECK(cudaMalloc((void **)&d_C, size));

    CHECK(cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice));
    
    sumArrayOnDevice<<<1,N>>>(d_A, d_B, d_C);
    cudaDeviceSynchronize();
    CHECK(cudaMemcpy(gpu_C, d_C, size, cudaMemcpyDeviceToHost));

    sumArrayOnHost(h_A, h_B, h_C, N);

    for (int i = 0; i < N; i++) {
        if (gpu_C[i] != h_C[i]) {
            printf("Error: gpu_C[%d] = %f != %f = h_C[%d]\n", i, gpu_C[i], h_C[i], i);
            exit(EXIT_FAILURE);
        }
    }

    free(h_A);
    free(h_B);
    free(h_C);
    free(gpu_C);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
        
}
