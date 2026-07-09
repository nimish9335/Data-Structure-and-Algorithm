/*
    ================================================================
    GENERIC TEMPLATE: Subset Enumeration (Submask Iteration)
    ================================================================

    Problem this solves: For a given mask, how do we efficiently
    iterate over ALL of its subsets (submasks)?

    This is a foundational trick used in "Sum over Subsets" (SOS) DP,
    subset-sum bitmask DP, and problems where you need to combine
    information from every possible subset of a set.

    Naive way: for each submask candidate from 0 to mask, check if
    it's actually a subset -> O(2^n) per mask -> O(4^n) total (BAD).

    Smart way (used here): the classic "submask enumeration trick"
    visits EXACTLY the subsets of 'mask' and nothing else.

    Time Complexity (key result):
        Enumerating all submasks of ALL masks from 0 to (2^n - 1)
        takes O(3^n) total, NOT O(4^n).
        Why 3^n? Because each of the n bits can independently be:
            - 0 in the original mask (so it's 0 in every submask), OR
            - 1 in the original mask, and then EITHER 0 or 1 in a
              given submask.
        That's 3 possibilities per bit -> 3^n total submask pairs.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int FULL = (1 << n) - 1;

    // ---------------------------------------------------------
    // PART 1: Enumerate all submasks of a SINGLE given mask
    // ---------------------------------------------------------
    int mask;
    cin >> mask;

    cout << "Submasks of " << mask << ":\n";

    // The trick: start sub = mask, and repeatedly do
    // sub = (sub - 1) & mask
    // This jumps directly to the next smaller submask of 'mask',
    // skipping all numbers that aren't actually submasks.
    for (int sub = mask; ; sub = (sub - 1) & mask) {
        cout << sub << " ";

        if (sub == 0) break; // 0 is always a submask (the empty set)
    }
    cout << "\n\n";

    // ---------------------------------------------------------
    // PART 2: Enumerate submasks of EVERY mask (used in SOS DP)
    // ---------------------------------------------------------
    // Example use case: f[mask] = sum of some value over every
    // submask of 'mask'. This is the "brute-force SOS" approach,
    // costing O(3^n) total (as explained above) instead of O(4^n).

    vector<long long> value(1 << n);
    for (int m = 0; m <= FULL; m++) value[m] = 1; // example: value=1 everywhere

    vector<long long> sumOverSubsets(1 << n, 0);

    for (int m = 0; m <= FULL; m++) {
        for (int sub = m; ; sub = (sub - 1) & m) {
            sumOverSubsets[m] += value[sub];
            if (sub == 0) break;
        }
    }

    cout << "Sum over subsets example (value[x]=1 for all x):\n";
    for (int m = 0; m <= FULL; m++) {
        // sumOverSubsets[m] should equal (number of submasks of m)
        // = 2^(popcount(m))
        cout << "mask=" << m << " -> sumOverSubsets=" << sumOverSubsets[m]
             << " (expected " << (1LL << __builtin_popcount(m)) << ")\n";
    }

    return 0;
}

/*
    ================================================================
    HOW THE "sub = (sub - 1) & mask" TRICK WORKS
    ================================================================
    Say mask = 1011 (binary). We want only numbers whose 1-bits are
    a subset of mask's 1-bits: 1011, 1010, 1001, 1000, 0011, 0010,
    0001, 0000.

    Start sub = mask = 1011.
    Step: sub = (sub - 1) & mask
        sub - 1 flips the lowest set bit and everything below it
        to see the "next smaller number" in general.
        ANDing with mask throws away any bits that aren't allowed
        (i.e., bits not in the original mask), snapping us to the
        next valid submask directly — no wasted iterations.

    This repeats until sub == 0, at which point we've seen the
    empty set (always a valid submask) and stop.

    ================================================================
    WHERE THIS IS USED
    ================================================================
    1. "Sum over Subsets" (SOS) DP — e.g., for every mask, find sum
       of an array value over all its submasks. The double loop
       above (brute-force O(3^n)) can be further optimized to
       O(n * 2^n) using proper SOS DP if needed for large n — that's
       a more advanced technique, worth learning separately.

    2. Bitmask DP where the transition needs to consider EVERY way
       to split a mask into two disjoint parts (partition DP):
           for (sub = mask; sub > 0; sub = (sub-1) & mask) {
               int other = mask ^ sub; // the complementary part
               // combine dp[sub] and dp[other] somehow
           }
       NOTE: here we often loop sub > 0 (not including 0) or sub < mask
       (not including mask itself) to avoid trivial/duplicate splits,
       depending on the exact problem.

    3. Any problem where "try every possible sub-group of a chosen
       group" comes up (e.g. partition into two teams, split items
       into groups with combined constraints).
*/