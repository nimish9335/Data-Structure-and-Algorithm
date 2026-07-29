# Single Element in a Sorted Array

## Problem Statement

You are given a sorted array consisting of only integers where every
element appears exactly twice, except for one element which appears
exactly once.

Return the single element that appears only once.

Your solution must run in `O(log n)` time and `O(1)` space.

## Examples

```
Example 1:
Input: nums = [1,1,2,3,3,4,4,8,8]
Output: 2

Example 2:
Input: nums = [3,3,7,7,10,11,11]
Output: 10
```

## Why Not Linear/XOR Scan?

A simple approach is to XOR all elements together — since every
duplicate cancels itself out, the result is the single element. This
works in `O(n)` time, but the problem specifically demands `O(log n)`.
Since the array is **sorted**, this is a hint to use **Binary Search**
instead.

## Key Observation

Before the single element appears, every pair sits at
**(even index, odd index)**, like `(0,1), (2,3), (4,5), ...`.

Once we pass the single element, this pattern flips — pairs now sit at
**(odd index, even index)**, like `(5,6), (7,8), ...`.

```
nums  = [1, 1, 2, 3, 3, 4, 4, 8, 8]
index =  0  1  2  3  4  5  6  7  8

Before single element (index 2):
  pairs at (0,1) -> even,odd -> matches "even index equals next"

After single element:
  pairs at (3,4), (5,6), (7,8) -> odd,even -> matches "odd index
  equals next"
```

So at any `mid` index, we can check:

- If `mid` is **even**: in a properly paired region, `nums[mid]`
  should equal `nums[mid + 1]`.
  - If it does, the single element is **not** in this pair or before
    it — search right: `lo = mid + 2`.
  - If it doesn't match, the single element is at `mid` or somewhere
    before it — search left: `hi = mid - 1`.
- If `mid` is **odd**: in a properly paired region, `nums[mid]` should
  equal `nums[mid - 1]`.
  - If it does, search right: `lo = mid + 1`.
  - If it doesn't, search left: `hi = mid - 2`.

This way, we eliminate half the array each time, keeping it
`O(log n)`.

## How it Works (Step by Step)

1. Take two pointers, `lo = 0` and `hi = n - 2` (we stop one before the
   end since we always compare `mid` with a neighbor).
2. While `lo <= hi`:
   - Find `mid = lo + (hi - lo) / 2`.
   - If `mid` is even:
     - If `nums[mid] == nums[mid + 1]`, the pairing is still intact up
       to here, so move right: `lo = mid + 2`.
     - Else, move left: `hi = mid - 1`.
   - If `mid` is odd:
     - If `nums[mid] == nums[mid - 1]`, the pairing is still intact,
       move right: `lo = mid + 1`.
     - Else, move left: `hi = mid - 2`.
3. When the loop ends, `lo` points to the index of the single element.
   Return `nums[lo]`.

## Code

```cpp
int singleNonDuplicate(vector<int>& nums) {
    int lo = 0, hi = nums.size() - 2;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (mid % 2 == 0) {
            if (nums[mid] == nums[mid + 1]) {
                lo = mid + 2;
            } else {
                hi = mid - 1;
            }
        } else {
            if (nums[mid] == nums[mid - 1]) {
                lo = mid + 1;
            } else {
                hi = mid - 2;
            }
        }
    }
    return nums[lo];
}
```

## Dry Run

```
nums = [1, 1, 2, 3, 3, 4, 4, 8, 8]

lo=0, hi=7, mid=3 (odd)
  nums[3]=3, nums[2]=2 -> 3 != 2 -> pairing broken -> search left
  hi = mid - 2 = 1

lo=0, hi=1, mid=0 (even)
  nums[0]=1, nums[1]=1 -> equal -> pairing intact -> search right
  lo = mid + 2 = 2

lo=2, hi=1 -> loop ends (lo > hi)

return nums[lo] = nums[2] = 2
```

Matches the expected output of `2`.

## Time Complexity

- **Time:** `O(log n)`
- **Space:** `O(1)`

## Notes for Revision

- The core trick: track whether `mid` is even or odd, and compare it
  with the correct neighbor to check if the pairing pattern still
  holds at that point.
- `lo = mid + 2` / `hi = mid - 2` skip over a full matched pair in one
  jump instead of moving by 1, since we already know that whole pair
  is not the answer.
- This problem is a great example of spotting a hidden **structural
  pattern** (the even/odd pairing shift) that makes binary search
  possible even though the array isn't monotonic in the traditional
  sense.
- Edge cases to keep in mind: array of size `1` (the single element is
  just `nums[0]`), and single element being at the very start or very
  end of the array.
