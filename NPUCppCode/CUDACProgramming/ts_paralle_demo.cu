#include <stdio.h>
#include <cuda_runtime.h>
#include <string.h>

#include "common/common.h"

__global__ void SumMatrix(float *A, float *B, float *C, const int nx, const int ny)
{
    int ix = threadIdx.x + blockIdx.x + blockDim.x;
    int iy = threadIdx.y + blockIdx.y + blockDim.y;
    int ixy = ix + iy * nx;

    if (ix < nx && iy < ny)
        C[ixy] = A[ixy] + B[ixy];
}

int main(int argc, char **argv)
{
    int devidx = 0;
    cudaSetDevice(devidx);

    int nx = 1 << 13;
    int ny = 1 << 13;
    int nxy = nx * ny;
    int nbytes = nxy * sizeof(float);

    float *h_A = (float *)malloc(nbytes);
    float *h_B = (float *)malloc(nbytes);
    float *h_C = (float *)malloc(nbytes);
    float *h_C_gpu = (float *)malloc(nbytes);
    memset(h_C, 0, nbytes);
    memset(h_C_gpu, 0, nbytes);

    float *d_A = NULL;
    float *d_B = NULL;
    float *d_C = NULL;

    CHECK(cudaMalloc((void **)&d_A, nbytes));
    CHECK(cudaMalloc((void **)&d_B, nbytes));
    CHECK(cudaMalloc((void **)&d_C, nbytes));

    CHECK(cudaMemcpy(d_A, h_A, nbytes, cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(d_B, h_B, nbytes, cudaMemcpyHostToDevice));

    int dimx = argc > 2 ? atoi(argv[1]) : 32;
    int dimy = argc > 2 ? atoi(argv[2]) : 32;

    double t_start, t_elaps;

    dim3 block(dimx, dimy);
    dim3 grid((nx - 1) / block.x + 1, (ny - 1) / block.y + 1);

    t_start = Seconds();
    SumMatrix<<<grid, block>>>(d_A, d_B, d_C, nx, ny);
    CHECK(cudaDeviceSynchronize());
    t_elaps = Seconds() - t_start;

    printf("GPU Execution configuration <<<(%d, %d), (%d, %d)>>>  time: %f\n", grid.x, grid.y, block.x, block.y, t_elaps);

    CHECK(cudaMemcpy(h_C_gpu, d_C, nbytes, cudaMemcpyDeviceToHost));

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    free(h_A);
    free(h_B);
    free(h_C);
    free(h_C_gpu);

    cudaDeviceReset();

    return 0;
}