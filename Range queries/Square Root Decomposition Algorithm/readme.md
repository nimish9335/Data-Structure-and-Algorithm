# 🧱 Square Root Decomposition

![Type](https://img.shields.io/badge/Type-Online-blueviolet)
![Complexity](https://img.shields.io/badge/Time-O(%E2%88%9An)-orange)
![Space](https://img.shields.io/badge/Space-O(n)-yellow)

> 🎯 **One-liner:** Split the array into `√n` blocks, precompute an answer per block, then combine full blocks + edge elements to answer any query fast.

---

## 🧠 1. Core Idea

```
Array:   [ 2   4   5 | 8   1   9 | 3   6   7 | 0 ]
Block:        0            1           2       3
```

Each block stores one precomputed value (sum, min, max, etc.) called `block[]`.

- 🟩 **Full blocks** inside a query → use `block[]` directly (O(1) per block)
- 🟨 **Partial blocks** at the edges → scan element by element

```
 Query [2, 8]
        ▼                             ▼
[ 2   4 | 5   8   1 | 9   3   6 | 7   0 ]
     🟨    🟩🟩🟩🟩🟩    🟩🟩🟩🟩   🟨
   partial     full block      full     partial
```

---

## 📦 2. Why Block Size = √n

| Term | Cost |
|---|---|
| Number of blocks | `n / s` |
| Elements scanned at 2 edges | `2s` |
| **Total per query** | `n/s + s` |

```
 ┌────────────────────────────────────┐
 │  minimized when  s = √n            │
 │  →  O(√n) per query                │
 └────────────────────────────────────┘
```
📐 This comes straight from AM-GM: for a fixed product, a sum of two terms is smallest when they're equal.

---

## 🎨 3. The Three Operations

| Operation | Cost | What Happens |
|:---:|:---:|---|
| 🏗️ **Build** | `O(n)` | Precompute `block[]` from `arr[]` |
| ✏️ **Update(i, val)** | `O(1)` | Fix `arr[i]`, patch only its block's aggregate |
| 🔍 **Query(l, r)** | `O(√n)` | Partial + full + partial, as shown above |

---

## 🔄 4. Update in One Picture

```
Before:  Block 1 = [8, 1, 9]   block[1] = 18

update(index_of_1, 5)

After:   Block 1 = [8, 5, 9]   block[1] = 18 + (5-1) = 22
```

```cpp
block[i / blockSize] += val - arr[i];
arr[i] = val;
```

---

## 🔍 5. Query in One Picture

```
query(2, 8):

 idx:     0   1   2   3   4   5   6   7   8   9
 arr:   [ 2   4 | 5   8   1 | 9   3   6 | 7   0 ]
              🟨  ───full block───  ──full──  🟨
              +5      +14              +18     +7
```

```
sum = arr[2] + block[1] + block[2] + arr[7]
    = 5      + 14        + 18       + 7
    = 44
```

---

## 🌈 6. Common Variants

| Variant | 🧩 Idea |
|---|---|
| 🟦 **Range Update, Point Query** | Store a `lazy[]` add-value per block; full blocks get `lazy[b] += val`, partial ones updated directly |
| 🟪 **Range Min / Max** | `block[]` holds min/max; if the changed value *was* the min/max, recompute that block from scratch |
| 🟧 **Mo's Algorithm** | Offline queries sorted by block — same block-splitting idea, different use case |
| 🟩 **Distinct Count / Frequency** | Each block stores a small frequency table instead of a single number |

---

## ✅ 7. When to Use It

| Use it when... | Skip it when... |
|---|---|
| 🟢 Merge logic is awkward for a segment tree | 🔴 You need strict `O(log n)` guarantees |
| 🟢 You want simple, quick-to-write code | 🔴 You need range update **+** range query together (segment tree + lazy prop is cleaner) |
| 🟢 `n` is small–moderate (≤ 10⁵ ish) | 🔴 Merge is trivial and associative (segment tree wins) |

---

## 🏷️ 8. Cheat Sheet

```
block_size   = ceil(sqrt(n))
block_id(i)  = i / block_size

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

## ⚠️ 9. Common Pitfalls

- ❗ Using `floor(sqrt(n))` instead of `ceil` → last block can be undersized
- ❗ Off-by-one on the last (smaller) block
- ❗ For min/max updates: forgetting to **recompute** the whole block when the changed element was the extremum
