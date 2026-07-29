#include <bits/stdc++.h>
using namespace std;

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

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> image(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> image[i][j];
        }
    }

    int sr, sc, newColor;
    cin >> sr >> sc >> newColor;

    vector<vector<int>> result = floodFill(image, sr, sc, newColor);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
