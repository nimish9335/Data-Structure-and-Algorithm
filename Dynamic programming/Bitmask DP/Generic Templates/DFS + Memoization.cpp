/*
    ================================================================
    GENERIC TEMPLATE: DFS + Memoization (Top-Down Bitmask DP)
    ================================================================

    Pattern:
        dp[mask][extra] = best/count/ways considering "mask" as the
        set of elements already used/visited/placed, and "extra"
        as any additional state (like current position, last index,
        sum so far, etc.)

    Why DFS + Memo (Top-Down) instead of Iterative (Bottom-Up)?
        - Easier to write and reason about.
        - You only compute states that are actually reachable
          (iterative DP computes ALL 2^n * extra states, even
           unreachable ones).
        - Recursion mirrors "decision tree" thinking:
              for every unused element -> try picking it -> recurse.

    Time Complexity (generic):
        O(2^n * n * transition_cost)
        because there are 2^n masks, and for each mask we try up to
        n choices (next element to include).

    Space Complexity:
        O(2^n * extra_states) for memo table
        + O(n) recursion stack depth.

    This file solves a CLASSIC problem as a template:
        "Minimum Cost to visit all nodes" style (like TSP-lite)
        You can copy this skeleton and modify the transition
        for YOUR specific problem.
*/

#include <bits/stdc++.h>
using namespace std;

int n;                          // number of elements/items
vector<vector<int>> cost;       // cost[i][j] = cost to go from i to j
vector<vector<int>> memo;       // memo[mask][pos] = best answer
const int INF = 1e9;

/*
    dfs(mask, pos):
        mask -> set of visited/used nodes (bit i set = node i used)
        pos  -> current node we are standing on

    Returns the minimum cost to complete the task from this state.
*/
int dfs(int mask, int pos) {
    // Base case: all nodes visited
    if (mask == (1 << n) - 1) {
        return cost[pos][0]; // example: return to start (TSP style)
    }

    // Return memoized state if already computed
    if (memo[mask][pos] != -1) return memo[mask][pos];

    int ans = INF;

    // Try to go to every unvisited node "next"
    for (int next = 0; next < n; next++) {
        // Skip if 'next' is already visited
        if (mask & (1 << next)) continue;

        int newMask = mask | (1 << next);   // mark 'next' as visited
        int newCost = cost[pos][next] + dfs(newMask, next);

        ans = min(ans, newCost);
    }

    return memo[mask][pos] = ans;
}

int solve() {
    memo.assign(1 << n, vector<int>(n, -1));
    // Start at node 0, only node 0 visited => mask = 1
    return dfs(1, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Example input (like Travelling Salesman Problem)
    cin >> n;
    cost.assign(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];

    cout << "Minimum cost: " << solve() << endl;

    return 0;
}

/*
    ================================================================
    HOW TO ADAPT THIS TEMPLATE TO YOUR OWN PROBLEM
    ================================================================
    1. Identify what "mask" represents in YOUR problem
       (subset of jobs done? subset of people assigned? subset of
        cities visited?)

    2. Identify the "extra" state besides mask
       (current position? current index? current sum?)
       - If no extra state needed, drop 'pos' and just use dp[mask].

    3. Define the base case:
       - When mask == (1<<n)-1 (all bits set) => everything used.
       - What should be returned then?

    4. Define the transition:
       - Loop over all bits NOT set in mask (unused elements).
       - For each, compute newMask = mask | (1<<i)
       - Recurse into dfs(newMask, ...) and combine result
         (min, max, sum, count, OR, etc. depending on problem)

    5. Memoize using a 2D (or 1D) array sized [1<<n][extra_states]

    See README.md in this folder for full conceptual explanation.
*/
