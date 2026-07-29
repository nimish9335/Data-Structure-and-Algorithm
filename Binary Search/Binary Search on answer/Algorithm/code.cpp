#include <bits/stdc++.h>
using namespace std;

bool isPossible(int arr[], int n, int mid) {
    return true;
}

int binarySearchOnAnswer(int arr[], int n, int lo, int hi) {
    int ans = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (isPossible(arr, n, mid)) {
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

    int lo = 1, hi = 1e9;
    int result = binarySearchOnAnswer(arr, n, lo, hi);
    cout << result << endl;

    return 0;
}
