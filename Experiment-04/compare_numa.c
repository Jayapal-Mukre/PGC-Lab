#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define N 100000000L
#define MB 512UL

static double run_counters(int threads, int stride, long *total) {
    size_t bytes = ((size_t)threads * stride * sizeof(long) + 63) / 64 * 64;
    long *counts = aligned_alloc(64, bytes);
    if (!counts) { perror("aligned_alloc"); exit(1); }
    memset(counts, 0, bytes);
    double start = omp_get_wtime();
    #pragma omp parallel num_threads(threads)
    {
        volatile long *value = &counts[omp_get_thread_num() * stride];
        for (long i = 0; i < N / threads; ++i) (*value)++;
    }
    double elapsed = omp_get_wtime() - start;
    *total = 0;
    for (int i = 0; i < threads; ++i) *total += counts[i * stride];
    free(counts);
    return elapsed;
}

static double run_sweep(char *buffer, size_t bytes, int threads) {
    long sum = 0;
    double start = omp_get_wtime();
    for (int pass = 0; pass < 4; ++pass) {
        #pragma omp parallel for num_threads(threads) reduction(+:sum)
        for (size_t i = 0; i < bytes; i += 64) sum += buffer[i];
    }
    if (sum == 0) fprintf(stderr, "Unexpected zero checksum\n");
    return omp_get_wtime() - start;
}

int main(void) {
    const int thread_counts[] = {1, 2, 4};
    puts("Table 1: false sharing (100000000 increments in total)");
    puts("Layout   | Threads | Final Count | Correctness | Time (s)");
    puts("---------------------------------------------------------");
    for (int i = 0; i < 3; ++i) {
        for (int stride = 1; stride <= 8; stride *= 8) {
            long total;
            double elapsed = run_counters(thread_counts[i], stride, &total);
            printf("%-8s | %7d | %11ld | %-11s | %8.4f\n",
                   stride == 1 ? "adjacent" : "padded", thread_counts[i],
                   total, total == N ? "Correct" : "INCORRECT", elapsed);
        }
        puts("---------------------------------------------------------");
    }

    size_t bytes = MB << 20;
    char *buffer = malloc(bytes);
    if (!buffer) { perror("malloc"); return 1; }
    memset(buffer, 1, bytes);
    puts("\nTable 2: memory sweep of 512 MB (4 passes)");
    puts("Threads | Time (s)");
    puts("-------------------");
    for (int i = 0; i < 2; ++i)
        printf("%7d | %8.4f\n", thread_counts[i],
               run_sweep(buffer, bytes, thread_counts[i]));
    free(buffer);
    return 0;
}
