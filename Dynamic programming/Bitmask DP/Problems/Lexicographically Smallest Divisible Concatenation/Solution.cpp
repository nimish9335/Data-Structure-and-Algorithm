/*
===============================================================================
            Lexicographically Smallest Divisible Concatenation
===============================================================================

Approach:
1. Sort the array to ensure lexicographically smallest answer.
2. Use Bitmask DP + DFS + Memoization.
3. DP State -> (mask, remainder)
4. Try every unused number.
5. Update remainder using concatenation formula.

Time Complexity : O(2^n * n * k)
Space Complexity: O(2^n * k)

===============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:

    int n;
    int k;
    int fullMask;

    // dp[mask][remainder]
    vector<vector<int>> dp;

    // Stores final answer
    vector<int> answer;

public:

    bool dfs(int mask,
             int rem,
             vector<int>& path,
             vector<int>& nums)
    {

        // ---------------- Base Case ----------------

        if(mask == fullMask)
        {
            if(rem == 0)
            {
                answer = path;
                return true;
            }

            return false;
        }

        // Already Computed

        if(dp[mask][rem] != -1)
            return dp[mask][rem];

        bool possible = false;

        // Try every unused number

        for(int i=0;i<n;i++)
        {
            if(mask & (1<<i))
                continue;

            //-------------------------------------------------------
            // Compute 10^(digits)
            //-------------------------------------------------------

            int multiplier = 1;

            int x = nums[i];

            while(x)
            {
                multiplier *= 10;
                x /= 10;
            }

            //-------------------------------------------------------
            // Concatenation Formula
            //
            // newRem =
            // (oldRem * 10^(digits) + currentNumber) % k
            //-------------------------------------------------------

            int newRem =
                (rem * multiplier + nums[i]) % k;

            path.push_back(nums[i]);

            possible |= dfs(mask | (1<<i),
                            newRem,
                            path,
                            nums);

            path.pop_back();

            //-------------------------------------------------------
            // Since array is sorted,
            // first valid answer is lexicographically smallest.
            //-------------------------------------------------------

            if(possible)
                break;
        }

        return dp[mask][rem] = possible;
    }

    vector<int> concatenatedDivisibility(vector<int>& nums,
                                         int K)
    {
        n = nums.size();
        k = K;

        fullMask = (1<<n) - 1;

        dp.assign(1<<n,
                  vector<int>(k,-1));

        // Important for lexicographical order
        sort(nums.begin(), nums.end());

        vector<int> path;

        dfs(0,0,path,nums);

        return answer;
    }
};

/*
===============================================================================

Key Observations

1.
State = (mask, remainder)

mask
-> Which numbers are already used.

remainder
-> Current concatenated value % k.

-------------------------------------------------------------------------------

2.

Concatenation Formula

Current Number = X

Append = Y

New Number

=

X * 10^(digits of Y) + Y

Modulo Version

newRem

=

(oldRem * multiplier + Y) % k

-------------------------------------------------------------------------------

3.

Sorting ensures

First successful DFS path

=

Lexicographically Smallest Answer.

-------------------------------------------------------------------------------

4.

Memoization removes repeated states.

Without DP

O(n!)

With DP

O(2^n * n * k)

===============================================================================
*/