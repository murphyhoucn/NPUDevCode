// Code 2-6
#include <cuda_runtime.h>
#include <stdio.h>

#define CHECK(call)                                                                                               \
    {                                                                                                             \
        const cudaError_t error = call;                                                                           \
        if (error != cudaSuccess)                                                                                 \
        {                                                                                                         \
            printf("Error %s: %d, code: %d, reason: %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error)); \
            exit(-10 * error);                                                                                    \
        }                                                                                                         \
    }

void InitialInt(int *ip, int size)
{
    for (int i = 0; i < size; ++i)
        ip[i] = i;
}

void PrintMatrix(int *c, const int knx, const int kny)
{
    int *ic = c;
    printf("\nMatrix: (%d, %d)\n", knx, kny);

    for (int iy = 0; iy < kny; ++iy)
    {
        for (int ix = 0; ix < knx; ++ix)
        {
            printf("%3d", ic[ix]);
        }
        ic += knx;
        printf("\n");
    }
    printf("\n");
}

__global__ void PrintThreadIndex(int *a, const int knx, const int kny)
{
    int ix = threadIdx.x + blockIdx.x * blockDim.x;
    int iy = threadIdx.y + blockIdx.y * blockDim.y;
    unsigned int idx = iy * knx + ix;

    printf("thread_id:(%d, %d) block_id:(%d, %d) coordinate:(%d, %d) global index:%d ival:%d\n",
           threadIdx.x, threadIdx.y, blockIdx.x, blockIdx.y, ix, iy, idx, a[idx]);
}

int main(int argc, char **argv)
{
    printf("%s Starting...\n", argv[0]);

    // get device infomation
    int dev = 0;
    cudaDeviceProp device_prop;
    CHECK(cudaGetDeviceProperties(&device_prop, dev));
    printf("Using device %d:%s\n", dev, device_prop.name);
    CHECK(cudaSetDevice(dev));

    // set matrix dimension
    int nx = 8;
    int ny = 6;
    int nxy = nx * ny;
    int n_bytes = nxy * sizeof(float);

    // malloc host memory
    int *h_a;
    h_a = (int *)malloc(n_bytes);

    // initialize host matrix with integer
    InitialInt(h_a, nxy);
    PrintMatrix(h_a, nx, ny);

    // malloc device memory
    int *d_matrix_a;
    cudaMalloc((void **)&d_matrix_a, n_bytes);

    // transfer data from host to device
    cudaMemcpy(d_matrix_a, h_a, n_bytes, cudaMemcpyHostToDevice);

    // set up execution configuration
    dim3 block(4, 2);
    dim3 grid((nx + block.x - 1) / block.x, (ny + block.y - 1) / block.y);

    // invoke the kernel
    PrintThreadIndex<<<grid, block>>>(d_matrix_a, nx, ny);
    cudaDeviceSynchronize();

    // free host and device memory
    free(h_a);
    cudaFree(d_matrix_a);

    // reset device
    cudaDeviceReset();

    return 0;
}