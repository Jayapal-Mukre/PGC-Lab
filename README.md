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
| **01** | **Experiment 1** | Parallel Matrix Multiplication (Sequential, OpenMP, MPI, and CUDA) |
| **02** | **Experiment 2** | Parallel Computing |
| **03** | **Experiment 3** | Parallel Computing |
| **04** | **Experiment 4** | GPU Computing |
| **05** | **Experiment 5** | GPU Computing |
| **06** | **Experiment 6** | GPU Computing |
| **07** | **Experiment 7** | GPU Computing |
| **08** | **Experiment 8** | GPU Computing |

*Experiment details will be updated as the laboratory work progresses.*

---

## Detailed Experiment 1: Matrix Multiplication Implementation

Experiment 1 implements a 4000 × 4000 matrix multiplication problem across four distinct computing models using matrices initialized with elements equal to 1.0, resulting in an expected verification value of C[0][0] = 4000.00.

### 1. Part A - Sequential Matrix Multiplication (Baseline)
* **Environment:** Windows PowerShell launching WSL2 Ubuntu.
* **Compilation:** `gcc -O2 matrix_sequential.c -o matrix_sequential`
* **Execution Time:** 244.120000 seconds
* **Verification:** C[0][0] = 4000.00

### 2. Part B - OpenMP Matrix Multiplication (Shared Memory)
* **Environment:** WSL2 Ubuntu with 8 logical CPUs (`export OMP_NUM_THREADS=8`).
* **Compilation:** `gcc -O2 -fopenmp matrix_openmp.c -o matrix_openmp`
* **Execution Time:** 30.830434 seconds
* **Speedup:** 7.92× over sequential

### 3. Part C - MPI Distributed Matrix Multiplication
* **Environment:** A virtual cluster consisting of 1 Master VM and 3 Worker VMs connected via VMware virtual networking.
* **Compilation & Execution:** Managed via `mpicc` and `mpirun` across nodes using process-level row distribution (`MPI_Scatter`, `MPI_Bcast`, `MPI_Gather`).
* **Execution Time:** 92.979510 seconds
* **Speedup:** 2.63× over sequential

### 4. Part D - CUDA Matrix Multiplication (GPU Acceleration)

### Summary Performance Table

| Implementation | Model | Resources | Execution Time | Speedup | Verification |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Sequential** | Single CPU execution | 1 CPU core | 244.120000 s | 1.00× | 4000.00 |
| **OpenMP** | Shared memory | 8 CPU threads | 30.830434 s | 7.92× | 4000.00 |
| **MPI** | Distributed memory | 4 processes / 4 VMs | 92.979510 s | 2.63× | 4000.00 |
| **CUDA** |

---

## Topics Covered

* Parallel Computing
* GPU Computing
* Multithreading
* Parallel Algorithms
* CUDA Programming
* CPU vs GPU Performance
* Parallel Processing
* Performance Analysis
* Speedup and Efficiency

---

## Technologies Used

* C
* C++
* Python
* CUDA
* OpenMP
* NVIDIA GPU Computing

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
