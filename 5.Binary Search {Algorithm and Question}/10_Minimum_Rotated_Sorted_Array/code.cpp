#include <bits/stdc++.h>
using namespace std;

int findMinBrute(vector<int>& arr) {
    int mini = INT_MAX;

    for (int x : arr) {
        mini = min(mini, x);
    }

    return mini;
}

int findMinBinarySearch(vector<int>& arr) {
    int n = arr.size();
    int low = 0, high = n - 1;
    int mini = INT_MAX;

    while (low <= high) {
        if (arr[low] <= arr[high]) {
            mini = min(mini, arr[low]);
            break;
        }

        int mid = low + (high - low) / 2;

        if (arr[low] <= arr[mid]) {
            mini = min(mini, arr[low]);
            low = mid + 1;
        } else {
            mini = min(mini, arr[mid]);
            high = mid - 1;
        }
    }

    return mini;
}

int main() {
    vector<int> arr1 = {4, 5, 6, 7, 0, 1, 2};
    cout << "Brute Force: " << findMinBrute(arr1) << endl;
    cout << "Binary Search: " << findMinBinarySearch(arr1) << endl;

    vector<int> arr2 = {11, 13, 15, 17};
    cout << "\nBrute Force: " << findMinBrute(arr2) << endl;
    cout << "Binary Search: " << findMinBinarySearch(arr2) << endl;

    return 0;
}
