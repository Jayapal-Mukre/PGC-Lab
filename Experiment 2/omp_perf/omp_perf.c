#include <stdio.h>
#include <omp.h>

#define N 1000000000L

int main()
{
    int num_threads;

    printf("Enter number of threads (1-32): ");
    scanf("%d", &num_threads);

    if (num_threads < 1 || num_threads > 32)
    {
        printf("Invalid number of threads.\n");
        return 1;
    }

    omp_set_num_threads(num_threads);

    double sum = 0.0;

    double start = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for (long i = 0; i < N; i++)
    {
        sum += (double)i * 0.000001;
    }

    double end = omp_get_wtime();

    printf("Sum = %.2f\n", sum);
    printf("Threads = %d\n", num_threads);
    printf("Execution time = %.6f seconds\n", end - start);

    return 0;
}
