/*
    ================================================================
    GENERIC TEMPLATE: Hamiltonian Path using Bitmask DP
    ================================================================

    Problem: Given a graph with n nodes, does there exist a path
    that visits EVERY node exactly once? (Hamiltonian Path — not
    necessarily returning to start, unlike TSP/Hamiltonian Cycle)

    Core Idea:
        dp[mask][pos] = TRUE if there exists a path that:
            - visits exactly the set of nodes in 'mask'
            - and currently ends at node 'pos'

        This is the SAME shape as the TSP dp[mask][pos], but instead
        of storing a "minimum cost" (integer), we store a "reachable
        or not" (boolean). Same structure, different payload.

    Time Complexity: O(2^n * n^2)
    Space Complexity: O(2^n * n)
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m; // n = nodes, m = edges

    vector<vector<int>> adj(n, vector<int>(n, 0)); // adjacency matrix
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = 1;
        adj[v][u] = 1; // remove this line if graph is directed
    }

    int FULL = (1 << n) - 1;

    // dp[mask][pos] = can we have a path visiting exactly 'mask'
    // nodes, ending at 'pos'?
    vector<vector<bool>> dp(1 << n, vector<bool>(n, false));

    // Base case: starting at any single node alone is always valid
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = true;
    }

    // Build up from smaller masks to larger masks
    for (int mask = 1; mask <= FULL; mask++) {
        for (int pos = 0; pos < n; pos++) {
            if (!(mask & (1 << pos))) continue; // pos not in mask
            if (!dp[mask][pos]) continue;       // state not reachable

            // Try to extend the path to every unvisited neighbor
            for (int next = 0; next < n; next++) {
                if (mask & (1 << next)) continue;   // already visited
                if (!adj[pos][next]) continue;      // no edge pos->next

                int newMask = mask | (1 << next);
                dp[newMask][next] = true;
            }
        }
    }

    // Answer: does ANY node have dp[FULL][node] == true?
    bool exists = false;
    for (int i = 0; i < n; i++) {
        if (dp[FULL][i]) {
            exists = true;
            break;
        }
    }

    cout << (exists ? "Hamiltonian Path EXISTS" : "No Hamiltonian Path") << endl;
    return 0;
}

/*
    ================================================================
    VARIATIONS YOU CAN BUILD FROM THIS TEMPLATE
    ================================================================
    1. Hamiltonian CYCLE (like TSP without costs):
       - Just check if dp[FULL][pos] is true AND adj[pos][start] == 1
         for whichever 'start' node you began from.

    2. COUNT number of Hamiltonian paths (instead of exists/not):
       - Change dp[mask][pos] from bool to long long (count).
       - dp[newMask][next] += dp[mask][pos]  (instead of "= true")

    3. Print the ACTUAL path (not just existence):
       - Store a parent[mask][pos] = previous node, then backtrack
         from dp[FULL][end_node] down to the base case.

    4. Hamiltonian path with FIXED start/end node:
       - Only set dp[1<<start][start] = true as base case (instead of
         looping over all i), and only check dp[FULL][end] at the end.
*/