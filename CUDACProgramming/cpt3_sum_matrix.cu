#include <stdio.h>
#include <cuda_runtime.h>
#include "common/common.h"

void InitialData(float *ip, const int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        *(ip + i) = (float)(rand() & 0xFF) / 10.0f;
    }
}

void SumMatrixOnHost(float *a, float *b, float *c, const int knx, const int kny)
{
    for (int iy = 0; iy < kny; ++iy)
    {
        for (int ix = 0; ix < knx; ++ix)
        {
            *(c + ix) = *(a + ix) + *(b + ix);
        }
        c += knx;
        b += knx;
        a += knx;
    }
}

void CheckResult(float *host_ref, float *device_ref, const int kn)
{
    double epsilon = 1.0e-8;
    for (int i = 0; i < kn; ++i)
    {
        if (abs(*(host_ref + i) - *(device_ref + i)) > epsilon)
        {
            printf("host: %f; device: %f\n", *(host_ref + i), *(device_ref + i));
            printf("Arrays do not match!\n");
            break;
        }
    }
}

__global__ void SumMatrixOnGPU2D(float *a, float *b, float *c, const int knx, const int kny)
{
    unsigned int ix = blockIdx.x * blockDim.x + threadIdx.x;
    unsigned int iy = blockIdx.y * blockDim.y + threadIdx.y;
    unsigned int idx = iy * knx + ix;

    if (ix < knx && ix < kny)
    {
        *(c + idx) = *(b + idx) + *(a + idx);
    }
}

int main(int argc, char **argv)
{
    // set device
    int dev = 0;
    cudaDeviceProp device_prop;
    CHECK(cudaGetDeviceProperties(&device_prop, dev));
    CHECK(cudaSetDevice(dev));
    printf("%s using Device %d : %s\n", argv[0], dev, device_prop.name);

    // set up data size of matrix
    int nx = 1 << 14;
    int ny = 1 << 14;
    int nxy = nx * ny;
    int n_bytes = nxy * sizeof(float);

    // malloc host memory
    float *h_a, *h_b, *host_ref, *device_ref;
    h_a = (float *)malloc(n_bytes);
    h_b = (float *)malloc(n_bytes);
    host_ref = (float *)malloc(n_bytes);
    device_ref = (float *)malloc(n_bytes);

    // initialize data at host side
    size_t i_start = Seconds();
    InitialData(h_a, nxy);
    InitialData(h_b, nxy);
    size_t i_elaps = Seconds() - i_start;

    memset(host_ref, 0, n_bytes);
    memset(device_ref, 0, n_bytes);

    // add matrix at host side for result checks
    i_start = Seconds();
    SumMatrixOnHost(h_a, h_b, host_ref, nx, ny);
    i_elaps = Seconds() - i_start;

    // malloc device global memory
    float *d_a, *d_b, *d_c;
    CHECK(cudaMalloc((void **)&d_a, n_bytes));
    CHECK(cudaMalloc((void **)&d_b, n_bytes));
    CHECK(cudaMalloc((void **)&d_c, n_bytes));

    // transfer datat from host to device
    CHECK(cudaMemcpy(d_a, h_a, n_bytes, cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(d_b, h_b, n_bytes, cudaMemcpyHostToDevice));

    // invoke kernel at host side
    int dimx = 32;
    int dimy = 32;

    if (argc > 2)
    {
        dimx = atoi(argv[1]);
        dimy = atoi(argv[2]);
    }

    dim3 block(dimx, dimy);
    dim3 grid((nx + block.x - 1) / block.x, (ny + block.y - 1) / block.y);

    // excute the kernal
    CHECK(cudaDeviceSynchronize());
    i_start = Seconds();
    SumMatrixOnGPU2D<<<block, grid>>>(d_a, d_b, d_c, nx, ny);
    CHECK(cudaDeviceSynchronize());
    i_elaps = Seconds() - i_start;
    printf("SumMatrixOnGPU2D<<<(%d, %d), (%d, %d)>>> elapsed %f ms\n", grid.x, grid.y, block.x, block.y, (double)i_elaps);
    CHECK(cudaGetLastError());

    // copy kernel result back to host side
    CHECK(cudaMemcpy(device_ref, d_c, n_bytes, cudaMemcpyDeviceToHost));

    // check results
    CheckResult(host_ref, device_ref, nxy);

    // free device global memory
    CHECK(cudaFree(d_a));
    CHECK(cudaFree(d_b));
    CHECK(cudaFree(d_c));

    // free host memory
    free(h_a);
    free(h_b);
    free(host_ref);
    free(device_ref);

    // reset device
    CHECK(cudaDeviceReset());

    return 0;
}