/*
 * LeetCode 260 - Single Number III
 * ---------------------------------
 * Given an integer array nums where every element appears twice except
 * for two elements which appear only once, return the two elements
 * that appear only once. You can return the answer in any order.
 *
 * This file contains BOTH approaches discussed in the take U forward video:
 *   1. Brute Force (Hash Map)      -> O(N log M) time, O(M) space
 *   2. Optimized (Bit Manipulation) -> O(N) time, O(1) space
 *
 * Compile:  g++ -std=c++17 -O2 SingleNumberIII.cpp -o solution
 * Run:      ./solution
 */

#include <bits/stdc++.h>
using namespace std;

// ------------------------------------------------------------------
// Approach 1: Brute Force using Hash Map
// ------------------------------------------------------------------
// Idea:
//   - Traverse the array once, store frequency of every number in a map.
//   - Traverse the map, collect the two numbers whose frequency is 1.
//
// Time Complexity : O(N log M)  (map operations cost log M, M = distinct
//                    elements; N is array size)
// Space Complexity: O(M)         (extra hash map storage)
// ------------------------------------------------------------------
vector<int> singleNumberBruteForce(vector<int>& nums) {
    map<int, int> freq;                 // ordered map -> log M per op
    for (int num : nums) {
        freq[num]++;
    }

    vector<int> result;
    for (auto& it : freq) {
        int key=it.first;
        int count=it.second;
        if (count == 1) {
            result.push_back(key);
            if (result.size() == 2) break; // found both, stop early
        }
    }
    return result;
}

// ------------------------------------------------------------------
// Approach 2: Optimized Bit Manipulation (XOR + Bucketing)
// ------------------------------------------------------------------
// Idea:
//   Step 1: XOR all elements together.
//           Duplicates cancel out (a ^ a = 0), so the final XOR value
//           equals (uniqueA ^ uniqueB).
//
//   Step 2: Since uniqueA != uniqueB, the XOR result is non-zero,
//           meaning at least one bit differs between them.
//           Isolate the rightmost set bit of the XOR result:
//               rightmostSetBit = xorAll & (-xorAll)
//           (Using two's complement trick; NOTE: cast to `long` to
//            avoid INT_MIN overflow when computing -xorAll, as
//            highlighted in the video around 22:04 - 23:25.)
//
//   Step 3: Use that bit to split ALL numbers in the array into two
//           buckets/groups:
//               - Bucket 1: numbers having that bit SET
//               - Bucket 2: numbers having that bit NOT SET
//           Every duplicate pair lands in the SAME bucket (since they
//           are identical numbers), so XOR-ing within each bucket
//           cancels all duplicates and leaves exactly one unique
//           number per bucket.
//
// Time Complexity : O(N)  -> two linear passes (XOR pass + bucket pass)
// Space Complexity: O(1)  -> only a few extra variables
// ------------------------------------------------------------------
vector<int> singleNumberOptimized(vector<int>& nums) {
    // Step 1: XOR all elements
    long xorAll = 0;
    for (int num : nums) {
        xorAll ^= num;
    }

    // Step 2: Isolate the rightmost set bit
    // Using `long` here prevents overflow if xorAll == INT_MIN,
    // because -INT_MIN overflows in 32-bit int arithmetic.
    long rightmostSetBit = xorAll & (-xorAll);

    // Step 3: Bucket numbers using that bit and XOR within buckets
    int bucket1 = 0, bucket2 = 0;
    for (int num : nums) {
        if (num & rightmostSetBit) {
            bucket1 ^= num;
        } else {
            bucket2 ^= num;
        }
    }

    return {bucket1, bucket2};
}


