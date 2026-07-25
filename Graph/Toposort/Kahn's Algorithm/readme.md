# Kahn's Algorithm — Topological Sort using BFS

## Definition

Kahn's Algorithm is a **BFS-based approach** to perform Topological Sort on a **Directed Acyclic Graph (DAG)**. It produces a linear ordering of vertices such that for every directed edge `u -> v`, `u` appears before `v` in the ordering.

> Like the DFS-based approach, this only works on **DAGs**. Cycles make a valid linear order impossible since no node in a cycle can be said to "come first."

---

## The Role of In-Degree

- **In-degree** of a node = number of incoming edges to it.
- A node with **in-degree 0** has no unresolved dependency — it can safely appear at the start of the ordering.
- The core idea of Kahn's algorithm: repeatedly pick nodes with in-degree 0, "remove" them from the graph (conceptually), and update the in-degree of their neighbors. Any neighbor whose in-degree drops to 0 becomes eligible next.

```
indegree(node) == 0   =>   no one depends on it being placed after something else
                       =>   safe to add to result right now
```

---

## Algorithm Steps

1. **Initialization**
   - Compute in-degree of every node by scanning the adjacency list.
   - Push all nodes with in-degree `0` into a queue.
2. **Processing (BFS)**
   - Pop a node from the front of the queue, append it to the result.
   - For each neighbor of that node, decrement its in-degree by 1.
   - If a neighbor's in-degree becomes `0`, push it into the queue.
3. **Result**
   - Repeat until the queue is empty. The order in which nodes were popped is the topological ordering.

---

## Pseudocode

```
function kahnTopoSort(V, adj):
    indegree = array of size V, all 0
    for node from 0 to V-1:
        for neighbor in adj[node]:
            indegree[neighbor]++

    queue = empty queue
    for node from 0 to V-1:
        if indegree[node] == 0:
            queue.push(node)

    result = []
    while queue not empty:
        node = queue.pop_front()
        result.append(node)
        for neighbor in adj[node]:
            indegree[neighbor]--
            if indegree[neighbor] == 0:
                queue.push(neighbor)

    return result
```

---

## Graph used in the example (`main()`)

```
        5 ----> 0
        |       ^
        |       |
        v       |
        2       4
        |       |
        v       |
        3 ----> 1
```

Edges:
```
5 -> 0
5 -> 2
4 -> 0
4 -> 1
2 -> 3
3 -> 1
```

---

## Dry Run

**Step 1 — compute in-degrees:**

| Node | Incoming edges | In-degree |
|------|-----------------|-----------|
| 0 | from 5, 4 | 2 |
| 1 | from 4, 3 | 2 |
| 2 | from 5 | 1 |
| 3 | from 2 | 1 |
| 4 | none | 0 |
| 5 | none | 0 |

Initial queue (in-degree 0 nodes): `[4, 5]`

**Step 2 — BFS processing:**

| Step | Pop | Result so far | Neighbors updated | New in-degree 0 → pushed | Queue after |
|------|-----|----------------|--------------------|----------------------------|-------------|
| 1 | 4 | `[4]` | 0 (2→1), 1 (2→1) | none | `[5]` |
| 2 | 5 | `[4,5]` | 0 (1→0), 2 (1→0) | 0, 2 | `[0,2]` |
| 3 | 0 | `[4,5,0]` | (no outgoing edges) | none | `[2]` |
| 4 | 2 | `[4,5,0,2]` | 3 (1→0) | 3 | `[3]` |
| 5 | 3 | `[4,5,0,2,3]` | 1 (1→0) | 1 | `[1]` |
| 6 | 1 | `[4,5,0,2,3,1]` | (no outgoing edges) | none | `[]` |

**Final topological order:**
```
4 5 0 2 3 1
```

Check validity:
- `5->0` ✅, `5->2` ✅, `4->0` ✅, `4->1` ✅, `2->3` ✅, `3->1` ✅

All dependencies respected — valid topological order (note: this order differs from the DFS-based one, since multiple valid orderings can exist for the same DAG).

---

## Complexity Analysis

| Complexity | Value | Reason |
|------------|-------|--------|
| Time | `O(V + E)` | Each node is pushed/popped from the queue once, and each edge is examined once while decrementing in-degrees. |
| Space | `O(V)` | For the `indegree` array and the `queue` (worst case holds all V nodes), plus `O(V)` for the result array. |

---

## Edge Cases

- **Disconnected graph / multiple components**: All independent in-degree-0 nodes across components start in the queue together, so every component gets processed.
- **Cycle in the graph**: This is Kahn's algorithm's built-in advantage — if a cycle exists, the nodes inside it never reach in-degree 0, so they never enter the queue. **If `result.size() < V` at the end, the graph has a cycle** — this makes Kahn's algorithm a natural way to detect cycles, unlike the plain DFS-stack method.
- **Single node, no edges**: In-degree 0 immediately, queue has just that node, result is `[node]`.
- **Multiple nodes with in-degree 0 initially**: Order among them depends on queue insertion order (loop order `0` to `V-1`), so multiple valid topological orders can result — this is expected and fine.

---

## Kahn's (BFS) vs DFS-based Topological Sort

| Aspect | Kahn's Algorithm (BFS) | DFS-based |
|--------|--------------------------|-----------|
| Data structure | Queue + in-degree array | Recursion stack + stack |
| Cycle detection | Built-in (`result.size() < V` implies cycle) | Not built-in, needs extra path-tracking |
| Approach | Iterative | Recursive (can hit stack overflow on very deep graphs) |
| Time | `O(V + E)` | `O(V + E)` |
| Space | `O(V)` | `O(V)` |

---

## Files

- `kahns_algorithm_bfs.cpp` — clean C++ implementation (in-degree + queue based topo sort) with a sample `main()`.
- `README.md` — this file.
