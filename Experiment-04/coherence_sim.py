#!/usr/bin/env python3
"""Two-core snooping-cache simulator for MSI, MESI and MOESI.

Two threads increment independent counters. In the adjacent layout both
counters occupy line A (false sharing); in the padded layout they occupy
separate lines A and B.
"""
import sys

def make_cores(n=2):
    return [dict() for _ in range(n)]

def access(proto, caches, core, line, op, stats):
    mine = caches[core]
    state = mine.get(line, "I")
    others = [i for i in range(len(caches)) if i != core]
    holders = [i for i in others if caches[i].get(line, "I") != "I"]

    if op == "R":
        if state != "I":
            return
        stats["BusRd"] += 1
        new_state = "S"
        for i in holders:
            other = caches[i][line]
            if other == "M":
                if proto == "MOESI":
                    caches[i][line] = "O"
                    stats["c2c"] += 1
                else:
                    caches[i][line] = "S"
                    stats["writeback"] += 1
            elif other == "O":
                stats["c2c"] += 1
            elif other == "E":
                caches[i][line] = "S"
        if not holders and proto in ("MESI", "MOESI"):
            new_state = "E"
        mine[line] = new_state
    else:
        if state == "M":
            return
        if state == "E":
            mine[line] = "M"
            stats["silent E->M"] += 1
            return
        if state in ("S", "O"):
            stats["BusUpgr"] += 1
        else:
            stats["BusRdX"] += 1
        for i in holders:
            other = caches[i][line]
            if other in ("M", "O"):
                if proto == "MOESI":
                    stats["c2c"] += 1
                else:
                    stats["writeback"] += 1
        for i in holders:
            caches[i][line] = "I"
            stats["invalidations"] += 1
        mine[line] = "M"

def run(proto, layout, iterations):
    keys = ["BusRd", "BusRdX", "BusUpgr", "silent E->M",
            "invalidations", "writeback", "c2c"]
    stats = dict.fromkeys(keys, 0)
    caches = make_cores()
    lx, ly = ("A", "A") if layout == "adjacent" else ("A", "B")
    log = []
    for _ in range(iterations):
        for core, line, op in ((0, lx, "R"), (0, lx, "W"),
                               (1, ly, "R"), (1, ly, "W")):
            access(proto, caches, core, line, op, stats)
            log.append((core, op, caches[0].get("A", "I"),
                        caches[1].get("A", "I")))
    stats["bus transactions"] = stats["BusRd"] + stats["BusRdX"] + stats["BusUpgr"]
    return stats, log

if __name__ == "__main__":
    iterations = int(sys.argv[1]) if len(sys.argv) > 1 else 1000
    print("State trace, first 2 iterations, adjacent layout (line A: C0 / C1)")
    for protocol in ("MSI", "MESI", "MOESI"):
        _, log = run(protocol, "adjacent", 2)
        print(f"\n{protocol}:")
        for core, op, c0, c1 in log[:8]:
            print(f" core{core} {op} -> C0={c0} C1={c1}")
    keys = ["bus transactions", "BusRd", "BusRdX", "BusUpgr",
            "invalidations", "writeback", "c2c", "silent E->M"]
    print(f"\nTotals for {iterations} iterations")
    print(f"{'layout':9} {'protocol':6} " + " ".join(f"{k:>16}" for k in keys))
    for layout in ("adjacent", "padded"):
        for protocol in ("MSI", "MESI", "MOESI"):
            stats, _ = run(protocol, layout, iterations)
            print(f"{layout:9} {protocol:6} " +
                  " ".join(f"{stats[k]:16}" for k in keys))
