#include <bits/stdc++.h>
using namespace std;

int singleElementBrute(vector<int>& arr) {
    int n = arr.size();

    if (n == 1) return arr[0];
    if (arr[0] != arr[1]) return arr[0];
    if (arr[n - 1] != arr[n - 2]) return arr[n - 1];

    for (int i = 1; i < n - 1; i++) {
        if (arr[i] != arr[i - 1] && arr[i] != arr[i + 1]) {
            return arr[i];
        }
    }

    return -1;
}

int singleElementBinarySearch(vector<int>& arr) {
    int n = arr.size();

    if (n == 1) return arr[0];
    if (arr[0] != arr[1]) return arr[0];
    if (arr[n - 1] != arr[n - 2]) return arr[n - 1];

    int low = 1, high = n - 2;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (mid % 2 == 1) mid--;

        if (arr[mid] == arr[mid + 1]) {
            low = mid + 2;
        } else if (arr[mid] == arr[mid - 1]) {
            high = mid - 2;
        } else {
            return arr[mid];
        }
    }

    return -1;
}

int main() {
    vector<int> arr1 = {1, 1, 2, 3, 3, 4, 4, 8, 8};
    cout << "Brute Force: " << singleElementBrute(arr1) << endl;
    cout << "Binary Search: " << singleElementBinarySearch(arr1) << endl;

    vector<int> arr2 = {3, 3, 7, 7, 10, 11, 11};
    cout << "\nBrute Force: " << singleElementBrute(arr2) << endl;
    cout << "Binary Search: " << singleElementBinarySearch(arr2) << endl;

    return 0;
}
