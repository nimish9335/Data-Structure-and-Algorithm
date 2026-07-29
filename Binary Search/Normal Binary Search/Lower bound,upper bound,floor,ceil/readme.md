# Lower Bound and Upper Bound

## What are they?

Lower Bound and Upper Bound are variations of Binary Search used on a
**sorted array** to find specific positions related to a `target`
value.

- **Lower Bound:** Find the smallest index `i` such that
  `arr[i] >= target`.
- **Upper Bound:** Find the smallest index `i` such that
  `arr[i] > target`.

If no such element exists in either case, both return `n` (size of the
array), meaning the value would be inserted at the end.

## Precondition

- The array **must be sorted** in ascending order.

---

## Lower Bound

### How it Works

1. Take two pointers, `lo` at the start and `hi` at the end of the
   array.
2. Keep a variable `ans` initialized to `n`.
3. Find `mid = lo + (hi - lo) / 2`.
4. Compare `arr[mid]` with `target`:
   - If `arr[mid] >= target`, store `mid` in `ans` and move
     `hi = mid - 1` to look for a smaller valid index.
   - If `arr[mid] < target`, move `lo = mid + 1`.
5. Repeat until `lo > hi`, then return `ans`.

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
```

### Example

```
arr = [1, 3, 5, 5, 7, 9]
target = 5

lowerBound(arr, 6, 5) -> returns index 2
(arr[2] = 5, first position where element >= 5)
```

---

## Upper Bound

### How it Works

1. Take two pointers, `lo` at the start and `hi` at the end of the
   array.
2. Keep a variable `ans` initialized to `n`.
3. Find `mid = lo + (hi - lo) / 2`.
4. Compare `arr[mid]` with `target`:
   - If `arr[mid] > target`, store `mid` in `ans` and move
     `hi = mid - 1` to look for a smaller valid index.
   - If `arr[mid] <= target`, move `lo = mid + 1`.
5. Repeat until `lo > hi`, then return `ans`.

### Code

```cpp
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
```

### Example

```
arr = [1, 3, 5, 5, 7, 9]
target = 5

upperBound(arr, 6, 5) -> returns index 4
(arr[4] = 7, first position where element > 5)
```

---

## Floor

Floor of a `target` in a sorted array is the **largest element that is
less than or equal to** the target.

> Find the largest index `i` such that `arr[i] <= target`.

If no such element exists (i.e., target is smaller than all elements),
floor returns `-1` (not found).

### How it Works

1. Take two pointers, `lo` at the start and `hi` at the end of the
   array.
2. Keep a variable `ans` initialized to `-1`.
3. Find `mid = lo + (hi - lo) / 2`.
4. Compare `arr[mid]` with `target`:
   - If `arr[mid] <= target`, this index **could be** the answer, so
     store it in `ans` and try to find a bigger valid index by moving
     `lo = mid + 1`.
   - If `arr[mid] > target`, this index is too big, move
     `hi = mid - 1`.
5. Repeat until `lo > hi`, then return `ans`.

### Code

```cpp
int findFloor(int arr[], int n, int target) {
    int lo = 0, hi = n - 1;
    int ans = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] <= target) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return ans;
}
```

### Example

```
arr = [1, 3, 5, 7, 9]
target = 6

findFloor(arr, 5, 6) -> returns index 2
(arr[2] = 5, largest element <= 6)
```

---

## Ceil

Ceil of a `target` in a sorted array is the **smallest element that is
greater than or equal to** the target.

> Find the smallest index `i` such that `arr[i] >= target`.

If no such element exists (i.e., target is greater than all elements),
ceil returns `-1` (not found).

Notice this condition is exactly the same as **lower bound**, just
returning `-1` instead of `n` when not found.

### How it Works

1. Take two pointers, `lo` at the start and `hi` at the end of the
   array.
2. Keep a variable `ans` initialized to `-1`.
3. Find `mid = lo + (hi - lo) / 2`.
4. Compare `arr[mid]` with `target`:
   - If `arr[mid] >= target`, this index **could be** the answer, so
     store it in `ans` and try to find a smaller valid index by moving
     `hi = mid - 1`.
   - If `arr[mid] < target`, this index is too small, move
     `lo = mid + 1`.
5. Repeat until `lo > hi`, then return `ans`.

### Code

```cpp
int findCeil(int arr[], int n, int target) {
    int lo = 0, hi = n - 1;
    int ans = -1;
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
```

### Example

```
arr = [1, 3, 5, 7, 9]
target = 6

findCeil(arr, 5, 6) -> returns index 3
(arr[3] = 7, smallest element >= 6)
```

---

## Difference Between Lower Bound and Upper Bound

| Function     | Condition           | Meaning                                    |
|--------------|---------------------|---------------------------------------------|
| lower_bound  | `arr[i] >= target`  | first index with value >= target            |
| upper_bound  | `arr[i] > target`   | first index with value strictly > target    |

- If `target` exists in the array, then:
  - `lower_bound` gives its **first occurrence**.
  - `upper_bound` gives the index **right after its last occurrence**.
- So, `upper_bound - lower_bound` gives the **count of occurrences** of
  `target` in the array.

## How Floor/Ceil Relate to Lower/Upper Bound

| Function | Condition           | Not Found Value | Meaning                                 |
|----------|---------------------|------------------|-------------------------------------------|
| floor    | `arr[i] <= target`  | `-1`             | largest element <= target                 |
| ceil     | `arr[i] >= target`  | `-1`             | smallest element >= target                |

- **Ceil** and **Lower Bound** use the exact same condition
  (`arr[i] >= target`) — the only difference is what they return when
  the element is not found (`-1` vs `n`).
- **Floor** moves in the opposite direction of lower bound: instead of
  shrinking `hi` on a match, it shrinks `lo`, because we want the
  **largest** valid index instead of the smallest.

## Time Complexity

- **Time:** `O(log n)` for each function.
- **Space:** `O(1)`

## When to Use

- Finding the first occurrence of an element → `lower_bound`.
- Finding the last occurrence of an element → `upper_bound - 1`.
- Counting frequency of an element →
  `upper_bound(target) - lower_bound(target)`.
- Finding insertion position to keep array sorted → `lower_bound`.
- Finding the closest smaller or equal element → `floor`.
- Finding the closest greater or equal element → `ceil`.
- Building block for many Binary Search on Answer problems.

## Notes for Revision

- Only one symbol changes between lower bound and upper bound
  templates: `>=` for lower bound, `>` for upper bound.
- Floor and Ceil follow the same binary search skeleton, just with
  `ans` initialized to `-1` instead of `n`, and floor moves `lo`
  forward on a match instead of pulling `hi` back.
- C++ STL already provides `lower_bound()` and `upper_bound()` — but
  writing all four (lower bound, upper bound, floor, ceil) manually
  helps solidify binary search logic, useful for competitive
  programming.
