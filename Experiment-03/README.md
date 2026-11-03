# Experiment 3 – Analyze Synchronization Mechanisms in Parallel Programs

## Objective

Implement and study synchronization mechanisms used in shared-memory parallel programs. Compare correctness, execution time, and scalability as the number of threads increases.

## Environment and tools

- VMware Workstation with Ubuntu 22.04 LTS
- GCC compiler and OpenMP runtime
- POSIX Threads (pthreads)
- POSIX semaphore library
- Ubuntu terminal

Install the required compiler and libraries:

```bash
sudo apt update
sudo apt install build-essential -y
```

Check GCC and OpenMP support:

```bash
gcc --version
echo '#include <omp.h>' | gcc -E -fopenmp -xc - > /dev/null && echo "OpenMP OK"
```

## Programs

| File | Mechanism | Purpose |
| --- | --- | --- |
| `race.c` | No synchronization | Demonstrates a race condition when multiple threads update a shared counter. |
| `critical.c` | Critical section | Protects the counter so only one thread updates it at a time. |
| `atomic.c` | Atomic operation | Makes the counter increment indivisible. |
| `barrier.c` | Barrier | Makes threads wait until all threads reach the synchronization point. |
| `semaphore.c` | Semaphore | Uses a binary semaphore to protect a shared counter between two pthreads. |
| `compare_sync.c` | Benchmark | Compares no synchronization, critical section, atomic operation, and an OpenMP lock. |

## Compile and run

Run these commands from the `Experiment-03` directory.

### 1. Race condition

```bash
gcc race.c -fopenmp -o race
./race
```

### 2. Critical section

```bash
gcc critical.c -fopenmp -o critical
./critical
```

### 3. Atomic operation

```bash
gcc atomic.c -fopenmp -o atomic
./atomic
```

### 4. Barrier

```bash
gcc barrier.c -fopenmp -o barrier
./barrier
```

To run an OpenMP program with a chosen number of threads:

```bash
OMP_NUM_THREADS=4 ./barrier
```

### 5. Semaphore

```bash
gcc semaphore.c -pthread -o semaphore
./semaphore
```

Expected counter: `200000`.

### 6. Comparison benchmark

```bash
gcc compare_sync.c -fopenmp -o compare_sync
./compare_sync
```

The benchmark tests 10,000,000 increments using 1, 2, 4, and 8 threads.

## Results recorded during the lab

The following values are transcribed from the terminal screenshots supplied for this lab session. Execution times are in seconds and can vary with VM resources and system load.

| Mechanism | Threads | Final count | Correctness | Time (s) |
| --- | ---: | ---: | --- | ---: |
| None | 1 | 10,000,000 | Correct | 0.0065 |
| Critical | 1 | 10,000,000 | Correct | 0.1247 |
| Atomic | 1 | 10,000,000 | Correct | 0.0682 |
| Lock | 1 | 10,000,000 | Correct | 0.1144 |
| None | 2 | 4,832,157 | Incorrect | 0.0132 |
| Critical | 2 | 10,000,000 | Correct | 0.3031 |
| Atomic | 2 | 10,000,000 | Correct | 0.1874 |
| Lock | 2 | 10,000,000 | Correct | 0.4261 |
| None | 4 | 3,463,773 | Incorrect | 0.0140 |
| Critical | 4 | 10,000,000 | Correct | 0.6428 |
| Atomic | 4 | 10,000,000 | Correct | 0.2068 |
| Lock | 4 | 10,000,000 | Correct | 1.0333 |
| None | 8 | 2,084,190 | Incorrect | 0.0162 |
| Critical | 8 | 10,000,000 | Correct | 1.0160 |
| Atomic | 8 | 10,000,000 | Correct | 0.2378 |
| Lock | 8 | 10,000,000 | Correct | 1.8498 |

## Observations

- **No synchronization:** Fast in the recorded benchmark, but produces incorrect results as thread count increases because increments can be lost in a race condition.
- **Critical section:** Produces the correct count, but serializes access to the shared counter and becomes slower as more threads contend for the section.
- **Atomic operation:** Produces the correct count and was faster than the critical section and lock in the recorded multi-threaded runs.
- **OpenMP lock:** Produces the correct count, but lock contention increased execution time in the recorded runs.
- **Barrier:** Synchronizes phases of parallel work; it does not itself protect a shared variable.
- **Semaphore:** The binary semaphore protects the counter so the two pthreads can safely perform their increments.

## Conclusion

Synchronization is necessary when multiple threads access shared data. The unsynchronized counter is fast but unreliable. Critical sections, atomic operations, locks, and semaphores provide controlled access with different overheads. In this lab's benchmark, the atomic operation gave a good balance of correctness and execution time for the simple counter increment. A barrier serves a different purpose: it coordinates when threads may proceed to the next phase.

## Files in this experiment

- `race.c`
- `critical.c`
- `atomic.c`
- `barrier.c`
- `semaphore.c`
- `compare_sync.c`
- `README.md`
