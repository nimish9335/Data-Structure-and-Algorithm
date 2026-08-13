# 3 Sum Problem

## Question

Given an array of integers `arr`, find all unique triplets `[arr[i], arr[j], arr[k]]` such that `i != j`, `j != k`, `i != k`, and `arr[i] + arr[j] + arr[k] == 0`. The solution set must not contain duplicate triplets.

### Test Case 1
**Input:**
```
6
-1 0 1 2 -1 -4
```
**Output:**
```
-1 -1 2
-1 0 1
```

### Test Case 2
**Input:**
```
3
0 0 0
```
**Output:**
```
0 0 0
```

## Solution Explanation

This problem is a natural extension of the 2 Sum problem covered in Striver's A to Z DSA Course, and it's typically explained right alongside it using a similar set of approaches, moving from brute force to the optimal two-pointer technique.

### 1. Brute Force Approach
Use three nested loops to check every possible triplet of elements in the array, and if a triplet sums to zero, store it after ensuring it isn't a duplicate (commonly done by inserting sorted triplets into a set). This works but is highly inefficient, with a time complexity of `O(n^3)` and extra space for duplicate removal.

### 2. Better Approach (Hashing)
Fix the first element with one loop, then for each first element, use a second loop combined with a hash set to check if the required third element (the complement needed to reach zero) has already been seen for the current second element. This reduces the complexity to about `O(n^2)` on average, using extra space for the hash set, plus a set to store unique triplets.

### 3. Optimal Approach (Two-Pointer)
This is the most efficient approach, and it builds directly on the two-pointer intuition from the 2 Sum problem:
- First, sort the array. Sorting makes it possible to use two pointers and also makes duplicate skipping straightforward.
- Fix the first element of the triplet with an outer loop, running from index `i = 0` to `n - 1`. Skip over duplicate values for `i` to avoid generating duplicate triplets.
- For each fixed `i`, use two pointers: `j` starting just after `i`, and `k` starting at the end of the array.
  - If `arr[i] + arr[j] + arr[k]` is less than `0`, move `j` forward to increase the sum.
  - If it's greater than `0`, move `k` backward to decrease the sum.
  - If it equals `0`, record the triplet, then move both `j` and `k` inward while skipping over any duplicate values to avoid repeating the same triplet.

Since the two-pointer scan for each fixed `i` takes `O(n)` time, and this is done for every element in the array, the overall time complexity becomes `O(n^2)` (with sorting itself costing `O(n log n)`, which is dominated by the `O(n^2)` two-pointer step). The auxiliary space used is `O(1)` beyond the space needed to store the output triplets, which is a significant improvement over the hashing approach's extra space usage.

### Takeaway
Just like in the 2 Sum problem, sorting the array unlocks the two-pointer technique, letting the algorithm avoid extra hash-based space while still achieving an efficient overall runtime, making it the preferred optimal solution for 3 Sum.
