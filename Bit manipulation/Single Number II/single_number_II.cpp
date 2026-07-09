#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    // ==========================================================
    // Approach 1 : Hashing
    // Time : O(N)
    // Space : O(N)
    // ==========================================================

    int singleNumberHashing(vector<int>& nums) {

        unordered_map<int, int> mp;

        for (int x : nums)
            mp[x]++;

        for (auto it : mp) {
            if (it.second == 1)
                return it.first;
        }

        return -1;
    }

    // ==========================================================
    // Approach 2 : Count Set Bits
    // Time : O(32 * N)
    // Space : O(1)
    // ==========================================================

    int singleNumberBitCount(vector<int>& nums) {

        int ans = 0;

        for (int bit = 0; bit < 32; bit++) {

            int cnt = 0;

            for (int x : nums) {
                if (x & (1LL << bit))
                    cnt++;
            }

            if (cnt % 3)
                ans |= (1LL << bit);
        }

        return ans;
    }

    // ==========================================================
    // Approach 3 : Sorting
    // Time : O(N log N)
    // Space : O(1)
    // ==========================================================

    int singleNumberSorting(vector<int>& nums) {

        sort(nums.begin(), nums.end());

        int n = nums.size();

        for (int i = 1; i < n; i += 3) {

            if (nums[i] != nums[i - 1])
                return nums[i - 1];

            if (i + 1 < n && nums[i] != nums[i + 1])
                return nums[i];
        }

        return nums[n - 1];
    }

    // ==========================================================
    // Approach 4 : Bucket Method (Optimal)
    // Time : O(N)
    // Space : O(1)
    // ==========================================================

    int singleNumber(vector<int>& nums) {

        int ones = 0;
        int twos = 0;

        for (int x : nums) {

            ones = (ones ^ x) & (~twos);
            twos = (twos ^ x) & (~ones);

        }

        return ones;
    }
};