#include <bits/stdc++.h>
using namespace std;

int singleNonDuplicate(vector<int>& nums) {
    int lo = 0, hi = nums.size() - 2;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (mid % 2 == 0) {
            if (nums[mid] == nums[mid + 1]) {
                lo = mid + 2;
            } else {
                hi = mid - 1;
            }
        } else {
            if (nums[mid] == nums[mid - 1]) {
                lo = mid + 1;
            } else {
                hi = mid - 2;
            }
        }
    }
    return nums[lo];
}

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    int result = singleNonDuplicate(nums);
    cout << result << endl;

    return 0;
}
