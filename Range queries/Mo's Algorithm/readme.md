# 🧩 Mo's Algorithm

![Offline](https://img.shields.io/badge/Type-Offline-blueviolet)
![Complexity](https://img.shields.io/badge/Time-O((n%2Bq)%E2%88%9An)-orange)
![Based%20On](https://img.shields.io/badge/Based%20On-Sqrt%20Decomposition-yellow)

> 🎯 **One-liner:** Sort queries smartly by block, then answer them using a sliding window that moves one step at a time.

---

## 🧠 1. Core Idea

We have an array and **q** range queries `[l, r]` known in advance (offline).
We maintain a window `[curL, curR]` and slide it query-to-query, adding/removing one element at a time.

```
        curL                          curR
         │                             │
Array:  [ 2   4   5   8   1   9   3   6   7   0 ]
                ▲───────── window ─────────▲
```

🔑 Trick: **sort the queries** so the window barely has to move between consecutive queries.

---

## 🎨 2. The Three-Step Recipe

| Step | What Happens |
|:---:|---|
| 🧱 **1. Block the array** | Split into blocks of size `√n` |
| 🔀 **2. Sort queries** | By `(l / blockSize, r)` |
| 🪟 **3. Slide the window** | Move `curL`, `curR` one element at a time, updating the answer |

---

## 📦 3. Why Blocks + Sorting Works

```
 Block 0        Block 1        Block 2
┌─────────┐   ┌─────────┐   ┌─────────┐
│ 0 1 2   │   │ 3 4 5   │   │ 6 7 8   │   ...
└─────────┘   └─────────┘   └─────────┘
```

Queries with `l` in the **same block** are grouped together, then sorted by `r`.

| Pointer | Movement Bound | Why |
|:---:|:---:|---|
| `curR` ▶️ | `O(n)` per block → `O(n√n)` total | `r` sorted ascending within a block, only moves forward |
| `curL` ↔️ | `O(√n)` per query → `O(q√n)` total | `l` stays within one block's width |

### ⚡ Total Complexity

```
 ┌────────────────────────────────────┐
 │   O( (n + q) · √n )                │
 └────────────────────────────────────┘
```

---

## 🔄 4. Sliding the Window — Order Matters!

```
while (curR < r) { curR++; add(arr[curR]);   }   ➕ expand right
while (curL > l) { curL--; add(arr[curL]);   }   ➕ expand left
while (curR > r) { remove(arr[curR]); curR--;}   ➖ shrink right
while (curL < l) { remove(arr[curL]); curL++;}   ➖ shrink left
```

🚨 **Always expand before shrinking** — otherwise the window can go negative-size mid-transition.

---

## 🌀 5. Zig-Zag Optimization

Without zig-zag, `curR` snaps back to the start every new block 😩

```
Block 0 (asc r) ──▶──▶──▶──▶
Block 1 (desc r)          ◀──◀──◀──◀   ⬅ saves the long reset jump!
Block 2 (asc r)                     ──▶──▶──▶──▶
```

```cpp
if ((l / blockSize) % 2 == 0) sort by r ascending;
else                          sort by r descending;
```

---

## 🏷️ 6. Cheat Sheet

| Concept | Formula |
|---|---|
| Block size | `√n` |
| Query sort key | `(l / blockSize, r)` |
| Total complexity | `O((n + q)√n)` |
| Needs | `add(x)` / `remove(x)` in `O(1)` or `O(log n)` |
| Extension | **Mo's with Updates** → add `time` as 3rd sort key → `O(n^(5/3))` |

---

## ✅ 7. When to Reach for Mo's

| Use it when... | Skip it when... |
|---|---|
| 🟢 Queries are offline | 🔴 Queries must be answered online |
| 🟢 `add`/`remove` is cheap | 🔴 Updates are interleaved with queries (needs the update-variant) |
| 🟢 No clean segment-tree merge exists (e.g. distinct count, mode) | 🔴 A segment tree already solves it in `O(log n)` |

---

## 🖼️ 8. Big Picture Diagram

```
 Queries (unsorted)         Sort by block, then r         Process in order
┌──────────────────┐        ┌──────────────────┐        ┌──────────────────┐
│ (2,8) (0,3)       │  ──▶  │ (0,3) (2,8) ...   │  ──▶   │ slide window ──▶ │
│ (5,9) (1,4)       │       │ grouped by block  │        │ O(1) add/remove  │
└──────────────────┘        └──────────────────┘        └──────────────────┘
```
