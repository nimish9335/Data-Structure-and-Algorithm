#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        int total = 1 << n;
        vector<vector<int>> ans;

        for (int mask = 0; mask < total; mask++) {
            vector<int> subset;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i))
                    subset.push_back(nums[i]);
            }

            ans.push_back(subset);
        }

        return ans;
    }
};