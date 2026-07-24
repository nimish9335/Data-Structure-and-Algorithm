# Flood Fill

## Problem

You are given an `m x n` grid called `image`.

Each cell represents the **color of a pixel**.

You are also given:

```text
sr    → starting row
sc    → starting column
color → new color
```

Starting from `(sr, sc)`, change the color of that pixel and all **connected pixels having the same original color**.

Pixels are considered connected only in **4 directions**:

```text
       Up
        ↑
Left ← Cell → Right
        ↓
      Down
```

Diagonal pixels are not considered connected.

Return the image after performing the flood fill.

---

## Example 1

```text
Input:

image =
1 1 1
1 1 0
1 0 1

sr = 1
sc = 1
color = 2
```

Starting pixel:

```text
image[1][1] = 1
```

All `1`s connected to this pixel are changed to `2`.

```text
Output:

2 2 2
2 2 0
2 0 1
```

The bottom-right `1` remains unchanged because it is not connected horizontally or vertically to the starting region.

---

## Example 2

```text
Input:

image =
0 0 0
0 0 0

sr = 0
sc = 0
color = 0
```

Output:

```text
0 0 0
0 0 0
```

The original color and new color are already the same, so nothing changes.

---

# Solution

Use **DFS** starting from `(sr, sc)`.

Store the starting pixel's original color:

```text
oldColor = image[sr][sc]
```

During DFS:

```text
1. Change current pixel to the new color.
2. Check its 4 neighboring pixels.
3. If a neighbor has oldColor, visit it using DFS.
4. Continue until no connected oldColor pixel remains.
```

### Important Case

If:

```text
oldColor == color
```

return the image directly.

Otherwise DFS would keep finding pixels with the same color and could cause repeated recursion.

## Complexity

```text
Time  : O(m × n)
Space : O(m × n)
```

In the worst case, DFS may visit every pixel in the grid.
