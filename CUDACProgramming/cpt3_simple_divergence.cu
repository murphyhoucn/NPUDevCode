#include <cuda_runtime.h>
#include <stdio.h>
#include <sys/time.h>

double CpuSecond()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double)tp.tv_sec + (double)tp.tv_usec * 1.0e-6);
}

__global__ void MathKernel1(float *c)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    float a, b;
    a = b = 0.0f;

    if (tid % 2 == 0)
    {
        a = 100.0f;
    }
    else
    {
        b = 200.0f;
    }
    c[tid] = a + b;
}

__global__ void MathKernel2(float *c)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    float a, b;
    a = b = 0.0f;

    if ((tid / warpSize) % 2 == 0)
    {
        a = 100.0f;
    }
    else
    {
        b = 200.0f;
    }
    c[tid] = a + b;
}

__global__ void MathKernel3(float *c)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    float a, b;
    a = b = 0.0f;
    bool pred = (tid % 2 == 0);
    if (pred)
    {
        a = 100.0f;
    }
    else
    {
        b = 200.0f;
    }
    c[tid] = a + b;
}

__global__ void WarmUp(float *c)
{
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    float a, b;
    a = b = 0.0f;

    if ((tid / warpSize) % 2 == 0)
    {
        a = 100.0f;
    }
    else
    {
        b = 200.0f;
    }
    c[tid] = a + b;
}
int main(int argc, char **argv)
{
    int dev = 0;
    cudaDeviceProp device_prop;
    cudaGetDeviceProperties(&device_prop, dev);
    printf("%s using Device %d : %s\n", argv[0], dev, device_prop.name);

    int data_size = 64;
    int block_size = 64;
    printf("Data size : %d\n", data_size);

    dim3 block(block_size, 1);
    dim3 grid((data_size + block.x - 1) / block.x, 1);
    printf("Execution Configure (block %d, grid %d)\n", block.x, grid.x);

    float *d_c;
    size_t n_bytes = data_size * sizeof(float);
    cudaMalloc((float **)&d_c, n_bytes);

    double i_start, i_elaps;
    cudaDeviceSynchronize();

    // warmup
    i_start = CpuSecond();
    WarmUp<<<grid, block>>>(d_c);
    cudaDeviceSynchronize();
    i_elaps = CpuSecond() - i_start;
    printf("WarmUp      <<<%d, %d>>> elapsed %f sec.\n", grid.x, block.x, i_elaps);

    // MathKernel1
    i_start = CpuSecond();
    MathKernel1<<<grid, block>>>(d_c);
    cudaDeviceSynchronize();
    i_elaps = CpuSecond() - i_start;
    printf("MathKernel1 <<<%d, %d>>> elapsed %f sec.\n", grid.x, block.x, i_elaps);

    // MathKernel2
    i_start = CpuSecond();
    MathKernel2<<<grid, block>>>(d_c);
    cudaDeviceSynchronize();
    i_elaps = CpuSecond() - i_start;
    printf("MathKernel2 <<<%d, %d>>> elapsed %f sec.\n", grid.x, block.x, i_elaps);

    // MathKernel3
    i_start = CpuSecond();
    MathKernel3<<<grid, block>>>(d_c);
    cudaDeviceSynchronize();
    i_elaps = CpuSecond() - i_start;
    printf("MathKernel3 <<<%d, %d>>> elapsed %f sec.\n", grid.x, block.x, i_elaps);

    cudaFree(d_c);
    cudaDeviceReset();
    return 0;
}