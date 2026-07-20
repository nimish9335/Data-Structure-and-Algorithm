# 🏝️ Number of Islands

> The **Number of Islands** problem is one of the most fundamental graph traversal problems on a 2D grid. It demonstrates how a matrix can be treated as a graph and solved using **Breadth First Search (BFS)** or **Depth First Search (DFS)**.

---

# 📚 Table of Contents

- Problem Statement
- Understanding the Grid
- What is an Island?
- Graph Perspective
- Key Observation
- Solution Approach
- Finding Neighbors
- BFS Algorithm
- DFS Algorithm
- Complexity Analysis
- Summary

---

# Problem Statement

Given a binary matrix

```
grid[row][col]
```

where

- **1** represents land
- **0** represents water

Return the total number of islands.

---

# Understanding the Grid

Example

```
1 1 0 0

0 1 0 0

1 0 0 1

0 0 1 1
```

Each cell is treated as one node.

---

# What is an Island?

An island is a group of connected land cells.

Two land cells belong to the same island if they are connected through any of the **8 possible directions**.

Those directions are

```
↖  ↑  ↗
←  ●  →
↙  ↓  ↘
```

This means connections are allowed

- Up
- Down
- Left
- Right
- Upper Left
- Upper Right
- Lower Left
- Lower Right

---

# Graph Perspective

Imagine every land cell is a graph node.

If two land cells touch in any of the eight directions, an edge exists between them.

Then the problem becomes

> Count the number of connected components.

Every connected component represents exactly one island.

---

# Key Observation

Whenever we discover an unvisited land cell,

```
grid[i][j] == 1
```

it must belong to a **new island**.

Start a BFS or DFS from that cell.

The traversal visits every land cell connected to it.

After traversal finishes,

the entire island has been explored.

Increase the island count by **1**.

---

# Solution Approach

Step 1

Create a visited matrix.

```
visited[row][col]
```

---

Step 2

Traverse every cell of the grid.

```
for every row

    for every column
```

---

Step 3

If

```
grid[row][col] == 1

and

visited[row][col] == false
```

then

- Increase answer
- Start BFS/DFS

---

Step 4

During traversal,

mark every connected land cell as visited.

These cells will never be processed again.

---

# Finding Neighbors

Instead of writing eight separate conditions,

generate neighbors automatically.

```
for dr = -1 to 1

    for dc = -1 to 1
```

Every pair

```
(dr, dc)
```

creates one neighboring cell.

```
newRow = row + dr

newCol = col + dc
```

Generated directions

```
(-1,-1)

(-1,0)

(-1,1)

(0,-1)

(0,1)

(1,-1)

(1,0)

(1,1)
```

Before visiting,

always check

- Inside matrix
- Land cell
- Not visited

---

# BFS Algorithm

1. Traverse every cell.
2. Find an unvisited land cell.
3. Increase island count.
4. Push it into the queue.
5. Visit all connected land cells.
6. Continue until queue becomes empty.
7. Repeat for remaining cells.

---

# DFS Algorithm

1. Traverse every cell.
2. Find an unvisited land cell.
3. Increase island count.
4. Recursively visit all eight neighboring land cells.
5. Return after every branch is explored.
6. Continue searching the matrix.

---

# Complexity Analysis

Let

- N = Number of rows
- M = Number of columns

## Time Complexity

```
O(N × M)
```

Every cell is visited only once.

Each visit checks only eight neighbors.

Since 8 is constant,

the overall complexity remains

```
O(N × M)
```

---

## Space Complexity

```
O(N × M)
```

Extra space is required for

- Visited matrix
- Queue (BFS)

or

- Recursion stack (DFS)

---

# Summary

- A matrix can be viewed as a graph.
- Every land cell represents a node.
- Connected land cells form one island.
- Every island is a connected component.
- BFS and DFS both solve the problem efficiently.
- Neighbor generation using two nested loops avoids writing eight separate conditions.
- Time Complexity is **O(N × M)**.