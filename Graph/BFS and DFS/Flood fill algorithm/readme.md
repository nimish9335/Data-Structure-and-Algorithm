# Flood Fill Algorithm

## Problem Statement

You are given an `n x m` matrix `image` representing an image, where
`image[i][j]` represents the color of the pixel at that location.

You are also given three integers `sr`, `sc`, and `newColor`. You
should perform a **flood fill** on the image starting from the pixel
`image[sr][sc]`.

To perform a flood fill:

1. Consider the starting pixel, along with any pixels connected
   **4-directionally** to it (up, down, left, right), and so on,
   recursively, that all share the same color as the starting pixel.
2. Replace the color of all these pixels with `newColor`.

Return the modified image after performing the flood fill.

## Example

```
Input: image = [[1,1,1],
                [1,1,0],
                [1,0,1]], sr = 1, sc = 1, newColor = 2

Output: [[2,2,2],
         [2,2,0],
         [2,0,1]]

Explanation: From the center of the image with position (1,1), all
pixels connected by a path of the same color as the starting pixel
(color 1) are colored with the new color (2). Note the bottom-right
corner is not colored 2, because it is not 4-directionally connected
to the starting pixel.
```

## Key Idea

This is a graph traversal problem in disguise — think of every pixel
as a **node**, and two pixels are connected by an **edge** if they are
4-directionally adjacent **and** share the same color.

Starting from `(sr, sc)`, we need to visit every pixel reachable
through such edges and change its color to `newColor`. This can be
done using either **DFS** or **BFS** — here we use **DFS**, since it
naturally fits the recursive "visit a pixel, then visit its valid
neighbors" structure.

## Important Detail — Don't Modify the Original Image Directly

A subtle but important point: if you start changing colors directly in
the `image` matrix while traversing it, you can run into a tricky bug.

Consider this case: if `initialColor` is `1` and `newColor` is also
`1`, or more generally, if the new color happens to match colors
elsewhere in unrelated regions, mutating the original array directly
could cause **infinite loops** or **incorrect results**, since your
checks (`image[nrow][ncol] == initialColor`) rely on the original
image staying unchanged during the traversal.

To avoid this, we create a **separate copy** of the image (`ans`) to
store the final result, and always compare against the original
`image` when deciding whether a neighbor should be filled.

## How it Works (Step by Step)

1. Note down the `initialColor` — the color at `image[sr][sc]` before
   any changes.
2. Create a copy of the image called `ans`, which will hold the final
   result.
3. Use `deltaRow` and `deltaCol` arrays to represent the four possible
   directions (up, down, left, right) in a clean, loopable way instead
   of writing four separate `if` conditions.
4. Run a recursive DFS starting from `(sr, sc)`:
   - Set `ans[row][col] = newColor`.
   - For each of the 4 neighboring directions:
     - Check that the neighbor is within bounds.
     - Check that the neighbor's color in the **original** `image`
       matches `initialColor` (so we only fill connected pixels of the
       same original color).
     - Check that the neighbor hasn't already been filled with
       `newColor` in `ans` (to avoid infinite recursion when
       `initialColor == newColor`).
     - If all checks pass, recursively call DFS on that neighbor.
5. Return `ans` once the DFS completes.

## Code

```cpp
void dfs(int row, int col, vector<vector<int>>& ans,
         vector<vector<int>>& image, int newColor, int initialColor,
         int deltaRow[], int deltaCol[]) {
    ans[row][col] = newColor;
    int n = image.size();
    int m = image[0].size();

    for (int i = 0; i < 4; i++) {
        int nrow = row + deltaRow[i];
        int ncol = col + deltaCol[i];

        if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m &&
            image[nrow][ncol] == initialColor &&
            ans[nrow][ncol] != newColor) {
            dfs(nrow, ncol, ans, image, newColor, initialColor,
                deltaRow, deltaCol);
        }
    }
}

vector<vector<int>> floodFill(vector<vector<int>>& image, int sr,
                               int sc, int newColor) {
    int initialColor = image[sr][sc];
    vector<vector<int>> ans = image;

    int deltaRow[] = {-1, 0, 1, 0};
    int deltaCol[] = {0, 1, 0, -1};

    dfs(sr, sc, ans, image, newColor, initialColor, deltaRow, deltaCol);

    return ans;
}
```

## Why Check `ans[nrow][ncol] != newColor` Instead of a Separate Visited Array?

Since we already fill `ans[row][col] = newColor` the moment we visit a
pixel, checking `ans[nrow][ncol] != newColor` effectively tells us
whether that neighbor has already been processed — acting like a
built-in visited check without needing a separate boolean matrix. This
is especially important for correctly handling the edge case where
`initialColor == newColor`, which would otherwise cause infinite
recursion.

## Dry Run

```
image = [[1,1,1],
         [1,1,0],
         [1,0,1]], sr = 1, sc = 1, newColor = 2

initialColor = image[1][1] = 1
ans starts as a copy of image

dfs(1,1): ans[1][1] = 2
  check (0,1): image=1 (matches), ans=1 (not 2) -> dfs(0,1)
    ans[0][1] = 2
    check (0,0): image=1, ans=1 -> dfs(0,0)
      ans[0][0] = 2
      neighbors out of bounds or don't match -> return
    check (0,2): image=1, ans=1 -> dfs(0,2)
      ans[0][2] = 2
      check (1,2): image=0, doesn't match initialColor -> skip
      return
    check (1,1): ans=2 already -> skip
  check (1,0): image=1, ans=1 -> dfs(1,0)
    ans[1][0] = 2
    check (2,0): image=1, ans=1 -> dfs(2,0)
      ans[2][0] = 2
      check (2,1): image=0, doesn't match -> skip
      return
  check (1,2): image=0, doesn't match -> skip
  check (2,1): image=0, doesn't match -> skip

Final ans = [[2,2,2],
             [2,2,0],
             [2,0,1]]
```

Matches the expected output exactly.

## Time Complexity

- **Time:** `O(N x M)` — in the worst case, every pixel in the image
  is visited exactly once (when all pixels share the same initial
  color).

## Space Complexity

- **Space:** `O(N x M)` — mainly due to the recursion call stack in
  the worst case (a fully connected region forces recursion depth
  proportional to the number of pixels), plus the space for the `ans`
  copy of the image.

## Notes for Revision

- This is a **connected component traversal** problem on a grid,
  almost identical in spirit to "Number of Islands" or "Rotten
  Oranges", just applied to pixel colors instead of land/water or
  rotten/fresh states.
- Always operate on a **copy** of the input when doing in-place-style
  fills — mutating the original data while reading from it in the same
  pass is a common source of subtle bugs.
- Using `deltaRow` / `deltaCol` arrays for direction handling keeps the
  neighbor-checking code compact and easy to extend (e.g., adding
  diagonal directions later just means adding more entries to these
  arrays).
- Watch out for the edge case where `initialColor == newColor` — the
  `ans[nrow][ncol] != newColor` check specifically guards against
  infinite recursion in this scenario.
