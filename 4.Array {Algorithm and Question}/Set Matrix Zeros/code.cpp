#include <bits/stdc++.h>
using namespace std;

void setZeroesBrute(vector<vector<int>>& mat) {
    int n = mat.size();
    int m = mat[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 0) {
                for (int k = 0; k < m; k++) {
                    if (mat[i][k] != 0) mat[i][k] = -1;
                }
                for (int k = 0; k < n; k++) {
                    if (mat[k][j] != 0) mat[k][j] = -1;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == -1) mat[i][j] = 0;
        }
    }
}

void setZeroesBetter(vector<vector<int>>& mat) {
    int n = mat.size();
    int m = mat[0].size();

    vector<int> row(n, 0), col(m, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 0) {
                row[i] = 1;
                col[j] = 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (row[i] || col[j]) {
                mat[i][j] = 0;
            }
        }
    }
}

void setZeroesOptimal(vector<vector<int>>& mat) {
    int n = mat.size();
    int m = mat[0].size();
    int col0 = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 0) {
                mat[i][0] = 0;
                if (j != 0) mat[0][j] = 0;
                else col0 = 0;
            }
        }
    }

    for (int i = n - 1; i >= 1; i--) {
        for (int j = m - 1; j >= 1; j--) {
            if (mat[i][0] == 0 || mat[0][j] == 0) {
                mat[i][j] = 0;
            }
        }
        if (col0 == 0) mat[i][0] = 0;
    }

    if (mat[0][0] == 0) {
        for (int j = 0; j < m; j++) mat[0][j] = 0;
    }
}

void printMatrix(vector<vector<int>>& mat) {
    for (auto& row : mat) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }
}

int main() {
    vector<vector<int>> mat1 = {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    };
    setZeroesOptimal(mat1);
    cout << "Optimal Result:" << endl;
    printMatrix(mat1);

    vector<vector<int>> mat2 = {
        {0, 1, 2, 0},
        {3, 4, 5, 2},
        {1, 3, 1, 5}
    };
    setZeroesBetter(mat2);
    cout << "\nBetter Approach Result:" << endl;
    printMatrix(mat2);

    return 0;
}
