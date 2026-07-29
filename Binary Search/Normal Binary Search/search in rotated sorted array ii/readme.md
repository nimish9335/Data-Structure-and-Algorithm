# Search in Rotated Sorted Array II

## Problem Statement

There is an integer array `nums` sorted in non-decreasing order (not
necessarily with distinct values).

Before being passed to your function, `nums` is rotated at an unknown
pivot index `k` (`0 <= k < nums.length`) such that the resulting array
is `[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ...,
nums[k-1]]` (0-indexed).

For example, `[0,1,2,4,4,4,5,6,6,7]` might be rotated at pivot index 5
and become `[4,5,6,6,7,0,1,2,4,4]`.

Given the array `nums` after the rotation and an integer `target`,
return `true` if `target` is in `nums`, or `false` if it is not in
`nums`.

You must decrease the overall operation steps as much as possible.

## Example

```
Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true

Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false
```

## How is This Different from Search in Rotated Sorted Array (I)?

In the previous version, all values in `nums` were **distinct**. That
guarantee let us always figure out which half (left or right of `mid`)
was properly sorted just by comparing `nums[lo]`, `nums[mid]`, and
`nums[hi]`.

Here, **duplicates are allowed**. This breaks that guarantee in one
specific edge case:

```
nums = [3, 1, 2, 3, 3, 3, 3]
lo = 0, hi = 6, mid = 3

nums[lo] = 3, nums[mid] = 3, nums[hi] = 3
```

When `nums[lo] == nums[mid] == nums[hi]`, we genuinely **cannot tell**
which half is sorted just by looking at these three values — both
halves could look identical on the boundary while the actual rotation
point is hidden somewhere inside.

## Key Fix

Whenever `nums[lo] == nums[mid] == nums[hi]`, we can't safely decide a
direction. Instead, we just shrink the search space slightly from both
ends:

```cpp
lo++;
hi--;
```

This is safe because we already checked `nums[mid] == target` before
this point, so we're not skipping over the answer if it happens to sit
exactly at `lo` or `hi` — we just move past that specific
indistinguishable duplicate and continue narrowing down.

In every other case, the logic is **exactly the same** as the distinct
values version.

## How it Works (Step by Step)

1. Take two pointers, `lo = 0` and `hi = n - 1`.
2. Find `mid = lo + (hi - lo) / 2`.
3. If `nums[mid] == target`, return `true`.
4. If `nums[lo] == nums[mid]` and `nums[mid] == nums[hi]`, we can't
   determine the sorted half, so shrink both ends: `lo++`, `hi--`.
5. Otherwise, determine which half is sorted:
   - If `nums[lo] <= nums[mid]`, the **left half** is sorted.
     - If `target` lies in `[nums[lo], nums[mid])`, search left:
       `hi = mid - 1`.
     - Otherwise, search right: `lo = mid + 1`.
   - Else, the **right half** is sorted.
     - If `target` lies in `(nums[mid], nums[hi]]`, search right:
       `lo = mid + 1`.
     - Otherwise, search left: `hi = mid - 1`.
6. Repeat until `lo > hi`. If not found, return `false`.

## Code

```cpp
bool search(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return true;

        if (nums[lo] == nums[mid] && nums[mid] == nums[hi]) {
            lo++;
            hi--;
        } else if (nums[lo] <= nums[mid]) {
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
    return false;
}
```

## Dry Run

```
nums = [2, 5, 6, 0, 0, 1, 2], target = 0

lo=0, hi=6, mid=3 -> nums[3]=0 == target -> return true
```

Found immediately in this case. Let's trace a case where the ambiguous
duplicate check actually kicks in:

```
nums = [3, 1, 2, 3, 3, 3, 3], target = 1

lo=0, hi=6, mid=3 -> nums[3]=3, not target
  nums[lo]=3, nums[mid]=3, nums[hi]=3 -> all equal, ambiguous
  shrink: lo=1, hi=5

lo=1, hi=5, mid=3 -> nums[3]=3, not target
  nums[lo]=1, nums[mid]=3, nums[hi]=3 -> not all equal
  nums[lo]=1 <= nums[mid]=3 -> left half [1,2,3] is sorted
  is target(1) in [1, 3)? Yes -> search left -> hi = 2

lo=1, hi=2, mid=1 -> nums[1]=1 == target -> return true
```

This shows exactly why the `lo++, hi--` shrink step is needed — at the
first step, all three of `nums[lo]`, `nums[mid]`, `nums[hi]` were equal
to `3`, so there was no way to tell which half was sorted purely from
those three values.

## Time Complexity

- **Best/Average Case:** `O(log n)` — same as the distinct-values
  version, when there aren't too many duplicates at the boundaries.
- **Worst Case:** `O(n)` — happens when the array has many repeated
  elements (e.g., `[2,2,2,2,2,2,2,2,0,2,2]`), forcing the `lo++, hi--`
  shrink step to run almost every iteration, effectively degrading to
  linear search.
- **Space:** `O(1)`

## Notes for Revision

- The only structural difference from "Search in Rotated Sorted Array
  I" is the extra check for `nums[lo] == nums[mid] == nums[hi]`, which
  handles the ambiguous case caused by duplicates.
- Because of this ambiguous case, this version cannot guarantee true
  `O(log n)` in the worst case — that's expected and is explicitly
  called out in most problem statements/solutions for this variant.
- Always check `nums[mid] == target` **before** doing the duplicate
  shrink check, otherwise you might waste steps or mishandle the case
  where the target is exactly at `mid`.
