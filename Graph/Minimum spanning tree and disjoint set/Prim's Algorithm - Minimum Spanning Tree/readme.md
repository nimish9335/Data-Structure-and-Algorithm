# 🌳 Prim's Algorithm

---

## 📖 The Goal

Prim's Algorithm is a **greedy algorithm** used to find the **Minimum Spanning Tree (MST)** of a weighted, undirected, and connected graph.

It selects a subset of edges that connects all the vertices, contains no cycles, and has the **minimum possible total edge weight**.

---

## 📖 Core Mechanics

Prim's Algorithm relies on two simple tools:

- **Priority Queue (Min-Heap)** — always gives us the edge with the **smallest weight** available at any point.
- **Visited Array** — keeps track of which nodes are already part of the MST, so we never add an edge that would create a **cycle**.

---

## 📖 How It Works

1. Start from any **arbitrary node** (commonly node `0`) and mark it as visited.
2. Push all edges connected to this node into the priority queue.
3. Pop the edge with the **smallest weight** from the priority queue.
4. If the node on the other end of that edge is **not visited yet**:
   - Add the edge to the MST.
   - Mark that node as visited.
   - Push all its connecting edges into the priority queue.
5. If the node is **already visited**, skip that edge (adding it would create a cycle).
6. Repeat steps 3–5 until all nodes are visited.
7. The sum of all the chosen edge weights gives the **total weight of the MST**.

---

## 📖 Complexity

Each edge is pushed and popped from the priority queue at most once, so the time complexity is:

```
O(E log E)
```

where `E` is the number of edges in the graph.

---

## 📝 Summary

| Term | Meaning |
|------|---------|
| **Priority Queue** | Always picks the smallest available edge weight next |
| **Visited Array** | Prevents cycles by tracking nodes already in the MST |
| **Time Complexity** | `O(E log E)` |
