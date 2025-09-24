// Code 2-1
#include <stdlib.h>
#include <string.h>
#include <time.h>

void SumArrayOnHost(float *array_a, float *array_b, float *array_c, const int kN)
{
    for (int idx = 0; idx < kN; ++idx)
    {
        array_c[idx] = array_a[idx] + array_b[idx];
    }
}

void InitialArray(float *ip, int size)
{
    time_t t;
    srand((unsigned int)time(&t));

    for (int i = 0; i < size; ++i)
    {
        ip[i] = (float)(rand() & 0xFF) / 10.0f;
    }
}

int main()
{
    int n_element = 1024;
    size_t n_bytes = n_element * sizeof(float);

    float *h_array_a, *h_array_b, *h_array_c;
    h_array_a = (float *)malloc(n_bytes);
    h_array_b = (float *)malloc(n_bytes);
    h_array_c = (float *)malloc(n_bytes);

    InitialArray(h_array_a, n_element);
    InitialArray(h_array_b, n_element);

    SumArrayOnHost(h_array_a, h_array_b, h_array_c, n_element);

    free(h_array_a);
    free(h_array_b);
    free(h_array_c);

    return 0;
}