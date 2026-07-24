# Rotten Oranges

## Problem

You are given an `m x n` grid where each cell contains one of three values:

* `0` → Empty cell
* `1` → Fresh orange
* `2` → Rotten orange

Every **1 minute**, a fresh orange becomes rotten if it is directly adjacent to a rotten orange.

An orange can affect another orange in **4 directions**:

```text
        Up
         ↑
Left ← Cell → Right
         ↓
       Down
```

Diagonal oranges are **not considered adjacent**.

The goal is to return the **minimum number of minutes** required until there are no fresh oranges remaining.

If some fresh orange can never become rotten, return:

```text
-1
```

If there are no fresh oranges initially, return:

```text
0
```

## Example 1

```text
Input:

2 1 1
1 1 0
0 1 1

Output: 4
```

All fresh oranges can eventually become rotten, and the process requires `4 minutes`.

## Example 2

```text
Input:

2 1 1
0 1 1
1 0 1

Output: -1
```

The orange at the bottom-left cannot be reached by any rotten orange because movement is allowed only in four directions.

Therefore, it can never become rotten.

## Example 3

```text
Input:

0 2

Output: 0
```

There are no fresh oranges initially, so no time is required.

## Constraints

```text
1 <= m, n <= 10

grid[i][j] = 0, 1, or 2
```
