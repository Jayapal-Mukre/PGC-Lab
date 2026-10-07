# Parallel Sum and Average of Dataset using OpenMP

## Parallel Computing Mini Project

### Theme 3 – Parallel Sum and Average of Dataset

---

## 1. Project Overview

This project implements the calculation of the **sum and average of a large dataset** using both sequential and parallel approaches.

The parallel implementation uses **OpenMP** to distribute the summation workload among multiple threads.

The main objective is to study the performance improvement obtained through parallel computing by comparing:

- Sequential execution
- OpenMP execution with 1 thread
- OpenMP execution with 2 threads
- OpenMP execution with 4 threads
- OpenMP execution with 8 threads

The experiments are performed using different dataset sizes and the execution time, speedup, and efficiency are analyzed.

---

## 2. Problem Statement

Calculating the sum and average of a very large dataset sequentially requires processing every element one after another.

For a large number of elements, the computation can take more time.

The problem is to design a parallel solution using OpenMP where the dataset is divided among multiple threads so that the sum can be calculated concurrently.

The final result must be correct and equivalent to the sequential implementation.

---

## 3. Objectives

The main objectives of this project are:

1. Implement a sequential sum and average calculation.
2. Implement a parallel version using OpenMP.
3. Use multiple threads to distribute the computation.
4. Use OpenMP reduction to safely calculate the total sum.
5. Test the implementation with different dataset sizes.
6. Compare execution time for different thread counts.
7. Calculate speedup and efficiency.
8. Generate graphs for performance analysis.
9. Determine the most effective number of threads for the tested workload.

---

## 4. Technologies Used

| Technology | Purpose |
|---|---|
| C | Program implementation |
| OpenMP | Parallel programming |
| GCC | C compiler |
| MSYS2 UCRT64 | Build and execution environment |
| Python | Graph generation |
| Pandas | Processing benchmark data |
| Matplotlib | Generating graphs |
| GitHub | Project repository and submission |

---

## 5. Parallel Computing Model

The project uses the **shared-memory parallel programming model** with OpenMP.

OpenMP allows multiple threads to execute parts of a loop concurrently.

The main parallel operation is:

```c
#pragma omp parallel for reduction(+:sum)
for (long long i = 0; i < n; ++i)
    sum += data[i];
```

The `parallel for` directive distributes loop iterations among multiple threads.

The `reduction(+:sum)` clause ensures that each thread can maintain its own partial sum and that the partial sums are safely combined into the final sum.

---

## 6. Algorithm

### 6.1 Sequential Algorithm

1. Read the dataset size.
2. Allocate memory for the dataset.
3. Initialize the dataset.
4. Set the sum to zero.
5. Traverse every element sequentially.
6. Add every element to the sum.
7. Calculate the average:

```text
Average = Sum / Number of Elements
```

8. Display the sum, average and execution time.

---

### 6.2 Parallel Algorithm

1. Read the dataset size and number of threads.
2. Allocate memory for the dataset.
3. Initialize the dataset using OpenMP.
4. Set the number of OpenMP threads.
5. Divide the summation loop among the available threads.
6. Each thread calculates a partial sum.
7. OpenMP reduction combines the partial sums.
8. Calculate the average.
9. Display the sum, average and execution time.

---

## 7. Dataset

For the benchmark experiments, the program initializes the dataset with values of `1.0`.

Therefore:

```text
Sum = Number of Elements
Average = 1.0
```

For example:

```text
Dataset size = 50,000,000

Sum     = 50,000,000
Average = 1.0
```

Using a known dataset makes it easy to verify the correctness of both the sequential and parallel implementations.

---

## 8. Project Structure

```text
Theme3_Parallel_Sum_Average_OpenMP_FINAL/
│
├── README.md
├── Makefile
├── run_experiments.sh
├── generate_graphs.py
├── WINDOWS_RUN_GUIDE.md
├── VIVA_QA.md
│
├── src/
│   ├── sequential.c
│   ├── parallel.c
│   ├── generate_dataset.c
│   └── parallel_file.c
│
├── data/
│   └── README.md
│
├── results/
│   ├── benchmark.csv
│   └── README.md
│
├── graphs/
│   ├── execution_time_threads_1000000.png
│   ├── execution_time_threads_5000000.png
│   ├── execution_time_threads_10000000.png
│   ├── execution_time_threads_50000000.png
│   ├── speedup_1000000.png
│   ├── speedup_5000000.png
│   ├── speedup_10000000.png
│   ├── speedup_50000000.png
│   ├── efficiency_1000000.png
│   ├── efficiency_5000000.png
│   ├── efficiency_10000000.png
│   └── efficiency_50000000.png
│
├── report/
│   └── REPORT_TEMPLATE.md
│
└── presentation/
    ├── PPT_CONTENT.md
    └── PPT_READY_CONTENT.md
```

---

## 9. Source Files

### `src/sequential.c`

Contains the sequential implementation for calculating the sum and average of the dataset.

### `src/parallel.c`

Contains the OpenMP parallel implementation using multiple threads and reduction.

### `src/generate_dataset.c`

Generates a dataset file containing numerical values.

