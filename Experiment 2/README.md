# Experiment 2 — Multithreaded Programming Using Pthreads and OpenMP

## Aim

To develop multithreaded programs using Pthreads and OpenMP and understand thread creation, management, work distribution, race conditions, synchronization, thread coordination, and performance improvement using multiple threads.

## Software Requirements

* Windows
* WSL (Ubuntu)
* GCC
* POSIX Threads (Pthreads)
* OpenMP
* Nano editor

## Programs

### Part A — Pthreads

* `thread1.c` — Create one thread
* `thread2.c` — Create multiple threads
* `thread_sum.c` — Divide work among threads
* `race.c` — Demonstrate a race condition
* `mutex.c` — Synchronize shared data using a mutex
* `pthread_perf.c` — Pthreads performance analysis

### Part B — OpenMP

* `omp1.c` — Basic parallel region
* `omp_sum.c` — Work sharing and reduction
* `omp_race.c` — OpenMP race condition
* `omp_critical.c` — Critical section synchronization
* `omp_barrier.c` — Thread coordination using a barrier
* `omp_perf.c` — OpenMP performance analysis

### Part C — Performance Analysis

* `sequential.c` — Sequential baseline
* Execution-time comparison
* Speedup calculation
* Efficiency calculation
* Performance interpretation

## Setup

Start WSL from PowerShell:

```bash
wsl
```

Create the working directory:

```bash
mkdir -p ~/parallel_lab
cd ~/parallel_lab
pwd
```

Check GCC:

```bash
gcc --version
```

Check OpenMP support:

```bash
gcc -fopenmp --version
```

## Pthreads

### 1. Creating One Thread

Source file: `thread1.c`

```bash
gcc thread1.c -o thread1 -pthread
./thread1
```

`pthread_create()` creates a new thread and `pthread_join()` makes the main thread wait for it to finish.

### 2. Creating Multiple Threads

Source file: `thread2.c`

```bash
gcc thread2.c -o thread2 -pthread
./thread2
```

Four additional threads are created. The order of their output can change because thread scheduling is controlled by the operating system.

### 3. Dividing Work Among Threads

Source file: `thread_sum.c`

The array is:

```text
10 20 30 40 50 60 70 80
```

| Thread   | Calculation | Partial Sum |
| -------- | ----------- | ----------: |
| Thread 1 | 10 + 20     |          30 |
| Thread 2 | 30 + 40     |          70 |
| Thread 3 | 50 + 60     |         110 |
| Thread 4 | 70 + 80     |         150 |

Final sum = `360`

```bash
gcc thread_sum.c -o thread_sum -pthread
./thread_sum
```

### 4. Race Condition

Source file: `race.c`

Four threads increment a shared counter 100,000 times each.

Expected result:

```text
400000
```

Without synchronization, the actual result may be smaller and may change between executions.

```bash
gcc race.c -o race -pthread
./race
```

A race condition occurs when multiple threads access and modify shared data at the same time without proper coordination.

### 5. Mutex Synchronization

Source file: `mutex.c`

The shared counter is protected using:

```c
pthread_mutex_lock(&mutex);
counter++;
pthread_mutex_unlock(&mutex);
```

Compile and run:

```bash
gcc mutex.c -o mutex -pthread
./mutex
```

Expected result: `400000`

A mutex allows only one thread at a time to execute the protected section.

## OpenMP

### 6. Basic Parallel Region

Source file: `omp1.c`

OpenMP uses:

```c
#pragma omp parallel
```

Useful functions include:

```c
omp_get_thread_num()
omp_get_num_threads()
```

Compile and run:

```bash
gcc omp1.c -o omp1 -fopenmp
./omp1
```

### 7. Work Sharing and Reduction

Source file: `omp_sum.c`

The program uses:

```c
#pragma omp parallel for reduction(+:total_sum)
```

`parallel for` distributes loop iterations among threads, while `reduction` safely combines the partial results.

Final sum = `360`

```bash
gcc omp_sum.c -o omp_sum -fopenmp
./omp_sum
```

### 8. OpenMP Race Condition

Source file: `omp_race.c`

Four threads increment a shared counter 100,000 times each.

Expected result: `400000`

```bash
gcc omp_race.c -o omp_race -fopenmp
./omp_race
```

OpenMP manages the threads, but shared-data operations still require synchronization.

### 9. OpenMP Critical Section

Source file: `omp_critical.c`

The shared operation is protected using:

```c
#pragma omp critical
```

Compile and run:

```bash
gcc omp_critical.c -o omp_critical -fopenmp
./omp_critical
```

Expected result: `400000`

### 10. OpenMP Barrier

Source file: `omp_barrier.c`

A barrier is created using:

```c
#pragma omp barrier
```

It ensures that all threads reach the synchronization point before any thread continues to the next stage.

```bash
gcc omp_barrier.c -o omp_barrier -fopenmp
./omp_barrier
```

## Performance Analysis

### Sequential Program

Source file: `sequential.c`

The performance workload uses:

```text
N = 1,000,000,000
```

Compile and run:

```bash
gcc sequential.c -o sequential
./sequential
```

Result:

```text
499999999500.00
```

Average sequential execution time:

```text
1.353219 seconds
```

