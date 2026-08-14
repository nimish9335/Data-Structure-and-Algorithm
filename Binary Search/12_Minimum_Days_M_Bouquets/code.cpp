#include <bits/stdc++.h>
using namespace std;

// Counts how many bouquets can be formed if we wait until day `day`.
long long countBouquets(vector<int>& bloomDay, int day, int k) {
    long long bouquets = 0;
    int consecutive = 0;

    for (int b : bloomDay) {
        if (b <= day) {
            consecutive++;
            if (consecutive == k) {
                bouquets++;
                consecutive = 0;
            }
        } else {
            consecutive = 0;
        }
    }

    return bouquets;
}

int minDaysBrute(vector<int>& bloomDay, int m, int k) {
    long long n = bloomDay.size();
    if ((long long)m * (long long)k > n) return -1;

    int low = *min_element(bloomDay.begin(), bloomDay.end());
    int high = *max_element(bloomDay.begin(), bloomDay.end());

    for (int day = low; day <= high; day++) {
        if (countBouquets(bloomDay, day, k) >= m) {
            return day;
        }
    }

    return -1;
}

int minDaysBinarySearch(vector<int>& bloomDay, int m, int k) {
    long long n = bloomDay.size();
    if ((long long)m * (long long)k > n) return -1;

    int low = *min_element(bloomDay.begin(), bloomDay.end());
    int high = *max_element(bloomDay.begin(), bloomDay.end());
    int ans = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (countBouquets(bloomDay, mid, k) >= m) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ans;
}

int main() {
    vector<int> bloomDay1 = {7, 7, 7, 7, 12, 7, 7};
    int m1 = 2, k1 = 3;
    cout << "Brute Force: " << minDaysBrute(bloomDay1, m1, k1) << endl;
    cout << "Binary Search: " << minDaysBinarySearch(bloomDay1, m1, k1) << endl;

    vector<int> bloomDay2 = {1, 10, 3, 10, 2};
    int m2 = 3, k2 = 1;
    cout << "\nBrute Force: " << minDaysBrute(bloomDay2, m2, k2) << endl;
    cout << "Binary Search: " << minDaysBinarySearch(bloomDay2, m2, k2) << endl;

    vector<int> bloomDay3 = {1, 10, 3, 10, 2};
    int m3 = 3, k3 = 2;
    cout << "\nBrute Force: " << minDaysBrute(bloomDay3, m3, k3) << endl;
    cout << "Binary Search: " << minDaysBinarySearch(bloomDay3, m3, k3) << endl;

    return 0;
}
