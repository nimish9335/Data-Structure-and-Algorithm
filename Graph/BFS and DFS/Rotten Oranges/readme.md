# Rotten Oranges

## Problem Statement

You are given an `n x m` grid where each cell can have one of three
values:

- `0` representing an empty cell.
- `1` representing a fresh orange.
- `2` representing a rotten orange.

Every minute, any fresh orange that is **4-directionally adjacent**
(up, down, left, right) to a rotten orange also becomes rotten.

Return the minimum number of minutes that must elapse until **no cell
has a fresh orange**. If this is impossible (some fresh orange can
never be reached), return `-1`.

## Example

```
Input: grid = [[2,1,1],
               [1,1,0],
               [0,1,1]]
Output: 4

Input: grid = [[2,1,1],
               [0,1,1],
               [1,0,1]]
Output: -1
Explanation: The orange in the bottom-left corner (row 2, column 0) is
never rotten, because rotting only happens 4-directionally, and this
orange is isolated.
```

## Key Idea — Why BFS and Not DFS?

The rotting process happens **simultaneously** for all fresh oranges
that are one step away from any rotten orange at a given moment. This
is exactly how BFS explores a graph — level by level, where each
"level" here corresponds to one unit of time (one minute).

DFS would go deep along one path first, which does not correctly
represent the "all neighbors rot together" nature of this problem.
BFS naturally processes all oranges at the same distance from a
rotten source before moving further out, making it the right fit.

## Approach

1. **Initial Setup:**
   - Scan the entire grid once.
   - Push every cell that is already rotten (`2`) into a queue, along
     with its starting time `0`.
   - Count the total number of fresh oranges (`1`) — we'll need this
     later to check whether every orange eventually rots.
2. **BFS Traversal:**
   - Pop a cell from the queue along with its current time `t`.
   - Check its four neighbors (up, down, left, right).
   - If a neighbor is a **fresh orange** and hasn't been marked
     rotten yet, mark it as rotten, push it into the queue with time
     `t + 1`, and increment a counter tracking how many oranges have
     been rotted so far.
   - Keep track of the maximum time seen across the whole traversal —
     this becomes our answer, since the last orange to rot determines
     the total time needed.
3. **Final Check:**
   - After BFS completes, compare the count of rotted oranges with the
     total fresh orange count from the start.
   - If they match, every orange was successfully rotted — return the
     maximum time recorded.
   - If they don't match, some oranges were unreachable — return `-1`.

## Code

```cpp
int orangesRotting(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    queue<pair<pair<int, int>, int>> q;
    vector<vector<int>> visited(n, vector<int>(m, 0));
    int freshCount = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 2) {
                q.push({{i, j}, 0});
                visited[i][j] = 2;
            }
            if (grid[i][j] == 1) {
                freshCount++;
            }
        }
    }

    int tm = 0;
    int rottenCount = 0;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!q.empty()) {
        int x = q.front().first.first;
        int y = q.front().first.second;
        int t = q.front().second;
        q.pop();
        tm = max(tm, t);

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                visited[nx][ny] != 2 && grid[nx][ny] == 1) {
                visited[nx][ny] = 2;
                q.push({{nx, ny}, t + 1});
                rottenCount++;
            }
        }
    }

    if (rottenCount != freshCount) return -1;

    return tm;
}
```

## Why a Separate `visited` Grid Instead of Modifying `grid` Directly?

It's common to mark a cell rotten directly in `grid` itself (setting
`grid[nx][ny] = 2`) instead of using a separate `visited` matrix — both
work fine. Using a `visited` grid here just keeps the original input
grid untouched, which can be useful if you need to refer back to the
original state later, or simply prefer not to mutate input data.

## Dry Run (Conceptual)

```
grid = [[2,1,1],
        [1,1,0],
        [0,1,1]]

Time 0: rotten oranges at (0,0)
Time 1: (0,1) and (1,0) rot
Time 2: (0,2) and (1,1) rot
Time 3: (2,1) rots
Time 4: (2,2) rots

All fresh oranges rotted by time 4 -> return 4
```

Matches the expected output of `4`.

## Time Complexity

- **Time:** `O(N x M)` — every cell is visited once, and for each
  cell, we check its 4 neighbors (a constant factor), so the total
  work is proportional to the number of cells in the grid.

## Space Complexity

- **Space:** `O(N x M)` — required for the `visited` matrix and, in
  the worst case, the queue can hold up to all the cells in the grid
  at some point during the traversal.

## Notes for Revision

- This is the classic **multi-source BFS** pattern: instead of
  starting BFS from a single source, we start from **all** rotten
  oranges at once (time `0`), since they all rot their neighbors
  simultaneously.
- The key trick to get the "time" right: store the time alongside each
  cell in the queue (or track it via BFS levels), and take the
  **maximum** time seen across the whole traversal as the answer.
- Always do the final `rottenCount == freshCount` check — forgetting
  this and just returning the max time directly will give a wrong
  answer when some oranges are unreachable (should return `-1`
  instead).
- This same multi-source BFS pattern is useful in many grid problems
  where multiple "starting points" spread outward simultaneously
  (e.g., "01 Matrix", "Walls and Gates").
