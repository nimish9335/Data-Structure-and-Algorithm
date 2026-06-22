# Rotting Oranges

## Problem Statement

You are given a grid where:

* `0` → Empty Cell
* `1` → Fresh Orange
* `2` → Rotten Orange

Every minute, any fresh orange adjacent (up, down, left, right) to a rotten orange becomes rotten.

Return the minimum number of minutes required to rot all oranges. If impossible, return `-1`.

---

# Key Observation

All rotten oranges spread infection simultaneously.

This is a classic **Multi-Source BFS** problem.

Instead of starting BFS from one node, we start from **all rotten oranges at once**.

---

# Visual Understanding

Input:

```text
[
 [2,1,1],
 [1,1,0],
 [0,1,1]
]
```

Legend:

```text
🟩 = Fresh Orange
🟥 = Rotten Orange
⬜ = Empty Cell
```

---

## Minute 0

```text
🟥 🟩 🟩
🟩 🟩 ⬜
⬜ 🟩 🟩
```

Initial rotten orange:

```text
(0,0)
```

Queue:

```text
[(0,0)]
```

---

## Minute 1

Orange at (0,0) rots:

```text
(0,1)
(1,0)
```

Grid:

```text
🟥 🟥 🟩
🟥 🟩 ⬜
⬜ 🟩 🟩
```

Queue:

```text
[(0,1),(1,0)]
```

---

## Minute 2

Rotten oranges spread again.

New rotten oranges:

```text
(0,2)
(1,1)
```

Grid:

```text
🟥 🟥 🟥
🟥 🟥 ⬜
⬜ 🟩 🟩
```

Queue:

```text
[(0,2),(1,1)]
```

---

## Minute 3

New rotten orange:

```text
(2,1)
```

Grid:

```text
🟥 🟥 🟥
🟥 🟥 ⬜
⬜ 🟥 🟩
```

Queue:

```text
[(2,1)]
```

---

## Minute 4

New rotten orange:

```text
(2,2)
```

Grid:

```text
🟥 🟥 🟥
🟥 🟥 ⬜
⬜ 🟥 🟥
```

Queue:

```text
[(2,2)]
```

All oranges are rotten.

Answer:

```text
4
```

---

# Why BFS?

Suppose:

```text
2 → 1 → 1 → 1
```

After:

```text
Minute 1 -> first orange rots
Minute 2 -> second orange rots
Minute 3 -> third orange rots
```

Each BFS level represents exactly **one minute**.

Therefore:

```text
Number of BFS Levels
=
Number of Minutes
```

---

# Algorithm

### Step 1

Push all rotten oranges into queue.

```cpp
if(grid[i][j] == 2)
    q.push({i,j});
```

---

### Step 2

Run BFS level by level.

Each level represents one minute.

```cpp
while(!q.empty())
```

---

### Step 3

Explore 4 directions.

```cpp
Up
Down
Left
Right
```

---

### Step 4

If fresh orange found:

```cpp
grid[nr][nc] = 2;
q.push({nr,nc});
```

---

### Step 5

After BFS ends:

If any fresh orange remains:

```cpp
return -1;
```

otherwise:

```cpp
return minutes;
```

---

# Dry Run Summary

```text
Minute 0 -> 1 Rotten Orange

Minute 1 -> 2 New Rotten Oranges

Minute 2 -> 2 New Rotten Oranges

Minute 3 -> 1 New Rotten Orange

Minute 4 -> 1 New Rotten Orange

Total Time = 4
```

---

# Intuition

Think of rotten oranges as a virus.

```text
Virus spreads every minute
to all adjacent cells
simultaneously.
```

Whenever something spreads layer by layer:

```text
Shortest Path
Fire Spread
Infection Spread
Rotting Oranges
```

BFS should immediately come to mind.

---

# Complexity Analysis

### Time Complexity

```text
O(N × M)
```

Each cell is visited at most once.

---

### Space Complexity

```text
O(N × M)
```

Queue may contain all cells in worst case.

---

# Pattern Recognition

Whenever the problem says:

* Spread
* Infection
* Fire
* Virus
* Minimum Time
* Level by Level Expansion

Think:

```text
Multi-Source BFS
```

This is one of the most important BFS interview patterns.
