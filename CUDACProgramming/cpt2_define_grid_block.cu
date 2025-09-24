// Code 2-3
#include <cuda_runtime.h>
#include <stdio.h>

int main()
{
    int n_element = 1024;

    dim3 block(1024);
    dim3 grid = ((n_element + block.x - 1) / block.x);
    printf("grid.x = %d, block.x = %d\n", grid.x, block.x);

    block.x = 512;
    grid.x = (n_element + block.x - 1) / block.x;
    printf("grid.x = %d, block.x = %d\n", grid.x, block.x);

    block.x = 256;
    grid.x = (n_element + block.x - 1) / block.x;
    printf("grid.x = %d, block.x = %d\n", grid.x, block.x);

    block.x = 128;
    grid.x = (n_element + block.x - 1) / block.x;
    printf("grid.x = %d, block.x = %d\n", grid.x, block.x);

    cudaDeviceReset();
    return 0;
}