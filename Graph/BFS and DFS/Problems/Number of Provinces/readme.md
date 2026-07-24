# Number of Provinces

## Problem

There are `n` cities. Some cities are directly connected to each other, while some are not.

If:

```text
City A ↔ City B
City B ↔ City C
```

then `City A` and `City C` are also considered connected **indirectly**.

A **province** is a group of cities where every city is directly or indirectly connected to the other cities in that group.

You are given an `n x n` matrix:

```text
isConnected[i][j]
```

where:

* `1` → City `i` and City `j` are directly connected.
* `0` → City `i` and City `j` are not directly connected.

Return the **total number of provinces**.

## Example 1

```text
Input:

1 1 0
1 1 0
0 0 1

Output: 2
```

Here:

```text
City 0 ↔ City 1

City 2
```

So there are two separate groups:

```text
Province 1 → {0, 1}
Province 2 → {2}
```

Therefore:

```text
Answer = 2
```

## Example 2

```text
Input:

1 0 0
0 1 0
0 0 1

Output: 3
```

No two different cities are connected.

Therefore:

```text
Province 1 → {0}
Province 2 → {1}
Province 3 → {2}
```

Hence:

```text
Answer = 3
```

## Constraints

```text
1 <= n <= 200

n == isConnected.length
n == isConnected[i].length

isConnected[i][j] = 0 or 1

isConnected[i][i] = 1

isConnected[i][j] = isConnected[j][i]
```
