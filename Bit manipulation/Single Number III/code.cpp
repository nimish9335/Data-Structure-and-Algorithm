#include <bits/stdc++.h>
using namespace std;

vector<int> singleNumber(vector<int>& nums) {
    long long xr = 0;

    for (int num : nums)
        xr ^= num;

    long long rightMostSetBit = xr & (-xr);

    int first = 0, second = 0;

    for (int num : nums) {
        if (num & rightMostSetBit)
            first ^= num;
        else
            second ^= num;
    }

    return {first, second};
}

int main() {
    int n;
    cin >> n;

    vector<int> nums(n);

    for (int i = 0; i < n; i++)
        cin >> nums[i];

    vector<int> ans = singleNumber(nums);

    cout << ans[0] << " " << ans[1];

    return 0;
}