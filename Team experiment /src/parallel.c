#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: parallel.exe <dataset_size> <threads>\n");
        return 1;
    }

    long long n = atoll(argv[1]);
    int threads = atoi(argv[2]);

    if (n <= 0 || threads <= 0)
    {
        printf("Dataset size and threads must be greater than 0.\n");
        return 1;
    }

    double *data = malloc(n * sizeof(double));

    if (data == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    omp_set_num_threads(threads);

    #pragma omp parallel for
    for (long long i = 0; i < n; i++)
    {
        data[i] = 1.0;
    }

    double start = omp_get_wtime();

    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (long long i = 0; i < n; i++)
    {
        sum += data[i];
    }

    double average = sum / (double)n;

    double end = omp_get_wtime();

    printf("OpenMP Parallel Sum and Average\n");
    printf("Dataset size: %lld\n", n);
    printf("Threads: %d\n", threads);
    printf("Sum: %.6f\n", sum);
    printf("Average: %.6f\n", average);
    printf("Execution time: %.9f seconds\n",
           end - start);

    free(data);

    return 0;
}
