#include<bits/stdc++.h>
using namespace std;

#define int long long

unordered_map<int,int> dp;

int helper(int n, int k){
    if(n < k) return LLONG_MAX;
    if(n == k) return 0;

    if(dp.count(n)) return dp[n];

    int ans;

    if(n % 2 == 0){
        int temp = helper(n / 2, k);

        if(temp == LLONG_MAX)
            return dp[n] = LLONG_MAX;

        ans = 1 + temp;
    }
    else{
        int left = helper(n / 2, k);
        int right = helper(n / 2 + 1, k);

        int temp = min(left, right);

        if(temp == LLONG_MAX)
            return dp[n] = LLONG_MAX;

        ans = 1 + temp;
    }

    return dp[n] = ans;
}

void solve(){
    int n, k;
    cin >> n >> k;

    dp.clear();

    int ans = helper(n, k);

    if(ans == LLONG_MAX)
        cout << -1 << '\n';
    else
        cout << ans << '\n';
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while(t--){
        solve();
    }

    return 0;
}