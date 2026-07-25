# Topological Sort using DFS

## Definition

Topological Sort is a **linear ordering of vertices** in a **Directed Acyclic Graph (DAG)** such that for every directed edge `u -> v`, vertex `u` appears **before** vertex `v` in the ordering.

> Applies only to DAGs — a valid topological order requires:
> - The graph must be **directed** (undirected edges imply a two-way dependency, which breaks ordering).
> - The graph must be **acyclic** (a cycle means `a` depends on `b` and `b` depends on `a` — a paradox with no valid order).

---

## Why not undirected graphs?

An undirected edge `u — v` means `u` reaches `v` AND `v` reaches `u`. There is no notion of "comes before" since both directions coexist. Topological order requires a strict dependency direction, so undirected graphs are disqualified by definition.

## Why not cyclic graphs?

If a cycle exists (e.g. `1 -> 2 -> 3 -> 1`), then `1` must come before `2`, `2` before `3`, and `3` before `1` — all at once. No linear arrangement can satisfy this. Hence topological sort is only defined for **DAGs**.

---

## Core Intuition

DFS naturally finishes exploring a node's *entire subtree* before returning from it. So if we push a node onto a **stack only after all its neighbors (dependents) have been fully explored**, we guarantee that every dependency of a node sits *below* it in the stack (i.e., gets popped after it).

Once DFS finishes for all components, **popping the stack** gives nodes in an order where every prerequisite appears before the nodes depending on it.

```
Finish DFS(node) -> push node to stack
                       |
                       v
        (all its dependents are already stacked below it,
         because they finished earlier and got pushed earlier)
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

A valid topological order for this graph: `5 4 2 3 1 0` (order can vary slightly depending on adjacency list arrangement and traversal starting point, but relative dependency order is always respected).

---

## Algorithm Steps

1. Create a `visited[]` array of size `V`, initialized to `0`.
2. Create an empty `stack<int>`.
3. For every unvisited node `i` from `0` to `V-1`, call `dfs(i)`.
4. Inside `dfs(node)`:
   - Mark `node` as visited.
   - Recursively call `dfs` on every unvisited neighbor.
   - **After** the loop (i.e., after all neighbors are fully processed), push `node` onto the stack.
5. Once all components are processed, pop elements from the stack one by one — this sequence is the topological order.

---

## Pseudocode

```
function dfs(node, visited, stack, adj):
    visited[node] = true
    for neighbor in adj[node]:
        if not visited[neighbor]:
            dfs(neighbor, visited, stack, adj)
    stack.push(node)

function topoSort(V, adj):
    visited = array of size V, all false
    stack = empty stack
    for node from 0 to V-1:
        if not visited[node]:
            dfs(node, visited, stack, adj)
    result = []
    while stack not empty:
        result.append(stack.pop())
    return result
```

---

## Dry Run

Graph edges: `5->0, 5->2, 4->0, 4->1, 2->3, 3->1`

Start loop from node `0`:

| Step | Action | visited[] | Stack (bottom → top) |
|------|--------|-----------|------------------------|
| 1 | `dfs(0)` called, node 0 has no outgoing edges | {0} | push 0 → `[0]` |
| 2 | `dfs(1)` called, node 1 has no outgoing edges | {0,1} | push 1 → `[0,1]` |
| 3 | `dfs(2)` called → visits neighbor 3 | {0,1,2} | — |
| 4 | inside dfs(2): `dfs(3)` called → visits neighbor 1 (already visited, skip) | {0,1,2,3} | push 3 → `[0,1,3]` |
| 5 | back in dfs(2), no more neighbors | — | push 2 → `[0,1,3,2]` |
| 6 | `dfs(4)` called → neighbor 0 (visited), neighbor 1 (visited) | {0,1,2,3,4} | push 4 → `[0,1,3,2,4]` |
| 7 | `dfs(5)` called → neighbor 0 (visited), neighbor 2 (visited) | {0,1,2,3,4,5} | push 5 → `[0,1,3,2,4,5]` |

**Final stack (top → bottom):** `5, 4, 2, 3, 1, 0`

**Popping the stack gives the topological order:**
```
5 4 2 3 1 0
```

Check validity:
- `5->0` ✅ (5 before 0)
- `5->2` ✅ (5 before 2)
- `4->0` ✅ (4 before 0)
- `4->1` ✅ (4 before 1)
- `2->3` ✅ (2 before 3)
- `3->1` ✅ (3 before 1)

All dependencies respected — valid topological order.

---

## Complexity Analysis

| Complexity | Value | Reason |
|------------|-------|--------|
| Time | `O(V + E)` | Standard DFS traversal — every vertex and every edge is visited exactly once. |
| Space | `O(V)` | For the `visited` array, the `stack` used for result, and the recursion stack (worst case depth `V` for a skewed graph). |

---

## Edge Cases

- **Disconnected graph / multiple components**: The outer loop in `topoSort` ensures every unvisited node triggers a fresh `dfs` call, so all components get included in the final ordering.
- **Single node, no edges**: Topological order is just that single node.
- **Graph with a cycle**: This DFS-based approach does **not** detect cycles by itself — running it on a cyclic graph will still produce *some* ordering, but it won't be a valid topological order. A separate cycle-detection step (e.g., tracking a recursion-stack/path-visited array) is required if cycle safety must be guaranteed.
- **Multiple valid answers**: A DAG can have more than one valid topological ordering; the exact order Claude/this algorithm produces depends on the order nodes are iterated and how the adjacency list is built. All such orders are equally "correct" as long as dependency constraints hold.

---

## Files

- `topological_sort_dfs.cpp` — clean C++ implementation (DFS + stack-based topo sort) with a sample `main()`.
- `README.md` — this file.
