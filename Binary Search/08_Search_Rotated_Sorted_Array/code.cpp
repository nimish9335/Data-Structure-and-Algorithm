#include <bits/stdc++.h>
using namespace std;

int searchLinear(vector<int>& arr, int target) {
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        if (arr[i] == target) return i;
    }

    return -1;
}

int searchBinarySearch(vector<int>& arr, int target) {
    int n = arr.size();
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) return mid;

        if (arr[low] <= arr[mid]) {
            if (arr[low] <= target && target < arr[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } else {
            if (arr[mid] < target && target <= arr[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }

    return -1;
}

int main() {
    vector<int> arr1 = {4, 5, 6, 7, 0, 1, 2};
    int target1 = 0;
    cout << "Linear Search: " << searchLinear(arr1, target1) << endl;
    cout << "Binary Search: " << searchBinarySearch(arr1, target1) << endl;

    vector<int> arr2 = {4, 5, 6, 7, 0, 1, 2};
    int target2 = 3;
    cout << "\nLinear Search: " << searchLinear(arr2, target2) << endl;
    cout << "Binary Search: " << searchBinarySearch(arr2, target2) << endl;

    return 0;
}
