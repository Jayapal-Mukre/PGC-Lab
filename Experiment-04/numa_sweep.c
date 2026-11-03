#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

int main(int argc, char **argv) {
    size_t mb = argc > 1 ? (size_t)atol(argv[1]) : 512;
    size_t bytes = mb << 20;
    char *buffer = malloc(bytes);
    if (!buffer) { perror("malloc"); return 1; }
    memset(buffer, 1, bytes); /* first-touch placement */

    long sum = 0;
    double start = omp_get_wtime();
    for (int pass = 0; pass < 4; ++pass) {
        #pragma omp parallel for reduction(+:sum)
        for (size_t i = 0; i < bytes; i += 64) sum += buffer[i];
    }
    printf("buffer=%zu MB | threads=%d | sum=%ld | time=%.4f s\n",
           mb, omp_get_max_threads(), sum, omp_get_wtime() - start);
    free(buffer);
    return 0;
}
