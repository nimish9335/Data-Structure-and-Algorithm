# 🧭 Dijkstra's Algorithm using Set (instead of Priority Queue)

![Topic](https://img.shields.io/badge/Topic-Graphs-blueviolet?style=for-the-badge)
![Algorithm](https://img.shields.io/badge/Algorithm-Dijkstra%20(Set)-orange?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium--Hard-yellow?style=for-the-badge)
![Time](https://img.shields.io/badge/Time-O(E%20logV)-green?style=for-the-badge)
![Space](https://img.shields.io/badge/Space-O(V%2BE)-red?style=for-the-badge)

---

## ❓ Problem Statement

> Given a **weighted graph** (directed or undirected) with `V` vertices and `E` edges, where **all edge weights are non-negative**, find the **shortest distance from a given source node to every other node** — this time implementing Dijkstra's Algorithm using a **`set`** data structure instead of a **priority queue (min-heap)**.
>
> If a node is **not reachable** from the source, its distance should be reported as `-1`.

**Input:**
- `V` → number of vertices
- `adj[]` → adjacency list where each entry is `{neighbor, weight}`
- `src` → source node

**Output:**
- An array `dist[]` of size `V`, where `dist[i]` = shortest distance from `src` to node `i` (or `-1` if unreachable)

### 📌 Example

```
Input:
V = 5, src = 0
Edges (u, v, weight):
0 -> 1 (w=4)   0 -> 2 (w=1)
2 -> 1 (w=2)   1 -> 3 (w=1)
2 -> 3 (w=5)   3 -> 4 (w=3)

Output:
dist[] = [0, 3, 1, 4, 7]
```

### 🚧 Constraints
- Edge weights must be **non-negative** (`w >= 0`)
- Graph may be **directed or undirected**
- Graph may be **disconnected**

---

## 🧠 Core Intuition — Set vs. Priority Queue

🟢 Both a **priority queue** and a **set** can efficiently give us the pair `(smallest distance, node)`. The key difference lies in what happens **after we find a shorter path** to a node that's already sitting in the structure:

| | Priority Queue | Set |
|---|---|---|
| Can remove a stale/old entry? | ❌ No — old `(largerDist, node)` pair just sits there as garbage | ✅ Yes — `erase()` the old pair before inserting the new one |
| Extra pairs floating around? | Yes, "stale" entries get silently skipped later | No, the set always holds **at most one entry per node** |
| Access smallest element | `top()` | `begin()` |

> ⚡ **The optimization:** the moment we find a shorter distance to a node that's *already* in the set, we **erase** its old `(oldDist, node)` pair first, then `insert` the new `(newDist, node)` pair. This keeps the set clean — it never carries dead weight the way a priority queue does — which can save iterations on graphs with lots of repeated relaxations.

---

## 🗺️ Step-by-Step Algorithm

### 🔹 Step 1 — Build the Adjacency List
Store each edge as `{neighbor, weight}` for every node.

### 🔹 Step 2 — Initialize Distance Array + Set
- `dist[]` of size `V`, filled with **infinity (∞)**, except `dist[src] = 0`
- Insert `{distance = 0, node = src}` into a `set<pair<int,int>>` (sets stay sorted by default, smallest pair first)

### 🔹 Step 3 — Process Nodes Using `begin()` and `erase()`
While the set is not empty:
- Take the pair at `st.begin()` → this is the `{dist_so_far, node}` with the **smallest distance**
- **Erase** it from the set (`st.erase(st.begin())`)
- For every neighbor `{v, w}` of `node`:
  - If `dist_so_far + w < dist[v]`:
    - **If `dist[v]` is not infinity**, first `erase({dist[v], v})` from the set (remove the stale, longer entry)
    - Update `dist[v] = dist_so_far + w`
    - `insert({dist[v], v})` into the set

### 🔹 Step 4 — Build the Result
- Any node still holding `∞` → unreachable → report `-1`
- Return `dist[]`

---

## 🎨 Visual Walkthrough

### Graph used in the example above:

<table>
<tr><td>

```
        4
   0 ------> 1
   |         |
  1|         |1
   v    2    v
   2 -------> 
   |         3
  5|         |
   v         |3
   3 <-------+
   |
  3|
   v
   4
```

*(See edge list above for exact directed weighted edges: 0→1(4), 0→2(1), 2→1(2), 1→3(1), 2→3(5), 3→4(3))*

</td></tr>
</table>

### 🌈 What the SET looks like at each moment (color = still-active entry)

<table>
<tr>
<th>🟦 After processing 0</th>
<th>🟩 After processing 2</th>
<th>🟨 After processing 1</th>
<th>🟧 After processing 3</th>
</tr>
<tr>
<td bgcolor="#8ecaff" align="center">{(1,2), (4,1)}</td>
<td bgcolor="#8fffb0" align="center">{(3,1), (6,3)}<br><s>❌(4,1) erased!</s></td>
<td bgcolor="#fff98f" align="center">{(4,3)}<br><s>❌(6,3) erased!</s></td>
<td bgcolor="#ffc08f" align="center">{(7,4)}</td>
</tr>
</table>

**Reading it:** Compare this to the priority-queue dry run — here, the moment `dist[1]` improves from `4` to `3`, the **old `(4,1)` pair is deleted immediately**. The set never has to carry or later discard stale garbage — unlike the priority queue, which just leaves old pairs floating until they're popped and discarded.

---

## 🔍 Dry Run Table

Starting distances: `[0, ∞, ∞, ∞, ∞]` &nbsp;|&nbsp; Set: `{(0, 0)}`

| Step | `begin()` picked `(dist, node)` | Edges Relaxed | Set Operations | Set After |
|------|-----------------------------------|----------------|------------------|-------------|
| 1 | (0, 0) | 0→1 (w4), 0→2 (w1) | insert (4,1), insert (1,2) | `{(1,2), (4,1)}` |
| 2 | (1, 2) | 2→1 (w2), 2→3 (w5) | **erase (4,1)**, insert (3,1); insert (6,3) | `{(3,1), (6,3)}` |
| 3 | (3, 1) | 1→3 (w1) | **erase (6,3)**, insert (4,3) | `{(4,3)}` |
| 4 | (4, 3) | 3→4 (w3) | insert (7,4) | `{(7,4)}` |
| 5 | (7, 4) | *(no outgoing edges)* | — | `{}` empty, stop |

✅ **Final `dist[] = [0, 3, 1, 4, 7]`**

> 💡 Notice there are only **5 steps** here (one per node, no revisits/skips) versus the priority-queue version, which had 2 extra "stale, discard" steps. This is the exact optimization the video highlights.

---

## ⏱️ Complexity Analysis

| Type | Complexity | Reason |
|------|------------|--------|
| ⏳ Time | `O(E log V)` | Every `insert`/`erase` on a `set` is `O(log V)`, done for up to `E` edge relaxations — same asymptotic bound as the priority-queue version, but with fewer *actual* stale operations in practice |
| 💾 Space | `O(V + E)` | Adjacency list `O(V + E)`, `dist[]` array `O(V)`, set holds **at most `V`** entries at any time (unlike PQ, which can hold up to `E`) |

---

## ⚠️ Limitations

- ❌ **Still does not work with negative edge weights** or **negative weight cycles** — the same core issue as the priority-queue version: once a node's shortest distance is finalized, Dijkstra never revisits it.
- ✅ For graphs with negative weights, use **Bellman-Ford Algorithm** instead.

---

## 🧩 Pattern Recognition (for future problems)

This is the same **"Single Source Shortest Path with Non-Negative Weights"** pattern as the priority-queue version — the `set` is just an **alternate implementation choice**, not a different algorithm. Reach for `set` over `priority_queue` when:
- 🟢 You want the internal structure to **never hold duplicate/stale entries** for the same node
- 🟢 You need `erase()`-style cleanup, which a standard STL `priority_queue` cannot do directly
- 🟢 The interview/problem explicitly asks about **PQ vs Set tradeoffs** in Dijkstra

> 📄 Full C++ implementation is provided separately in `dijkstra_using_set.cpp` (kept out of this README as requested).
