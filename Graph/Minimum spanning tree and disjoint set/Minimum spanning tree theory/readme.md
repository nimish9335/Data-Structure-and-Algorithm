# 🌳 Minimum Spanning Tree (MST)

---

## 📖 What is a Spanning Tree?

A **spanning tree** is a part of a graph that:

- Includes **all the nodes** of the graph.
- Has exactly **`N - 1` edges** (where `N` is the number of nodes).
- Connects every node so that **all nodes are reachable from one another**.

In short, it takes a graph and keeps just enough edges to form a **tree** — no extra edges, no disconnected nodes, and no cycles.

---

## 📖 What is a Minimum Spanning Tree (MST)?

A single graph can have **many different spanning trees**, each made by picking a different set of edges.

The **Minimum Spanning Tree (MST)** is simply the spanning tree whose edges add up to the **smallest total weight**, compared to every other possible spanning tree of that graph.

So among all the possible spanning trees, MST is the **cheapest** one.

---

## 📖 A Simple Example

Imagine a weighted graph with several nodes and edges. There can be more than one way to connect all the nodes into a spanning tree, and each way will have a different total weight.

If we try out the different combinations and pick the one with the **lowest total edge weight**, that combination is the MST.

In the example shown, the minimum possible total weight to connect all nodes turned out to be **17**.

---

## 📝 Summary

| Term | Meaning |
|------|---------|
| **Spanning Tree** | A subset of the graph with all nodes and `N - 1` edges, connecting everything without cycles |
| **MST** | The spanning tree with the **minimum total edge weight** among all possible spanning trees |
