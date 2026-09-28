#include <stdio.h>
#include <omp.h>

int main()
{
    int array[] = {10, 20, 30, 40, 50, 60, 70, 80};

    int total_sum = 0;

    #pragma omp parallel for reduction(+:total_sum)
    for (int i = 0; i < 8; i++)
    {
        int thread_id = omp_get_thread_num();

        printf("Thread %d processing array[%d] = %d\n",
               thread_id,
               i,
               array[i]);

        total_sum += array[i];
    }

    printf("Total sum = %d\n", total_sum);

    return 0;
}
