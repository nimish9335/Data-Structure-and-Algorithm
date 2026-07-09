# DFS + Memoization (Top-Down Bitmask DP)

## 📌 Core Idea

Bitmask DP is used when you need to track **which subset of items/elements
have been used/visited/chosen so far**, and the number of elements `n` is
small (usually `n ≤ 20`, since `2^20 ≈ 10^6`).

Instead of tracking state as a list/set (slow, hard to hash), we compress
the subset into a single integer called a **mask**, where:

- Bit `i` = `1` → element `i` is **included/used/visited**
- Bit `i` = `0` → element `i` is **not yet used**

Example: for `n = 4` elements, `mask = 0b1010` (=10) means elements
**1 and 3** are used (0-indexed from right), elements 0 and 2 are not.

## 🔑 Why Bitmask Instead of Normal DP?

Normal DP state is usually `dp[i]` or `dp[i][j]` — a small number of
dimensions. But problems like:

- "Visit all cities with minimum cost" (TSP)
- "Assign all jobs to workers with minimum cost"
- "Find shortest path that visits every node"

...need the state **"which exact elements have I used so far"** — not just
*how many*. A count isn't enough because *which specific ones* matters for
future transitions. So we need `dp[mask]` where mask encodes the exact
subset.

## 🧠 Why DFS + Memoization (Top-Down) First?

This is the **easiest way to start with bitmask DP** because:

1. You write it like normal recursion (brute force), then just add memo.
2. You don't need to worry about **processing order of masks** (unlike
   bottom-up, where you must go from smaller mask to larger mask).
3. Only *reachable* states get computed — can be faster in practice when
   not all `2^n` masks are actually visited.

## 🏗️ General Recipe (memorize this!)

```
dfs(mask, extra...):
    if mask == full_mask:
        return base_case_value

    if memo[mask][extra] exists:
        return memo[mask][extra]

    ans = identity_value   // 0 for sum, INF for min, -INF for max, etc.

    for each element i not in mask:
        newMask = mask | (1 << i)
        result  = transition_cost(i) + dfs(newMask, new_extra)
        ans = combine(ans, result)   // min()/max()/sum()/etc.

    return memo[mask][extra] = ans
```

## 🔧 Key Bit Tricks Used Here

| Operation | Meaning | Code |
|---|---|---|
| Check if bit `i` is set | is element `i` used? | `mask & (1 << i)` |
| Set bit `i` | mark element `i` as used | `mask \| (1 << i)` |
| Clear bit `i` | mark element `i` as unused | `mask & ~(1 << i)` |
| Toggle bit `i` | flip usage of element `i` | `mask ^ (1 << i)` |
| Full mask (all `n` bits set) | everyone used | `(1 << n) - 1` |
| Count set bits | how many elements used | `__builtin_popcount(mask)` |
| Lowest set bit | smallest unused/used index trick | `mask & (-mask)` |

## 📂 File in This Folder

- **`DFS + Memoization.cpp`** — Generic top-down template solved on the
  classic **TSP-style problem** (minimum cost to visit all nodes and
  return to start). Structured with comments so you can copy-paste and
  adapt the transition logic to your own problem (job assignment,
  Hamiltonian path, subset sum with visited state, etc.)

## ✅ Complexity Cheatsheet

- **States**: `2^n * (extra state size)`
- **Transition**: usually `O(n)` (looping over next element to add)
- **Total**: `O(2^n * n * extra_states)`
- This is why `n` is capped around 15–20 in most problems — `2^20 * 20`
  is already ~20 million, near the practical limit for 1-2 sec time limits.

## 🔗 How This Connects to Other Folders

- **Iterative Bitmask DP.cpp** → Same idea, but bottom-up (loop over
  masks in increasing order instead of recursion). Use once you're
  comfortable with this template — it's usually faster (no recursion
  overhead) but harder to write from scratch.
- **Hamiltonian Path.cpp** → Direct application: `dp[mask][pos]` = can
  we reach `pos` having visited exactly the nodes in `mask`.
- **TSP Template.cpp** → This exact template extended for the full TSP
  (with actual path reconstruction).
- **Subset Enumeration.cpp** → Helper technique to loop over all subsets
  of a given mask (used in bitmask DP over subsets, like SOS DP).

## 🎯 Practice Strategy

