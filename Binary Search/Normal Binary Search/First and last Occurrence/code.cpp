#include <bits/stdc++.h>
using namespace std;

int findFirst(int arr[], int n, int target) {
    int lo = 0, hi = n - 1;
    int ans = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) {
            ans = mid;
            hi = mid - 1;
        } else if (arr[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}

int findLast(int arr[], int n, int target) {
    int lo = 0, hi = n - 1;
    int ans = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) {
            ans = mid;
            lo = mid + 1;
        } else if (arr[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}

vector<int> searchRange(int arr[], int n, int target) {
    int first = findFirst(arr, n, target);
    int last = findLast(arr, n, target);
    return {first, last};
}

int main() {
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) cin >> arr[i];

    int target;
    cin >> target;

    vector<int> result = searchRange(arr, n, target);
    cout << result[0] << " " << result[1] << endl;

    return 0;
}
