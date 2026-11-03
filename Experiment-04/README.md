# Experiment 4 – Cache Coherence (MSI, MESI, MOESI) and NUMA Performance

## Objective
Study how MSI, MESI and MOESI cache-coherence protocols maintain consistency, demonstrate false sharing, and measure local versus remote NUMA memory access.

## Environment
- VMware Workstation with Ubuntu 22.04 LTS
- GCC with OpenMP support
- Python 3
- `numactl` and `hwloc`

Install the tools:
```bash
sudo apt update
sudo apt install build-essential numactl hwloc python3 -y
```

Check CPU and NUMA topology:
```bash
lscpu | grep -E "Socket|Core|Thread|NUMA"
numactl --hardware
lscpu -e
```

> **VM note:** The supplied screenshots show one NUMA node (node 0). Therefore, a true remote-node test with `--membind=1` is not available in this VM. The local NUMA results are valid for this environment; remote NUMA performance must be measured on a system exposing at least two NUMA nodes.

## Files
| File | Description |
|---|---|
| `coherence_sim.py` | Simulates MSI, MESI and MOESI for adjacent and padded counters |
| `false_sharing.c` | Compares adjacent and cache-line-padded counters |
| `numa_sweep.c` | Reads a memory buffer to measure NUMA placement effects |
| `compare_numa.c` | Combined false-sharing and memory-sweep benchmark |
| `screenshots/` | Lab terminal evidence supplied with the experiment |

## 1. Cache coherence protocol simulator
Run:
```bash
python3 coherence_sim.py 1000
```
The simulator models two cores and reports cache-line states and transaction counts for MSI, MESI and MOESI.

## 2. False sharing test
Compile:
```bash
gcc -O2 false_sharing.c -fopenmp -o false_sharing
```
Run:
```bash
OMP_NUM_THREADS=2 ./false_sharing adjacent
OMP_NUM_THREADS=2 ./false_sharing padded
``
Adjacent counters share a 64-byte cache line. Padded counters are separated by 64 bytes to reduce cache-line bouncing.

## 3. NUMA memory sweep
Compile:
```bash
gcc -O2 numa_sweep.c -fopenmp -o numa_sweep
``
Run with node IDs reported by `numactl --hardware`:
```bash
OMP_NUM_THREADS=2 numactl --cpunodebind=0 --membind=0 ./numa_sweep
# Only on a machine with node 1:
OMP_NUM_THREADS=2 numactl --cpunodebind=0 --membind=1 ./numa_sweep
``

## 4. Combined benchmark
Compile and run:
```bash
gcc -O2 compare_numa.c -fopenmp -o compare_numa
./compare_numa
numactl --cpunodebind=0 --membind=0 ./compare_numa
``
Run each configuration three times and compare median timings when preparing a formal report.

## Results from the supplied terminal screenshots

### Protocol simulator (1000 iterations)
| Layout | Protocol | Bus transactions | BusRd | BusUpgr | Invalidations | Write-backs | Cache-to-cache | Silent E→M |
|---|---|---:|---:|---:|---:|---:|---:|---:|
| Adjacent | MSI | 4000 | 2000 | 2000 | 1999 | 1999 | 0 | 0 |
| Adjacent | MESI | 3999 | 2000 | 1999 | 1999 | 1999 | 0 | 1 |
| Adjacent | MOESI | 3999 | 2000 | 1999 | 1999 | 0 | 1999 | 1 |
| Padded | MSI | 4 | 2 | 2 | 0 | 0 | 0 | 0 |
| Padded | MESI | 2 | 2 | 0 | 0 | 0 | 0 | 2 |
| Padded | MOESI | 2 | 2 | 0 | 0 | 0 | 0 | 2 |

### False-sharing / NUMA benchmark
The supplied terminal captures show all measured false-sharing counter totals as **100,000,000 (Correct)**. Recorded timings vary by run and VM load. One captured run reported:
| Layout | Threads | Final count | Time (s) |
|---|---:|---:|---:|
| Adjacent | 1 | 100,000,000 | 0.4067 |
| Padded | 1 | 100,000,000 | 0.4056 |
| Adjacent | 2 | 100,000,000 | 0.5073 |

The screenshots also show local-node NUMA runs on node 0. A remote-node result is not claimed because the VM reports only one available NUMA node.

## Observations
- MSI requires an upgrade transaction when a shared line is written.
- MESI can transition from Exclusive to Modified without a bus transaction.
- MOESI can retain a dirty line in Owned state and supply it to another cache, avoiding a memory write-back.
- False sharing occurs when independent variables share a cache line; padding reduces unnecessary coherence traffic.
- NUMA local/remote comparisons are meaningful only when at least two NUMA nodes are available.

## Conclusion
The simulation illustrates the transaction differences between MSI, MESI and MOESI. The counter benchmark demonstrates that cache-line placement affects performance even when threads update separate variables. NUMA placement can also affect memory-bound workloads, but this VM exposes only one NUMA node, so a genuine remote-memory comparison requires suitable multi-node hardware.

## Evidence
Terminal screenshots are organized in the `screenshots` subfolder. Refer to them for the simulator output, compilation/run steps, counter benchmark and NUMA topology.
