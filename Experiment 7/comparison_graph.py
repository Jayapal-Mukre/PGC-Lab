import matplotlib.pyplot as plt
import numpy as np
metrics=["GPU Utilization (%)","Execution Time (s)","Throughput (batches/s)","Copy Time (ms)","Copy/Kernel Overlap (ms)","Idle Gap Time (ms)"]
baseline=[41.7,4.161,48.1,120.18,0,114.18]
optimized=[92.7,1.897,105.4,49.91,43.27,1.22]
x=np.arange(len(metrics)); width=.36
plt.figure(figsize=(13,7))
plt.bar(x-width/2,baseline,width,label="Baseline")
plt.bar(x+width/2,optimized,width,label="Optimized")
plt.title("Experiment 7: Baseline vs Optimized GPU Performance")
plt.xlabel("Performance Metrics");plt.ylabel("Measured Values (units shown in labels)")
plt.xticks(x,metrics,rotation=20,ha="right");plt.legend();plt.grid(axis="y",alpha=.3);plt.tight_layout()
plt.savefig("Experiment7_Comparison_Graph.png",dpi=300);plt.show()
