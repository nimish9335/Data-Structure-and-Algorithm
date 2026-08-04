# 🧭 Dijkstra's Algorithm — Shortest Path using Priority Queue (Min-Heap)

![Topic](https://img.shields.io/badge/Topic-Graphs-blueviolet?style=for-the-badge)
![Algorithm](https://img.shields.io/badge/Algorithm-Dijkstra-orange?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium--Hard-yellow?style=for-the-badge)
![Time](https://img.shields.io/badge/Time-O(E%20logV)-green?style=for-the-badge)
![Space](https://img.shields.io/badge/Space-O(V%2BE)-red?style=for-the-badge)

---

## ❓ Problem Statement

> Given a **weighted graph** (directed or undirected) with `V` vertices and `E` edges, where **all edge weights are non-negative**, find the **shortest distance from a given source node to every other node**.
>
> If a node is **not reachable** from the source, its distance should be reported as `-1` (or infinity, depending on convention).

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

## 🧠 Core Intuition

🟢 Dijkstra's Algorithm is a **greedy** algorithm — at every step, it picks the **unvisited node with the currently smallest known distance** and "finalizes" it, then uses that node to try and shorten the distance of its neighbors.

Because we always expand the **closest** known node first, once a node's shortest distance is picked out of the priority queue, **it can never be improved again** — it is finalized for good.

> ⚡ A **Min-Heap (Priority Queue)** is used instead of a simple queue so that, unlike BFS (which assumes equal weights), we always process the node with the **smallest distance so far**, even if graph edges have different weights.

---

## 🗺️ Step-by-Step Algorithm

### 🔹 Step 1 — Build the Adjacency List
Store each edge as `{neighbor, weight}` for every node.

### 🔹 Step 2 — Initialize Distance Array + Priority Queue
- `dist[]` of size `V`, filled with **infinity (∞)**, except `dist[src] = 0`
- Push `{distance = 0, node = src}` into a **Min-Heap** (priority queue ordered by smallest distance)

### 🔹 Step 3 — Process Nodes Greedily
While the priority queue is not empty:
- Pop the `{dist_so_far, node}` with the **smallest distance**
- For every neighbor `{v, w}` of `node`:
  - If `dist_so_far + w < dist[v]`:
    - Update `dist[v] = dist_so_far + w`
    - Push `{dist[v], v}` into the priority queue

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

### 🌈 Order in which nodes get finalized (color = pop order from min-heap)

<table>
<tr>
<th>🟦 1st (finalized)</th>
<th>🟩 2nd</th>
<th>🟨 3rd</th>
<th>🟧 4th</th>
<th>🟪 5th</th>
</tr>
<tr>
<td bgcolor="#8ecaff" align="center"><b>0 (dist 0)</b></td>
<td bgcolor="#8fffb0" align="center"><b>2 (dist 1)</b></td>
<td bgcolor="#fff98f" align="center"><b>1 (dist 3)</b></td>
<td bgcolor="#ffc08f" align="center"><b>3 (dist 4)</b></td>
<td bgcolor="#d8a6ff" align="center"><b>4 (dist 7)</b></td>
</tr>
</table>

**Reading it:** Notice node `2` (distance 1) is finalized *before* node `1` (distance 4 initially), even though `1` was discovered first — because the min-heap always pops the **smallest distance available**, not the order of discovery.

---

## 🔍 Dry Run Table

Starting distances: `[0, ∞, ∞, ∞, ∞]` &nbsp;|&nbsp; Min-Heap: `{(0, 0)}`

| Step | Popped `(dist, node)` | Edges Relaxed | Updated `dist[]` | Heap After Push |
|------|------------------------|----------------|--------------------|-------------------|
| 1 | (0, 0) | 0→1 (w4), 0→2 (w1) | `dist[1]=4, dist[2]=1` | `{(1,2), (4,1)}` |
| 2 | (1, 2) | 2→1 (w2), 2→3 (w5) | `dist[1]=3` (improved), `dist[3]=6` | `{(3,1), (4,1)❌stale, (6,3)}` |
| 3 | (3, 1) | 1→3 (w1) | `dist[3]=4` (improved) | `{(4,1)❌stale, (4,3), (6,3)❌stale}` |
| 4 | (4,1) *stale — dist[1] already 3* | — skipped — | *(no change, discard)* | `{(4,3), (6,3)❌stale}` |
| 5 | (4, 3) | 3→4 (w3) | `dist[4]=7` | `{(6,3)❌stale, (7,4)}` |
| 6 | (6,3) *stale — dist[3] already 4* | — skipped — | *(no change, discard)* | `{(7,4)}` |
| 7 | (7, 4) | *(no outgoing edges)* | — | `{}` empty, stop |

✅ **Final `dist[] = [0, 3, 1, 4, 7]`**

> 💡 Notice the "stale" entries — since we never remove old heap entries when a shorter distance is found, the heap can hold outdated pairs. We simply **skip** them when popped by checking if the popped distance still matches `dist[node]`.

---

## ⏱️ Complexity Analysis

| Type | Complexity | Reason |
|------|------------|--------|
| ⏳ Time | `O(E log V)` | Each edge can trigger a heap push/pop → `O(log V)` per operation, done for up to `E` edges |
| 💾 Space | `O(V + E)` | Adjacency list `O(V + E)`, `dist[]` array `O(V)`, priority queue can hold up to `O(E)` entries |

---

## ⚠️ Limitations

- ❌ **Does not work with negative edge weights.** A negative edge can make a "finalized" node's distance invalid later, but Dijkstra never revisits a finalized node — leading to a wrong (too large) answer.
- ❌ **Does not work with negative weight cycles.** The total path cost can keep decreasing forever, so the shortest path is technically undefined (`-∞`), and the algorithm has no way to detect or terminate this correctly.
- ✅ For graphs with negative weights, use **Bellman-Ford Algorithm** instead.

---

## 🧩 Pattern Recognition (for future problems)

This is the classic **"Single Source Shortest Path with Non-Negative Weights"** pattern. Recognize it when:
- 🟢 Graph has **weighted edges**, and all weights are **`>= 0`**
- 🟢 Question asks for **minimum cost / minimum distance / cheapest path**
- 🟢 Graph can be **directed or undirected**, cyclic or acyclic — Dijkstra doesn't care about cycles as long as weights are non-negative

Common variants that reuse this exact pattern:
- Network Delay Time
- Cheapest Flights (with relaxed constraints)
- Path with Minimum Effort / Minimum Maximum edge weight (modified relaxation)
- Swim in Rising Water style problems

> 📄 Full C++ implementation is provided separately in `dijkstra.cpp` (kept out of this README as requested).
