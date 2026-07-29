# Count Occurrences in Sorted Array

## Problem Statement

You are given a sorted array containing `N` integers and a number `X`,
you have to find the number of occurrences of `X` in the given array.

## Examples

```
Example 1:
Input: N = 7, X = 3, array[] = {2, 2, 3, 3, 3, 3, 4}
Output: 4
Explanation: 3 is occurring 4 times in the given array so it is our
answer.

Example 2:
Input: N = 8, X = 2, array[] = {1, 1, 2, 2, 2, 2, 2, 3}
Output: 5
Explanation: 2 is occurring 5 times in the given array so it is our
answer.
```

## Brute Force Approach

Linearly scan the whole array and increment a counter every time
`arr[i] == x`. Simple, but this checks every element even though the
array is sorted.

- **Time Complexity:** `O(N)`
- **Space Complexity:** `O(1)`

Since the array is **sorted**, we don't need to check every element —
this is a strong signal to use **Binary Search** instead.

---

## Optimal Approach — Using Lower Bound and Upper Bound

### Key Idea

In a sorted array, all occurrences of `x` (if they exist) are grouped
together, forming a contiguous block:

```
arr = [1, 1, 2, 2, 2, 2, 2, 3]
                ^-------^
             all the 2's sit together
```

So instead of counting one by one, we just need to find:

1. The index of the **first occurrence** of `x` → this is exactly what
   `lower_bound(x)` gives us (`arr[i] >= x`, and since `x` exists, the
   first such index is exactly where `x` starts).
2. The index right **after the last occurrence** of `x` → this is
   exactly what `upper_bound(x)` gives us (`arr[i] > x`, i.e., the
   first index strictly greater than `x`).

Once we have both, the **count of occurrences** is simply:

```
count = upperBound(x) - lowerBound(x)
```

This works because `upperBound` and `lowerBound` mark the exact start
and end boundary of the block of `x` values.

### Handling the "Not Found" Case

If `x` doesn't exist in the array at all, `lowerBound(x)` will point to
where `x` *would* be inserted, but `arr[lowerBound(x)]` will not
actually equal `x`. So before computing the count, we check:

```cpp
if (lb == n || arr[lb] != x) return 0;
```

This avoids wrongly reporting a count when `x` is not present.

### Code

```cpp
int lowerBound(int arr[], int n, int target) {
    int lo = 0, hi = n - 1;
    int ans = n;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] >= target) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

int upperBound(int arr[], int n, int target) {
    int lo = 0, hi = n - 1;
    int ans = n;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] > target) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

int countOccurrences(int arr[], int n, int x) {
    int lb = lowerBound(arr, n, x);
    if (lb == n || arr[lb] != x) return 0;
    int ub = upperBound(arr, n, x);
    return ub - lb;
}
```

## Dry Run

```
arr = {2, 2, 3, 3, 3, 3, 4}, x = 3

lowerBound(x=3):
  finds first index where arr[i] >= 3 -> index 2

upperBound(x=3):
  finds first index where arr[i] > 3  -> index 6

count = upperBound - lowerBound = 6 - 2 = 4
```

Matches the expected output of `4`.

## Time Complexity

- **Time:** `O(log N)` — one call to `lower_bound` and one call to
  `upper_bound`, each `O(log N)`.
- **Space:** `O(1)`

This is a big improvement over the brute force `O(N)` approach,
especially useful when `N` is large and there are many queries.

## Notes for Revision

- Count of occurrences of `x` in a sorted array = `upper_bound(x) -
  lower_bound(x)`.
- Always check if `x` actually exists in the array before subtracting
  (`arr[lowerBound] == x`), otherwise you may get a wrong count of `0`
  values as something non-zero, or vice versa in edge cases.
- This is a direct, practical application of the Lower Bound / Upper
  Bound templates — no need to write separate first/last occurrence
  logic if you already have these two ready.
