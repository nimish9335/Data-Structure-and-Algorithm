# 4 Sum Problem

## Question

Given an array of integers `arr` and a target value `target`, find all unique quadruplets `[arr[i], arr[j], arr[k], arr[l]]` such that `i`, `j`, `k`, `l` are all distinct indices, and `arr[i] + arr[j] + arr[k] + arr[l] == target`. The solution set must not contain duplicate quadruplets.

### Test Case 1
**Input:**
```
6
1 0 -1 0 -2 2
0
```
**Output:**
```
-2 -1 1 2
-2 0 0 2
-1 0 0 1
```

### Test Case 2
**Input:**
```
5
2 2 2 2 2
8
```
**Output:**
```
2 2 2 2
```

## Solution Explanation

This problem extends the same family of problems as 2 Sum and 3 Sum from Striver's A to Z DSA Course, and it's typically solved by generalizing the sorted two-pointer technique one level further, fixing two elements instead of one before scanning with two pointers.

### 1. Brute Force Approach
Use four nested loops to check every possible quadruplet of elements in the array, and if a quadruplet sums to the target, store it after ensuring it isn't a duplicate (commonly done by inserting sorted quadruplets into a set). This works but is highly inefficient, with a time complexity of `O(n^4)` and extra space for duplicate removal.

### 2. Better Approach (Hashing)
Fix the first two elements using two nested loops, then use a hash set to check, for each pair, whether the required fourth element (the complement needed to reach the target) has already been seen among the elements processed for the third position. This reduces the complexity to about `O(n^3)` on average, at the cost of extra hash set space, plus a set to store unique quadruplets.

### 3. Optimal Approach (Two-Pointer)
This is the most efficient approach, and it directly extends the two-pointer intuition used in 3 Sum by fixing one more element:
- First, sort the array. Sorting enables the two-pointer technique and makes duplicate skipping straightforward.
- Fix the first element with an outer loop (`i` from `0` to `n - 1`), skipping duplicate values for `i`.
- Fix the second element with a nested loop (`j` from `i + 1` to `n - 1`), skipping duplicate values for `j` .
- For each fixed pair `(i, j)`, use two pointers: `k` starting just after `j`, and `l` starting at the end of the array.
  - If `arr[i] + arr[j] + arr[k] + arr[l]` is less than the target, move `k` forward to increase the sum.
  - If it's greater than the target, move `l` backward to decrease the sum.
  - If it equals the target, record the quadruplet, then move both `k` and `l` inward while skipping over duplicate values to avoid repeating the same quadruplet.

Since the two-pointer scan for each fixed pair `(i, j)` takes `O(n)` time, and this is done for every pair of elements, the overall time complexity becomes `O(n^3)` (sorting itself costs `O(n log n)`, which is dominated by the `O(n^3)` main loop). The auxiliary space used is `O(1)` beyond the space needed to store the output quadruplets, making this far more efficient than the hashing approach in terms of extra space.

*Note: When adding up four numbers, intermediate sums can exceed the range of a 32-bit integer, so it's good practice to use a wider type (like `long long`) when computing the sum to avoid overflow.*

### Takeaway
2 Sum, 3 Sum, and 4 Sum all follow the same underlying pattern: sort the array, fix all but the last two elements, and use two pointers to efficiently find the remaining pair, skipping duplicates at every fixed level to ensure unique results.
