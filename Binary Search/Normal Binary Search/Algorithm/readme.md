# Standard Binary Search

## What is it?

Binary Search is a searching algorithm used to find the position of a
target value within a **sorted array**. Instead of checking every
element one by one (like linear search), it repeatedly divides the
search space in half, making it much faster.

## Precondition

- The array **must be sorted** (ascending in this template).
- If the array is not sorted, binary search will give incorrect results.

## How it Works

1. Take two pointers, `lo` at the start and `hi` at the end of the array.
2. Find the middle index: `mid = lo + (hi - lo) / 2`.
3. Compare `arr[mid]` with the `target`:
   - If `arr[mid] == target`, we found the answer, return `mid`.
   - If `arr[mid] < target`, the target must be in the right half, so
     move `lo = mid + 1`.
   - If `arr[mid] > target`, the target must be in the left half, so
     move `hi = mid - 1`.
4. Repeat until `lo > hi`. If the loop ends without finding the target,
   return `-1` (not found).

## Template Explanation

```cpp
int binarySearch(int arr[], int n, int target) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return -1;
}
```

- `lo` and `hi` represent the current search boundary (array indices).
- `mid = lo + (hi - lo) / 2` is used instead of `(lo + hi) / 2` to avoid
  integer overflow when `lo` and `hi` are large.
- The loop shrinks the search space by half every iteration.

## Why `mid = lo + (hi - lo) / 2`?

If `lo` and `hi` are both large numbers, `lo + hi` can overflow the
integer range. Writing it as `lo + (hi - lo) / 2` avoids that overflow
while giving the same result.

## Time Complexity

- **Time:** `O(log n)`
- **Space:** `O(1)` (iterative version)

## When to Use Binary Search

- Searching in a sorted array.
- Finding first/last occurrence of an element (variations of this
  template).
- Finding floor/ceiling of a value in a sorted array.
- Used as the foundation for advanced patterns like:
  - Binary Search on Answer
  - Binary Search on 2D matrices
  - Binary Search on rotated sorted arrays

## Notes for Revision

- Always check if the array is sorted before applying binary search.
- Two common mistakes to avoid:
  - Using `(lo + hi) / 2` instead of `lo + (hi - lo) / 2` (overflow risk).
  - Forgetting to update `lo` or `hi` correctly, causing infinite loops.
- This is the base template — variations like "first occurrence",
  "last occurrence", "lower bound", and "upper bound" are built by
  tweaking the condition checks inside the loop.
