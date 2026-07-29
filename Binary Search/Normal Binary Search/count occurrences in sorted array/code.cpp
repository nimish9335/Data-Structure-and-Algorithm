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

int countOccurrences(int arr[], int n, int x) {
    int lb = lowerBound(arr, n, x);
    if (lb == n || arr[lb] != x) return 0;
    int ub = upperBound(arr, n, x);
    return ub - lb;
}

int main() {
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) cin >> arr[i];

    int x;
    cin >> x;

    int ans = countOccurrences(arr, n, x);
    cout << "The number of occurrences is: " << ans << endl;

    return 0;
}
