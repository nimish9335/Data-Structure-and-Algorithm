#include <bits/stdc++.h>
using namespace std;

int findPeakBrute(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        int left = (i == 0) ? INT_MIN : arr[i - 1];
        int right = (i == n - 1) ? INT_MIN : arr[i + 1];

        if (arr[i] > left && arr[i] > right) {
            return i;
        }
    }

    return -1;
}

int findPeakBinarySearch(vector<int>& arr) {
    int n = arr.size();

    if (n == 1) return 0;
    if (arr[0] > arr[1]) return 0;
    if (arr[n - 1] > arr[n - 2]) return n - 1;

    int low = 1, high = n - 2;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {
            return mid;
        } else if (arr[mid] < arr[mid + 1]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

int main() {
    vector<int> arr1 = {1, 2, 3, 1};
    cout << "Brute Force: " << findPeakBrute(arr1) << endl;
    cout << "Binary Search: " << findPeakBinarySearch(arr1) << endl;

    vector<int> arr2 = {1, 2, 1, 3, 5, 6, 4};
    cout << "\nBrute Force: " << findPeakBrute(arr2) << endl;
    cout << "Binary Search: " << findPeakBinarySearch(arr2) << endl;

    return 0;
}
