#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 1000000000L
#define MAX_THREADS 32

double partial_sum[MAX_THREADS];

typedef struct
{
    int thread_id;
    long start;
    long end;
} ThreadData;

void *calculate_sum(void *arg)
{
    ThreadData *data = (ThreadData *)arg;

    double sum = 0.0;

    for (long i = data->start; i < data->end; i++)
    {
        sum += (double)i * 0.000001;
    }

    partial_sum[data->thread_id] = sum;

    return NULL;
}

int main()
{
    int num_threads;

    printf("Enter number of threads (1-%d): ", MAX_THREADS);
    scanf("%d", &num_threads);

    if (num_threads < 1 || num_threads > MAX_THREADS)
    {
        printf("Invalid number of threads.\n");
        return 1;
    }

    pthread_t threads[MAX_THREADS];
    ThreadData thread_data[MAX_THREADS];

    long chunk = N / num_threads;

    struct timespec start_time, end_time;

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    for (int i = 0; i < num_threads; i++)
    {
        thread_data[i].thread_id = i;
        thread_data[i].start = i * chunk;

        if (i == num_threads - 1)
        {
            thread_data[i].end = N;
        }
        else
        {
            thread_data[i].end = (i + 1) * chunk;
        }

        pthread_create(
            &threads[i],
            NULL,
            calculate_sum,
            &thread_data[i]
        );
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    double total_sum = 0.0;

    for (int i = 0; i < num_threads; i++)
    {
        total_sum += partial_sum[i];
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    double elapsed =
        (end_time.tv_sec - start_time.tv_sec) +
        (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    printf("Sum = %.2f\n", total_sum);
    printf("Threads = %d\n", num_threads);
    printf("Execution time = %.6f seconds\n", elapsed);

    return 0;
}
