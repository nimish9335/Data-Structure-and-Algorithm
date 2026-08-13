#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> rotateBrute(vector<vector<int>>& mat) {
    int n = mat.size();
    vector<vector<int>> result(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[j][n - 1 - i] = mat[i][j];
        }
    }

    return result;
}

void rotateOptimal(vector<vector<int>>& mat) {
    int n = mat.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(mat[i][j], mat[j][i]);
        }
    }

    for (int i = 0; i < n; i++) {
        reverse(mat[i].begin(), mat[i].end());
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
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    vector<vector<int>> result1 = rotateBrute(mat1);
    cout << "Brute Force Result:" << endl;
    printMatrix(result1);

    vector<vector<int>> mat2 = {
        {1, 2},
        {3, 4}
    };
    rotateOptimal(mat2);
    cout << "\nOptimal Result:" << endl;
    printMatrix(mat2);

    return 0;
}
