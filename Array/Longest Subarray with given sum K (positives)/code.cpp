#include <bits/stdc++.h>
using namespace std;

int longestSubarrayBrute(vector<int>& arr, int k) {
    int n = arr.size();
    int maxLen = 0;

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += arr[j];
            if (sum == k) {
                maxLen = max(maxLen, j - i + 1);
            }
        }
    }

    return maxLen;
}

int longestSubarrayHashing(vector<int>& arr, int k) {
    unordered_map<int, int> prefixSumMap;
    int sum = 0;
    int maxLen = 0;

    for (int i = 0; i < (int)arr.size(); i++) {
        sum += arr[i];

        if (sum == k) {
            maxLen = max(maxLen, i + 1);
        }

        if (prefixSumMap.find(sum - k) != prefixSumMap.end()) {
            maxLen = max(maxLen, i - prefixSumMap[sum - k]);
        }

        if (prefixSumMap.find(sum) == prefixSumMap.end()) {
            prefixSumMap[sum] = i;
        }
    }

    return maxLen;
}

int longestSubarrayTwoPointers(vector<int>& arr, int k) {
    int n = arr.size();
    int left = 0, right = 0;
    int sum = 0;
    int maxLen = 0;

    while (right < n) {
        sum += arr[right];

        while (sum > k && left <= right) {
            sum -= arr[left];
            left++;
        }

        if (sum == k) {
            maxLen = max(maxLen, right - left + 1);
        }

        right++;
    }

    return maxLen;
}

int main() {
    vector<int> arr1 = {10, 5, 2, 7, 1, 9};
    int k1 = 15;
    cout << "Brute Force: " << longestSubarrayBrute(arr1, k1) << endl;
    cout << "Hashing: " << longestSubarrayHashing(arr1, k1) << endl;
    cout << "Two Pointers: " << longestSubarrayTwoPointers(arr1, k1) << endl;

    vector<int> arr2 = {-1, 1, 1};
    int k2 = 1;
    cout << "\nBrute Force: " << longestSubarrayBrute(arr2, k2) << endl;
    cout << "Hashing: " << longestSubarrayHashing(arr2, k2) << endl;

    return 0;
}
