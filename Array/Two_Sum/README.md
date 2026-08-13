# 2 Sum Problem

## Question

Given an array of integers `arr` and an integer `target`, find two numbers in the array such that they add up to `target`, and return the indices of those two numbers. Assume that exactly one valid pair exists, and the same element cannot be used twice.

*(Note: There is also a Yes/No variant of this problem, which only asks whether such a pair exists, without needing to return indices.)*

### Test Case 1
**Input:**
```
4
2 7 11 15
9
```
**Output:**
```
0 1
```
*(arr[0] + arr[1] = 2 + 7 = 9)*

### Test Case 2
**Input:**
```
3
3 2 4
6
```
**Output:**
```
1 2
```
*(arr[1] + arr[2] = 2 + 4 = 6)*

## Solution Explanation

This problem and its solutions are explained in Striver's A to Z DSA Course video on the 2 Sum problem. The video covers two versions of the problem — checking whether a pair with the given sum exists (Yes/No), and returning the actual indices of that pair — along with three approaches of increasing efficiency.

### 1. Brute Force Approach
Check every possible pair of elements in the array using two nested loops: for each element, look at every other element that comes after it and check if the two add up to the target. This works but is inefficient, with a time complexity of `O(n^2)`.

### 2. Better Approach (Hashing)
Use a hash map to store each element's value along with its index while iterating through the array just once:
- For each element, compute its complement (`target - arr[i]`).
- Check if that complement already exists in the hash map. If it does, a valid pair has been found, and the two indices can be returned.
- If not, insert the current element and its index into the hash map, and move on to the next element.

This reduces the lookup for each element's complement to average `O(1)` time, giving an overall time complexity of `O(n)` at the cost of `O(n)` extra space for the hash map. This is the approach implemented in the accompanying code, since it directly and efficiently supports returning the indices of the pair.

### 3. Optimal Approach (Two-Pointer)
This approach requires the array to be sorted first. Once sorted, place one pointer at the beginning of the array and another at the end:
- If the sum of the elements at the two pointers equals the target, a valid pair is found.
- If the sum is less than the target, move the left pointer forward to increase the sum.
- If the sum is greater than the target, move the right pointer backward to decrease the sum.

Because of the initial sort, this approach runs in `O(n log n)` time overall, but uses only `O(1)` auxiliary space, making it very memory-efficient. However, since sorting the array changes the original positions of elements, this approach is best suited for the Yes/No variety of the problem rather than for returning original indices (unless the original indices are tracked separately alongside the values before sorting).

### Takeaway
The hashing approach is generally preferred for its speed and simplicity when indices are needed, while the two-pointer technique is a valuable alternative when memory is constrained or when sorting the array is acceptable, particularly for the Yes/No variant of the problem.
