#include <bits/stdc++.h>
using namespace std;

// Number of days needed to ship all packages, loading in order, at a given capacity.
int daysNeeded(vector<int>& weights, int cap) {
    int days = 1;
    long long load = 0;

    for (int w : weights) {
        if (load + w > cap) {
            days++;
            load = 0;
        }
        load += w;
    }

    return days;
}

int shipCapacityBrute(vector<int>& weights, int d) {
    int low = *max_element(weights.begin(), weights.end());
    long long high = accumulate(weights.begin(), weights.end(), 0LL);

    for (long long cap = low; cap <= high; cap++) {
        if (daysNeeded(weights, (int)cap) <= d) {
            return (int)cap;
        }
    }

    return (int)high;
}

int shipCapacityBinarySearch(vector<int>& weights, int d) {
    int low = *max_element(weights.begin(), weights.end());
    long long high = accumulate(weights.begin(), weights.end(), 0LL);
    int ans = (int)high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;

        if (daysNeeded(weights, (int)mid) <= d) {
            ans = (int)mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ans;
}

int main() {
    vector<int> weights1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int d1 = 5;
    cout << "Brute Force: " << shipCapacityBrute(weights1, d1) << endl;
    cout << "Binary Search: " << shipCapacityBinarySearch(weights1, d1) << endl;

    vector<int> weights2 = {3, 2, 2, 4, 1, 4};
    int d2 = 3;
    cout << "\nBrute Force: " << shipCapacityBrute(weights2, d2) << endl;
    cout << "Binary Search: " << shipCapacityBinarySearch(weights2, d2) << endl;

    return 0;
}
