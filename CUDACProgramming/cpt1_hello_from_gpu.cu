// Code 1-1
#include <stdio.h>

__global__ void helloFromGPU(void)
{
    int thread_index_x = threadIdx.x;

    printf("Hello world from GPU! thread: %d\n", thread_index_x);
}

int main()
{
    printf("Hello world from CPU!\n");

    helloFromGPU<<<1, 10>>>();
    cudaDeviceReset();
    // cudaDeviceSynchronize();

    return 0;
}