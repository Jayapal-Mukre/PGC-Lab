#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4

int array[] = {10, 20, 30, 40, 50, 60, 70, 80};

int partial_sum[NUM_THREADS];

void *calculate_sum(void *arg)
{
    int thread_id = *(int *)arg;

    int start = thread_id * 2;
    int end = start + 2;

    partial_sum[thread_id] = 0;

    for (int i = start; i < end; i++)
    {
        partial_sum[thread_id] += array[i];
    }

    printf("Thread %d calculated partial sum = %d\n",
           thread_id + 1,
           partial_sum[thread_id]);

    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_ids[i] = i;

        pthread_create(
            &threads[i],
            NULL,
            calculate_sum,
            &thread_ids[i]
        );
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    int total = 0;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        total += partial_sum[i];
    }

    printf("Total sum = %d\n", total);

    return 0;
}
