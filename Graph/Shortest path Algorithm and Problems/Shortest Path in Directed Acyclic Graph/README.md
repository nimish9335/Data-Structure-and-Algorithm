# 🧭 Shortest Path in a Directed Acyclic Graph (DAG) — Topological Sort + Edge Relaxation

![Topic](https://img.shields.io/badge/Topic-Graphs-blueviolet?style=for-the-badge)
![Algorithm](https://img.shields.io/badge/Algorithm-TopoSort%20%2B%20Relaxation-orange?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium--Hard-yellow?style=for-the-badge)
![Time](https://img.shields.io/badge/Time-O(V%2BE)-green?style=for-the-badge)
![Space](https://img.shields.io/badge/Space-O(V%2BE)-red?style=for-the-badge)

---

## ❓ Problem Statement

> Given a **weighted Directed Acyclic Graph (DAG)** with `V` vertices and `E` edges, find the **shortest distance from a given source node to every other node**.
>
> Edges can have **any weight** (not necessarily 1) — but since the graph is a **DAG** (no cycles), we can solve this **faster than Dijkstra's Algorithm**.
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
V = 8, src = 6
Edges (u -> v, weight):
6 -> 4 (w=1)   6 -> 1 (w=2)
4 -> 0 (w=1)   4 -> 5 (w=4)
1 -> 0 (w=2)   1 -> 2 (w=6)
5 -> 0 (w=1)   5 -> 3 (w=2)
0 -> 3 (w=3)   2 -> 7 (w=1)
3 -> 2 (w=6)

Output:
dist[] = [2, 2, 8, 5, 1, 5, 0, 9]
```

### 🚧 Constraints
- Graph is **directed and acyclic (no cycles)**
- Edge weights can be **positive, negative, or zero** (unlike Dijkstra, negative weights are fine here!)
- Graph may be **disconnected**

---

## 🧠 Why Topological Sort + Relaxation? (Core Intuition)

🟢 In a DAG, we can arrange all nodes in a line such that **every edge points forward** (left → right). This ordering is called a **Topological Order**.

If we process nodes strictly in this order, then **by the time we reach any node `u`, every node that could possibly shorten the path to `u` has already been fully processed.** So a single left-to-right pass is enough — no need to revisit nodes like Dijkstra's priority queue does.

> ⚡ This is why DAG shortest path beats Dijkstra's `O((V+E) log V)` — it runs in a clean `O(V + E)`, and it even works correctly with **negative edge weights**, which Dijkstra cannot handle.

---

## 🗺️ Step-by-Step Algorithm

### 🔹 Step 1 — Topological Sort (DFS based)
- For every unvisited node, run DFS
- After exploring **all** neighbors of a node, push that node onto a **stack**
- Once DFS finishes for all nodes, popping the stack gives nodes in **topological order**

### 🔹 Step 2 — Initialize Distance Array
Create `dist[]` of size `V`, fill every value with **infinity (∞)**, except:
```
dist[src] = 0
```

### 🔹 Step 3 — Edge Relaxation in Topological Order
- Pop nodes one by one from the topological stack
- For the popped node `u`, if `dist[u] != ∞`:
  - For every edge `u -> v` with weight `w`:
    - If `dist[u] + w < dist[v]` → update `dist[v] = dist[u] + w`

### 🔹 Step 4 — Build the Result
- Any node still holding `∞` → unreachable → report `-1`
- Return `dist[]`

---

## 🎨 Visual Walkthrough

### Graph used in the example above:

<table>
<tr><td>

```
        6
      1/ \2
      1    4
     /|    |\
    0 2   1 4
    |  \  |/ \
    3   6 0   5
     \ / |    |
      2  3 -- 1
      |
      7
```

*(Simplified — see edge list above for exact directed weighted edges)*

</td></tr>
</table>

### 🌈 Topological order → processing sequence (color = position in stack)

<table>
<tr>
<th>🟦 1st</th>
<th>🟩 2nd</th>
<th>🟨 3rd</th>
<th>🟧 4th</th>
<th>🟪 5th</th>
<th>🟥 6th</th>
<th>🟫 7th</th>
<th>⬛ 8th</th>
</tr>
<tr>
<td bgcolor="#8ecaff" align="center"><b>6</b></td>
<td bgcolor="#8fffb0" align="center"><b>1</b></td>
<td bgcolor="#fff98f" align="center"><b>4</b></td>
<td bgcolor="#ffc08f" align="center"><b>5</b></td>
<td bgcolor="#d8a6ff" align="center"><b>0</b></td>
<td bgcolor="#ff8f8f" align="center"><b>3</b></td>
<td bgcolor="#c9a27a" align="center"><b>2</b></td>
<td bgcolor="#bfbfbf" align="center"><b>7</b></td>
</tr>
</table>

**Reading it:** Node `6` (source) is relaxed first, so every node it can reach gets its *first* distance update immediately. By the time we process node `2`, nodes `1`, `3`, and `5` (all of which feed into `2`) are already finalized — so `dist[2]` computed at that point is guaranteed optimal.

---

## 🔍 Dry Run Table

Topological order (stack popped): `6, 1, 4, 5, 0, 3, 2, 7`
Starting distances: `[∞, ∞, ∞, ∞, ∞, ∞, 0, ∞]` *(index = node, dist[6] = 0)*

| Step | Node Processed | Edges Relaxed | Updated `dist[]` |
|------|-----------------|----------------|-------------------|
| 1 | 6 | 6→4 (w1), 6→1 (w2) | `dist[4]=1, dist[1]=2` |
| 2 | 1 | 1→0 (w2), 1→2 (w6) | `dist[0]=4, dist[2]=8` |
| 3 | 4 | 4→0 (w1), 4→5 (w4) | `dist[0]=2` (improved from 4), `dist[5]=5` |
| 4 | 5 | 5→0 (w1), 5→3 (w2) | `dist[0]` stays `2` (6 not shorter), `dist[3]=7` |
| 5 | 0 | 0→3 (w3) | `dist[3]=5` (improved from 7) |
| 6 | 3 | 3→2 (w6) | `dist[2]` stays `8` (11 not shorter) |
| 7 | 2 | 2→7 (w1) | `dist[7]=9` |
| 8 | 7 | *(no outgoing edges)* | — |

✅ Final: `dist[] = [2, 2, 8, 5, 1, 5, 0, 9]` — verified by running the accompanying `shortest_path_dag.cpp`.

Once all nodes are processed, `dist[]` holds the **final shortest distances**. Replace `∞` with `-1` for unreachable nodes.

---

## ⏱️ Complexity Analysis

| Type | Complexity | Reason |
|------|------------|--------|
| ⏳ Time | `O(V + E)` | Topological sort takes `O(V + E)`; relaxation visits every edge exactly once more → `O(V + E)` |
| 💾 Space | `O(V + E)` | Adjacency list `O(V + E)`, plus `O(V)` for `dist[]`, visited array, and the topological stack |

> 🆚 **Compared to Dijkstra:** Dijkstra is `O((V + E) log V)` and **cannot** handle negative weights. DAG shortest path is faster (`O(V + E)`) and negative-weight-safe — but **only works because the graph has no cycles**.

---

## 🧩 Pattern Recognition (for future problems)

This is the classic **"DAG Shortest/Longest Path via Topological Order"** pattern. Recognize it when:
- 🟢 Graph is explicitly **directed and acyclic**
- 🟢 Edge weights can be **arbitrary (including negative)**
- 🟢 Question mentions **"dependencies"**, **"prerequisites"**, or **"scheduling"** alongside costs/durations

Common variants that reuse this exact pattern:
- Longest path in a DAG (just flip the relaxation comparison to `>`)
- Course Schedule with time/cost constraints
- Critical Path Method (CPM) in project scheduling
- Longest Increasing Path style DP-on-DAG problems

> 📄 Full C++ implementation is provided separately in `shortest_path_dag.cpp` (kept out of this README as requested).
