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

// ---------- Approach 2: Better — Binary Search Each Row ----------
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

bool searchMatrixBetter(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();

    for (int i = 0; i < m; i++) {
        if (binarySearchRow(matrix[i], target)) {
            return true;
        }
    }

    return false;
}

// ---------- Approach 3: Optimal — Binary Search on Flattened Matrix ----------
bool searchMatrixOptimal(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int low = 0, high = (m * n) - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int row = mid / n;
        int col = mid % n;
        int value = matrix[row][col];

        if (value == target) {
            return true;
        } else if (value < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return false;
}

void printResult(bool result) {
    cout << (result ? "true" : "false") << endl;
}

int main() {
    vector<vector<int>> matrix = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };

    int target1 = 3;
    cout << "Target = 3" << endl;
    cout << "Brute Force: "; printResult(searchMatrixBrute(matrix, target1));
    cout << "Better:      "; printResult(searchMatrixBetter(matrix, target1));
    cout << "Optimal:     "; printResult(searchMatrixOptimal(matrix, target1));

    int target2 = 13;
    cout << "\nTarget = 13" << endl;
    cout << "Brute Force: "; printResult(searchMatrixBrute(matrix, target2));
    cout << "Better:      "; printResult(searchMatrixBetter(matrix, target2));
    cout << "Optimal:     "; printResult(searchMatrixOptimal(matrix, target2));

    return 0;
}