### `src/parallel_file.c`

Reads a dataset from a file and calculates the sum and average using OpenMP.

### `generate_graphs.py`

Reads benchmark results and generates execution-time, speedup and efficiency graphs.

### `results/benchmark.csv`

Contains the measured execution times from the experiments.

---

## 10. Compilation

The project was compiled using GCC.

### Sequential Program

```bash
gcc -O2 -o sequential.exe src/sequential.c
```

### Parallel Program

```bash
gcc -O2 -fopenmp -o parallel.exe src/parallel.c
```

The `-fopenmp` option enables OpenMP support.

---

## 11. Running the Programs

### Sequential

```bash
./sequential.exe 1000000
```

### Parallel with 1 Thread

```bash
./parallel.exe 1000000 1
```

### Parallel with 2 Threads

```bash
./parallel.exe 1000000 2
```

### Parallel with 4 Threads

```bash
./parallel.exe 1000000 4
```

### Parallel with 8 Threads

```bash
./parallel.exe 1000000 8
```

The same commands can be used with other dataset sizes.

---

## 12. Experimental Configuration

The experiments were performed using the following dataset sizes:

```text
1,000,000
5,000,000
10,000,000
50,000,000
```

The following OpenMP thread counts were tested:

```text
1
2
4
8
```

Therefore, a total of:

```text
4 dataset sizes × 4 thread configurations = 16 parallel experiments
```

were performed.

Sequential measurements were also collected for each dataset size.

---

# 13. Experimental Results

## 13.1 Execution Time

The measured execution times were:

| Dataset Size | Sequential (s) | 1 Thread (s) | 2 Threads (s) | 4 Threads (s) | 8 Threads (s) |
|---:|---:|---:|---:|---:|---:|
| 1,000,000 | 0.002000 | 0.002000 | 0.001000 | 0.001000 | 0.002000 |
| 5,000,000 | 0.007000 | 0.007000 | 0.004000 | 0.003000 | 0.004000 |
| 10,000,000 | 0.014000 | 0.013000 | 0.008000 | 0.005000 | 0.006000 |
| 50,000,000 | 0.068000 | 0.062000 | 0.038000 | 0.024000 | 0.025000 |

The results show that execution time generally decreases when multiple threads are used.

The best execution time for the 50-million-element dataset was obtained using 4 threads.

---

## 13.2 50-Million-Element Dataset

For the largest dataset, the measured results were:

| Threads | Execution Time (s) |
|---:|---:|
| 1 | 0.062000036 |
| 2 | 0.037999868 |
| 4 | 0.023999929 |
| 8 | 0.025000095 |

The 4-thread configuration provided the lowest measured execution time.

---

# 14. Speedup

Speedup is calculated using:

```text
Speedup = Sequential Execution Time / Parallel Execution Time
```

For the 50-million-element dataset:

```text
Sequential Time = 0.068000000 s
```

### Speedup Results

| Threads | Execution Time (s) | Speedup |
|---:|---:|---:|
| 1 | 0.062000036 | 1.10× |
| 2 | 0.037999868 | 1.79× |
| 4 | 0.023999929 | 2.83× |
| 8 | 0.025000095 | 2.72× |

The highest speedup obtained using the sequential program as the baseline was approximately:

```text
2.83×
```

with 4 threads.

---

# 15. Efficiency

Efficiency is calculated using:

```text
Efficiency = (Speedup / Number of Threads) × 100
```

For the 50-million-element dataset:

| Threads | Speedup | Efficiency |
|---:|---:|---:|
| 1 | 1.10× | 109.7% |
| 2 | 1.79× | 89.5% |
| 4 | 2.83× | 70.8% |
| 8 | 2.72× | 34.0% |

The efficiency decreases as the number of threads increases.

The measured efficiency above 100% for one thread is caused by differences between separate sequential and OpenMP program executions and the extremely small measured execution times. It should not be interpreted as actual parallel efficiency greater than 100%.

---

# 16. Performance Analysis

The experimental results demonstrate that OpenMP can improve the execution time of the sum and average calculation by distributing the workload among multiple threads.

For the 50-million-element dataset, execution time decreased from approximately:

```text
0.062 seconds → 0.024 seconds
```

when increasing the OpenMP thread count from 1 to 4.

The corresponding speedup relative to the sequential implementation was approximately:

```text
2.83×
```

However, increasing the number of threads from 4 to 8 did not improve performance.

The execution time increased slightly:

```text
4 threads = 0.023999929 s
8 threads = 0.025000095 s
```

This demonstrates that increasing the number of threads does not always result in proportional performance improvement.

Possible reasons include:

- Thread management overhead
- Synchronization overhead
- Memory access limitations
- CPU resource limitations
- OpenMP scheduling overhead
- Reduction overhead

Therefore, the optimal number of threads depends on both the workload and the hardware.

---

# 17. Graphs

The project generates three types of graphs for each dataset size.

### Execution Time vs Threads

Shows how execution time changes as the number of OpenMP threads increases.

Example:

```text
graphs/execution_time_threads_50000000.png
```

### Speedup vs Threads

