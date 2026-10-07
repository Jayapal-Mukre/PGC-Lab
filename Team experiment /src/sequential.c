#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: sequential.exe <dataset_size>\n");
        return 1;
    }

    long long n = atoll(argv[1]);

    if (n <= 0)
    {
        printf("Dataset size must be greater than 0.\n");
        return 1;
    }

    double *data = malloc(n * sizeof(double));

    if (data == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (long long i = 0; i < n; i++)
    {
        data[i] = 1.0;
    }

    clock_t start = clock();

    double sum = 0.0;

    for (long long i = 0; i < n; i++)
    {
        sum += data[i];
    }

    double average = sum / (double)n;

    clock_t end = clock();

    double execution_time =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("Sequential Sum and Average\n");
    printf("Dataset size: %lld\n", n);
    printf("Sum: %.6f\n", sum);
    printf("Average: %.6f\n", average);
    printf("Execution time: %.9f seconds\n",
           execution_time);

    free(data);

    return 0;
}
