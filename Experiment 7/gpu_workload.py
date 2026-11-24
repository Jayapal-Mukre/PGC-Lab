"""
Experiment 7: Profiling and GPU Utilization
Baseline and optimized GPU workloads
"""
import argparse
import math
import time
import torch

def make_weights(n):
    g = torch.Generator().manual_seed(1)
    return (torch.randn(n, n, generator=g) / math.sqrt(n)).cuda()

def make_host_batches(rows, cols, pinned, unique=4):
    g = torch.Generator().manual_seed(0)
    batches = []
    for _ in range(unique):
        t = torch.randn(rows, cols, generator=g)
        batches.append(t.pin_memory() if pinned else t)
    return batches

def compute(x, w, reps):
    y = x
    for _ in range(reps):
        y = y @ w
        y = torch.relu(y)
        y = y.mul_(0.5).add_(1.0)
    return y.sum(dim=1)

def run_baseline(host, w, reps, nbatches):
    results = []
    for i in range(nbatches):
        x = host[i % len(host)].cuda()
        r = compute(x, w, reps)
        results.append(r.cpu())
    torch.cuda.synchronize()
    return torch.stack(results)

def run_optimized(host, w, reps, nbatches):
    rows, cols = host[0].shape
    copy_s = torch.cuda.Stream()
    comp_s = torch.cuda.Stream()
    buf = [torch.empty(rows, cols, device="cuda") for _ in range(2)]
    copied = [torch.cuda.Event() for _ in range(2)]
    freed = [torch.cuda.Event() for _ in range(2)]
    out_host = torch.empty(nbatches, rows).pin_memory()
    torch.cuda.synchronize()
    for e in freed:
        e.record(comp_s)
    def issue_copy(i):
        k = i % 2
        copy_s.wait_event(freed[k])
        with torch.cuda.stream(copy_s):
            buf[k].copy_(host[i % len(host)], non_blocking=True)
            copied[k].record(copy_s)
    issue_copy(0)
    for i in range(nbatches):
        k = i % 2
        if i + 1 < nbatches:
            issue_copy(i + 1)
        comp_s.wait_event(copied[k])
        with torch.cuda.stream(comp_s):
            r = compute(buf[k], w, reps)
            out_host[i].copy_(r, non_blocking=True)
            freed[k].record(comp_s)
    torch.cuda.synchronize()
    return out_host

def main():
    p = argparse.ArgumentParser()
    p.add_argument("--mode", choices=["baseline", "optimized"], required=True)
    p.add_argument("--batches", type=int, default=200)
    p.add_argument("--rows", type=int, default=16384)
    p.add_argument("--cols", type=int, default=1024)
    p.add_argument("--reps", type=int, default=3)
    p.add_argument("--profile", action="store_true")
    p.add_argument("--profile-batches", type=int, default=10)
    a = p.parse_args()
    if not torch.cuda.is_available():
        raise SystemExit("CUDA GPU not available.")
    pinned = a.mode == "optimized"
    fn = run_optimized if pinned else run_baseline
    host = make_host_batches(a.rows, a.cols, pinned)
    w = make_weights(a.cols)
    print(f"GPU       : {torch.cuda.get_device_name(0)}")
    print(f"Mode      : {a.mode}")
    print(f"Batch size: {a.rows * a.cols * 4 / 1e6:.0f} MB")
    fn(host, w, a.reps, 3)
    torch.cuda.synchronize()
    t0 = time.perf_counter()
    res = fn(host, w, a.reps, a.batches)
    torch.cuda.synchronize()
    dt = time.perf_counter() - t0
    print(f"Batches    : {a.batches}")
    print(f"Total time : {dt:.3f} s")
    print(f"Per batch  : {dt / a.batches * 1000:.2f} ms")
    print(f"Throughput : {a.batches / dt:.1f} batches/s")
    print(f"Checksum   : {res.double().sum().item():.6e}")
    if a.profile:
        from torch.profiler import profile, ProfilerActivity
        with profile(activities=[ProfilerActivity.CPU, ProfilerActivity.CUDA]) as prof:
            fn(host, w, a.reps, a.profile_batches)
            torch.cuda.synchronize()
        name = f"trace_{a.mode}.json"
        prof.export_chrome_trace(name)
        print(f"\nTrace saved: {name}")
        print(prof.key_averages().table(sort_by="cuda_time_total", row_limit=10))

if __name__ == "__main__":
    main()
