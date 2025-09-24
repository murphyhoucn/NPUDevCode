# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// # include <time.h> //提供了处理日期和时间的标准函数和数据结构

# include <sys/time.h> // 通常用于获取更加精确的时间信息


void sumArrayOnHost(float *A, float *B, float *C, const int N)
{
    for (int i = 0; i < N; i++)
        C[i] = A[i] + B[i];
}

int main()
{

    const int N = 1024;
    size_t size = N * sizeof(float);

    float *h_A = (float*)malloc(size);
    float *h_B = (float*)malloc(size);
    float *h_C = (float*)malloc(size);

    for (int i = 0; i < N; i++)
    {
        h_A[i] = 1.0f;
        h_B[i] = 2.0f;
    }
    memset(h_C, 0, size);

    struct timeval tp;
    gettimeofday(&tp, NULL); // 从1970年1月1日0点以来到现在的秒数，需要头文件sys/time.h
    double time_point1 = (double)tp.tv_sec + (double)tp.tv_usec * 1e-6;

    sumArrayOnHost(h_A, h_B, h_C, N);

    gettimeofday(&tp, NULL); // 从1970年1月1日0点以来到现在的秒数，需要头文件sys/time.h
    double time_point2 = (double)tp.tv_sec + (double)tp.tv_usec * 1e-6;

    printf("time cost : %f\n", time_point2 - time_point1);

    free(h_A);
    free(h_B);
    free(h_C);

    return 0;
}