### Pthreads Performance

Source file: `pthread_perf.c`

Compile and run:

```bash
gcc pthread_perf.c -o pthread_perf -pthread
./pthread_perf
```

Measured results:

| Threads | Execution Time (seconds) |
| ------: | -----------------------: |
|       1 |                 1.348142 |
|       2 |                 0.680737 |
|       4 |                 0.358872 |
|       6 |                 0.241345 |
|      16 |                 0.144812 |

### OpenMP Performance

Source file: `omp_perf.c`

Compile and run:

```bash
gcc omp_perf.c -o omp_perf -fopenmp
./omp_perf
```

Measured results:

| Threads | Execution Time (seconds) |
| ------: | -----------------------: |
|       1 |                 1.409294 |
|       2 |                 0.715560 |
|       4 |                 0.360803 |
|       6 |                 0.241608 |
|      16 |                 0.140692 |

## Execution-Time Comparison

Sequential baseline = `1.353219 seconds`

| Threads | Pthreads (s) | OpenMP (s) |
| ------: | -----------: | ---------: |
|       1 |     1.348142 |   1.409294 |
|       2 |     0.680737 |   0.715560 |
|       4 |     0.358872 |   0.360803 |
|       6 |     0.241345 |   0.241608 |
|      16 |     0.144812 |   0.140692 |

The measured execution time generally decreases as the number of threads increases for this workload.

## Speedup

Formula:

```text
Speedup = Sequential Time / Parallel Time
```

| Threads | Pthreads Speedup | OpenMP Speedup |
| ------: | ---------------: | -------------: |
|       1 |           1.004x |         0.960x |
|       2 |           1.988x |         1.891x |
|       4 |           3.771x |         3.751x |
|       6 |           5.608x |         5.601x |
|      16 |           9.345x |         9.618x |

At 16 threads, the measured OpenMP speedup is approximately `9.62x`.

## Efficiency

Formula:

```text
Efficiency = (Speedup / Number of Threads) × 100
```

| Threads | Pthreads Efficiency | OpenMP Efficiency |
| ------: | ------------------: | ----------------: |
|       1 |             100.38% |            96.02% |
|       2 |              99.39% |            94.56% |
|       4 |              94.27% |            93.76% |
|       6 |              93.45% |            93.35% |
|      16 |              58.40% |            60.11% |

Efficiency decreases at higher thread counts because speedup is not perfectly linear.

The experiment identifies several sources of overhead, including thread management, scheduling, synchronization, memory access, operating-system activity, and non-parallel work.

## Pthreads vs OpenMP

| Feature                     | Pthreads                        | OpenMP                                       |
| --------------------------- | ------------------------------- | -------------------------------------------- |
| Thread creation             | `pthread_create()`              | `#pragma omp parallel`                       |
| Waiting                     | `pthread_join()`                | Runtime handles completion                   |
| Work distribution           | Programmer-managed              | `parallel for`                               |
| Shared-data synchronization | Mutex                           | Critical section and other OpenMP mechanisms |
| Coordination                | Join/synchronization mechanisms | Barrier                                      |
| Combining results           | Programmer-managed              | Reduction                                    |
| Control level               | More explicit                   | Higher-level                                 |

## Important Concepts

| Concept              | Meaning                                                                       |
| -------------------- | ----------------------------------------------------------------------------- |
| Thread               | A path of execution within a program                                          |
| Main Thread          | The thread that starts `main()`                                               |
| Multithreading       | Using multiple threads in one program                                         |
| Parallel Programming | Dividing work so multiple execution units can work concurrently               |
| Work Distribution    | Dividing a large task among threads                                           |
| Race Condition       | Incorrect or unpredictable result caused by unsynchronized shared-data access |
| Mutex                | Pthreads mechanism used to protect shared data                                |
| Critical Section     | Code section where simultaneous execution must be restricted                  |
| Barrier              | Synchronization point where threads wait for one another                      |
| Reduction            | Combining partial results from multiple threads                               |
| Speedup              | Improvement compared with a sequential baseline                               |
| Efficiency           | How effectively the available threads produce speedup                         |

## Learning Flow

```text
Understand Threads
        ↓
Create One Thread
        ↓
Create Multiple Threads
        ↓
Divide Work
        ↓
Shared Data
        ↓
Race Condition
        ↓
Synchronization
        ↓
OpenMP Parallel Region
        ↓
Work Sharing
        ↓
OpenMP Race Condition
        ↓
Critical Section
        ↓
Barrier
        ↓
Sequential Performance
        ↓
Pthreads Performance
        ↓
OpenMP Performance
        ↓
Execution-Time Comparison
        ↓
Speedup
        ↓
Efficiency
```

## Conclusion

This experiment demonstrates multithreaded programming using Pthreads and OpenMP. Pthreads provides explicit control over thread creation, joining, and mutex-based synchronization, while OpenMP provides a higher-level approach using parallel regions, work-sharing constructs, critical sections, barriers, and reductions.

The experiments demonstrate race conditions, synchronization, work distribution, and the effect of increasing the number of threads on execution time, speedup, and efficiency. The results also show that parallel speedup is not perfectly linear because of thread-management overhead, synchronization, memory access, scheduling, and other system factors.
