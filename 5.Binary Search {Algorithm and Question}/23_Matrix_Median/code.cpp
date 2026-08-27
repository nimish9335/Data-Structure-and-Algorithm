#include <bits/stdc++.h>
using namespace std;

// ---------- Brute Force ----------
int medianBrute(vector<vector<int>>& matrix) {
    vector<int> flat;

    for (auto& row : matrix) {
        for (int val : row) {
            flat.push_back(val);
        }
    }

    sort(flat.begin(), flat.end());
    return flat[flat.size() / 2];
}

// ---------- Optimal — Binary Search on Value Range ----------

// Count how many elements in the matrix are <= x, using upper_bound per row.
int countSmallerEqual(vector<vector<int>>& matrix, int x) {
    int count = 0;

    for (auto& row : matrix) {
        count += upper_bound(row.begin(), row.end(), x) - row.begin();
    }

    return count;
}

int medianOptimal(vector<vector<int>>& matrix) {
    int n = matrix.size(), m = matrix[0].size();

    int low = INT_MAX, high = INT_MIN;
    for (auto& row : matrix) {
        low = min(low, row.front());
        high = max(high, row.back());
    }

    int half = (n * m) / 2;

    while (low < high) {
        int mid = low + (high - low) / 2;

        if (countSmallerEqual(matrix, mid) <= half) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return low;
}

int main() {
    vector<vector<int>> matrix1 = {
        {1, 3, 5},
        {2, 6, 9},
        {3, 6, 9}
    };

    cout << "Matrix 1:" << endl;
    cout << "Brute Force:   " << medianBrute(matrix1) << endl;
    cout << "Binary Search: " << medianOptimal(matrix1) << endl;

    vector<vector<int>> matrix2 = {
        {1, 3, 4},
        {2, 5, 6},
        {3, 7, 8}
    };

    cout << "\nMatrix 2:" << endl;
    cout << "Brute Force:   " << medianBrute(matrix2) << endl;
    cout << "Binary Search: " << medianOptimal(matrix2) << endl;

    return 0;
}