1. Read this template fully, run it on paper for `n = 3` or `n = 4`.
2. Draw the recursion tree for a small mask by hand.
3. Try re-deriving it WITHOUT looking, for a new problem (e.g. "minimum
   cost to assign N tasks to N workers").
4. Once comfortable, convert it to iterative form (see next file).


# Iterative Bitmask DP (Bottom-Up)

## 📌 Core Idea

This is the bottom-up sibling of "DFS + Memoization". Instead of
recursion pulling an answer backward from a full mask, we push
forward: starting from the base case, we build up dp[mask] for
increasing masks until we reach the full mask.

## 🔑 Why Order Matters

`dp[mask]` depends only on smaller masks (masks with fewer bits set,
or more precisely masks that are numerically smaller since we only
ever *add* bits). So iterating `mask` from `0` to `(1<<n)-1` in a
simple for loop guarantees every dependency is already computed.

This is the single most important rule in iterative bitmask DP:
**you can never use a mask before all its "sub-masks" are ready.**

## 🧠 Top-Down vs Bottom-Up — Mental Model Shift

| | Top-Down (DFS+Memo) | Bottom-Up (Iterative) |
|---|---|---|
| Direction | "From here, how do I finish?" | "Having gotten here, what's best so far?" |
| Starting point | Full/end state | Base/start state |
| Order handled by | Recursion + memo | Manual mask loop (increasing order) |
| Risk | Stack overflow for large n | None |
| Speed | Slightly slower (function calls) | Slightly faster |
| Ease of first-write | Easier | Harder (must flip the direction of thinking) |

## 🏗️ General Recipe

## 🔧 Key Bit Tricks Used

Same as DFS+Memo file — see that README for the full table
(`mask & (1<<i)` to check, `mask | (1<<i)` to set, `(1<<n)-1` for full
mask, `__builtin_popcount(mask)` to count bits).

## ✅ Complexity

- States: `2^n * n`
- Transition: `O(n)` per state
- Total: `O(2^n * n^2)` — same asymptotic complexity as top-down,
  but no recursion overhead in practice.

## 🔗 Connection to Other Files

- **DFS + Memoization.cpp** → Same exact problem, opposite direction
  of thinking. Compare both side-by-side to internalize top-down vs
  bottom-up.
- **TSP Template.cpp** → This file IS essentially the TSP core; that
  file extends it with path reconstruction.
- **Hamiltonian Path.cpp** → Uses this exact `dp[mask][pos]` shape,
  just checks *reachability* (boolean) instead of *minimum cost*.

## 🎯 Practice Strategy

1. Trace through `dp` table by hand for `n = 3`.
2. Notice: `dp[mask][pos]` is only meaningful if bit `pos` is set in
   `mask` — this is a common bug source, always guard for it.
3. Try converting your own top-down solution into this bottom-up form
   as an exercise — it's the best way to truly understand mask ordering.


# Hamiltonian Path — Bitmask DP

## 📌 Problem Statement

Given a graph of `n` nodes, does a path exist that visits **every
node exactly once**? (No requirement to return to the start — that
would be a Hamiltonian **Cycle**, which is what TSP essentially checks
for, but with costs.)

## 🔑 Core Insight

This reuses the **exact same `dp[mask][pos]` shape** you saw in the
TSP/Iterative Bitmask DP file — but the *meaning* of the stored value
changes:

| File | dp[mask][pos] stores... |
|---|---|
| TSP / Iterative Bitmask DP | Minimum **cost** to reach `pos` visiting exactly `mask` |
| Hamiltonian Path (this file) | **Whether it's possible** (true/false) to reach `pos` visiting exactly `mask` |

This is the biggest lesson of bitmask DP: **the state definition
(mask + extra) stays the same across many problems — only the
payload and combine-operation change** (min → boolean OR, min → count,
etc.)

## 🧠 Why This Works

- `mask` = which nodes have been visited so far (order doesn't matter,
  only the set matters).
- `pos` = where the path currently ends (this matters because future
  moves depend on which neighbors `pos` has).
- Base case: every single node alone is trivially a valid "path of
  length 1".
- Transition: extend the path by moving to an unvisited neighbor.
- Final check: is there ANY `pos` such that `dp[FULL][pos]` is true?
  (Full mask = all nodes visited.)

## 🔧 Bit Tricks Used

Same core set as previous files:
- `mask & (1 << pos)` → is `pos` part of this mask?
- `mask | (1 << next)` → mark `next` as visited
- `(1 << n) - 1` → full mask (all nodes visited)
- `1 << i` → base case mask for starting at node `i` alone

## ✅ Complexity

- States: `2^n * n`
- Transition: `O(n)` per state (loop over possible next node)
- Total: `O(2^n * n^2)`
- Space: `O(2^n * n)` (can be optimized to `O(2^n)` per mask if you
  process one mask fully before moving to next, using bitset tricks —
  advanced optimization, not needed for typical constraints).

## 🔗 Connection to Other Files

- **Iterative Bitmask DP.cpp** → Nearly identical dp table shape;
  compare the transition line: `min(...)` there vs `= true` here.
- **DFS + Memoization.cpp** → You could equally solve this top-down;
  try rewriting it yourself as practice (recursion + memo of booleans).
- **TSP Template.cpp** → Hamiltonian Cycle = Hamiltonian Path + edge
  back to start. TSP = Hamiltonian Cycle + minimizing total cost.

## 🎯 Practice Strategy

1. Draw a small graph (4-5 nodes) on paper, manually trace `dp[mask][pos]`
   for a few masks.
2. Modify this template to count paths instead of just checking
   existence (see "Variations" comment block in the code).
3. Try the Hamiltonian Cycle variant as your own exercise before
   looking at the TSP Template file.


# Travelling Salesman Problem (TSP) — Bitmask DP

## 📌 Problem Statement

Given `n` cities and `cost[i][j]` (cost to travel from city `i` to
city `j`), find the **minimum cost tour** that visits every city
exactly once and returns to the starting city.

This is the "boss level" of the templates you've seen so far — it
combines:
- The `dp[mask][pos]` = minimum cost shape from **Iterative Bitmask DP**
- The "visit-all-nodes" idea from **Hamiltonian Path**
- Plus a NEW concept: **reconstructing the actual optimal path**,
  not just its cost.

## 🔑 Why TSP Needs Bitmask DP (and not simpler DP)

Brute force would try all `(n-1)!` permutations of city orders —
way too slow even for `n = 15`. Bitmask DP reduces this to
`O(2^n * n^2)` by realizing:

> To know the best way to finish a tour, you don't need to remember
> the exact ORDER of cities visited — only WHICH cities have been
> visited (the set) and WHERE you currently are.

This is the key insight of all bitmask DP: **compress "history" down
to just "the relevant summary of history"** (here: set of visited
nodes + current position).

## 🧠 New Concept: Path Reconstruction

Until now, our templates only computed the *optimal value* (minimum
cost, boolean existence). This file shows how to recover the
**actual sequence of decisions** using a `parent[mask][pos]` table:

1. Whenever you improve `dp[newMask][next]`, also store
   `parent[newMask][next] = pos` (where you came from).
2. After the DP finishes, walk backward from the final state,
   using `parent` to know the previous state, and remove the
   current bit from mask as you go back (`mask ^ (1 << pos)`).
3. Reverse the collected sequence — you now have the path in
   correct forward order.

**This backtracking trick isn't just for bitmask DP** — it's a
general technique for recovering an optimal path/decision sequence
in *any* DP (LCS, knapsack, edit distance, etc.) Learn it once,
reuse everywhere.

## 🔧 Bit Tricks Used

- `mask & (1 << pos)` → check membership
- `mask | (1 << next)` → add city to visited set
- `mask ^ (1 << pos)` → **remove** city from visited set (used only
  during backtracking, to "undo" a visit when walking backward)
- `(1 << n) - 1` → full mask

## ✅ Complexity

- Time: `O(2^n * n^2)`
- Space: `O(2^n * n)` for both `dp` and `parent` tables
- Practical limit: `n ≤ 18-20` depending on time limit

## 🔗 Connection to Other Files

- **Iterative Bitmask DP.cpp** → This file IS that file, extended
  with `parent[][]` for path reconstruction.
- **Hamiltonian Path.cpp** → TSP = Hamiltonian Cycle + minimizing
  cost. If you skip `cost[pos][0]` at the end and only need existence,
  you're back to Hamiltonian Path/Cycle.
- **DFS + Memoization.cpp** → Same TSP problem, solved top-down. Try
  adding path reconstruction to THAT version too as practice (hint:
  you'd store the best 'next' choice at each memoized state).

## 🎯 Practice Strategy

1. Run this on a 4-5 city example, manually verify the printed path
   matches a route you can confirm cheapest by inspection.
2. Extend it to NOT return to start (Hamiltonian Path version) —
   remove `+ cost[pos][0]` from the final answer computation.
3. Try adapting this exact template to a **job assignment problem**
   (n workers, n jobs, cost[worker][job]) — the code structure barely
   changes, just the semantic meaning of "city" becomes "job".


# Subset Enumeration (Submask Iteration)

## 📌 What Problem Does This Solve?

Sometimes a bitmask DP transition needs to look at **every subset of
a given mask** — not just "add one more bit" like our earlier
templates (TSP, Hamiltonian Path). Examples:

- "For every mask, what's the sum of some value over all its subsets?"
- "Split this group of items into two smaller groups — try every
  possible split."

Naively checking all numbers from `0` to `mask` and filtering only
the ones that are actual subsets wastes a lot of time. This file
shows the **standard trick** to enumerate ONLY real submasks,
efficiently.

## 🔑 The Core Trick

```cpp
for (int sub = mask; ; sub = (sub - 1) & mask) {
    // sub is a submask of mask
    if (sub == 0) break;
}
```

Walk through it conceptually:
- `sub - 1` behaves like normal subtraction: it flips the lowest set
  bit to 0, and flips every bit below it to 1 (standard binary
  subtraction behavior).
- ANDing with `mask` immediately discards any bits that shouldn't be
  there (i.e., bits that are 0 in the original mask), snapping us
  directly to the next valid submask.
- This never "wastes" an iteration on a non-submask number — every
  value of `sub` we see IS a genuine submask of `mask`.

## 🧠 Why the Total Complexity is O(3^n), Not O(4^n)

If you enumerate submasks for **every mask from 0 to 2^n - 1**
(common in "Sum over Subsets" style problems), a naive analysis might
assume `2^n` masks × `2^n` submasks each = `O(4^n)`. But that's wrong
— most masks have far fewer submasks than `2^n`.

The real count: think per-bit. For each of the `n` bits, across all
(mask, submask) pairs:
- The bit is `0` in mask → it MUST be `0` in submask too. (1 way)
- The bit is `1` in mask → it can be `0` OR `1` in submask. (2 ways)

Since a bit is independently either "forced 0" or "free choice of 2",
and we're summing over all masks (so each bit is "in mask" for half
the masks and "not in mask" for the other half)... the clean way to
see it: for each bit, there are 3 total combined states across
(mask-bit, submask-bit) pairs: `(0,0)`, `(1,0)`, `(1,1)`. Multiply
across `n` independent bits → **3^n total (mask, submask) pairs.**

This is a famous and important complexity result — memorize it,
because `3^n` is dramatically smaller than `4^n` for reasonably
sized `n` (e.g. `3^20 ≈ 3.5 billion` vs `4^20 ≈ 1 trillion`... still
big, but the ratio matters a lot as `n` grows, and for `n` around
15-18, `3^n` is very manageable while `4^n` is not).

## 🔧 Bit Tricks Introduced Here (NEW)

| Trick | Meaning |
|---|---|
| `sub = (sub - 1) & mask` | Jump to next smaller submask of `mask` |
| `mask ^ sub` | Get the **complement** part (mask minus sub) — useful for splitting into two disjoint groups |
| `1LL << __builtin_popcount(m)` | Number of submasks of `m` = `2^(number of set bits)` |

## ✅ Complexity

- Enumerating submasks of ONE mask: `O(2^(popcount(mask)))`
- Enumerating submasks of EVERY mask (0 to 2^n - 1): `O(3^n)` total
  — this is the key result to remember.

## 🔗 Connection to Other Files

- **Iterative Bitmask DP.cpp / TSP Template.cpp** → Those transitions
  only ever add ONE bit at a time (`mask | (1 << next)`). This file's
  trick is for when you need to consider **many bits at once** (a
  whole submask), which is a different (and more expensive) category
  of transition.
- Useful as a building block for advanced "partition into k groups"
  or "assign items to teams" style bitmask DP problems, which you may
  add to this repo later (e.g. "Partition DP" folder).

## 🎯 Practice Strategy

1. Run this file with a small `mask` (like `mask = 1011` binary = 11
   decimal) and manually list all its submasks on paper — confirm
   the code's output matches.
2. Verify the `sumOverSubsets` output equals `2^(popcount(mask))` for
   a few masks by hand.
3. Try writing the "split mask into two disjoint non-empty parts"
   loop (`sub` from `mask` down but excluding `mask` and `0`) as your
   own exercise — this pattern shows up in partition-style bitmask DP.


/*
    ================================================================
    GENERIC TEMPLATE: Remainder Bitmask DP (Mask + Modulo State)
    ================================================================

    Problem this pattern solves: Partition/arrange a set of n numbers
    into groups such that some SUM or PRODUCT condition involving a
    remainder (mod k) is satisfied.

    Classic problem used here: "Partition array into K subsets with
    equal sum" style, extended with remainder tracking — specifically:

    "Given n numbers, split them into groups (in order) such that
    each group's sum is divisible by k. Count/find ways to do this,
    or find minimum number of groups."

    Core Idea:
        dp[mask][rem] = considering the numbers picked so far (mask),
        where 'rem' = (sum of current, still-open group) % k,
        what's the best (count/min groups/etc.) way to proceed?

    This introduces a SECOND dimension to the state beyond mask:
    'rem' = running remainder — a very common pattern whenever a
    problem involves "sum so far mod k" alongside a subset.

    Time Complexity: O(2^n * n * k)
    Space Complexity: O(2^n * k)
*/

#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> a;
vector<vector<int>> memo;      // memo[mask][rem] = min groups needed
const int INF = 1e9;

/*
    dfs(mask, rem):
        mask -> set of numbers already placed into SOME group
        rem  -> (sum of the CURRENT, still-open group) % k

    Returns minimum number of groups needed to place all remaining
    numbers (numbers not in mask), given the current group's
    remainder is 'rem'.

    Key transition idea:
        For every unused number i:
            - Try adding it to the CURRENT open group.
              newRem = (rem + a[i]) % k
              If newRem == 0, this group is now complete/closed,
              so the NEXT number (if any) starts a fresh group
              -> cost of "closing a group" = +1 to answer, and we
                 recurse with rem = 0 (fresh group) for future picks.
              Otherwise the group stays open -> recurse with newRem,
                 no extra cost yet (group not closed).
*/
int dfs(int mask, int rem) {
    // Base case: all numbers placed.
    if (mask == (1 << n) - 1) {
        // If current open group has rem == 0, it's a valid finished
        // group needing no extra closing; if not, this arrangement
        // is invalid (can't leave a group with nonzero remainder).
        return (rem == 0) ? 0 : INF;
    }

    if (memo[mask][rem] != -1) return memo[mask][rem];

    int ans = INF;

    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) continue; // already used

        int newMask = mask | (1 << i);
        int newRem = (rem + a[i]) % k;

        if (newRem == 0) {
            // Current group closes perfectly here.
            // +1 for completing this group; next group starts at rem=0
            int res = dfs(newMask, 0);
            if (res != INF) ans = min(ans, res + 1);
        } else {
            // Group stays open, no group completed yet
            int res = dfs(newMask, newRem);
            ans = min(ans, res);
        }
    }

    return memo[mask][rem] = ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    a.assign(n, 0);
    for (int i = 0; i < n; i++) cin >> a[i];

    memo.assign(1 << n, vector<int>(k, -1));

    int result = dfs(0, 0); // start: nothing used, current group sum%k = 0

    if (result >= INF) cout << "Not possible\n";
    else cout << "Minimum groups: " << result << "\n";

    return 0;
}

