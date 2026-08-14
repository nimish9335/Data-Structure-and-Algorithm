#include <bits/stdc++.h>
using namespace std;

int kthMissingBrute(vector<int>& arr, int k) {
    int n = arr.size();
    int i = 0;
    int missingCount = 0;
    int num = 1;

    while (true) {
        if (i < n && arr[i] == num) {
            i++;
        } else {
            missingCount++;
            if (missingCount == k) {
                return num;
            }
        }
        num++;
    }
}

int kthMissingBinarySearch(vector<int>& arr, int k) {
    int n = arr.size();
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int missing = arr[mid] - (mid + 1);

        if (missing < k) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    // low = high + 1 at this point
    return low + k;
}

int main() {
    vector<int> arr1 = {2, 3, 4, 7, 11};
    int k1 = 5;
    cout << "Brute Force: " << kthMissingBrute(arr1, k1) << endl;
    cout << "Binary Search: " << kthMissingBinarySearch(arr1, k1) << endl;

    vector<int> arr2 = {1, 2, 3, 4};
    int k2 = 2;
    cout << "\nBrute Force: " << kthMissingBrute(arr2, k2) << endl;
    cout << "Binary Search: " << kthMissingBinarySearch(arr2, k2) << endl;

    return 0;
}
