#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define N 100000000L

int main(int argc, char **argv) {
    int stride = (argc > 1 && argv[1][0] == 'p') ? 8 : 1;
    int threads = omp_get_max_threads();
    size_t bytes = ((size_t)threads * stride * sizeof(long) + 63) / 64 * 64;
    long *counts = aligned_alloc(64, bytes);
    if (!counts) { perror("aligned_alloc"); return 1; }
    memset(counts, 0, bytes);

    double start = omp_get_wtime();
    #pragma omp parallel
    {
        volatile long *value = &counts[omp_get_thread_num() * stride];
        for (long i = 0; i < N / threads; ++i) (*value)++;
    }
    double elapsed = omp_get_wtime() - start;

    long total = 0;
    for (int i = 0; i < threads; ++i) total += counts[i * stride];
    printf("%s | threads=%d | total=%ld | time=%.4f s\n",
           stride == 1 ? "adjacent" : "padded", threads, total, elapsed);
    free(counts);
    return 0;
}
