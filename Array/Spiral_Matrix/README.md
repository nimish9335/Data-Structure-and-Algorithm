# Spiral Matrix

## Question

Given an `n x m` matrix, print/return all the elements of the matrix in spiral order — starting from the top-left corner, moving right, then down, then left, then up, and repeating this cycle inward until every element has been visited.

### Test Case 1
**Input:**
```
3 3
1 2 3
4 5 6
7 8 9
```
**Output:**
```
1 2 3 6 9 8 7 4 5
```

### Test Case 2
**Input:**
```
3 4
1 2 3 4
5 6 7 8
9 10 11 12
```
**Output:**
```
1 2 3 4 8 12 11 10 9 5 6 7
```

## Solution Explanation

This problem and its solution are explained in Striver's A2Z DSA Course video on printing a matrix in spiral order.

### The Pattern
Spiral traversal follows a repeating cycle of four directions: **Right → Bottom → Left → Top**. The traversal starts at the top-left of the matrix, sweeps right across the top row, then down the rightmost column, then left across the bottom row, then up the leftmost column, and this cycle repeats on the next inner "layer" of the matrix until all elements have been covered.

### Implementation Strategy
The approach uses four pointers to track the current boundaries of the unvisited portion of the matrix:
- `top` — the topmost unvisited row
- `bottom` — the bottommost unvisited row
- `left` — the leftmost unvisited column
- `right` — the rightmost unvisited column

At every stage, only the elements lying within these boundaries are considered part of the "remaining" matrix still to be traversed.

### Boundary Updates
As each side of the current boundary is traversed and its elements are added to the result:
- After traversing the top row (left to right), `top` is incremented (`top++`) since that row is now done.
- After traversing the right column (top to bottom), `right` is decremented (`right--`).
- After traversing the bottom row (right to left), `bottom` is decremented (`bottom--`).
- After traversing the left column (bottom to top), `left` is incremented (`left++`).

This inward shrinking of the boundary continues, effectively peeling off one "ring" of the matrix at a time, until the boundaries cross.

### Edge Cases
The algorithm relies on `while` loops with conditional checks (`top <= bottom` and `left <= right`) around the boundary traversal. These checks are essential for non-square matrices, since without them the algorithm could revisit or double-print elements once the matrix has been reduced to a single row or a single column. Specifically:
- Before traversing the bottom row, we check `top <= bottom` to ensure a bottom row still exists and hasn't already been covered by the top-row traversal.
- Before traversing the left column, we check `left <= right` to ensure a left column still exists and hasn't already been covered by the right-column traversal.

### Complexity Analysis
- **Time Complexity:** `O(n * m)`, since every element in the matrix is visited exactly once.
- **Space Complexity:** `O(n * m)` to store the result in the output vector/list (this doesn't count the space for the output if it isn't considered extra space).
