/*
    ================================================================
    BITMASK BASICS — Fundamental Bit Operations for Bitmask DP
    ================================================================

    Before diving into bitmask DP templates, you need to be fluent
    in the basic bit operations used everywhere in this repo. This
    file is a hands-on playground — run it and see every operation
    in action with actual numbers.

    Think of an integer as a row of light switches (bits). Bitmask
    DP is just "cleverly tracking which switches are ON/OFF" to
    represent a subset of n items.
*/

#include <bits/stdc++.h>
using namespace std;

void printBinary(int x, int width) {
    for (int i = width - 1; i >= 0; i--) {
        cout << ((x >> i) & 1);
    }
}

int main() {
    int n = 6; // pretend we have 6 items: item 0 to item 5

    cout << "=== 1. Representing a subset as a mask ===\n";
    // mask = 0b010110 means items 1, 2, 4 are included (0-indexed from right)
    int mask = 0b010110;
    cout << "mask = "; printBinary(mask, n); cout << " (decimal: " << mask << ")\n\n";

    cout << "=== 2. Check if item i is in the mask ===\n";
    for (int i = 0; i < n; i++) {
        bool present = mask & (1 << i);
        cout << "Item " << i << " present? " << (present ? "YES" : "no") << "\n";
    }
    cout << "-> Logic: (1 << i) creates a mask with ONLY bit i set.\n";
    cout << "-> ANDing with mask keeps bit i only if BOTH have it set.\n\n";

    cout << "=== 3. Set (add) item i into the mask ===\n";
    int mask2 = mask | (1 << 0); // add item 0
    cout << "Before: "; printBinary(mask, n);
    cout << "  ->  After adding item 0: "; printBinary(mask2, n); cout << "\n";
    cout << "-> Logic: OR forces bit i to 1, leaves other bits untouched.\n\n";

    cout << "=== 4. Clear (remove) item i from the mask ===\n";
    int mask3 = mask & ~(1 << 2); // remove item 2
    cout << "Before: "; printBinary(mask, n);
    cout << "  ->  After removing item 2: "; printBinary(mask3, n); cout << "\n";
    cout << "-> Logic: ~(1<<i) flips EVERY bit except bit i (which becomes 0).\n";
    cout << "-> ANDing keeps all other bits same, but forces bit i to 0.\n\n";

    cout << "=== 5. Toggle (flip) item i ===\n";
    int mask4 = mask ^ (1 << 1); // flip item 1
    cout << "Before: "; printBinary(mask, n);
    cout << "  ->  After toggling item 1: "; printBinary(mask4, n); cout << "\n";
    cout << "-> Logic: XOR flips bit i: 0->1 or 1->0, others unchanged.\n\n";

    cout << "=== 6. Full mask (all n items included) ===\n";
    int full = (1 << n) - 1;
    cout << "full = "; printBinary(full, n); cout << " (decimal: " << full << ")\n";
    cout << "-> Logic: (1<<n) is a 1 followed by n zeros; subtracting 1\n";
    cout << "   flips it to n ones. This represents 'everything selected'.\n\n";

    cout << "=== 7. Count how many items are in the mask ===\n";
    int count = __builtin_popcount(mask);
    cout << "mask has " << count << " items set.\n";
    cout << "-> __builtin_popcount(x) is a built-in GCC function, very fast.\n\n";

    cout << "=== 8. Get the lowest set bit ===\n";
    int lowest = mask & (-mask);
    cout << "mask = "; printBinary(mask, n);
    cout << "  ->  lowest set bit = "; printBinary(lowest, n); cout << "\n";
    cout << "-> Useful trick: -mask is the two's complement (flip all bits, add 1).\n";
    cout << "   ANDing mask with -mask isolates only the lowest 1-bit.\n\n";

    cout << "=== 9. Iterate over all subsets (masks) of n items ===\n";
    cout << "for (int m = 0; m < (1<<n); m++) { ... }\n";
    cout << "-> This loop visits EVERY possible subset exactly once,\n";
    cout << "   from empty set (0) to full set ((1<<n)-1).\n";
    cout << "   This is the backbone of all bitmask DP: dp[mask] = ...\n\n";

    cout << "=== 10. Iterate over which items are set in a mask ===\n";
    cout << "Items set in mask " << mask << ": ";
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) cout << i << " ";
    }
    cout << "\n";

    return 0;
}

/*
    ================================================================
    QUICK REFERENCE TABLE (memorize this before moving to templates)
    ================================================================
    Check bit i set?     mask & (1 << i)
    Set bit i             mask | (1 << i)
    Clear bit i            mask & ~(1 << i)
    Toggle bit i           mask ^ (1 << i)
    Full mask (n bits)     (1 << n) - 1
    Count set bits         __builtin_popcount(mask)
    Lowest set bit         mask & (-mask)
    Remove lowest set bit  mask & (mask - 1)
    Is mask a power of 2?  (mask & (mask - 1)) == 0
    Loop all subsets       for (m = 0; m < (1<<n); m++)
    Loop submasks of mask  for (s=mask;;s=(s-1)&mask) { if(s==0) break; }

    ================================================================
    WHY THIS MATTERS FOR DP
    ================================================================
    Every template in this repo (Generic Templates folder) builds on
    exactly these operations:
        - dp[mask] arrays are indexed using masks built from the ops above
        - Transitions add/remove one bit at a time (set/clear operations)
        - Base/final states check against 0 or full mask
        - Loops over "next item to pick" use the "check if set" operation

    If any of the 10 sections above feel unclear, re-run this file,
    change 'mask' and 'n' to different values, and predict the output
    BEFORE running it. This intuition is the #1 prerequisite for
    everything else in this repo.
*/