/*
    ================================================================
    WHY 'rem' IS A SEPARATE DP DIMENSION (IMPORTANT CONCEPT)
    ================================================================
    Normally bitmask DP state is just "mask" (+ maybe "pos" for
    position-dependent problems like TSP). But whenever the problem
    involves a SUM or accumulated value where only "value mod k"
    matters for future decisions (not the exact value), you add
    that remainder as an EXTRA dimension: dp[mask][rem].

    This works because of a key property of modulo arithmetic:
        (sum_so_far + next_number) % k
    depends ONLY on (sum_so_far % k) and next_number — NOT on the
    exact value of sum_so_far. So instead of tracking the full sum
    (which could be huge), we only need to track it mod k, giving
    us just 'k' possible extra states instead of "sum many" states.

    ================================================================
    HOW TO ADAPT THIS TEMPLATE
    ================================================================
    1. Identify what you're accumulating that only matters mod k
       (a sum, an XOR of remainders, a product mod k, etc.)

    2. dp[mask][rem] where rem = accumulated_value % k for whatever
       "currently open" chunk/group/segment you're building.

    3. Base case: mask == full mask AND rem satisfies your target
       condition (usually rem == 0 for "divisible by k").

    4. Transition: for each unused element, update rem using modulo
       arithmetic, and decide whether picking it "closes" a group
       (rem becomes 0) or keeps it "open" (rem stays nonzero).

    5. This idea generalizes beyond "sum % k": you could track
       "product % k", "XOR value", "count % k", etc. — same pattern,
       different combination operator instead of "+".
*/