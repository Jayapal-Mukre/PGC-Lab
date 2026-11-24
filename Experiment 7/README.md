# Experiment 7 — Profiling and GPU Utilization

This folder contains the GPU profiling workload, baseline and optimized traces, monitoring logs, analysis script, comparison graph, and lab manual.

## Objective
Profile a CUDA workload and compare baseline execution with an optimized version using pinned host memory, asynchronous transfers, and separate CUDA streams to overlap data movement and computation.

## Workload
`gpu_workload.py` performs matrix multiplication, ReLU, scale/add, and row-wise reduction. Baseline uses pageable host memory and sequential processing. Optimized mode uses pinned host batches, two CUDA streams, alternating GPU buffers, and CUDA events to coordinate buffer reuse and transfers.

## Contents
- `gpu_workload.py` — workload and modes, optional trace export.
- `analyze_trace.py` — Chrome trace analysis of kernels, copies, overlap, and idle gaps.
- `comparison_graph.py` — comparison graph generation.
- `Experiment7_Comparison_Graph.png` — experiment comparison graphic.
- `trace_baseline.json`, `trace_optimized.json` — profiler traces.
- `smi_baseline.csv`, `smi_optimized.csv` — GPU monitoring logs.
- `Experiment7_Manual.pdf` — lab manual/reference.

## Reproducing
Requires Python, PyTorch with CUDA support, and an NVIDIA GPU.

```bash
python gpu_workload.py --mode baseline --profile
python gpu_workload.py --mode optimized --profile
python analyze_trace.py trace_baseline.json trace_optimized.json
python comparison_graph.py
```
Defaults: 200 batches, 16,384 rows, 1,024 columns, 3 repetitions; profiling defaults to 10 batches.

## Recorded Trace Comparison
| Metric | Baseline | Optimized |
|---|---:|---:|
| Profile window | 217.66 ms | 99.05 ms |
| Kernel busy time | 90.77 ms | 91.83 ms |
| Kernel busy/window | 41.7% | 92.7% |
| Copy time | 120.18 ms | 49.91 ms |
| Copy overlapped with kernels | 0.00 ms | 43.27 ms |
| Idle gaps over 50 us | 9 | 9 |
| Total idle-gap duration | 114.18 ms | 1.22 ms |

These values were calculated from the included traces using `analyze_trace.py`. The busy/window ratio is the script's kernel-busy-time-to-window metric, not independently measured whole-device utilization.

