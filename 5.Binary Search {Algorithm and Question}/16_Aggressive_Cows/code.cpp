#include <bits/stdc++.h>
using namespace std;

// Greedily checks if k cows can be placed with at least `dist` gap between them.
bool canWePlace(vector<int>& stalls, int dist, int k) {
    int n = stalls.size();
    int cowsPlaced = 1;
    int lastPos = stalls[0];

    for (int i = 1; i < n; i++) {
        if (stalls[i] - lastPos >= dist) {
            cowsPlaced++;
            lastPos = stalls[i];
        }
    }

    return cowsPlaced >= k;
}

int aggressiveCowsBrute(vector<int>& stalls, int k) {
    sort(stalls.begin(), stalls.end());
    int n = stalls.size();
    int maxDist = stalls[n - 1] - stalls[0];
    int ans = 1;

    for (int d = 1; d <= maxDist; d++) {
        if (canWePlace(stalls, d, k)) {
            ans = d;
        } else {
            break; // once it fails, larger d will fail too
        }
    }

    return ans;
}

int aggressiveCowsBinarySearch(vector<int>& stalls, int k) {
    sort(stalls.begin(), stalls.end());
    int n = stalls.size();
    int low = 1, high = stalls[n - 1] - stalls[0];
    int ans = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (canWePlace(stalls, mid, k)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return ans;
}

int main() {
    vector<int> stalls1 = {0, 3, 4, 7, 10, 9};
    int k1 = 4;
    cout << "Brute Force: " << aggressiveCowsBrute(stalls1, k1) << endl;
    cout << "Binary Search: " << aggressiveCowsBinarySearch(stalls1, k1) << endl;

    vector<int> stalls2 = {1, 2, 4, 8, 9};
    int k2 = 3;
    cout << "\nBrute Force: " << aggressiveCowsBrute(stalls2, k2) << endl;
    cout << "Binary Search: " << aggressiveCowsBinarySearch(stalls2, k2) << endl;

    return 0;
}
