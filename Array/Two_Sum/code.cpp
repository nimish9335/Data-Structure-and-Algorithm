#include <bits/stdc++.h>
using namespace std;

vector<int> twoSum(vector<int> &arr, int target) {
    unordered_map<int, int> mp;

    for (int i = 0; i < arr.size(); i++) {
        int complement = target - arr[i];
        if (mp.find(complement) != mp.end()) {
            return {mp[complement], i};
        }
        mp[arr[i]] = i;
    }

    return {-1, -1};
}

int main() {
    int n, target;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    cin >> target;

    vector<int> ans = twoSum(arr, target);

    cout << ans[0] << " " << ans[1] << endl;

    return 0;
}
