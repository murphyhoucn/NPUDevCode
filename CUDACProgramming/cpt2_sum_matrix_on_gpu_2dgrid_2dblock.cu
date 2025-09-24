// Code 2-7
#include <cuda_runtime.h>
#include <stdio.h>
#include <sys/time.h>

#define CHECK(call)                                                                                               \
    {                                                                                                             \
        const cudaError_t error = call;                                                                           \
        if (error != cudaSuccess)                                                                                 \
        {                                                                                                         \
            printf("Error: %s:%d, code: %d, reason: %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error)); \
            exit(-10 * error);                                                                                    \
        }                                                                                                         \
    }

void CheckResult(float *host_ref, float *gpu_ref, const int kN)
{
    double epsilon = 1.0e-8;
    bool match = 1;

    for (int i = 0; i < kN; ++i)
    {
        if (abs(host_ref[i] - gpu_ref[i]) > epsilon)
        {
            match = 0;
            printf("Matrix do no match!");
            printf("host: %5.2f gpu: %5.2f at current %d\n", host_ref[i], gpu_ref[i], i);
            break;
        }
    }
    if (match)
        printf("Matrix math!\n");
}

double CpuSecond()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double)tp.tv_sec + (double)tp.tv_usec * 1.0e-6);
}

void InitData(float *ip, int size)
{
    time_t t;
    srand((unsigned)time(&t));

    for (int i = 0; i < size; ++i)
    {
        *(ip + i) = (float)(rand() & 0xFF) / 10.0f;
    }
}

void SumMatrixOnHost(float *a, float *b, float *c, const int knx, const int kny)
{
    for (int i = 0; i < knx; ++i)
    {
        for (int j = 0; j < kny; ++j)
        {
            *(c + i * kny + j) = *(b + i * kny + j) + *(a + i * kny + j);
        }
    }
}

__global__ void SumMatrixOnGPU2D(float *a, float *b, float *c, int knx, int kny)
{
    unsigned int ix = threadIdx.x + blockIdx.x * blockDim.x;
    unsigned int iy = threadIdx.y + blockIdx.y * blockDim.y;
    unsigned int idx = iy * knx + ix;

    if (ix < knx && iy < kny)
        *(c + idx) = *(a + idx) + *(b + idx);
}

int main(int argc, char **argv)
{
    printf("%s Starting...\n", argv[0]);

    // set up device
    int dev = 0;
    cudaDeviceProp device_prop;
    CHECK(cudaGetDeviceProperties(&device_prop, dev));
    printf("Using device %d : %s \n", dev, device_prop.name);
    CHECK(cudaSetDevice(dev));

    // set up data size of matrix
    int nx = 1 << 14;
    int ny = 1 << 14;

    int nxy = nx * ny;
    int n_bytes = nxy * sizeof(float);
    printf("Matrix size : (nx, ny): (%d, %d)\n", nx, ny);

    // malloc host memory
    float *h_a, *h_b, *host_ref, *gpu_ref;
    h_a = (float *)malloc(n_bytes);
    h_b = (float *)malloc(n_bytes);
    host_ref = (float *)malloc(n_bytes);
    gpu_ref = (float *)malloc(n_bytes);

    // initialize data at host side
    double i_start = CpuSecond();
    InitData(h_a, nxy);
    InitData(h_b, nxy);
    double i_elaps = CpuSecond() - i_start;

    memset(host_ref, 0, n_bytes);
    memset(gpu_ref, 0, n_bytes);

    // add matrix at host side for result checks
    i_start = CpuSecond();
    SumMatrixOnHost(h_a, h_b, host_ref, nx, ny);
    i_elaps = CpuSecond() - i_start;

    // malloc device global memory
    float *d_a, *d_b, *d_c;
    cudaMalloc((void **)&d_a, n_bytes);
    cudaMalloc((void **)&d_b, n_bytes);
    cudaMalloc((void **)&d_c, n_bytes);

    // transfer data from host to device
    cudaMemcpy(d_a, h_a, n_bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, n_bytes, cudaMemcpyHostToDevice);

    // invoke kernel at host side
    int dimx = 32;
    int dimy = 32;

    dim3 block(dimx, dimy);
    dim3 grid((nx + block.x - 1) / block.x, (ny + block.y - 1) / block.y);

    i_start = CpuSecond();
    SumMatrixOnGPU2D<<<grid, block>>>(d_a, d_b, d_c, nx, ny);
    cudaDeviceSynchronize();
    i_elaps = CpuSecond() - i_start;
    printf("SumMatrixOnGPU2D<<<(%d, %d), (%d, %d)>>> elapsd %f sec.\n", grid.x, grid.y, block.x, block.y, i_elaps);

    // copy kernel result back to host
    cudaMemcpy(gpu_ref, d_c, n_bytes, cudaMemcpyDeviceToHost);

    // check device results
    CheckResult(host_ref, gpu_ref, nxy);

    // free device global memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    // free host memory
    free(h_a);
    free(h_b);
    free(host_ref);
    free(gpu_ref);

    // reset device
    cudaDeviceReset();

    return 0;
}