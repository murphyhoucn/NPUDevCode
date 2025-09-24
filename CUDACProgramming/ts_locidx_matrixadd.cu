# include <stdio.h>
# include <cuda_runtime.h>
# include <stdlib.h>
# include <string.h>

#include "common/common.h"

__global__ void printThreadIdx(float* A, const int nx, const int ny)
{
    int ix = threadIdx.x + blockIdx.x * blockDim.x;
    int iy = threadIdx.y + blockIdx.y * blockDim.y;

    unsigned int idx = ix + nx * iy;
    printf("thread_id(%d,%d) block_id(%d,%d) coordinate(%d,%d) global index %2d ival %2f\n",threadIdx.x,threadIdx.y, blockIdx.x,blockIdx.y, ix,iy, idx, A[idx]);

}

__global__ void sumMatrix(float* MA, float* MB, float* MC, const int nx, const int ny)
{
    int ix = threadIdx.x + blockIdx.x * blockDim.x;
    int iy = threadIdx.y + blockIdx.y * blockDim.y;
    int ixy = ix + iy * nx;
    if (ix < nx && iy < ny)
        MC[ixy] = MA[ixy] + MB[ixy];
}

void sumMatrixCPU(float* MA, float* MB, float* MC, const int nx, const int ny)
{
    float* pa = MA;
    float* pb = MB;
    float* pc = MC;

    for(int j = 0; j < ny; j++)
    {
        for(int i = 0; i < nx; i++)
        {
            pc[i] = pa[i] + pb[i];
        }
        pa += nx;
        pb += nx;
        pc += nx;
    }
}

void checkResult(float * CPU, float * GPU, const int N)
{
    for (int i = 0; i < N; i++) {
        if (GPU[i] != CPU[i]) {
            printf("Error: gpu_C[%d] = %f != %f = h_C[%d]\n", i, GPU[i], CPU[i], i);
            exit(EXIT_FAILURE);
        }
    }
}

int main()
{
    int dev_idx = 0;
    cudaSetDevice(dev_idx);

    srand((unsigned int)time(NULL));

    int nx = 1<<12, ny=1<<12;
    int nxy = nx * ny;
    size_t nBytes = nxy * sizeof(float);

    float* h_A = (float*)malloc(nBytes);
    float* h_B = (float*)malloc(nBytes);
    float* h_C = (float*)malloc(nBytes);
    float* h_C_from_gpu = (float*)malloc(nBytes);


    for (int i = 0; i < nxy; i++)
    {
        h_A[i] = (float)rand() / RAND_MAX;
        h_B[i] = (float)rand() / RAND_MAX;
    }
    memset(h_C, 0, nBytes);
    memset(h_C_from_gpu, 0, nBytes);


    // device
    float* d_A = NULL;
    float* d_B = NULL;
    float* d_C = NULL;
    CHECK(cudaMalloc((void**)&d_A, nBytes));
    CHECK(cudaMalloc((void**)&d_B, nBytes));
    CHECK(cudaMalloc((void**)&d_C, nBytes));
    
    cudaMemcpy(d_A, h_A, nBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, nBytes, cudaMemcpyHostToDevice);

    // cpu section
    double iStart = Seconds();
    sumMatrixCPU(h_A, h_B, h_C, nx, ny);
    double iElaps = Seconds() - iStart;
    printf("CPU Execution Time elapsed %f sec\n",iElaps);

    // gpu section

    // 2d block and 2d grid
    int dimx=32;
    int dimy=32; 
    dim3 block1(dimx, dimy);
    dim3 grid1((nx - 1)/block1.x + 1 ,(ny - 1)/block1.y + 1);

    iStart=Seconds();
    sumMatrix<<<grid1,block1>>>(d_A, d_B, d_C, nx, ny);
    CHECK(cudaDeviceSynchronize());
    iElaps=Seconds()-iStart;
    printf("GPU Execution configuration<<<(%d,%d),(%d,%d)>>> Time elapsed %f sec\n", grid1.x,grid1.y, block1.x,block1.y, iElaps);
    CHECK(cudaMemcpy(h_C_from_gpu,d_C,nBytes,cudaMemcpyDeviceToHost));
    checkResult(h_C, h_C_from_gpu, nxy);

    // 1d block and 1d grid
    dimx=32;
    dim3 block2(dimx);
    dim3 grid2((nxy-1)/block2.x+1);
    iStart=Seconds();
    sumMatrix<<<grid2,block2>>>(d_A,d_B,d_C,nx*ny,1);
    CHECK(cudaDeviceSynchronize());
    iElaps=Seconds()-iStart;
    printf("GPU Execution configuration<<<(%d,%d),(%d,%d)>>> Time elapsed %f sec\n",
        grid2.x,grid2.y,block2.x,block2.y,iElaps);
    CHECK(cudaMemcpy(h_C_from_gpu,d_C,nBytes,cudaMemcpyDeviceToHost));
    checkResult(h_C,h_C_from_gpu,nxy);


    // 2d block and 1d grid
    dimx=32;
    dim3 block3(dimx);
    dim3 grid3((nx-1)/block3.x+1,ny);
    iStart=Seconds();
    sumMatrix<<<grid3,block3>>>(d_A,d_B,d_C,nx,ny);
    CHECK(cudaDeviceSynchronize());
    iElaps=Seconds()-iStart;
    printf("GPU Execution configuration<<<(%d,%d),(%d,%d)>>> Time elapsed %f sec\n",
        grid3.x,grid3.y,block3.x,block3.y,iElaps);
    CHECK(cudaMemcpy(h_C_from_gpu,d_C,nBytes,cudaMemcpyDeviceToHost));
    checkResult(h_C,h_C_from_gpu,nxy);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    free(h_A);
    free(h_B);
    free(h_C);
    free(h_C_from_gpu);
    cudaDeviceReset();
    return 0;    
}