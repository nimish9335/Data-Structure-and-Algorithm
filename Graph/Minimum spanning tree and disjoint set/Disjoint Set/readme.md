# 🔗 Disjoint Set Data Structure (Union-Find)

---

## 📖 What is it?

The **Disjoint Set** data structure (also called **Union-Find**) is used in graph theory to manage **dynamic graphs** — graphs where edges keep getting added over time — and to efficiently answer one key question:

> **"Do these two nodes belong to the same component?"**

It supports two main operations:

- **Find** — figure out which component a node belongs to.
- **Union** — merge two components into one.

---

## 📖 Find Parent (Ultimate Parent)

Every node has a **parent**, and by following the parent chain repeatedly, we eventually reach the **ultimate parent** — the "root boss" of that entire component.

### Path Compression

While finding the ultimate parent, we can **directly attach every visited node to the ultimate parent**. This flattens the tree so that future `find` calls on those nodes are almost instant.

```
findParent(node):
    if node is its own parent:
        return node
    parent[node] = findParent(parent[node])   // path compression
    return parent[node]
```

---

## 📖 Union Operation

`union` connects two components by linking the ultimate parent of one to the ultimate parent of the other. There are two common strategies to decide **which parent attaches to which**, so the resulting tree stays shallow.

### 1️⃣ Union by Rank

- **Rank** roughly represents the height of a tree.
- The tree with the **smaller rank** is attached under the tree with the **larger rank**.
- If both ranks are equal, attach either one and increase the resulting rank by 1.

### 2️⃣ Union by Size

- **Size** represents the total number of nodes in a component.
- The component with the **smaller size** is attached under the component with the **larger size**.
- After merging, the size of the new root is updated to the sum of both sizes.
- The narrator notes this is often more **intuitive** than rank, since size directly answers "how many nodes are in this group."

---

## 📖 Efficiency

Using **path compression** together with **either** union by rank **or** union by size makes both `find` and `union` run in **almost constant time**, denoted as:

```
O(4α)  ≈  O(1)
```

where `α` is the inverse Ackermann function, which grows so slowly that it's effectively constant for any realistic input size.

---

## 📖 Implementation Notes

The video builds a reusable `DisjointSet` class in C++ that:

- Has a **constructor** that resizes the `parent`, `rank`, and `size` arrays for `n` nodes.
- Implements `findUPar` (find ultimate parent) with path compression.
- Implements both `unionByRank` and `unionBySize`.
- Is used to check whether two nodes are connected **before** and **after** performing a union.

---

## 📝 Summary

| Term | Meaning |
|------|---------|
| **Find Parent** | Locates the ultimate parent (root) of a node |
| **Path Compression** | Flattens the tree during find, speeding up future queries |
| **Union by Rank** | Attaches shorter tree under the taller tree |
| **Union by Size** | Attaches smaller component under the larger component |
| **Time Complexity** | `O(4α)` ≈ constant time per operation |

---

## 🖥️ C++ Implementation

See [`disjoint_set.cpp`](./disjoint_set.cpp)
