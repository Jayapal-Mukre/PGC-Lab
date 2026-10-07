#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: parallel_file.exe <input_file> <threads>\n");
        return 1;
    }

    const char *filename = argv[1];
    int threads = atoi(argv[2]);

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Unable to open dataset file.\n");
        return 1;
    }

    long long capacity = 100000;
    long long n = 0;

    double *data = malloc(capacity * sizeof(double));

    if (data == NULL)
    {
        fclose(file);
        printf("Memory allocation failed.\n");
        return 1;
    }

    while (fscanf(file, "%lf", &data[n]) == 1)
    {
        n++;

        if (n >= capacity)
        {
            capacity *= 2;

            double *temp =
                realloc(data, capacity * sizeof(double));

            if (temp == NULL)
            {
                free(data);
                fclose(file);
                printf("Memory allocation failed.\n");
                return 1;
            }

            data = temp;
        }
    }

    fclose(file);

    omp_set_num_threads(threads);

    double start = omp_get_wtime();

    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (long long i = 0; i < n; i++)
    {
        sum += data[i];
    }

    double average = sum / (double)n;

    double end = omp_get_wtime();

    printf("Parallel File Sum and Average\n");
    printf("Dataset size: %lld\n", n);
    printf("Threads: %d\n", threads);
    printf("Sum: %.6f\n", sum);
    printf("Average: %.6f\n", average);
    printf("Execution time: %.9f seconds\n",
           end - start);

    free(data);

    return 0;
}
