# Sort an Array of 0s, 1s, and 2s

## Question

Given an array `arr` consisting only of the integers `0`, `1`, and `2`, sort the array in-place without using any built-in sort function, in a single pass if possible.

### Test Case 1
**Input:**
```
6
0 2 1 2 0 1
```
**Output:**
```
0 0 1 1 2 2
```

### Test Case 2
**Input:**
```
5
0 1 2 0 1
```
**Output:**
```
0 0 1 1 2
```

## Solution Explanation

This problem and its solution are explained in Striver's A to Z DSA Course video on sorting an array of 0s, 1s, and 2s. The video walks through three approaches, increasing in efficiency.

### 1. Brute Force
Simply apply a standard sorting algorithm such as Merge Sort on the array. This works correctly but doesn't take advantage of the fact that only three distinct values are present. It runs in `O(n log n)` time and uses extra space.

### 2. Better Solution
Make two passes over the array:
- **First pass:** Count the number of 0s, 1s, and 2s in the array.
- **Second pass:** Overwrite the array by placing that many 0s first, followed by the counted number of 1s, and finally the counted number of 2s.

This takes `O(2n)` time (two linear passes) and `O(1)` extra space, but it does require looking at the array twice.

### 3. Optimal Solution — Dutch National Flag Algorithm
Striver explains this as the optimal approach, achieving the sort in a single pass with `O(n)` time and `O(1)` space, using three pointers: `low`, `mid`, and `high`.

The array is conceptually divided into four regions as the algorithm progresses:
- `arr[0 ... low-1]` → all 0s
- `arr[low ... mid-1]` → all 1s
- `arr[mid ... high]` → unsorted (unknown elements, yet to be processed)
- `arr[high+1 ... n-1]` → all 2s

The `mid` pointer walks through the unsorted region and decides what to do based on the value it finds:

- If `arr[mid] == 0`: swap `arr[low]` and `arr[mid]`, then increment both `low` and `mid`. This places the 0 in its correct region.
- If `arr[mid] == 1`: it's already in the correct place, so just increment `mid`.
- If `arr[mid] == 2`: swap `arr[mid]` and `arr[high]`, then decrement `high`. Note that `mid` is **not** incremented here, since the element swapped in from `high` still needs to be checked.

This process continues until `mid` crosses `high`, at which point the unsorted region shrinks to nothing and the entire array is sorted into the 0s, 1s, and 2s regions — all in a single traversal of the array.

This algorithm is known as the **Dutch National Flag algorithm**, named after the three colored bands of the Dutch flag, since it partitions the array into three distinct sections in one pass.
