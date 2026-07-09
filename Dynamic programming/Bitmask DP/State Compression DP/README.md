# State Compression DP

## Concept

State Compression DP (a.k.a. **Bitmask DP** at the "state" level, not just
subset-enumeration level) is used when:

- You have **N small elements** (usually N ≤ 20, sometimes up to 22–24)
- The DP state needs to remember **which combination** of these elements
  has been used, visited, assigned, or covered so far
- That combination can be represented as a **binary string of length N**,
  so we compress it into a single integer `mask` (0 to 2^N - 1)

> Think of it as: "the state I need to remember is too big for a normal
> array index, but it's really just N yes/no facts — so pack them into bits
> of an integer and use that integer as the DP index."

This builds directly on **Bitmask Basics** (representing sets as bits) and
**Subset Enumeration** (iterating submasks) — State Compression DP is the
application of those tools to actual optimization/counting problems.

---

## When to Recognize This Pattern

Ask yourself:

1. Is there a small set of N items (N ≤ ~20)?
2. Does the answer/state depend on **which subset** of items has been
   processed, not just *how many*?
3. Does a naive DP state like `dp[i][j]...` explode because you'd need to
   track an unbounded combination of choices?

If yes to all three → bitmask the state.

**Classic signals in problem statements:**
- "N ≤ 20" or "N ≤ 22" in constraints (huge hint!)
- "assign N tasks to N slots"
- "partition into groups"
- "visit all cities" (→ TSP, already covered)
- "cover all elements with minimum sets"
- "count ways to fill a grid" (profile/broken profile DP)

---

## Core Template Shape

```cpp
dp[mask] = best/count value achievable when the set of "done" items = mask

dp[0] = base case (nothing done yet)

for mask in 0 .. (1<<n)-1:
    if dp[mask] is not reachable: continue
    for each item i not in mask:
        newMask = mask | (1 << i)
        dp[newMask] = combine(dp[newMask], dp[mask] + cost(i, mask))

answer = dp[(1<<n) - 1]   // all items done
```

**Complexity:** O(2^N * N) for simple transitions, O(2^N * N^2) if the
transition itself scans over items, or O(3^N) if you enumerate submasks
inside every mask (see Pattern 2 below — comes from Subset Enumeration).

---

## Common Patterns (see `State Compression DP.cpp`)

### Pattern 1 — Sequential Assignment
Assign item `i` to the next available "slot" (slot number = popcount of
mask, i.e., how many items already assigned). Used for:
- Assignment problem (assign workers to tasks, minimize cost)
- "Place N non-attacking queens/rooks row by row" style problems

Key trick: **slot index = `__builtin_popcount(mask)`** — you don't need to
store the slot separately, it's derivable from the mask itself.

### Pattern 2 — Partition into Valid Groups
Cover all N elements using the minimum number of valid groups (each group
is itself a submask). Uses **submask enumeration** (`for sub = mask; sub>0; sub=(sub-1)&mask`)
inside the DP transition — this is why Subset Enumeration is a prerequisite.

Key trick: always extend from the **lowest uncovered bit** — this avoids
counting the same partition multiple times and dramatically prunes states.

### Pattern 3 — Row-by-Row / Profile DP
Used for grid tiling / domino placement / counting matchings. State =
bitmask of "which cells in the current row/column are filled." Transition
moves row by row, and mask represents a "profile" (boundary) between
processed and unprocessed cells.

---

## Debugging Checklist

- [ ] Confirm N is small enough (2^N states must be feasible — 2^20 ≈ 1M, fine)
- [ ] Initialize `dp[]` with a proper "unreachable" sentinel (INF or -1)
- [ ] Base case `dp[0]` (or whatever the empty state is) set correctly
- [ ] Iterate masks in increasing order if transitions only ADD bits
      (guarantees `mask` is finalized before you use it to update larger masks)
- [ ] Final answer is at `dp[(1<<n) - 1]` (full mask) — or wherever
      "everything accounted for" corresponds to
- [ ] Watch for **overcounting** in partition-style problems — enforce an
      ordering rule (e.g., always cover lowest free bit next)

---

## Related Notes in This Repo
- `Bitmask Basics/` — how to represent/manipulate sets as integers
- `Generic Templates/Subset Enumeration.cpp` — iterating all submasks of a mask (O(3^N) trick)
- `Generic Templates/TSP Template.cpp` — a specific, very common instance of state compression DP
- `Generic Templates/DFS + Memoization.cpp` — alternative (recursive) way to write the same DP
