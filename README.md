# Parallel and GPU Computing Lab

This repository contains the laboratory programs, experiments, and implementations completed as part of the Parallel and GPU Computing Laboratory.

## Student Information

| Details | Information |
| :--- | :--- |
| **Name** | Jayapal Mukre |
| **Course** | Computer Science and Engineering (AI) |
| **Semester** | 5th Semester |
| **Institution** | KLE Technological University, Hubballi |
| **Academic Year** | 2026–27 |

---

## Experiments

| No. | Experiment | Description |
| :--- | :--- | :--- |
| **01** | **Experiment 1** | Parallel Matrix Multiplication (Sequential, OpenMP, MPI, and CUDA)|
| **02** | **Experiment 2** | |
| **03** | **Experiment 3** |  |
| **04** | **Experiment 4** | |
| **05** | **Experiment 5** | |
| **06** | **Experiment 6** | |
| **07** | **Experiment 7** |  |
| **08** | **Experiment 8** | |

*Experiment details will be updated as the laboratory work progresses.*

---

## Detailed Experiment 1: Matrix Multiplication Implementation

Experiment 1 implements a 4000 × 4000 matrix multiplication problem across four distinct computing models using matrices initialized with elements equal to $1.0$, resulting in an expected verification value of $C[0][0] = 4000.00$.

### 1. Part A - Sequential Matrix Multiplication (Baseline)
* **Environment:** Windows PowerShell launching WSL2 Ubuntu.
* **Compilation:** `gcc -O2 matrix_sequential.c -o matrix_sequential`
* **Execution Time:** $244.120000$ seconds
* **Verification:** $C[0][0] = 4000.00$

### 2. Part B - OpenMP Matrix Multiplication (Shared Memory)
* **Environment:** WSL2 Ubuntu with 8 logical CPUs (`export OMP_NUM_THREADS=8`)
* **Compilation:** `gcc -O2 -fopenmp matrix_openmp.c -o matrix_openmp`
* **Execution Time:** $30.830434$ seconds
* **Speedup:** $7.92\times$ over sequential

### 3. Part C - MPI Distributed Matrix Multiplication
* **Environment:** A virtual cluster consisting of 1 Master VM and 3 Worker VMs connected via VMware virtual networking
* **Compilation & Execution:** Managed via `mpicc` and `mpirun` across nodes using process-level row distribution (`MPI_Scatter`, `MPI_Bcast`, `MPI_Gather`)
* **Execution Time:** $92.979510$ seconds
* **Speedup:** $2.63\times$ over sequential

### 4. Part D - CUDA Matrix Multiplication (GPU Acceleration)

### Summary Performance Table

| Implementation | Model | Resources | Execution Time | Speedup | Verification |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Sequential** | Single CPU execution[span_18](start_span)[span_18](end_span) | 1 CPU core[span_19](start_span)[span_19](end_span) | $244.120000\text{ s}$[span_20](start_span)[span_20](end_span) | $1.00\times$[span_21](start_span)[span_21](end_span) | $4000.00$| **OpenMP** | Shared memory[span_23](start_span)[span_23](end_span) | 8 CPU threads[span_24](start_span)[span_24](end_span) | $30.830434\text{ s}$[span_25](start_span)[span_25](end_span) | $7.92\times$[span_26](start_span)[span_26](end_span) | $4000.00$[span_27](start_span)[span_27](end_span) |
| **MPI** | Distributed memory[span_28](start_span)[span_28](end_span) | 4 processes / 4 VMs[span_29](start_span)[span_29](end_span) | $92.979510\text{ s}$[span_30](start_span)[span_30](end_span) | $2.63\times$[span_31](start_span)[span_31](end_span) | $4000.00$[span_32](start_span)[span_32](end_span) |
| **CUDA** | 
---

## Topics Covered

* Parallel Computing[span_38](start_span)[span_38](end_span)
* GPU Computing[span_39](start_span)[span_39](end_span)
* Multithreading
* Parallel Algorithms
* CUDA Programming[span_40](start_span)[span_40](end_span)
* CPU vs GPU Performance[span_41](start_span)[span_41](end_span)
* Parallel Processing
* Performance Analysis[span_42](start_span)[span_42](end_span)
* Speedup and Efficiency[span_43](start_span)[span_43](end_span)

---

## Technologies Used

* C[span_44](start_span)[span_44](end_span)
* C++[span_45](start_span)[span_45](end_span)
* Python
* CUDA[span_46](start_span)[span_46](end_span)
* OpenMP[span_47](start_span)[span_47](end_span)
* NVIDIA GPU Computing[span_48](start_span)[span_48](end_span)

---

## Repository Structure

```text
PGC-Lab/
│
├── Experiment-01/
│   ├── sequential/
│   ├── openmp/
│   ├── mpi/
│   └── cuda/
├── Experiment-02/
├── Experiment-03/
├── Experiment-04/
├── Experiment-05/
├── Experiment-06/
├── Experiment-07/
├── Experiment-08/
│
└── README.md
