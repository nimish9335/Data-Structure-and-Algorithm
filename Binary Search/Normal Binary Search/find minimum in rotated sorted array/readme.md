# Find Minimum in Rotated Sorted Array

## Problem Statement

Suppose an array of length `n` sorted in ascending order is **rotated**
between `1` and `n` times. For example, the array
`nums = [0,1,2,4,5,6,7]` might become:

- `[4,5,6,7,0,1,2]` if it was rotated 4 times.
- `[0,1,2,4,5,6,7]` if it was rotated 7 times.

Notice that rotating an array `[a[0], a[1], a[2], ..., a[n-1]]` 1 time
results in the array `[a[n-1], a[0], a[1], a[2], ..., a[n-2]]`.

Given the sorted rotated array `nums` of **unique** elements, return
**the minimum element** of this array.

You must write an algorithm that runs in `O(log n)` time.

## Example

```
Input: nums = [4,5,6,7,0,1,2]
Output: 0

Input: nums = [3,4,5,1,2]
Output: 1

Input: nums = [11,13,15,17]
Output: 11
```

## Why Not Linear Search?

Checking every element gives `O(n)`, but the problem demands
`O(log n)`. Since the array is a rotated version of a sorted array, it
still has enough structure for binary search to work.

## Key Observation

The minimum element is exactly the **pivot point** — the one spot
where the array "breaks" from ascending order (or, if the array isn't
rotated at all, the minimum is simply `nums[0]`).

```
nums = [4, 5, 6, 7, 0, 1, 2]
                   ^
              pivot / minimum
```

For any `mid` index, we compare `nums[mid]` with `nums[hi]`:

- If `nums[mid] > nums[hi]`, the minimum **cannot** be in the left part
  up to and including `mid` — it must be somewhere in the right half,
  strictly after `mid`. So we move `lo = mid + 1`.
- If `nums[mid] <= nums[hi]`, that means the right half from `mid` to
  `hi` is fully sorted, so the minimum could be `nums[mid]` itself or
  something before it. So we move `hi = mid` (keeping `mid` in the
  search space, since it could be the answer).

We keep shrinking the range this way until `lo == hi`, at which point
that index holds the minimum.

## How it Works (Step by Step)

1. Take two pointers, `lo = 0` and `hi = n - 1`.
2. While `lo < hi`:
   - Find `mid = lo + (hi - lo) / 2`.
   - If `nums[mid] > nums[hi]`, the minimum lies to the right of `mid`,
     so set `lo = mid + 1`.
   - Else, the minimum lies at `mid` or to its left, so set `hi = mid`.
3. When the loop ends, `lo == hi`, and `nums[lo]` is the minimum
   element.

## Code

```cpp
int findMin(vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[hi]) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return nums[lo];
}
```

## Dry Run

```
nums = [4, 5, 6, 7, 0, 1, 2]

lo=0, hi=6, mid=3 -> nums[3]=7, nums[6]=2
  7 > 2 -> minimum is to the right -> lo = 4

lo=4, hi=6, mid=5 -> nums[5]=1, nums[6]=2
  1 <= 2 -> minimum is at mid or left -> hi = 5

lo=4, hi=5, mid=4 -> nums[4]=0, nums[5]=1
  0 <= 1 -> minimum is at mid or left -> hi = 4

lo=4, hi=4 -> loop ends -> return nums[4] = 0
```

Matches the expected output of `0`.

## Why Compare with `nums[hi]` and Not `nums[lo]`?

Comparing `nums[mid]` with `nums[hi]` gives an unambiguous decision in
every case (since the array has **unique** elements):

- `nums[mid] > nums[hi]` always means the minimum is strictly to the
  right of `mid`.
- `nums[mid] <= nums[hi]` always means the right portion is sorted,
  and the minimum is at `mid` or somewhere to its left.

Comparing with `nums[lo]` instead can be ambiguous in some rotated
cases and requires extra care, so `nums[hi]` is the simpler and safer
choice for this template.

## Time Complexity

- **Time:** `O(log n)`
- **Space:** `O(1)`

## Notes for Revision

- This is a **find the pivot point** problem — the minimum element is
  the pivot, and it's the only place where the sorted order "resets".
- Always compare `nums[mid]` with `nums[hi]`, not `nums[mid]` with
  `nums[lo]` — it keeps the logic simpler and avoids extra edge case
  handling.
- Note the loop condition is `lo < hi` (not `lo <= hi`), and `hi = mid`
  (not `mid - 1`) — this is intentional, since `mid` itself could be
  the answer and must stay in the search space.
- If the array has **duplicate elements**, this exact template breaks
  in some edge cases (similar to "Search in Rotated Sorted Array II")
  and needs an extra check for `nums[mid] == nums[hi]`, shrinking
  `hi--` in that case.
