# Find Peak Element

## Problem Statement

A peak element is an element that is strictly greater than its
neighbors.

Given a 0-indexed integer array `nums`, find a peak element, and return
its index. If the array contains multiple peaks, return the index to
**any of the peaks**.

You may imagine that `nums[-1] = nums[n] = -infinity`. In other words,
an element is always considered to be strictly greater than a
neighbor that is outside the array.

You must write an algorithm that runs in `O(log n)` time.

## Example

```
Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the
index number 2.

Input: nums = [1,2,1,3,5,6,4]
Output: 1 or 5
Explanation: Your function can return either index number 1 where the
peak element is 2, or index number 5 where the peak element is 6.
```

## Why Not Linear Search?

Scanning every element and checking both neighbors gives `O(n)`, but
the problem demands `O(log n)`. Since we don't need *the* peak, just
*a* peak, this hints that binary search can be used to zero in on one
efficiently, even though the array isn't sorted.

## Key Observation

Since `nums[-1]` and `nums[n]` are treated as `-infinity`, the array is
guaranteed to have **at least one peak**. Think of the array as a
"terrain" — it always starts and ends going "downhill" from a peak's
perspective, so somewhere in between, there must be a high point.

At any index `mid`, compare `nums[mid]` with its next neighbor
`nums[mid + 1]`:

- If `nums[mid] > nums[mid + 1]`, the array is going **downhill** after
  `mid`. This means a peak must exist at `mid` itself or somewhere to
  its **left** (since the slope is decreasing here, and it has to have
  risen from somewhere on the left, or `mid` itself is already the
  top). So we move `hi = mid`.
- If `nums[mid] < nums[mid + 1]`, the array is still going **uphill**
  at `mid`. This means a peak must exist somewhere to the **right** of
  `mid` (since it keeps rising, and eventually must come back down or
  hit the edge). So we move `lo = mid + 1`.

This works because we always move towards a "rising" direction, and a
peak is guaranteed to exist at the point where rising stops.

## How it Works (Step by Step)

1. Take two pointers, `lo = 0` and `hi = n - 1`.
2. While `lo < hi`:
   - Find `mid = lo + (hi - lo) / 2`.
   - If `nums[mid] > nums[mid + 1]`, a peak lies at `mid` or to its
     left, so set `hi = mid`.
   - Else, a peak lies to the right of `mid`, so set `lo = mid + 1`.
3. When the loop ends, `lo == hi`, and this index is a valid peak.
   Return `lo`.

## Code

```cpp
int findPeakElement(vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[mid + 1]) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}
```

## Dry Run

```
nums = [1, 2, 1, 3, 5, 6, 4]

lo=0, hi=6, mid=3 -> nums[3]=3, nums[4]=5
  3 < 5 -> still uphill -> search right -> lo = 4

lo=4, hi=6, mid=5 -> nums[5]=6, nums[6]=4
  6 > 4 -> downhill after mid -> peak at mid or left -> hi = 5

lo=4, hi=5, mid=4 -> nums[4]=5, nums[5]=6
  5 < 6 -> still uphill -> search right -> lo = 5

lo=5, hi=5 -> loop ends -> return 5
```

`nums[5] = 6`, which is indeed a valid peak (`5 < 6 > 4`). Matches one
of the accepted outputs.

## Time Complexity

- **Time:** `O(log n)`
- **Space:** `O(1)`

## Notes for Revision

- The array does **not** need to be sorted — the only property we use
  is comparing each element with its immediate next neighbor to decide
  a direction, which always works because of the guaranteed
  `-infinity` boundaries.
- Always compare `nums[mid]` with `nums[mid + 1]`, not `nums[mid - 1]`
  — this is what determines whether to move `hi = mid` (keeping `mid`
  in range) or `lo = mid + 1`.
- Since multiple peaks can exist, this algorithm doesn't try to find
  all of them — it just guarantees landing on **one** valid peak,
  which is exactly what the problem asks for.
- This is a nice example of applying binary search on a property
  (local slope direction) rather than on a fully sorted or rotated
  array.
