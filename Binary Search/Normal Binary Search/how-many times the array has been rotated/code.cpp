#include <bits/stdc++.h>
using namespace std;

int findKRotation(vector<int>& arr) {
    int lo = 0, hi = arr.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] > arr[hi]) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    int result = findKRotation(arr);
    cout << result << endl;

    return 0;
}
