#include <bits/stdc++.h>
using namespace std;

// Sum of ceil(nums[i] / d) across the array.
long long calculateSum(vector<int>& nums, int d) {
    long long sum = 0;

    for (int num : nums) {
        sum += (num + d - 1) / d;   // ceiling division
    }

    return sum;
}

int smallestDivisorBrute(vector<int>& nums, int threshold) {
    int maxVal = *max_element(nums.begin(), nums.end());

    for (int d = 1; d <= maxVal; d++) {
        if (calculateSum(nums, d) <= threshold) {
            return d;
        }
    }

    return maxVal;
}

int smallestDivisorBinarySearch(vector<int>& nums, int threshold) {
    int low = 1, high = *max_element(nums.begin(), nums.end());
    int ans = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (calculateSum(nums, mid) <= threshold) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ans;
}

int main() {
    vector<int> nums1 = {1, 2, 5, 9};
    int threshold1 = 6;
    cout << "Brute Force: " << smallestDivisorBrute(nums1, threshold1) << endl;
    cout << "Binary Search: " << smallestDivisorBinarySearch(nums1, threshold1) << endl;

    vector<int> nums2 = {44, 22, 33, 11, 1};
    int threshold2 = 5;
    cout << "\nBrute Force: " << smallestDivisorBrute(nums2, threshold2) << endl;
    cout << "Binary Search: " << smallestDivisorBinarySearch(nums2, threshold2) << endl;

    return 0;
}
