#include <bits/stdc++.h>
using namespace std;

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

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    int result = orangesRotting(grid);
    cout << result << endl;

    return 0;
}
