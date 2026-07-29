# Number of Provinces

## Problem Statement

There are `n` cities. Some of them are connected, while some are not.
If city `a` is connected directly with city `b`, and city `b` is
connected directly with city `c`, then city `a` is connected indirectly
with city `c`.

A **province** is a group of directly or indirectly connected cities
and no other cities outside of the group.

You are given an `n x n` matrix `isConnected` where
`isConnected[i][j] = 1` if the `i`-th city and the `j`-th city are
directly connected, and `isConnected[i][j] = 0` otherwise.

Return the total number of provinces.

## Example

```
Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2

Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
```

## Core Concept

A **province** is essentially a **connected component** in an
undirected graph. Every node inside a province is reachable from every
other node within that same province, and no node outside the province
is reachable from within it.

So this problem reduces to a classic graph question:

> Given an undirected graph, find the number of connected components.

## Key Idea

We treat each city as a **node** in a graph, and each `1` in the
matrix (excluding the diagonal, since a city is trivially connected to
itself) as an **edge** between two cities.

Once the graph is built, we just need to count how many separate
"clusters" of connected nodes exist. This is done using **DFS or BFS**
along with a `visited` array:

1. Iterate through every node from `0` to `n - 1`.
2. If a node has **not** been visited yet, that means we've found a
   brand-new province. Increment the province counter, and run a
   DFS/BFS from that node to mark every node reachable from it as
   visited.
3. If a node has **already** been visited, skip it — it's already part
   of a province we've counted.
4. By the end of the loop, the counter holds the total number of
   provinces.

## Adjacency Matrix to Adjacency List

The input is given as an adjacency matrix (`isConnected[i][j]`), but
for efficient traversal, it helps to convert it into an **adjacency
list** first:

```cpp
vector<int> adj[n];
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (isConnected[i][j] == 1 && i != j) {
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
    }
}
```

This makes the DFS traversal cleaner and avoids repeatedly scanning
entire matrix rows during the search.

## Code

```cpp
void dfs(int node, vector<int> adj[], vector<int>& visited) {
    visited[node] = 1;
    for (auto neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited);
        }
    }
}

int numProvinces(vector<vector<int>>& isConnected, int n) {
    vector<int> adj[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (isConnected[i][j] == 1 && i != j) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    vector<int> visited(n, 0);
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            count++;
            dfs(i, adj, visited);
        }
    }

    return count;
}
```

## Dry Run

```
isConnected = [[1,1,0],
               [1,1,0],
               [0,0,1]]

Adjacency list built:
  adj[0] = [1]
  adj[1] = [0]
  adj[2] = []

visited = [0, 0, 0], count = 0

i=0: not visited -> count=1, dfs(0)
  visited[0]=1
  visit neighbor 1 -> not visited -> dfs(1)
    visited[1]=1
    neighbor 0 already visited -> return
  back to dfs(0), done

i=1: already visited -> skip

i=2: not visited -> count=2, dfs(2)
  visited[2]=1
  no neighbors -> return

Final count = 2
```

Matches the expected output of `2`.

## Time Complexity

- **Time:** `O(N^2)` for converting the adjacency matrix to a list
  (scanning the whole matrix), plus `O(N + E)` for the DFS/BFS
  traversal, where every node and edge is visited exactly once. Since
  the graph is built from an `N x N` matrix, this is often expressed
  overall as `O(N^2)`.
- **Space:** `O(N)` for the `visited` array and the recursion stack in
  the worst case (a chain-like connected component), plus `O(N + E)`
  for the adjacency list.

## Notes for Revision

- This is the standard **connected components counting** pattern:
  loop over every node, and every time you find an unvisited node,
  that's a brand-new component — run DFS/BFS to mark the rest of that
  component as visited.
- Converting an adjacency matrix to an adjacency list first is a good
  habit whenever the input is given as a matrix but the traversal
  logic is naturally list-based (cleaner code, avoids repeated row
  scans inside DFS).
- This exact same counter + DFS pattern reappears in many problems:
  "Number of Islands", "Number of Connected Components in an
  Undirected Graph", and other component-counting variants — the core
  idea barely changes.
