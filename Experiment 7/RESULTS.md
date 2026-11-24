# Experiment 7 Results

| Metric | Baseline | Optimized |
|---|---:|---:|
| Profile window | 217.66 ms | 99.05 ms |
| Kernel busy time | 90.77 ms | 91.83 ms |
| Busy/window | 41.7% | 92.7% |
| Copy time | 120.18 ms | 49.91 ms |
| Copy/kernel overlap | 0 ms | 43.27 ms |
| Idle gaps over 50 us | 9 | 9 |
| Total idle gap duration | 114.18 ms | 1.22 ms |

The ratio is kernel busy time divided by the profiled window, not an independently measured system-wide utilization value. Results reflect the provided trace analysis.
