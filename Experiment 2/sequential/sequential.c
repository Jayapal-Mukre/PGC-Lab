#include <stdio.h>
#include <time.h>

#define N 1000000000L

int main()
{
    double sum = 0.0;

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (long i = 0; i < N; i++)
    {
        sum += (double)i * 0.000001;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed =
        (end.tv_sec - start.tv_sec) +
        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Sum = %.2f\n", sum);
    printf("Execution time = %.6f seconds\n", elapsed);

    return 0;
}
