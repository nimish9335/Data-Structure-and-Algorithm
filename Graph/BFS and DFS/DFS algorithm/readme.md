# DFS (Depth First Search)

## Concept

**Depth First Search (DFS)** is a graph traversal algorithm that explores one path **as deeply as possible** before backtracking and exploring another path.

DFS can be implemented using **recursion** or an explicit **stack**.

## Algorithm

1. Create an adjacency list for the graph.
2. Maintain a `visited` array to track visited nodes.
3. Start DFS from an unvisited node.
4. Mark the current node as visited.
5. Process the current node.
6. Check all neighbors of the current node.
7. If a neighbor is not visited, recursively call DFS for that neighbor.
8. When a node has no unvisited neighbors, backtrack to the previous node.
9. For a disconnected graph, start DFS again from every remaining unvisited node.

## Example

Graph:

```text
0 -- 1 -- 3s
|    |
2    4
```

Starting DFS from `0`, one possible traversal is:

```text
0 → 1 → 3 → 4 → 2
```

DFS first goes deep:

```text
0 → 1 → 3
```

No unvisited neighbor remains at `3`, so it backtracks:

```text
3 → 1
```

Then it explores the next unvisited neighbor.

## Why `visited` is Required

In graphs, nodes can be connected in cycles.

```text
0 → 1 → 2 → 0
```

Without a `visited` array, DFS could repeatedly visit:

```text
0 → 1 → 2 → 0 → 1 → 2 → ...
```

Therefore, each node is marked visited before exploring its neighbors.

## Complexity

**Time Complexity:** `O(V + E)`

Each vertex is visited once and every edge is examined.

**Space Complexity:** `O(V)`

Space is required for the `visited` array and recursion stack.

Where:

* `V` = number of vertices
* `E` = number of edges
