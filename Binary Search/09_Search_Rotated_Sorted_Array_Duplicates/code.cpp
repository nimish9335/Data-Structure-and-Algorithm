#include <bits/stdc++.h>
using namespace std;

bool searchRotatedDuplicates(vector<int>& arr, int target) {
    int n = arr.size();
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) return true;

        if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
            low++;
            high--;
            continue;
        }

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

    return false;
}

int main() {
    vector<int> arr1 = {2, 5, 6, 0, 0, 1, 2};
    int target1 = 0;
    cout << "Result: " << (searchRotatedDuplicates(arr1, target1) ? "true" : "false") << endl;

    vector<int> arr2 = {2, 5, 6, 0, 0, 1, 2};
    int target2 = 3;
    cout << "Result: " << (searchRotatedDuplicates(arr2, target2) ? "true" : "false") << endl;

    return 0;
}
