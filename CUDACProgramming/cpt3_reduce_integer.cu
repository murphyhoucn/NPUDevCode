#include <cuda_runtime.h>
#include <stdio.h>
#include "common/common.h"

/*
 * This code implements the interleaved and neighbour-paired approaches to parallel reduction in CUDA.
*/

// CPU Reduction
unsigned RecursiveReduce(int *data, int const kSize)
{
    // terminate check
    if (kSize == 1) return(data[0]);

    // renew the stride
    int const kStride = kSize / 2;
    
    // in-place reduction
    for (int i = 0; i < kStride; ++i)
    {
        data[i] += data[i + kStride];
    }

    // call recursicely
    return RecursiveReduce(data, kStride);
}

// Neighboured pair implementation with divergence
__global__ void ReduceNeighboured(int *g_idata, int *g_odata, unsigned int kN)
{
    unsigned int t_id = threadIdx.x;
    unsigned int idx = blockIdx.x * blockDim.x + threadIdx.x;

    // define idata as a pointer
    int *idata = g_idata + blockIdx.x * blockDim.x;

    if (idx >= kN) return;
    
    // 这段代码实现了分块内的并行归约操作。
    for(int stride = 1; stride < blockDim.x; stride *= 2)
    {
        if((t_id % (2 * stride)) == 0)
        {
           idata[t_id] += idata[t_id + stride]; 
        }
        __syncthreads(); // 是一个同步原语，确保块内所有线程在继续下一步之前都完成当前步的计算。
    }

    if(t_id == 0) g_odata[blockIdx.x] = idata[0];
}

// Neighboured pair implementation with divergence
// WarmUp function is same to ReduceNeighboured
__global__ void WarmUp(int *g_idata, int *g_odata, unsigned int kN)
{
    unsigned int t_id = threadIdx.x;
    unsigned int idx = blockIdx.x * blockDim.x + threadIdx.x;

    // define idata as a pointer
    int *idata = g_idata + blockIdx.x * blockDim.x;

    if (idx >= kN) return;
    
    for(int stride = 1; stride < blockDim.x; stride *= 2)
    {
        if((t_id % (2 * stride)) == 0)
        {
           idata[t_id] += idata[t_id + stride]; 
        }
        __syncthreads();
    }

    if(t_id == 0) g_odata[blockIdx.x] = idata[0];
}

int main(int argc, char **argv)
{
    int dev = 0;
    cudaDeviceProp device_prop;
    cudaGetDeviceProperties(&device_prop, dev);
    printf("%s starting reduction at ", argv[0]);
    printf("device %d : %s ", dev, device_prop.name);
    cudaSetDevice(dev);

    bool result_flag = false;

    // initialization
    int array_size = 1<<24;
    printf("with array size %d \n", array_size);

    // execution configuration
    int block_size = 512;
    if(argc > 1){block_size = atoi(argv[1]);}

    dim3 block (block_size, 1);
    dim3 grid ((array_size + block.x - 1) / block.x, 1);
    printf("grid : %d, block : %d\n", grid.x, block.x);

    // allocate host memory
    size_t bytes = array_size * sizeof(int);
    int *h_idata = (int *)malloc(bytes);
    int *h_odata = (int *)malloc(grid.x * sizeof(int));
    int *tmp = (int *)malloc(bytes);

    // initialization the array
    for (int i = 0; i < array_size; ++i)
    {
        h_idata[i] = (int)(rand() & 0xFF); // 返回一个范围在 0 到 255 之间的整数
    }
    memcpy(tmp, h_idata, bytes);

    double i_start, i_elaps;
    unsigned gpu_sum = 0;
    
    // allocate device memory
    int *d_idata = NULL;
    int *d_odata = NULL;
    CHECK(cudaMalloc((void **)&d_idata, bytes));
    CHECK(cudaMalloc((void **)&d_odata, bytes));

    // cpu reduction
    i_start = Seconds();
    unsigned cpu_sum = RecursiveReduce(tmp, array_size);
    i_elaps = Seconds() - i_start;
    printf("cpu reduce      elapsed %f ms. cpu_sum: %u\n", i_elaps * 1000, cpu_sum);

    // kernel 1: reduce neighboured(warm up)
    CHECK(cudaMemcpy(d_idata, h_idata, bytes, cudaMemcpyHostToDevice));
    CHECK(cudaDeviceSynchronize());
    i_start = Seconds();
    WarmUp<<<grid, block>>>(d_idata, d_odata, array_size);
    CHECK(cudaDeviceSynchronize());
    i_elaps = Seconds() - i_start;
    CHECK(cudaMemcpy(h_odata, d_odata, grid.x * sizeof(int), cudaMemcpyDeviceToHost));

    gpu_sum = 0;
    for(int i = 0; i < grid.x; ++i) gpu_sum += h_odata[i];
    printf("gpu warmup      elapsed %f ms. gpu_sum = %u. <<<grid: %d, block:%d>>>. \n", i_elaps * 1000, gpu_sum, grid.x, block.x);

    // kernel 1: reduce neighboured
    CHECK(cudaMemcpy(d_idata, h_idata, bytes, cudaMemcpyHostToDevice));
    CHECK(cudaDeviceSynchronize());
    i_start = Seconds();
    ReduceNeighboured<<<grid, block>>>(d_idata, d_odata, array_size);
    CHECK(cudaDeviceSynchronize());
    i_elaps = Seconds() - i_start;
    CHECK(cudaMemcpy(h_odata, d_odata, grid.x * sizeof(int), cudaMemcpyDeviceToHost));
    
    gpu_sum = 0;
    for(int i = 0; i < grid.x; ++i) gpu_sum += h_odata[i];
    printf("gpu Reduce      elapsed %f ms. gpu_sum = %u. <<<grid: %d, block:%d>>>. \n", i_elaps * 1000, gpu_sum, grid.x, block.x);

    CHECK(cudaDeviceSynchronize());
    i_elaps = Seconds() - i_start;
    CHECK(cudaMemcpy(h_odata, d_odata, grid.x / 8 * sizeof(int), cudaMemcpyDeviceToHost));
    gpu_sum = 0;
    for(int i = 0; i < grid.x / 8; ++i) gpu_sum += h_odata[i];
    printf("gpu Cmptnroll   elapsed %f ms. gpu_sum = %u. <<<grid: %d, block:%d>>>. \n", i_elaps * 1000, gpu_sum, grid.x, block.x);

    // free host memeory
    free(h_idata);
    free(h_odata);

    // free device memory
    CHECK(cudaFree(d_idata));
    CHECK(cudaFree(d_odata));

    // rest device
    CHECK(cudaDeviceReset());

    // check the result
    result_flag = (gpu_sum == cpu_sum);
    if(!result_flag) printf("Test failed!\n");

    return EXIT_SUCCESS;
}