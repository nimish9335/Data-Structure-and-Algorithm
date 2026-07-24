#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    void dfs(int i, int j, vector<vector<int>>& image,
             int oldColor, int color) {

        int n = image.size();
        int m = image[0].size();

        image[i][j] = color;

        int row[4] = {-1, 0, 1, 0};
        int col[4] = {0, 1, 0, -1};

        for (int k = 0; k < 4; k++) {
            int ni = i + row[k];
            int nj = j + col[k];

            if (ni >= 0 && ni < n &&
                nj >= 0 && nj < m &&
                image[ni][nj] == oldColor) {

                dfs(ni, nj, image, oldColor, color);
            }
        }
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image,
                                  int sr, int sc, int color) {

        int oldColor = image[sr][sc];

        // Prevent infinite recursion
        if (oldColor == color)
            return image;

        dfs(sr, sc, image, oldColor, color);

        return image;
    }
};