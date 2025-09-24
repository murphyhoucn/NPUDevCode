// 习题 1
#include <cuda_runtime.h>
#include <stdio.h>
#include <sys/time.h>

// '/'的意思是换行符，一行代码写成了多行
#define CHECK(call)                                                             \
    {                                                                           \
        const cudaError_t error = call;                                         \
        if (error != cudaSuccess)                                               \
        {                                                                       \
            printf("Error: %s:%d, ", __FILE__, __LINE__);                       \
            printf("cude: %d, reason: %s\n", error, cudaGetErrorString(error)); \
            exit(1);                                                            \
        }                                                                       \
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
            printf("Array do not match!\n");
            printf("host %5.2f gpu %5.2f at current %d\n", host_ref[i], gpu_ref[i], i);
            break;
        }
    }

    if (match)
        printf("Arrays match.\n\n");
}

void InitData(float *ip, int size)
{
    // generate different seed for random number.
    time_t t;
    srand((unsigned)time(&t));

    for (int i = 0; i < size; ++i)
    {
        ip[i] = (float)(rand() & 0xFF) / 10.0f;
    }
}

double CpuSecond()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double)tp.tv_sec + (double)tp.tv_usec * 1.0e-6);
}

void SumArrayOnHost(float *a, float *b, float *c, const int kN)
{
    for (int idx = 0; idx < kN; ++idx)
    {
        c[idx] = a[idx] + b[idx];
    }
}

__global__ void SumArrayOnDevice(float *a, float *b, float *c, const int kN)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < kN)
        c[i] = a[i] + b[i];
}

int main()
{
    // set device
    int dev = 0;
    cudaDeviceProp device_prop;
    CHECK(cudaGetDeviceProperties(&device_prop, dev));
    printf("Using device %d: %s\n", dev, device_prop.name);
    CHECK(cudaSetDevice(dev));

    // set up data size of vector
    int n_element = 1 << 24;
    printf("Vector size %d\n", n_element);

    // malloc host memory
    size_t n_bytes = n_element * sizeof(float);

    float *h_a, *h_b, *host_ref, *gpu_ref;
    h_a = (float *)malloc(n_bytes);
    h_b = (float *)malloc(n_bytes);
    host_ref = (float *)malloc(n_bytes);
    gpu_ref = (float *)malloc(n_bytes);

    double i_strat, i_elaps;

    // initialize data at host side
    i_strat = CpuSecond();
    InitData(h_a, n_element);
    InitData(h_b, n_element);
    i_elaps = CpuSecond() - i_strat;

    memset(host_ref, 0, n_bytes);
    memset(gpu_ref, 0, n_bytes);

    // malloc device global memoty
    float *d_a, *d_b, *d_c;
    cudaMalloc((float **)&d_a, n_bytes);
    cudaMalloc((float **)&d_b, n_bytes);
    cudaMalloc((float **)&d_c, n_bytes);

    // transfer data from host to device
    cudaMemcpy(d_a, h_a, n_bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, n_bytes, cudaMemcpyHostToDevice);

    // invoke kernel at host side
    int i_lens = 1024;
    dim3 block(i_lens);
    dim3 grid((n_element + block.x - 1) / block.x);

    i_strat = CpuSecond();
    SumArrayOnDevice<<<grid, block>>>(d_a, d_b, d_c, n_element);
    i_elaps = CpuSecond() - i_strat;
    printf("Execution configuration<<<%d, %d>>> Time eplapsed %f sec\n", grid.x, block.x, i_elaps);

    // copy kernel result back to host side
    cudaMemcpy(gpu_ref, d_c, n_bytes, cudaMemcpyDeviceToHost);

    // add vector at host side for result checks
    i_strat = CpuSecond();
    SumArrayOnHost(h_a, h_b, host_ref, n_element);
    i_elaps = CpuSecond() - i_strat;

    // check device results
    CheckResult(host_ref, gpu_ref, n_element);

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

/*
 *Using device 0: NVIDIA GeForce RTX 3080
 *Vector size 16777216
 *Execution configuration<<<16401, 1023>>> Time eplapsed 0.000504 sec
 *Arrays match.
 *
 *grid = (16401,1,1)
 *block = (1023,1,1)
 */

/*
 *Using device 0: NVIDIA GeForce RTX 3080
 *Vector size 16777216
 *Execution configuration<<<16384, 1024>>> Time eplapsed 0.000495 sec
 *Arrays match.
 *
 *grid = (16384,1,1)
 *block = (1024,1,1)
 */

/*
 *额。。。。不知道怎么分析，感觉运行速度差不多？？
 */