# First and Last Occurrence of a Target in Sorted Array

## Problem Statement

Given an array of integers `nums` sorted in non-decreasing order, find
the starting and ending position of a given `target` value.

If `target` is not found in the array, return `[-1, -1]`.

You must write an algorithm with `O(log n)` runtime complexity.

## Example

```
Input: nums = [5, 7, 7, 8, 8, 10], target = 8
Output: [3, 4]

Input: nums = [5, 7, 7, 8, 8, 10], target = 6
Output: [-1, -1]
```

## Why Not Linear Search?

A simple approach is to scan the array and note the first and last
index where `target` occurs — but that is `O(n)`, and the problem
specifically demands `O(log n)`. Since the array is sorted, this is a
strong hint to use **Binary Search**.

## Key Idea

Instead of one binary search, we run **two separate binary searches**:

1. One to find the **first occurrence** of `target`.
2. One to find the **last occurrence** of `target`.

Both are just modified versions of standard binary search, where
instead of stopping at the first match, we keep searching further in a
specific direction to push the answer to the boundary.

---

## Finding First Occurrence

We want the **smallest index** where `arr[i] == target`.

### How it Works

1. Take two pointers, `lo` at the start and `hi` at the end of the
   array.
2. Keep a variable `ans` initialized to `-1`.
3. Find `mid = lo + (hi - lo) / 2`.
4. Compare `arr[mid]` with `target`:
   - If `arr[mid] == target`, this could be the answer, so store `mid`
     in `ans`, but keep searching on the **left half** (`hi = mid - 1`)
     to check for an even earlier occurrence.
   - If `arr[mid] < target`, move `lo = mid + 1`.
   - If `arr[mid] > target`, move `hi = mid - 1`.
5. Repeat until `lo > hi`, then return `ans`.

### Code

```cpp
int findFirst(int arr[], int n, int target) {
    int lo = 0, hi = n - 1;
    int ans = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) {
            ans = mid;
            hi = mid - 1;
        } else if (arr[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}
```

---

## Finding Last Occurrence

We want the **largest index** where `arr[i] == target`.

### How it Works

Same as above, but this time, on a match we move towards the **right
half** instead of the left, to push the answer as far right as
possible.

1. Take two pointers, `lo` at the start and `hi` at the end of the
   array.
2. Keep a variable `ans` initialized to `-1`.
3. Find `mid = lo + (hi - lo) / 2`.
4. Compare `arr[mid]` with `target`:
   - If `arr[mid] == target`, store `mid` in `ans`, but keep searching
     on the **right half** (`lo = mid + 1`) to check for a later
     occurrence.
   - If `arr[mid] < target`, move `lo = mid + 1`.
   - If `arr[mid] > target`, move `hi = mid - 1`.
5. Repeat until `lo > hi`, then return `ans`.

### Code

```cpp
int findLast(int arr[], int n, int target) {
    int lo = 0, hi = n - 1;
    int ans = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) {
            ans = mid;
            lo = mid + 1;
        } else if (arr[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}
```

---

## Combining Both

```cpp
vector<int> searchRange(int arr[], int n, int target) {
    int first = findFirst(arr, n, target);
    int last = findLast(arr, n, target);
    return {first, last};
}
```

- If `target` doesn't exist in the array, both `findFirst` and
  `findLast` will return `-1`, so the final result is naturally
  `[-1, -1]` — no extra check needed.

## Dry Run

```
arr = [5, 7, 7, 8, 8, 10], target = 8

findFirst:
  lo=0, hi=5, mid=2 -> arr[2]=7 < 8 -> lo=3
  lo=3, hi=5, mid=4 -> arr[4]=8 == 8 -> ans=4, hi=3
  lo=3, hi=3, mid=3 -> arr[3]=8 == 8 -> ans=3, hi=2
  loop ends -> first = 3

findLast:
  lo=0, hi=5, mid=2 -> arr[2]=7 < 8 -> lo=3
  lo=3, hi=5, mid=4 -> arr[4]=8 == 8 -> ans=4, lo=5
  lo=5, hi=5, mid=5 -> arr[5]=10 > 8 -> hi=4
  loop ends -> last = 4

Result: [3, 4]
```

## Time Complexity

- **Time:** `O(log n)` — two independent binary searches, each
  `O(log n)`.
- **Space:** `O(1)` (excluding the output vector).

## Relation to Lower Bound / Upper Bound

This problem can also be solved using `lower_bound` and `upper_bound`:

- `first occurrence` = `lower_bound(target)`, but only valid if
  `arr[lower_bound(target)] == target`.
- `last occurrence` = `upper_bound(target) - 1`, again only valid if
  that index actually holds `target`.

Both approaches are equivalent — the direct first/last template above
is usually easier to remember and adapt during interviews.

## Notes for Revision

- This is essentially **two binary searches with a small tweak**: on a
  match, don't stop — keep narrowing in the direction that pushes
  toward the boundary you want (left for first, right for last).
- Always double check that the middle element actually equals
  `target` before narrowing further — moving too early on `<` or `>`
  cases without matching `==` first will break the logic.
- This pattern is very common in interviews (LeetCode: "Find First and
  Last Position of Element in Sorted Array") and is a must-know
  variation of binary search.
