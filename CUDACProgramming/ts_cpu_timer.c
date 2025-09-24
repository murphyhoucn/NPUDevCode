# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

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

    __clock_t start, finish;

    start = clock();
    sumArrayOnHost(h_A, h_B, h_C, N);
    finish = clock();
    double duration = (double)(finish - start) / CLOCKS_PER_SEC;
    // 注意：在并行程序中，使用这种计时方式有严重问题！
    
    printf("Duration = %f\n", duration);

    free(h_A);
    free(h_B);
    free(h_C);

    return 0;
}
