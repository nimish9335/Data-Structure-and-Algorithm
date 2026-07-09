## What is Bitmask DP?

Bitmask DP is a technique for problems where the DP state depends on **which specific subset** of a small set of elements has been used, visited, or assigned — not just a count. Since a subset of N elements can be represented as an N-bit binary number, we use that integer directly as an array index: `dp[mask]`.

> Core idea: "the state I need to remember is really just N yes/no facts — pack them into the bits of an integer, and use that integer as the DP index."

## Prerequisite: Representing Sets as Bits

- A set of N elements → integer `mask` from `0` to `(1 << N) - 1`
- Bit `i` of `mask` = 1 means element `i` is included/used/visited
- `1 << i` — bitmask with only bit `i` set
- `mask | (1 << i)` — add element `i` to the set
- `mask & ~(1 << i)` — remove element `i` from the set
- `mask & (1 << i)` — check if element `i` is in the set
- `mask ^ (1 << i)` — toggle element `i`
- `__builtin_popcount(mask)` — count how many elements are in the set
- Full set = `(1 << N) - 1`

## When to Recognize This Pattern

Ask yourself:

1. Is there a small set of N items (N ≤ ~20)?
2. Does the answer/state depend on **which subset** of items has been processed, not just how many?
3. Would a normal `dp[i][j]...` state explode because you'd need to track an unbounded combination of choices?

If yes to all three → bitmask the state.

**Classic signals in problem statements:**
- `N ≤ 20` or `N ≤ 22` in constraints (huge hint)
- "assign N tasks to N slots/workers"
- "visit all cities" → Traveling Salesman Problem (TSP)
- "partition into groups" / "cover all elements with minimum sets"
- "count ways to fill a grid" → profile/broken profile DP
- "find shortest/cheapest way to include every item exactly once"

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

## Common Sub-Patterns

### 1. Sequential Assignment
Assign item `i` to the next available "slot," where slot number = `__builtin_popcount(mask)`. Used for assignment problems (minimize cost of assigning workers to tasks) and row-by-row placement problems.

### 2. TSP / Hamiltonian Path (`dp[mask][i]`)
State = (set of visited nodes, current node). `dp[mask][i]` = minimum cost to have visited exactly the nodes in `mask`, ending at node `i`. Transition tries moving to every unvisited neighbor.

### 3. Partition into Valid Groups
Cover all N elements using the minimum number of valid groups, where each group is itself a submask. Requires **submask enumeration**: `for (sub = mask; sub > 0; sub = (sub - 1) & mask)`. Always extend from the lowest uncovered bit to avoid overcounting.

### 4. Profile / Broken-Profile DP
Used for grid tiling, domino placement, counting perfect matchings. `mask` represents which cells along the current row/column boundary are filled; DP moves cell by cell or row by row.

### 5. Bitmask + Remainder DP
Combine a bitmask dimension with a modulo/remainder dimension: `dp[mask][rem]`, for problems with both a subset constraint and a numeric (divisibility/sum) constraint.

## Complexity Cheatsheet

| Pattern                            | Typical Complexity   |
|-------------------------------------|-----------------------|
| Simple `dp[mask]` transitions       | O(2^N * N)            |
| `dp[mask][i]` (TSP-style)           | O(2^N * N^2)          |
| Submask enumeration inside DP       | O(3^N)                |
| Bitmask + extra remainder/mod dim   | O(2^N * N * K)        |

## Debugging Checklist

- [ ] Confirm N is small enough (2^N states must be feasible — 2^20 ≈ 1M is fine)
- [ ] Initialize `dp[]` with a proper "unreachable" sentinel (INF or -1)
- [ ] Base case (`dp[0]` or equivalent) set correctly
- [ ] Iterate masks in increasing order if transitions only add bits, so `mask` is finalized before being used to update larger masks
- [ ] Final answer is at `dp[(1<<n) - 1]` (full mask), or wherever "everything accounted for" corresponds to
- [ ] Watch for overcounting in partition-style problems — enforce an ordering rule (e.g., always cover the lowest free bit next)
- [ ] Recursive (DFS + memo) and iterative versions should give the same answer — use one to sanity-check the other

## Learning Path (recommended order)

1. **Bitmask Basics** — bit operations: set/clear/toggle/check a bit, count set bits, iterate all subsets, iterate submasks.
2. **Subset Enumeration** — the O(3^N) trick to iterate all `(mask, submask)` pairs.
3. **State Compression DP** — the general `dp[mask] = ...` pattern.
4. **TSP Template / Hamiltonian Path** — classic instances of state compression DP (`dp[mask][i]`).
5. **Iterative Bitmask DP / DFS + Memoization** — bottom-up vs top-down implementations of the same DP.
6. **Remainder DP** — bitmask combined with a modulo/remainder dimension.
7. **Problems/** — apply everything above to real problems.

## See Also
Each subfolder has its own README with detailed notes for that specific sub-topic.