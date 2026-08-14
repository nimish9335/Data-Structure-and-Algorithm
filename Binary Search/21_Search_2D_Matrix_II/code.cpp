#include <bits/stdc++.h>
using namespace std;

// ---------- Approach 1: Brute Force ----------
bool searchMatrixBrute(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == target) {
                return true;
            }
        }
    }

    return false;
}

// ---------- Approach 2: Binary Search Each Row ----------
bool binarySearchRow(vector<int>& row, int target) {
    int low = 0, high = row.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (row[mid] == target) {
            return true;
        } else if (row[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return false;
}

bool searchMatrixRowBinarySearch(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();

    for (int i = 0; i < m; i++) {
        if (binarySearchRow(matrix[i], target)) {
            return true;
        }
    }

    return false;
}

// ---------- Approach 3: Optimal — Top-Right Elimination ----------
bool searchMatrixOptimal(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int row = 0, col = n - 1;

    while (row < m && col >= 0) {
        int value = matrix[row][col];

        if (value == target) {
            return true;
        } else if (value > target) {
            col--; // eliminate this column
        } else {
            row++; // eliminate this row
        }
    }

    return false;
}

void printResult(bool result) {
    cout << (result ? "true" : "false") << endl;
}

int main() {
    vector<vector<int>> matrix = {
        {1, 4, 7, 11, 15},
        {2, 5, 8, 12, 19},
        {3, 6, 9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };

    int target1 = 5;
    cout << "Target = 5" << endl;
    cout << "Brute Force:          "; printResult(searchMatrixBrute(matrix, target1));
    cout << "Row Binary Search:    "; printResult(searchMatrixRowBinarySearch(matrix, target1));
    cout << "Optimal (Elimination):"; printResult(searchMatrixOptimal(matrix, target1));

    int target2 = 20;
    cout << "\nTarget = 20" << endl;
    cout << "Brute Force:          "; printResult(searchMatrixBrute(matrix, target2));
    cout << "Row Binary Search:    "; printResult(searchMatrixRowBinarySearch(matrix, target2));
    cout << "Optimal (Elimination):"; printResult(searchMatrixOptimal(matrix, target2));

    return 0;
}
