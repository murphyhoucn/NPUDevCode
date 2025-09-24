#include <iostream>

int main()
{
    std::cout << sizeof(int) << std::endl;

    cudaError_t cudaDeviceSetShareMemConfig(cudaSharedMemConfig config);

    return 0;
}