# 🌐 Graph Traversal - Breadth First Search (BFS) & Depth First Search (DFS)

> Graph traversal is the process of visiting every vertex of a graph in a systematic manner. The two most fundamental traversal algorithms are **Breadth First Search (BFS)** and **Depth First Search (DFS)**.

---

# 📚 Table of Contents

- Graph Traversal
- Breadth First Search (BFS)
- BFS Algorithm
- BFS Example
- BFS Complexity
- Depth First Search (DFS)
- DFS Algorithm
- DFS Example
- DFS Complexity
- BFS vs DFS
- Complete Traversal for Disconnected Graphs
- Summary

---

# Graph Traversal

Graph traversal means visiting the vertices of a graph following a specific order.

The two standard traversal techniques are

- Breadth First Search (BFS)
- Depth First Search (DFS)

Both algorithms ensure that every reachable vertex is visited exactly once.

---

# Breadth First Search (BFS)

Breadth First Search explores a graph **level by level**.

Starting from a source vertex, it first visits all immediate neighbors before moving to the next level.

```
Level 0

      1

Level 1

   2     3

Level 2

 4  5   6  7
```

Traversal

```
1 → 2 → 3 → 4 → 5 → 6 → 7
```

---

# BFS Working Principle

BFS follows the **FIFO (First In First Out)** principle.

A queue is used to maintain the order of traversal.

Required Data Structures

- Queue
- Visited Array

---

# BFS Algorithm

1. Insert the starting node into the queue.
2. Mark the node as visited.
3. Remove the front node from the queue.
4. Visit the node.
5. Push every unvisited neighbor into the queue.
6. Repeat until the queue becomes empty.

---

# BFS Example

Graph

```
        1
      /   \
     2     3
    / \   / \
   4   5 6   7
```

Queue Progress

```
Queue

[1]

↓

Visit 1

[2 3]

↓

Visit 2

[3 4 5]

↓

Visit 3

[4 5 6 7]

↓

Visit 4

[5 6 7]

↓

Visit 5

[6 7]

↓

Visit 6

[7]

↓

Visit 7

[]
```

Traversal Order

```
1 2 3 4 5 6 7
```

---

# BFS Complexity

| Operation | Complexity |
|-----------|------------|
| Time | O(N + E) |
| Space | O(N) |

Where

- N = Number of Vertices
- E = Number of Edges

Each vertex is visited once.

Each edge is processed once (directed graph) or twice (undirected graph).

---

# Depth First Search (DFS)

Depth First Search explores a graph by moving as deep as possible before backtracking.

Instead of visiting every neighbor first, DFS continues exploring one branch completely.

```
        1
      /   \
     2     3
    / \
   4   5
```

Possible Traversal

```
1 → 2 → 4

Backtrack

2 → 5

Backtrack

1 → 3
```

---

# DFS Working Principle

DFS naturally follows recursion.

Required Data Structures

- Visited Array
- Recursive Call Stack

---

# DFS Algorithm

1. Visit the current node.
2. Mark it as visited.
3. Traverse every unvisited neighbor recursively.
4. Return automatically when all neighbors are explored.
5. Continue exploring remaining branches.

---

# DFS Example

Graph

```
        1
      /   \
     2     3
    / \
   4   5
```

Recursive Calls

```
DFS(1)

↓

DFS(2)

↓

DFS(4)

↓

Return

↓

DFS(5)

↓

Return

↓

Return

↓

DFS(3)
```

Traversal

```
1 2 4 5 3
```

---

# DFS Backtracking

Backtracking happens automatically.

When a node has no unvisited neighbors, recursion returns to its parent.

```
1
|
2
|
3

↓

Return to 2

↓

Return to 1
```

---

# DFS Complexity

| Operation | Complexity |
|-----------|------------|
| Time | O(N + E) |
| Space | O(N) |

Space is required for

- Visited Array
- Recursive Stack

---

# BFS vs DFS

| Feature | BFS | DFS |
|----------|-----|-----|
| Traversal | Level Wise | Depth Wise |
| Data Structure | Queue | Recursion / Stack |
| Order | Nearest First | Deepest First |
| Backtracking | No | Yes |
| Space | O(N) | O(N) |
| Time | O(N + E) | O(N + E) |

---

# Traversing Disconnected Graphs

A single BFS or DFS only explores the connected component containing the starting node.

To traverse the complete graph

```
for every node

    if node is not visited

        perform BFS/DFS
```

This ensures every connected component is visited.

---

# Summary

- Graph traversal visits vertices in a systematic order.
- BFS explores vertices level by level.
- DFS explores one branch completely before backtracking.
- BFS uses a queue.
- DFS uses recursion (or a stack).
- A visited array prevents revisiting vertices.
- Both BFS and DFS run in **O(N + E)** time.
- For disconnected graphs, initiate traversal from every unvisited vertex.