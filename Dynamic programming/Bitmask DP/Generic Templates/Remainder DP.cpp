/*
    ================================================================
    GENERIC TEMPLATE: Remainder Bitmask DP (Mask + Modulo State)
    ================================================================

    Problem this pattern solves: Partition/arrange a set of n numbers
    into groups such that some SUM or PRODUCT condition involving a
    remainder (mod k) is satisfied.

    Classic problem used here: "Partition array into K subsets with
    equal sum" style, extended with remainder tracking — specifically:

    "Given n numbers, split them into groups (in order) such that
    each group's sum is divisible by k. Count/find ways to do this,
    or find minimum number of groups."

    Core Idea:
        dp[mask][rem] = considering the numbers picked so far (mask),
        where 'rem' = (sum of current, still-open group) % k,
        what's the best (count/min groups/etc.) way to proceed?

    This introduces a SECOND dimension to the state beyond mask:
    'rem' = running remainder — a very common pattern whenever a
    problem involves "sum so far mod k" alongside a subset.

    Time Complexity: O(2^n * n * k)
    Space Complexity: O(2^n * k)
*/

#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> a;
vector<vector<int>> memo;      // memo[mask][rem] = min groups needed
const int INF = 1e9;

/*
    dfs(mask, rem):
        mask -> set of numbers already placed into SOME group
        rem  -> (sum of the CURRENT, still-open group) % k

    Returns minimum number of groups needed to place all remaining
    numbers (numbers not in mask), given the current group's
    remainder is 'rem'.

    Key transition idea:
        For every unused number i:
            - Try adding it to the CURRENT open group.
              newRem = (rem + a[i]) % k
              If newRem == 0, this group is now complete/closed,
              so the NEXT number (if any) starts a fresh group
              -> cost of "closing a group" = +1 to answer, and we
                 recurse with rem = 0 (fresh group) for future picks.
              Otherwise the group stays open -> recurse with newRem,
                 no extra cost yet (group not closed).
*/
int dfs(int mask, int rem) {
    // Base case: all numbers placed.
    if (mask == (1 << n) - 1) {
        // If current open group has rem == 0, it's a valid finished
        // group needing no extra closing; if not, this arrangement
        // is invalid (can't leave a group with nonzero remainder).
        return (rem == 0) ? 0 : INF;
    }

    if (memo[mask][rem] != -1) return memo[mask][rem];

    int ans = INF;

    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) continue; // already used

        int newMask = mask | (1 << i);
        int newRem = (rem + a[i]) % k;

        if (newRem == 0) {
            // Current group closes perfectly here.
            // +1 for completing this group; next group starts at rem=0
            int res = dfs(newMask, 0);
            if (res != INF) ans = min(ans, res + 1);
        } else {
            // Group stays open, no group completed yet
            int res = dfs(newMask, newRem);
            ans = min(ans, res);
        }
    }

    return memo[mask][rem] = ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    a.assign(n, 0);
    for (int i = 0; i < n; i++) cin >> a[i];

    memo.assign(1 << n, vector<int>(k, -1));

    int result = dfs(0, 0); // start: nothing used, current group sum%k = 0

    if (result >= INF) cout << "Not possible\n";
    else cout << "Minimum groups: " << result << "\n";

    return 0;
}

/*
    ================================================================
    WHY 'rem' IS A SEPARATE DP DIMENSION (IMPORTANT CONCEPT)
    ================================================================
    Normally bitmask DP state is just "mask" (+ maybe "pos" for
    position-dependent problems like TSP). But whenever the problem
    involves a SUM or accumulated value where only "value mod k"
    matters for future decisions (not the exact value), you add
    that remainder as an EXTRA dimension: dp[mask][rem].

    This works because of a key property of modulo arithmetic:
        (sum_so_far + next_number) % k
    depends ONLY on (sum_so_far % k) and next_number — NOT on the
    exact value of sum_so_far. So instead of tracking the full sum
    (which could be huge), we only need to track it mod k, giving
    us just 'k' possible extra states instead of "sum many" states.

    ================================================================
    HOW TO ADAPT THIS TEMPLATE
    ================================================================
    1. Identify what you're accumulating that only matters mod k
       (a sum, an XOR of remainders, a product mod k, etc.)

    2. dp[mask][rem] where rem = accumulated_value % k for whatever
       "currently open" chunk/group/segment you're building.

    3. Base case: mask == full mask AND rem satisfies your target
       condition (usually rem == 0 for "divisible by k").

    4. Transition: for each unused element, update rem using modulo
       arithmetic, and decide whether picking it "closes" a group
       (rem becomes 0) or keeps it "open" (rem stays nonzero).

    5. This idea generalizes beyond "sum % k": you could track
       "product % k", "XOR value", "count % k", etc. — same pattern,
       different combination operator instead of "+".
*/