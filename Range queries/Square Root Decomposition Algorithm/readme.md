# Square Root Decomposition — Notes

## 1. What Problem It Solves

Given an array of size `n`, we want to efficiently support:
- **Range queries**: sum / min / max / gcd over `[l, r]`
- **Point updates**: change value at index `i`

Brute force: O(n) per query, O(1) per update.
Segment Tree: O(log n) per query and update.
**Sqrt Decomposition: O(√n) per query and update — simpler to code, slightly slower asymptotically.**

---

## 2. Core Idea

Split the array into blocks of size `√n`.

```
Array:   [ 2 4 5 | 8 1 9 | 3 6 7 | 0 ]
Block:       0        1       2     3
```

For each block, precompute an aggregate value (sum, min, etc.) called `block[]`.

- **Update**: change `arr[i]`, then update only the aggregate of the block containing `i` → O(1)
- **Query(l, r)**:
  - Left partial block → add elements one by one until block boundary
  - Middle full blocks → add `block[]` value directly
  - Right partial block → add elements one by one
  - Total touched elements ≈ O(√n)

---

## 3. Why Block Size = √n

Let block size = `s`.

- Number of blocks ≈ `n / s`
- Elements scanned at the two partial edges ≈ `2s`

Total work per query ≈ `n/s + s`

This is minimized when `s = √n` (AM-GM inequality: for fixed product, sum is minimized when the two terms are equal).

Result: **O(√n) per query**.

---

## 4. Step-by-Step Algorithm

### Build
1. Compute `block_size = ceil(sqrt(n))`
2. Compute `num_blocks = ceil(n / block_size)`
3. For each index `i`, its block id = `i / block_size`
4. Accumulate `block[block_id] += arr[i]`

### Update(i, val)
1. `block_id = i / block_size`
2. `block[block_id] += val - arr[i]`
3. `arr[i] = val`

### Query(l, r)  — for sum
1. Start at `i = l`
2. While `i <= r`:
   - If `i` is at the start of a block **and** the whole block `[i, i+block_size-1]` lies inside `[l, r]`:
     - `sum += block[i / block_size]`
     - `i += block_size`
   - Else:
     - `sum += arr[i]`
     - `i += 1`
3. Return `sum`

---

## 5. Complexity

| Operation | Time |
|---|---|
| Build | O(n) |
| Update | O(1) |
| Query | O(√n) |
| Space | O(n + √n) |

---

## 6. Variants (good to remember)

| Variant | Idea |
|---|---|
| **Range Update, Point Query** | Keep a "lazy" add value per block. On range update, fully-covered blocks just get `lazy[block] += val`; partial blocks updated element-wise. Point query = `arr[i] + lazy[block_of_i]`. |
| **Range Min/Max** | Same structure, but `block[]` stores min/max instead of sum; update requires recomputing block from scratch if the changed element was the min/max → O(block_size) update. |
| **Mo's Algorithm** | Offline range queries. Sort queries by `(l / block_size, r)`. Maintain a sliding window `[curL, curR]` and move pointers query to query. Total complexity O((n + q)·√n). |
| **Frequency / Distinct counting** | Blocks store frequency tables or counts of distinct elements; useful for "count distinct in range" type problems. |

---

## 7. When to Use This Over Segment Tree

Use sqrt decomposition when:
- The merge operation is awkward or non-associative (segment tree needs a clean merge function)
- You need range-update + point-query and don't want lazy propagation complexity
- Problem size is moderate (n ≤ 10^5 or so) and code simplicity matters more than the log factor
- You're implementing **Mo's Algorithm**, which inherently uses block decomposition

Use segment tree when:
- You need O(log n) guarantees
- You need range update + range query together (segment tree with lazy propagation handles this cleanly)

---

## 8. Quick Recall Cheat-Sheet

```
block_size = sqrt(n)
block_id(i) = i / block_size
block_start(b) = b * block_size
block_end(b) = min(n-1, block_start(b) + block_size - 1)

update(i, val):
    block[block_id(i)] += val - arr[i]
    arr[i] = val

query(l, r):
    sum = 0
    while l <= r:
        if l % block_size == 0 and l + block_size - 1 <= r:
            sum += block[block_id(l)]
            l += block_size
        else:
            sum += arr[l]
            l += 1
    return sum
```

---

## 9. Pitfalls to Remember

- Off-by-one errors on the last block if `n` is not divisible by `block_size` (last block may be smaller)
- Recomputing block aggregate after a "destructive" update (like min/max) instead of doing it in O(1)
- Forgetting `block_size = ceil(sqrt(n))`, not `floor` (floor can leave one block short)