Shows the performance improvement obtained from parallel execution.

Example:

```text
graphs/speedup_50000000.png
```

### Efficiency vs Threads

Shows how efficiently the available threads are being utilized.

Example:

```text
graphs/efficiency_50000000.png
```

Graphs are generated using:

```bash
python generate_graphs.py
```

---

# 18. Correctness Verification

The program was verified using the expected mathematical result.

Since every generated element has a value of `1.0`:

```text
Expected Sum = Dataset Size
Expected Average = 1.0
```

For 50 million elements:

```text
Sum     = 50000000.000000
Average = 1.000000
```

The same results were obtained from the sequential and parallel implementations.

Therefore, the OpenMP reduction produces the correct final result.

---

# 19. Complexity

For a dataset containing `N` elements:

### Sequential

```text
Time Complexity: O(N)
Space Complexity: O(N)
```

### Parallel

The total amount of work remains approximately:

```text
O(N)
```

but the computation is distributed among multiple threads.

Ideally, the computation time can approach:

```text
O(N / P)
```

where:

```text
N = number of dataset elements
P = number of threads
```

In practice, the performance is affected by parallelization overhead, synchronization, memory access and hardware limitations.

---

# 20. Advantages of the Parallel Approach

- Faster processing for sufficiently large datasets.
- Multiple CPU threads can work simultaneously.
- OpenMP provides a relatively simple way to implement shared-memory parallelism.
- Reduction provides safe accumulation of partial sums.
- Performance can be evaluated using different thread counts.

---

# 21. Limitations

- Increasing threads does not always improve performance.
- Thread management introduces overhead.
- Performance depends on available CPU resources.
- Very small datasets may not benefit significantly from parallelization.
- Memory bandwidth can become a limiting factor.
- Execution times can vary slightly between runs because of system activity.

---

# 22. Conclusion

This project successfully implements parallel sum and average calculation using OpenMP.

Both the sequential and parallel implementations produce the correct sum and average.

Experiments were performed using four dataset sizes and four different thread configurations.

The results demonstrate that parallel execution can reduce computation time, particularly for larger datasets.

For the 50-million-element dataset, the best measured configuration was **4 OpenMP threads**, with an execution time of approximately:

```text
0.024 seconds
```

and a speedup of approximately:

```text
2.83×
```

compared with the sequential implementation.

Increasing the thread count from 4 to 8 did not improve performance, demonstrating that more threads do not always result in better performance.

Overall, the project demonstrates the practical application of OpenMP for shared-memory parallel computing and performance analysis.

---

# 23. Team Members

### Parallel Computing Mini Project – Theme 3

| Member |
|---|
| Jayapal Mukre |
| Amogh Loni |
| Chanabasappa Metgud |
| Sammed Patil |

---

# 24. GitHub Submission

The repository contains:

- Source code
- Sequential implementation
- OpenMP parallel implementation
- Dataset generation code
- Benchmark results
- Performance graphs
- Report material
- Presentation material
- Viva questions and answers

Executable files and temporary build files should not be committed to the GitHub repository unless specifically required.

---

# 25. How to Reproduce the Experiment

### Step 1 – Compile

```bash
gcc -O2 -o sequential.exe src/sequential.c
gcc -O2 -fopenmp -o parallel.exe src/parallel.c
```

### Step 2 – Run Sequential Version

```bash
./sequential.exe 1000000
./sequential.exe 5000000
./sequential.exe 10000000
./sequential.exe 50000000
```

### Step 3 – Run Parallel Version

```bash
./parallel.exe 1000000 1
./parallel.exe 1000000 2
./parallel.exe 1000000 4
./parallel.exe 1000000 8

./parallel.exe 5000000 1
./parallel.exe 5000000 2
./parallel.exe 5000000 4
./parallel.exe 5000000 8

./parallel.exe 10000000 1
./parallel.exe 10000000 2
./parallel.exe 10000000 4
./parallel.exe 10000000 8

./parallel.exe 50000000 1
./parallel.exe 50000000 2
./parallel.exe 50000000 4
./parallel.exe 50000000 8
```

### Step 4 – Generate Graphs

```bash
python generate_graphs.py
```

The generated graphs are stored in:

```text
graphs/
```

---

# 26. Key Takeaways

1. OpenMP allows the summation workload to be distributed among multiple threads.
2. Reduction is used to safely combine partial sums.
3. Larger datasets generally provide more opportunity for parallel execution.
4. Increasing the number of threads does not always produce proportional speedup.
5. In this experiment, 4 threads provided the best performance for the 50-million-element dataset.
6. Performance should be evaluated using execution time, speedup and efficiency.
7. The experimental results demonstrate the practical benefits and limitations of shared-memory parallel computing.

---

## Project Status

**Status: Completed**

- [x] Sequential implementation
- [x] OpenMP parallel implementation
- [x] Correctness verification
- [x] Multiple dataset sizes
- [x] Multiple thread configurations
- [x] Benchmark data collection
- [x] Execution-time analysis
- [x] Speedup analysis
- [x] Efficiency analysis
- [x] Graph generation
- [x] Results and conclusion
