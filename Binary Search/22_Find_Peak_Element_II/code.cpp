#include <bits/stdc++.h>
using namespace std;

int getVal(vector<vector<int>>& matrix, int i, int j) {
    int m = matrix.size(), n = matrix[0].size();
    if (i < 0 || i >= m || j < 0 || j >= n) return INT_MIN;
    return matrix[i][j];
}

// ---------- Brute Force ----------
pair<int, int> findPeakBrute(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int val = matrix[i][j];
            if (val > getVal(matrix, i - 1, j) &&
                val > getVal(matrix, i + 1, j) &&
                val > getVal(matrix, i, j - 1) &&
                val > getVal(matrix, i, j + 1)) {
                return {i, j};
            }
        }
    }

    return {-1, -1}; // should not happen if matrix is non-empty
}

// ---------- Optimal — Binary Search on Columns ----------
int findMaxRowInColumn(vector<vector<int>>& matrix, int col) {
    int m = matrix.size();
    int maxRow = 0;

    for (int i = 1; i < m; i++) {
        if (matrix[i][col] > matrix[maxRow][col]) {
            maxRow = i;
        }
    }

    return maxRow;
}

pair<int, int> findPeakOptimal(vector<vector<int>>& matrix) {
    int n = matrix[0].size();
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int maxRow = findMaxRowInColumn(matrix, mid);

        int leftVal = getVal(matrix, maxRow, mid - 1);
        int rightVal = getVal(matrix, maxRow, mid + 1);
        int currentVal = matrix[maxRow][mid];

        if (currentVal > leftVal && currentVal > rightVal) {
            return {maxRow, mid};
        } else if (leftVal > currentVal) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return {-1, -1}; // should not happen
}

void printPeak(vector<vector<int>>& matrix, pair<int, int> pos) {
    cout << "(" << pos.first << ", " << pos.second << ") -> value "
         << matrix[pos.first][pos.second] << endl;
}

int main() {
    vector<vector<int>> matrix1 = {
        {10, 20, 15},
        {21, 30, 14},
        {7,  16, 32}
    };

    cout << "Matrix 1:" << endl;
    cout << "Brute Force:   "; printPeak(matrix1, findPeakBrute(matrix1));
    cout << "Binary Search: "; printPeak(matrix1, findPeakOptimal(matrix1));

    vector<vector<int>> matrix2 = {
        {1, 4},
        {3, 2}
    };

    cout << "\nMatrix 2:" << endl;
    cout << "Brute Force:   "; printPeak(matrix2, findPeakBrute(matrix2));
    cout << "Binary Search: "; printPeak(matrix2, findPeakOptimal(matrix2));

    return 0;
}
