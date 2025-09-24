#include <sys/time.h>

#ifndef __COMMON_H

#define __COMMOM_H

#define CHECK(call)                                                                                               \
    {                                                                                                             \
        const cudaError_t error = call;                                                                           \
        if (error != cudaSuccess)                                                                                 \
        {                                                                                                         \
            printf("Error %s: %d, code: %d, reason: %s\n", __FILE__, __LINE__, error, cudaGetErrorString(error)); \
            exit(1);                                                                                              \
        }                                                                                                         \
    }

inline double Seconds()
{
    struct timeval tp;
    struct timezone tzp;
    int i = gettimeofday(&tp, &tzp);
    return ((double)tp.tv_sec + (double)tp.tv_usec * 1.e-6);
}

void initialData_int(int *ip, int size)
{
    time_t t;
    srand((unsigned)time(&t));
    for (int i = 0; i < size; i++)
    {
        ip[i] = int(rand() & 0xff);
    }
}

void initialData(float *ip, int size)
{
    time_t t;
    srand((unsigned)time(&t));
    for (int i = 0; i < size; i++)
    {
        ip[i] = (float)(rand() & 0xffff) / 1000.0f;
    }
}

double cpuSecond()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double)tp.tv_sec + (double)tp.tv_usec * 1e-6);
}

void initDevice(int devNum)
{
    int dev = devNum;
    cudaDeviceProp deviceProp;
    CHECK(cudaGetDeviceProperties(&deviceProp, dev));
    printf("Using device %d: %s\n", dev, deviceProp.name);
    CHECK(cudaSetDevice(dev));
}

void checkResult(float *hostRef, float *gpuRef, const int N)
{
    double epsilon = 1.0E-8;
    for (int i = 0; i < N; i++)
    {
        if (abs(hostRef[i] - gpuRef[i]) > epsilon)
        {
            printf("Results don\'t match!\n");
            printf("%f(hostRef[%d] )!= %f(gpuRef[%d])\n", hostRef[i], i, gpuRef[i], i);
            return;
        }
    }
    printf("Check result success!\n");
}

#endif // __COMMON_H