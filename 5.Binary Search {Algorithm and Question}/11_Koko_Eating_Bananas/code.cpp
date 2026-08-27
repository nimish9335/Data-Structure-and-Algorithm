#include <bits/stdc++.h>
using namespace std;

long long calculateHours(vector<int>& piles, int k) {
    long long hours = 0;

    for (int pile : piles) {
        hours += (pile + k - 1) / k;
    }

    return hours;
}

int kokoBrute(vector<int>& piles, int h) {
    int maxPile = *max_element(piles.begin(), piles.end());

    for (int k = 1; k <= maxPile; k++) {
        if (calculateHours(piles, k) <= h) {
            return k;
        }
    }

    return maxPile;
}

int kokoBinarySearch(vector<int>& piles, int h) {
    int low = 1, high = *max_element(piles.begin(), piles.end());
    int ans = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (calculateHours(piles, mid) <= h) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ans;
}

int main() {
    vector<int> piles1 = {3, 6, 7, 11};
    int h1 = 8;
    cout << "Brute Force: " << kokoBrute(piles1, h1) << endl;
    cout << "Binary Search: " << kokoBinarySearch(piles1, h1) << endl;

    vector<int> piles2 = {30, 11, 23, 4, 20};
    int h2 = 5;
    cout << "\nBrute Force: " << kokoBrute(piles2, h2) << endl;
    cout << "Binary Search: " << kokoBinarySearch(piles2, h2) << endl;

    return 0;
}
