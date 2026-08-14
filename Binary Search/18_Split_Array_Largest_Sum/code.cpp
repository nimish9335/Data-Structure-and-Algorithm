#include <bits/stdc++.h>
using namespace std;

// ---------- SHARED CORE LOGIC ----------

// Number of contiguous groups needed to partition `arr` without any
// single group's sum exceeding `barrier`.
int countGroups(vector<int>& arr, long long barrier) {
    int groups = 1;
    long long sum = 0;

    for (int x : arr) {
        if (sum + x > barrier) {
            groups++;
            sum = 0;
        }
        sum += x;
    }

    return groups;
}

// The one true algorithm: minimize the largest sum among `k` contiguous
// groups. This single function powers Painter's Partition, Split Array
// Largest Sum, AND Allocate Books — only the argument names differ.
long long minimizedLargestSum(vector<int>& arr, int k) {
    int n = arr.size();
    if (k > n) return -1; // can't form k non-empty contiguous groups

    long long low = *max_element(arr.begin(), arr.end());
    long long high = accumulate(arr.begin(), arr.end(), 0LL);
    long long ans = high;

    while (low <= high) {
        long long mid = low + (high - low) / 2;

        if (countGroups(arr, mid) <= k) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ans;
}

// ---------- THIN WRAPPERS (same core, different names) ----------

long long painterPartition(vector<int>& boards, int k) {
    // "painting time" per board == board length, k painters == k groups
    return minimizedLargestSum(boards, k);
}

long long splitArrayLargestSum(vector<int>& nums, int m) {
    // m contiguous subarrays == m groups
    return minimizedLargestSum(nums, m);
}

long long allocateBooks(vector<int>& books, int m) {
    // m students == m groups (already covered in the Allocate Books file,
    // included here to show all three collapse into one function)
    return minimizedLargestSum(books, m);
}

int main() {
    vector<int> boards = {10, 20, 30, 40};
    int k = 2;
    cout << "Painter's Partition: " << painterPartition(boards, k) << endl;

    vector<int> nums = {7, 2, 5, 10, 8};
    int m = 2;
    cout << "Split Array Largest Sum: " << splitArrayLargestSum(nums, m) << endl;

    vector<int> books = {12, 34, 67, 90};
    int students = 2;
    cout << "Allocate Books: " << allocateBooks(books, students) << endl;

    return 0;
}
