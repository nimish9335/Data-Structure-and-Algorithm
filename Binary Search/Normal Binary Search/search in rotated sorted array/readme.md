
# Search in Rotated Sorted Array

## Problem Statement

There is an integer array `nums` sorted in ascending order (with
distinct values).

Prior to being passed to your function, `nums` is possibly left
rotated at an unknown index `k` (`1 <= k < nums.length`) such that the
resulting array is
`[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]`
(0-indexed).

For example, `[0,1,2,4,5,6,7]` might be left rotated by `3` indices and
become `[4,5,6,7,0,1,2]`.

Given the array `nums` after the possible rotation and an integer
`target`, return the index of `target` if it is in `nums`, or `-1` if
it is not in `nums`.

You must write an algorithm with `O(log n)` runtime complexity.

## Example

```
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
```

## Why Not Linear Search?

Scanning the array element by element gives `O(n)`, but the problem
demands `O(log n)`. This is a hint that binary search must still work
here — even though the array is not fully sorted, it has a special
structure we can exploit.

## Key Observation

Even after rotation, if you split the array at any `mid` index, **at
least one of the two halves (left or right) is always sorted**.

```
nums = [4, 5, 6, 7, 0, 1, 2]
                  mid = 3 (value 7)

Left half  [4, 5, 6, 7] -> sorted
Right half [0, 1, 2]    -> sorted (in this case both look sorted
                            individually, but only one half is
                            guaranteed to be fully sorted around mid
                            in general rotated cases)
```

So at every step of binary search:

1. Check which half (`lo` to `mid` or `mid` to `hi`) is sorted.
2. Check if `target` lies within the range of that sorted half.
   - If yes, discard the other half and search inside this half.
   - If no, the target must be in the other half — discard this half.

This way, we always eliminate half the array in every step, keeping
the algorithm `O(log n)`.

## How it Works (Step by Step)

1. Take two pointers, `lo = 0` and `hi = n - 1`.
2. Find `mid = lo + (hi - lo) / 2`.
3. If `nums[mid] == target`, return `mid` — found it.
4. Determine which half is sorted:
   - If `nums[lo] <= nums[mid]`, the **left half** (`lo` to `mid`) is
     sorted.
     - If `target` lies between `nums[lo]` and `nums[mid]` (exclusive
       of mid, since we already checked it), search left:
       `hi = mid - 1`.
     - Otherwise, search right: `lo = mid + 1`.
   - Else, the **right half** (`mid` to `hi`) is sorted.
     - If `target` lies between `nums[mid]` and `nums[hi]`, search
       right: `lo = mid + 1`.
     - Otherwise, search left: `hi = mid - 1`.
5. Repeat until `lo > hi`. If not found by then, return `-1`.

## Code

```cpp
int search(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return mid;

        if (nums[lo] <= nums[mid]) {
            if (nums[lo] <= target && target < nums[mid]) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        } else {
            if (nums[mid] < target && target <= nums[hi]) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
    }
    return -1;
}
```

## Dry Run

```
nums = [4, 5, 6, 7, 0, 1, 2], target = 0

lo=0, hi=6, mid=3 -> nums[3]=7
  nums[lo]=4 <= nums[mid]=7 -> left half [4,5,6,7] is sorted
  is target(0) in [4,7)? No -> search right -> lo = 4

lo=4, hi=6, mid=5 -> nums[5]=1
  nums[lo]=0 <= nums[mid]=1 -> left half [0,1] is sorted
  is target(0) in [0,1)? Yes -> search left -> hi = 4

lo=4, hi=4, mid=4 -> nums[4]=0 == target -> return 4
```

Matches the expected output of `4`.

## Time Complexity

- **Time:** `O(log n)`
- **Space:** `O(1)`

## Notes for Revision

- The array is not globally sorted, but **one half around any mid is
  always sorted** — this is the property that keeps binary search
  valid here.
- The trick is always: figure out which half is sorted first, then
  check if the target fits inside that sorted range before deciding
  which side to eliminate.
- Careful with boundary conditions (`<=` vs `<`) when checking if
  `target` lies inside a sorted half — getting these wrong is the most
  common bug in this problem.
- A common follow-up variation: what if the array has duplicate
  values? That breaks the "at least one half is sorted" guarantee in
  edge cases and requires an extra check (`nums[lo] == nums[mid]` then
  shrink both pointers by 1).
