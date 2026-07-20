# 📊 Graph Basics in C++

> A graph is a non-linear data structure used to represent relationships between objects. It consists of **vertices (nodes)** connected by **edges**.

---

# 📚 Table of Contents

- Graph Terminology
- Types of Graphs
- Cycles
- Paths
- Directed Acyclic Graph (DAG)
- Degree of a Node
- Edge Weights
- Graph Representations
- Connected Components
- Complexity Analysis

---

# Graph Terminology

## Vertex (Node)

A vertex is a point in the graph.

```
A   B   C
```

---

## Edge

An edge connects two vertices.

```
A ----- B
```

---

# Types of Graphs

## Undirected Graph

The connection works in both directions.

```
1 ----- 2
|       |
3 ----- 4
```

If an edge exists between **u** and **v**, then

- u is connected to v
- v is connected to u

---

## Directed Graph

Edges have directions.

```
1 ----> 2
^       |
|       v
4 <---- 3
```

Here, movement is only allowed in the arrow direction.

---

# Cycles

A cycle exists if we can start from a node and return to the same node following the edges.

Example

```
1
| \
|  \
2---3
```

Cycle:

```
1 → 2 → 3 → 1
```

---

# Acyclic Graph

A graph without any cycle is called an **Acyclic Graph**.

---

# Directed Acyclic Graph (DAG)

A directed graph with no cycles is called a **Directed Acyclic Graph (DAG)**.

Example

```
1 → 2 → 4
↓
3 → 5
```

DAGs are widely used for dependency ordering and scheduling problems.

---

# Path

A path is a sequence of connected vertices where no vertex is visited more than once.

Example

```
1 → 3 → 5 → 7
```

Length of path = Number of edges used.

---

# Degree of a Node

## Undirected Graph

Degree = Number of edges connected to the node.

Example

```
    2
   /
1--3--4
   \
    5
```

Degree of node 3 = **4**

---

## Directed Graph

Two different degrees exist.

### In-Degree

Number of incoming edges.

### Out-Degree

Number of outgoing edges.

Example

```
1 → 2 ← 3
     |
     ↓
     4
```

Node 2

- In-Degree = 2
- Out-Degree = 1

---

# Edge Weights

Sometimes edges store additional information called **weights**.

Example

```
A --5-- B
 \      |
  2     8
   \    |
     C
```

The numbers represent the cost or distance between vertices.

If no weight is specified, every edge is assumed to have weight **1**.

---

# Graph Representations

There are two common ways to store graphs.

---

## 1. Adjacency Matrix

A 2D matrix stores whether an edge exists.

Example

```
    1 2 3
1   0 1 1
2   1 0 0
3   1 0 0
```

### Space Complexity

```
O(N²)
```

### Advantages

- Easy edge lookup
- Simple implementation

### Disadvantages

- High memory usage
- Inefficient for sparse graphs

---

## 2. Adjacency List

Each vertex stores a list of its neighbors.

Example

```
1 → 2 3
2 → 1
3 → 1
```

### Space Complexity

Undirected Graph

```
O(2E)
```

Directed Graph

```
O(E)
```

Overall storage

```
O(N + E)
```

### Advantages

- Memory efficient
- Preferred in competitive programming
- Faster traversal

---

# Weighted Graph Representation

Store both the neighbor and the edge weight.

Example

```
1 → (2,5)
1 → (3,2)
2 → (4,7)
```

Each pair stores

```
(Neighbor, Weight)
```

---

# Graph Input

A graph contains

- N vertices
- E edges

For every edge

```
u v
```

Undirected Graph

```
u → v
v → u
```

Directed Graph

```
u → v
```

Weighted Graph

```
u v w
```

where

- u = source
- v = destination
- w = weight

---

# Connected Components

A graph may consist of multiple disconnected parts.

Example

```
1 --- 2

3 --- 4 --- 5

6
```

This graph has **3 connected components**.

---

## Why Traversing Once Isn't Enough?

If traversal starts only from node **1**, only

```
1 2
```

will be visited.

Remaining components remain unvisited.

---

## Complete Traversal Strategy

Maintain a visited array.

Loop through every vertex.

If a vertex has not been visited, start a DFS or BFS from that vertex.

```
for every node
    if not visited
        run DFS/BFS
```

This guarantees every vertex in every connected component is explored.

---

# Complexity Analysis

| Representation | Space |
|---------------|--------|
| Adjacency Matrix | O(N²) |
| Adjacency List | O(N + E) |

Traversal

```
O(N + E)
```

---

# Summary

- Graphs consist of vertices and edges.
- Graphs can be directed or undirected.
- Cycles return to the starting node.
- A graph without cycles is acyclic.
- A directed acyclic graph is called a DAG.
- A path visits each node at most once.
- Undirected graphs use degree.
- Directed graphs use in-degree and out-degree.
- Graphs may be weighted or unweighted.
- Adjacency List is the most commonly used graph representation.
- Graphs may contain multiple connected components.
- A visited array is required to traverse every component.