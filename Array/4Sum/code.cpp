#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> fourSum(vector<int> &arr, int target) {
    int n = arr.size();
    vector<vector<int>> ans;
    sort(arr.begin(), arr.end());

    for (int i = 0; i < n; i++) {
        if (i > 0 && arr[i] == arr[i - 1]) continue;

        for (int j = i + 1; j < n; j++) {
            if (j > i + 1 && arr[j] == arr[j - 1]) continue;

            int k = j + 1, l = n - 1;

            while (k < l) {
                long long sum = (long long)arr[i] + arr[j] + arr[k] + arr[l];

                if (sum < target) {
                    k++;
                } else if (sum > target) {
                    l--;
                } else {
                    ans.push_back({arr[i], arr[j], arr[k], arr[l]});
                    k++;
                    l--;
                    while (k < l && arr[k] == arr[k - 1]) k++;
                    while (k < l && arr[l] == arr[l + 1]) l--;
                }
            }
        }
    }

    return ans;
}

int main() {
    int n;
    long long target;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    cin >> target;

    vector<vector<int>> ans = fourSum(arr, target);

    for (auto &quad : ans) {
        cout << quad[0] << " " << quad[1] << " " << quad[2] << " " << quad[3] << endl;
    }

    return 0;
}
