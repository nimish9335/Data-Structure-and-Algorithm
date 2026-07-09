/*
    ================================================================
    GENERIC TEMPLATE: Travelling Salesman Problem (TSP)
    ================================================================

    Problem: Given n cities and cost[i][j] = cost to travel from
    city i to city j, find the minimum cost to visit ALL cities
    exactly once and return back to the starting city.

    This file builds on:
        - Iterative Bitmask DP.cpp  (core dp[mask][pos] shape)
        - Hamiltonian Path.cpp      (visiting-all-nodes concept)

    NEW addition in this file: PATH RECONSTRUCTION.
    We don't just want the minimum cost — we also want to print
    the actual optimal route (the order in which cities are visited).

    Time Complexity: O(2^n * n^2)
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

    // dp[mask][pos]     = minimum cost to reach 'pos' having visited
    //                      exactly the nodes in 'mask' (starting at 0)
    // parent[mask][pos] = which node we came FROM to reach this
    //                      (mask, pos) state with minimum cost
    //                      -> used to reconstruct the actual path
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    vector<vector<int>> parent(1 << n, vector<int>(n, -1));

    // Base case: start at node 0, only node 0 visited
    dp[1][0] = 0;

    for (int mask = 1; mask <= FULL; mask++) {
        for (int pos = 0; pos < n; pos++) {
            if (!(mask & (1 << pos))) continue;
            if (dp[mask][pos] == INF) continue;

            for (int next = 0; next < n; next++) {
                if (mask & (1 << next)) continue; // already visited

                int newMask = mask | (1 << next);
                int newCost = dp[mask][pos] + cost[pos][next];

                if (newCost < dp[newMask][next]) {
                    dp[newMask][next] = newCost;
                    parent[newMask][next] = pos; // record how we got here
                }
            }
        }
    }

    // Find best ending node to close the loop back to node 0
    int ans = INF, lastNode = -1;
    for (int pos = 0; pos < n; pos++) {
        if (dp[FULL][pos] == INF) continue;
        int total = dp[FULL][pos] + cost[pos][0];
        if (total < ans) {
            ans = total;
            lastNode = pos;
        }
    }

    cout << "Minimum cost: " << ans << endl;

    // ---------- Reconstruct the path using 'parent' table ----------
    vector<int> path;
    int mask = FULL, pos = lastNode;
    while (pos != -1) {
        path.push_back(pos);
        int prevPos = parent[mask][pos];
        int prevMask = mask ^ (1 << pos); // remove current node from mask
        mask = prevMask;
        pos = prevPos;
    }
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (int city : path) cout << city << " -> ";
    cout << "0 (return to start)" << endl;

    return 0;
}

/*
    ================================================================
    HOW PATH RECONSTRUCTION WORKS (IMPORTANT CONCEPT)
    ================================================================
    Every time we update dp[newMask][next] with a better cost, we
    also record parent[newMask][next] = pos (the node we came from).

    To reconstruct the path, we start from the final state
    (FULL mask, lastNode) and walk BACKWARDS:
        1. Add current 'pos' to path.
        2. Look up parent[mask][pos] -> this is where we came from.
        3. Remove 'pos' from mask (mask ^ (1 << pos)) since we're
           going back in time to before 'pos' was visited.
        4. Repeat until parent is -1 (this is our starting node 0,
           whose base case had no parent).
        5. Reverse the collected path (since we built it backward).

    This "record parent + backtrack" trick works for ANY DP where
    you want to recover the actual sequence of decisions, not just
    the optimal value. It generalizes far beyond bitmask DP.

    ================================================================
    HOW TO ADAPT THIS TEMPLATE
    ================================================================
    - If the problem is "assign N jobs to N workers minimizing cost"
      instead of "visit N cities", the logic is IDENTICAL — just
      rename cost[i][j] to cost[worker][job] and mask tracks which
      jobs are already assigned.
    - If you don't need to return to node 0 at the end (Hamiltonian
      Path instead of Cycle), skip adding cost[pos][0] and just take
      min over dp[FULL][pos] directly.
*/