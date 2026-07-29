# Binary Search on Answer

## What is it?

Binary Search on Answer is a technique used when we don't binary search on
an array index, but instead binary search on the **range of possible
answers** to a problem.

It is used when:

1. The answer lies in some range `[lo, hi]`.
2. There exists a function `isPossible(mid)` that tells whether a given
   value `mid` is a valid / feasible answer.
3. The feasibility function is **monotonic** — meaning if `mid` is
   possible, then everything on one side of `mid` is also possible
   (either all values greater than mid, or all values smaller than mid).

This monotonic property is what allows binary search to work, even though
we are not directly searching inside a sorted array.

## Identifying the Pattern

Ask yourself these questions when solving a problem:

- Can I guess an answer and check in O(n) or O(log n) whether it works?
- Does "if X works, does X+1 or X-1 also work" hold true?
- Is the question asking for **minimum value that satisfies a condition**
  or **maximum value that satisfies a condition**?

If yes, it is very likely a Binary Search on Answer problem.

Common problem types:

- Minimum time to complete tasks
- Minimum largest sum after splitting an array into k parts
- Maximum minimum distance (aggressive cows type problems)
- Minimum days to make m bouquets
- Capacity to ship packages within d days

## Template Explanation

```cpp
bool isPossible(int arr[], int n, int mid) {
    // Custom logic:
    // return true if 'mid' is a valid/feasible answer
    // return false otherwise
}
```

This function is problem-specific. You write the feasibility check here.

```cpp
int binarySearchOnAnswer(int arr[], int n, int lo, int hi) {
    int ans = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (isPossible(arr, n, mid)) {
            ans = mid;
            hi = mid - 1;   // try to find a smaller valid answer
        } else {
            lo = mid + 1;   // mid not valid, search on the right half
        }
    }
    return ans;
}
```

- `lo` and `hi` define the search space of possible answers (not indices
  of the array).
- If `isPossible(mid)` is `true`, we store it as a candidate answer and
  try to minimize it further by moving `hi = mid - 1`.
- If `isPossible(mid)` is `false`, we move `lo = mid + 1`.
- If we are looking for the **maximum** valid answer instead of minimum,
  simply reverse the update logic:
  ```cpp
  if (isPossible(mid)) {
      ans = mid;
      lo = mid + 1;   // try to find a bigger valid answer
  } else {
      hi = mid - 1;
  }
  ```

## Time Complexity

- `O(log(hi - lo) * cost_of_isPossible())`
- The `isPossible()` function is usually O(n), making total complexity
  `O(n log(range))`.

## Steps to Solve Any Binary Search on Answer Problem

1. Identify the range `[lo, hi]` of possible answers.
2. Write the `isPossible(mid)` function based on problem constraints.
3. Decide whether you need the **minimum** or **maximum** valid answer.
4. Apply the binary search template accordingly.
5. Return the stored `ans`.

## Notes for Revision

- This pattern converts a brute-force O(range) search into O(log(range)).
- The key is always the **monotonic feasibility check**, not the array
  itself being sorted.
- Practice identifying `isPossible()` logic — that is the actual hard
  part of these problems, the template stays the same.
