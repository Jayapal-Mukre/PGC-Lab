#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define ITERATIONS 100000

int main()
{
    int counter = 0;

    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
        for (int i = 0; i < ITERATIONS; i++)
        {
            counter++;
        }
    }

    printf("Expected counter = %d\n",
           NUM_THREADS * ITERATIONS);

    printf("Actual counter = %d\n", counter);

    return 0;
}
