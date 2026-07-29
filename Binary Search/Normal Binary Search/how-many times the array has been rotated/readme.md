# Find Out How Many Times the Array Has Been Rotated

## Problem Statement

Given an integer array `arr` of size `N`, sorted in ascending order
(with distinct values). Now the array is rotated between 1 to N times,
which is unknown. Find how many times the array has been rotated.

## Pre-requisites

- Find Minimum in Rotated Sorted Array
- Search in Rotated Sorted Array II
- Binary Search algorithm

## Examples

```
Input : arr = [4,5,6,7,0,1,2,3]
Result: 4
Explanation: The original array should be [0,1,2,3,4,5,6,7]. So, we can
notice that the array has been rotated 4 times.

Input : arr = [3,4,5,1,2]
Output: 3
Explanation: The original array should be [1,2,3,4,5]. So, we can
notice that the array has been rotated 3 times.
```

## Key Observation

This problem is a direct extension of **"Find Minimum in Rotated
Sorted Array"**.

Notice something important: the number of times the array has been
rotated is exactly equal to the **index of the minimum element** in
the rotated array.

```
arr    = [4, 5, 6, 7, 0, 1, 2, 3]
index  =  0  1  2  3  4  5  6  7
                       ^
              minimum element (0) is at index 4
              -> array has been rotated 4 times
```

This makes sense because rotating a sorted array `k` times pushes the
first `k` elements to the end, and the original smallest element
(`arr[0]` before rotation) ends up sitting exactly at index `k` in the
rotated array.

So the problem reduces to: **find the index of the minimum element**,
using the same binary search idea as before.

## How it Works (Step by Step)

1. Take two pointers, `lo = 0` and `hi = n - 1`.
2. While `lo < hi`:
   - Find `mid = lo + (hi - lo) / 2`.
   - If `arr[mid] > arr[hi]`, the minimum (and hence the rotation
     point) lies strictly to the right of `mid`, so set
     `lo = mid + 1`.
   - Else, the minimum lies at `mid` or to its left, so set
     `hi = mid`.
3. When the loop ends, `lo == hi`, and this index **is** the answer —
   the number of times the array was rotated.

## Code

```cpp
int findKRotation(vector<int>& arr) {
    int lo = 0, hi = arr.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] > arr[hi]) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    return lo;
}
```

## Dry Run

```
arr = [4, 5, 6, 7, 0, 1, 2, 3]

lo=0, hi=7, mid=3 -> arr[3]=7, arr[7]=3
  7 > 3 -> rotation point is to the right -> lo = 4

lo=4, hi=7, mid=5 -> arr[5]=1, arr[7]=3
  1 <= 3 -> rotation point is at mid or left -> hi = 5

lo=4, hi=5, mid=4 -> arr[4]=0, arr[5]=1
  0 <= 1 -> rotation point is at mid or left -> hi = 4

lo=4, hi=4 -> loop ends -> return 4
```

Matches the expected output of `4`.

## Edge Case: Array Not Rotated at All

If the array is already fully sorted (e.g., `[1,2,3,4,5]`), the
minimum element sits at index `0`, and the algorithm correctly returns
`0`, meaning the array was rotated `0` times (or a full `n` times,
depending on how the problem defines it — check the exact problem
constraints if `k` is expected to be strictly between `1` and `n`).

## Time Complexity

- **Time:** `O(log n)`
- **Space:** `O(1)`

## Notes for Revision

- This problem is really just **"Find Minimum in Rotated Sorted
  Array"** in disguise — instead of returning `arr[lo]` (the value),
  we return `lo` (the index), since the index of the minimum directly
  tells us the rotation count.
- Same care applies here as with the minimum-finding template: compare
  `arr[mid]` with `arr[hi]`, use `lo < hi` as the loop condition, and
  use `hi = mid` (not `mid - 1`), since `mid` could still be the
  answer.
- If duplicate elements are allowed, the same fix from "Search in
  Rotated Sorted Array II" applies — add a check for
  `arr[mid] == arr[hi]` and shrink `hi--` in that case, since we can't
  safely decide direction otherwise.
