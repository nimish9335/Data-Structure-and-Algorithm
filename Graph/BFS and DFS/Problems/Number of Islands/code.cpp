#include <bits/stdc++.h>
using namespace std;

class Solution
{
    int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    void bfs(int row, int col, vector<vector<int>> &vis, vector<vector<char>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();

        queue<pair<int, int>> q;
        q.push({row, col});
        vis[row][col] = 1;

        while (!q.empty())
        {
            auto it = q.front();
            int r=it.first;
            int c=it.second;
            q.pop();

            for (int k = 0; k < 8; k++)
            {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                    grid[nr][nc] == '1' && !vis[nr][nc])
                {
                    vis[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }
        }
    }

    void dfs(int row, int col, vector<vector<int>> &vis, vector<vector<char>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();

        vis[row][col] = 1;

        for (int k = 0; k < 8; k++)
        {
            int nr = row + dr[k];
            int nc = col + dc[k];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                grid[nr][nc] == '1' && !vis[nr][nc])
            {
                dfs(nr, nc, vis, grid);
            }
        }
    }

public:
    int numIslandsBFS(vector<vector<char>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> vis(n, vector<int>(m, 0));

        int islands = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == '1' && !vis[i][j])
                {
                    islands++;
                    bfs(i, j, vis, grid);
                }
            }
        }

        return islands;
    }

    int numIslandsDFS(vector<vector<char>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> vis(n, vector<int>(m, 0));

        int islands = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == '1' && !vis[i][j])
                {
                    islands++;
                    dfs(i, j, vis, grid);
                }
            }
        }

        return islands;
    }
};

int main()
{
    vector<vector<char>> grid = {
        {'1', '1', '0', '0'},
        {'0', '1', '0', '0'},
        {'1', '0', '0', '1'},
        {'0', '0', '1', '1'}};

    Solution obj;

    cout << "BFS Answer : " << obj.numIslandsBFS(grid) << endl;
    cout << "DFS Answer : " << obj.numIslandsDFS(grid) << endl;

    return 0;
}