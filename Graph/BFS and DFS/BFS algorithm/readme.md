# BFS (Breadth First Search)

## Concept

**Breadth First Search (BFS)** is a graph traversal algorithm that explores nodes **level by level**.

It first visits all immediate neighbors of a node, then their neighbors, and continues in this manner.

BFS uses a **Queue (FIFO)**.

## Algorithm

1. Create an adjacency list for the graph.
2. Maintain a `visited` array to track visited nodes.
3. Start BFS from an unvisited node.
4. Mark the starting node as visited and push it into the queue.
5. Take the front node from the queue.
6. Process that node.
7. Check all its neighbors.
8. If a neighbor is not visited:

   * Mark it as visited.
   * Push it into the queue.
9. Continue until the queue becomes empty.
10. For a disconnected graph, start BFS again from every remaining unvisited node.

## Example

Graph:

```text
      0
     / \
    1   2
   / \   \
  3   4   5
```

Starting BFS from `0`:

```text
0 → 1 → 2 → 3 → 4 → 5
```

BFS traverses level by level:

```text
Level 0: 0

Level 1: 1, 2

Level 2: 3, 4, 5
```

## Why Queue is Used

BFS needs to process nodes in the same order in which they are discovered.

```text
Push 0

Queue: [0]

Process 0 → Push 1, 2

Queue: [1, 2]

Process 1 → Push 3, 4

Queue: [2, 3, 4]
```

Because a queue follows **FIFO (First In First Out)**, nodes are processed level by level.

## Why `visited` is Required

Graphs can contain cycles.

```text
0 → 1 → 2 → 0
```

Without a `visited` array, the same nodes could be inserted into the queue repeatedly.

Therefore, a node is marked **visited when it is pushed into the queue**.

## Complexity

**Time Complexity:** `O(V + E)`

Each vertex is visited once and every edge is examined.

**Space Complexity:** `O(V)`

Space is required for the `visited` array and queue.

Where:

* `V` = number of vertices
* `E` = number of edges

## Key Point

**DFS → Goes depth-wise → Recursion / Stack**

**BFS → Goes level-wise → Queue**

BFS is also commonly used to find the **shortest path in an unweighted graph**.
