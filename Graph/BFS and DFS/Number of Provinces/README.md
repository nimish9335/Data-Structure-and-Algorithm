# Number of Provinces

## Problem Statement

There are `n` cities represented by an `n × n` adjacency matrix `isConnected`.

- `isConnected[i][j] = 1` → City `i` and City `j` are directly connected.
- `isConnected[i][j] = 0` → No direct connection.

A **Province** is a group of cities that are directly or indirectly connected.

Return the total number of provinces.

---

## Example 1

Input

```text
isConnected =
[
 [1,1,0],
 [1,1,0],
 [0,0,1]
]
```

Output

```text
2
```

Explanation

```text
Province 1: {0,1}
Province 2: {2}
```

---

## Example 2

Input

```text
isConnected =
[
 [1,0,0],
 [0,1,0],
 [0,0,1]
]
```

Output

```text
3
```

Explanation

```text
Each city is isolated, so each city forms its own province.
```

---

# Intuition

A province is simply a **connected component** in an undirected graph.

If we start from any city inside a province and perform DFS:

- We can visit every city belonging to that province.
- All visited cities are marked.
- When we find another unvisited city, it means we have discovered a new province.

Therefore:

```text
Number of Provinces
=
Number of Connected Components
```

---

# Approach

### Step 1: Convert Matrix → Graph

Given:

```text
[
 [1,1,0],
 [1,1,0],
 [0,0,1]
]
```

Create adjacency list:

```text
0 → 1
1 → 0
2 → -
```

---

### Step 2: Maintain Visited Array

```cpp
vector<int> vis(n, 0);
```

- 0 → Not Visited
- 1 → Visited

---

### Step 3: Traverse Every City

For every city:

```cpp
if(!vis[i])
```

then:

1. New province found.
2. Increment answer.
3. Run DFS.

---

### Step 4: DFS Traversal

DFS visits all cities reachable from the current city.

```cpp
dfs(node)
```

Mark node visited and recursively visit all unvisited neighbours.

---

# Dry Run

Input

```text
[
 [1,1,0],
 [1,1,0],
 [0,0,1]
]
```

Adjacency List

```text
0 → 1
1 → 0
2 → -
```

### Start

```text
vis = [0,0,0]
count = 0
```

### i = 0

Unvisited

```text
count = 1
DFS(0)
```

DFS visits:

```text
0 → 1
```

Now

```text
vis = [1,1,0]
```

### i = 1

Already visited

Skip

### i = 2

Unvisited

```text
count = 2
DFS(2)
```

Now

```text
vis = [1,1,1]
```

Final Answer

```text
2
```

---

# Why Does This Work?

Whenever DFS starts from an unvisited node:

- It visits every city in that connected component.
- No city from another component can be reached.
- Therefore one DFS call corresponds to exactly one province.

Hence,

```text
Number of DFS Calls
=
Number of Provinces
```

---

# Complexity Analysis

### Time Complexity

Building adjacency list:

```text
O(N²)
```

DFS traversal:

```text
O(V + E)
```

Overall:

```text
O(N²)
```

because the matrix itself contains `N²` elements.

---

### Space Complexity

Adjacency List:

```text
O(V + E)
```

Visited Array:

```text
O(V)
```

DFS Recursive Stack:

```text
O(V)
```

Total:

```text
O(V + E)
```

---

# Key Learning

- Province = Connected Component
- Matrix Graph → Adjacency List Conversion
- DFS/BFS can be used to count connected components
- Number of DFS/BFS starts = Number of Provinces

---

## Related Topics

- Graphs
- DFS
- BFS
- Connected Components
- Adjacency Matrix
- Adjacency List