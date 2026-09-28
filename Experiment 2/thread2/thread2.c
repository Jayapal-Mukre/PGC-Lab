#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg)
{
    int id = *(int *)arg;

    printf("Hello from thread %d\n", id);

    return NULL;
}

int main()
{
    pthread_t threads[4];
    int thread_ids[4];

    for (int i = 0; i < 4; i++)
    {
        thread_ids[i] = i + 1;

        pthread_create(
            &threads[i],
            NULL,
            thread_function,
            &thread_ids[i]
        );
    }

    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished.\n");

    return 0;
}
