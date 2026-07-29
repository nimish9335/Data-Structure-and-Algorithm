#include <bits/stdc++.h>
using namespace std;

int lowerBound(int arr[], int n, int target) {
    int lo = 0, hi = n - 1;
    int ans = n;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] >= target) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

int upperBound(int arr[], int n, int target) {
    int lo = 0, hi = n - 1;
    int ans = n;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] > target) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

int findFloor(int arr[], int n, int target) {
    int lo = 0, hi = n - 1;
    int ans = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] <= target) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}

int findCeil(int arr[], int n, int target) {
    int lo = 0, hi = n - 1;
    int ans = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] >= target) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

int main() {
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) cin >> arr[i];

    int target;
    cin >> target;

    cout << lowerBound(arr, n, target) << endl;
    cout << upperBound(arr, n, target) << endl;
    cout << findFloor(arr, n, target) << endl;
    cout << findCeil(arr, n, target) << endl;

    return 0;
}
