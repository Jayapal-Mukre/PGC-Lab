#include <stdio.h>
#include <omp.h>

int main(void) {
    long counter = 0;

    #pragma omp parallel for
    for (long i = 0; i < 10000000L; i++) {
        #pragma omp atomic
        counter++;
    }

    printf("Counter = %ld\n", counter);
    return 0;
}
