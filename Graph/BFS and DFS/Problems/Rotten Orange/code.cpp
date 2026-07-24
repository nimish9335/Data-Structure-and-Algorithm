#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        queue<pair<int, int>> q;

        // Push all initially rotten oranges
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                }
            }
        }

        int r[4] = {0, 1, 0, -1};
        int c[4] = {-1, 0, 1, 0};

        int ans = 0;

        // Multi-Source BFS
        while (!q.empty()) {
            int size = q.size();
            ans++;

            for (int x = 0; x < size; x++) {
                auto it = q.front();
                q.pop();

                int i = it.first;
                int j = it.second;

                for (int k = 0; k < 4; k++) {
                    int ni = i + r[k];
                    int nj = j + c[k];

                    if (ni >= 0 && ni < n &&
                        nj >= 0 && nj < m &&
                        grid[ni][nj] == 1) {

                        grid[ni][nj] = 2;
                        q.push({ni, nj});
                    }
                }
            }
        }

        // Check if any fresh orange is left
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    return -1;
                }
            }
        }

        return ans == 0 ? 0 : ans - 1;
    }
};