/*
    STATE COMPRESSION DP — GENERIC TEMPLATE
    -----------------------------------------
    Idea:
      When a problem has N small "items/elements" (N <= ~20-22) and we need
      to track WHICH SUBSET of them has been used/covered/assigned so far,
      we compress that subset into a single integer "mask" (bitmask).

      dp[mask] = best/count/ways of achieving state described by mask
      dp[mask] transitions to dp[mask | (1<<i)] by "adding" element i.

    This differs from plain Subset Enumeration / TSP templates in that the
    state isn't just "which cities visited" — mask can represent ANY
    finite combination of binary facts (assigned/not, used/not, colored/not).

    Time complexity is usually O(2^N * N) or O(2^N * N^2) depending on
    transition cost — always check N is small enough (<= 20 ideally).
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const long long INF = 1e18;

int n;                     // number of elements/items
long long dp[1 << MAXN];   // dp[mask] = answer for this subset-state

// ---------------------------------------------------------
// PATTERN 1: Basic "assign elements one by one" DP
// e.g. Assign N tasks to N workers minimizing cost
// ---------------------------------------------------------
long long cost[MAXN][MAXN]; // cost[i][j] = cost of assigning item i (by popcount) to slot j

long long assignmentDP() {
    int full = (1 << n) - 1;
    fill(dp, dp + (1 << n), INF);
    dp[0] = 0;

    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == INF) continue;
        int idx = __builtin_popcount(mask); // which "slot" we are filling next
        if (idx >= n) continue;

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) continue;      // element i already used
            int nextMask = mask | (1 << i);
            long long val = dp[mask] + cost[i][idx];
            dp[nextMask] = min(dp[nextMask], val);
        }
    }
    return dp[full];
}

// ---------------------------------------------------------
// PATTERN 2: "Cover/partition into groups" DP
// e.g. Minimum groups to partition N items into valid subsets
// (valid[] precomputed: valid[mask] = true if mask is an allowed group)
// ---------------------------------------------------------
bool valid[1 << MAXN];

int partitionDP() {
    int full = (1 << n) - 1;
    vector<int> dp2(1 << n, INT_MAX);
    dp2[0] = 0;

    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp2[mask] == INT_MAX) continue;

        // find first unset bit -> must be covered next (prunes redundant states)
        int firstFree = -1;
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i))) { firstFree = i; break; }
        }
        if (firstFree == -1) continue;

        // try every submask (containing firstFree) as the "next group"
        int rem = full ^ mask;
        for (int sub = rem; sub > 0; sub = (sub - 1) & rem) {
            if (!(sub & (1 << firstFree))) continue;
            if (!valid[sub]) continue;
            int nextMask = mask | sub;
            dp2[nextMask] = min(dp2[nextMask], dp2[mask] + 1);
        }
    }
    return dp2[full];
}

// ---------------------------------------------------------
// PATTERN 3: Counting ways with bitmask state
// e.g. Count ways to fill an N x M grid / count perfect matchings
// dp[row][mask] = ways to reach 'mask' configuration at given row
// ---------------------------------------------------------
long long countWaysDP(int rows, int cols) {
    vector<vector<long long>> dpRow(rows + 1, vector<long long>(1 << cols, 0));
    dpRow[0][0] = 1;

    for (int r = 0; r < rows; r++) {
        for (int mask = 0; mask < (1 << cols); mask++) {
            if (dpRow[r][mask] == 0) continue;
            // transition logic depends on problem (place/skip per column)
            // example: identity transition (replace with real transitions)
            dpRow[r + 1][mask] += dpRow[r][mask];
        }
    }

    long long total = 0;
    for (int mask = 0; mask < (1 << cols); mask++)
        total += dpRow[rows][mask];
    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Example usage (Pattern 1: assignment problem)
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];

    cout << "Min assignment cost: " << assignmentDP() << "\n";

    return 0;
}
