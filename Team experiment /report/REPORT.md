# Parallel Sum and Average of Dataset using OpenMP

## 1. Introduction

This project implements the calculation of the sum and average of a large dataset using both sequential and parallel approaches.

The parallel implementation uses OpenMP to divide the summation work among multiple threads.

The project compares execution time for different dataset sizes and different numbers of threads.

---

## 2. Problem Statement

Calculate the sum and average of a large dataset efficiently using multiple threads with OpenMP and analyze the performance improvement compared with the sequential implementation.

---

## 3. Objectives

- Implement a sequential sum and average algorithm.
- Implement a parallel version using OpenMP.
- Use multiple threads to perform the summation.
- Compare execution times for different dataset sizes.
- Analyze speedup and efficiency.
- Determine the best thread configuration for the tested system.

---

## 4. Technologies Used

- Programming Language: C
- Parallel Programming Model: OpenMP
- Compiler: GCC
- Operating System: Windows
- Version Control: GitHub

---

## 5. Sequential Algorithm

The sequential algorithm processes every element one by one.

### Steps

1. Allocate memory for the dataset.
2. Initialize the dataset.
3. Set `sum = 0`.
4. Traverse all elements.
5. Add each element to `sum`.
6. Calculate:

```text
Average = Sum / Number of Elements
