/*
    ================================================================
    GENERIC TEMPLATE: Iterative (Bottom-Up) Bitmask DP
    ================================================================

    Same problem as "DFS + Memoization.cpp" (TSP-style: minimum cost
    to visit all nodes and return to start), but solved bottom-up.

    Why Bottom-Up?
        - No recursion overhead / no stack overflow risk.
        - Computes masks in increasing order, so every dp[mask] is
          ready before we use it to build dp[newMask].
        - Usually faster in practice than top-down.

    Core difference from top-down:
        Top-down:  dfs(mask, pos) -> "from here, what's the best
                    way to FINISH?"
        Bottom-up: dp[mask][pos]  -> "having reached 'pos' using
                    exactly the nodes in 'mask', what's the best
                    cost SO FAR?"
        So the transition direction flips: bottom-up PUSHES forward
        from a smaller mask to a bigger mask, instead of pulling
        backward from a bigger mask to a smaller one.

    Time Complexity: O(2^n * n * n)   -> n^2 transition inside loop
    Space Complexity: O(2^n * n)
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<vector<int>> cost(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];

    const int INF = 1e9;
    int FULL = (1 << n) - 1;

    // dp[mask][pos] = minimum cost to reach 'pos' having visited
    // exactly the set of nodes in 'mask' (starting from node 0)
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));

    // Base case: start at node 0, only node 0 visited
    dp[1][0] = 0;

    // Iterate over all masks in increasing order (this is CRUCIAL —
    // dp[mask] must be fully computed before we use it to update
    // dp[newMask], and newMask is always > mask numerically)
    for (int mask = 1; mask <= FULL; mask++) {
        for (int pos = 0; pos < n; pos++) {
            // Skip invalid states:
            // 1. pos must actually be part of this mask
            // 2. dp[mask][pos] must be reachable (not INF)
            if (!(mask & (1 << pos))) continue;
            if (dp[mask][pos] == INF) continue;

            // Try to extend to every unvisited node "next"
            for (int next = 0; next < n; next++) {
                if (mask & (1 << next)) continue; // already visited

                int newMask = mask | (1 << next);
                int newCost = dp[mask][pos] + cost[pos][next];

                dp[newMask][next] = min(dp[newMask][next], newCost);
            }
        }
    }

    // Answer: from the FULL mask (all visited), return to node 0
    int ans = INF;
    for (int pos = 0; pos < n; pos++) {
        if (dp[FULL][pos] != INF)
            ans = min(ans, dp[FULL][pos] + cost[pos][0]);
    }

    cout << "Minimum cost: " << ans << endl;
    return 0;
}

/*
    ================================================================
    HOW TO ADAPT THIS TEMPLATE
    ================================================================
    1. Define dp[mask][extra] = best value achievable having used
       exactly the elements in 'mask', currently at state 'extra'.

    2. Base case: dp[starting_mask][starting_extra] = starting_value

    3. Loop mask from smallest to FULL (1 << n) - 1:
         for every valid 'extra' where dp[mask][extra] is reachable:
             try every way to extend to a new unused element
             update dp[newMask][new_extra] = combine(...)

    4. Final answer = combine dp[FULL][all valid extra states]

    IMPORTANT: mask must be iterated in increasing numeric order.
    Since newMask = mask | (1 << next) is ALWAYS strictly greater
    than mask (we're only ever setting new bits, never clearing),
    a simple for loop from 0 to FULL guarantees correct ordering.
*/