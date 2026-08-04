# 🧭 Shortest Path in an Unweighted (Unit Weight) Undirected Graph — BFS

![Topic](https://img.shields.io/badge/Topic-Graphs-blueviolet?style=for-the-badge)
![Algorithm](https://img.shields.io/badge/Algorithm-BFS-orange?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Time](https://img.shields.io/badge/Time-O(V%2B2E)-green?style=for-the-badge)
![Space](https://img.shields.io/badge/Space-O(V%2BE)-red?style=for-the-badge)

---

## ❓ Problem Statement

> Given an **undirected graph** with `V` vertices (numbered `0` to `V-1`) and `E` edges, where **every edge has weight = 1**, find the **shortest distance from a given source node to every other node** in the graph.
>
> If a node is **not reachable** from the source, its distance should be reported as `-1`.

**Input:**
- `V` → number of vertices
- `adj[]` → adjacency list representation of the graph
- `src` → source node

**Output:**
- An array `dist[]` of size `V`, where `dist[i]` = shortest distance from `src` to node `i` (or `-1` if unreachable)

### 📌 Example

```
Input:
V = 9, src = 0
Edges = (0,1) (0,3) (3,4) (4,5) (5,6) (1,2) (2,6) (6,7) (7,8)

Output:
dist[] = [0, 1, 2, 1, 2, 3, 3, 4, 5]
```

### 🚧 Constraints
- Graph is **undirected**
- All edges have **unit weight (1)**
- Graph may be **disconnected**

---

## 🧠 Why BFS? (Core Intuition)

🟢 In a graph where **all edges cost the same (1)**, BFS explores the graph **level by level**, like ripples spreading in water.

Since BFS visits nodes in the exact order of their distance from the source (1 hop, then 2 hops, then 3 hops...), **the first time a node is reached, it is guaranteed to be via the shortest path.**

> ⚠️ This is why BFS works only for **unit-weight graphs**. If weights vary, we'd need Dijkstra's Algorithm instead.

---

## 🗺️ Step-by-Step Algorithm

### 🔹 Step 1 — Build the Adjacency List
Represent the graph so each node knows its direct neighbors.

### 🔹 Step 2 — Initialize Distance Array
Create `dist[]` of size `V`, fill every value with **infinity (∞)**, except:
```
dist[src] = 0
```

### 🔹 Step 3 — BFS Traversal using a Queue
- Push `{src, distance = 0}` into the queue
- While queue is not empty:
  - Pop the front node `{node, dist_so_far}`
  - For every neighbor of `node`:
    - If `dist[neighbor] > dist_so_far + 1` → update it and push `{neighbor, dist_so_far + 1}`

### 🔹 Step 4 — Build the Result
- Any node still holding `∞` → was never reached → set it to `-1`
- Return `dist[]`

---

## 🎨 Visual Walkthrough

### Graph used in the example above:

<table>
<tr><td>

```
        1 —— 2
       /       \
      0         6 —— 7 —— 8
       \       /
        3 — 4 — 5
```

</td></tr>
</table>

### 🌈 BFS spreading level-by-level (color = distance from source)

<table>
<tr>
<th>🟦 Level 0 (dist 0)</th>
<th>🟩 Level 1 (dist 1)</th>
<th>🟨 Level 2 (dist 2)</th>
<th>🟧 Level 3 (dist 3)</th>
<th>🟥 Level 4 (dist 4)</th>
<th>🟪 Level 5 (dist 5)</th>
</tr>
<tr>
<td bgcolor="#8ecaff" align="center"><b>0</b></td>
<td bgcolor="#8fffb0" align="center"><b>1, 3</b></td>
<td bgcolor="#fff98f" align="center"><b>2, 4</b></td>
<td bgcolor="#ffc08f" align="center"><b>5, 6</b></td>
<td bgcolor="#ff8f8f" align="center"><b>7</b></td>
<td bgcolor="#d8a6ff" align="center"><b>8</b></td>
</tr>
</table>

**Reading it:** BFS finishes coloring the entire "0" ring before touching the "1" ring, finishes the "1" ring before touching the "2" ring, and so on — exactly why the first-visit distance is always the shortest one.

---

## 🔍 Dry Run Table

Starting distances: `[0, ∞, ∞, ∞, ∞, ∞, ∞, ∞, ∞]`

| Step | Queue (front → back) | Node Popped | Neighbors Checked | Updated `dist[]` |
|------|----------------------|-------------|--------------------|-------------------|
| 1 | `[(0,0)]` | 0 | 1, 3 | `dist[1]=1, dist[3]=1` |
| 2 | `[(1,1), (3,1)]` | 1 | 0, 2 | `dist[2]=2` |
| 3 | `[(3,1), (2,2)]` | 3 | 0, 4 | `dist[4]=2` |
| 4 | `[(2,2), (4,2)]` | 2 | 1, 6 | `dist[6]=3` |
| 5 | `[(4,2), (6,3)]` | 4 | 3, 5 | `dist[5]=3` |
| 6 | `[(6,3), (5,3)]` | 6 | 2, 7 | `dist[7]=4` |
| 7 | `[(5,3), (7,4)]` | 5 | 4, 6 | — (already visited) |
| 8 | `[(7,4)]` | 7 | 6, 8 | `dist[8]=5` |
| 9 | `[(8,5)]` | 8 | 7 | — (already visited) |

✅ **Final `dist[] = [0, 1, 2, 1, 2, 3, 3, 4, 5]`**

---

## ⏱️ Complexity Analysis

| Type | Complexity | Reason |
|------|------------|--------|
| ⏳ Time | `O(V + 2E)` | Each vertex is pushed/popped once → `O(V)`; each edge is checked from both its endpoints (undirected) → `O(2E)` |
| 💾 Space | `O(V + E)` | `O(V)` for the `dist[]` array + queue, `O(E)` (specifically `O(2E)`) for the adjacency list |

---

## 🧩 Pattern Recognition (for future problems)

This is the classic **"Unweighted Shortest Path via BFS"** pattern. Recognize it when:
- 🟢 Graph edges have **no weight / equal weight**
- 🟢 Question asks for **minimum number of edges / hops / moves**
- 🟢 Keywords like *"shortest path"*, *"minimum steps"*, *"fewest moves"* appear alongside an **unweighted grid or graph**

Common variants that reuse this exact pattern:
- Shortest path in a binary maze/grid
- Word Ladder (min steps to transform one word to another)
- Rotten Oranges (min time for infection to spread)
- Knight's minimum moves on a chessboard

> 📄 Full C++ implementation is provided separately in `shortest_path_bfs.cpp` (kept out of this README as requested).
