# 🔢 Arrays — Basics & Core Problems

---

## 📑 Table of Contents

- [📖 What is an Array?](#-what-is-an-array)
- [🧭 Problem Solving Approach](#-problem-solving-approach)
- [1️⃣ Largest Element in an Array](#1️⃣-largest-element-in-an-array)
- [2️⃣ Second Largest Element (Without Sorting)](#2️⃣-second-largest-element-without-sorting)
- [3️⃣ Check if Array is Sorted](#3️⃣-check-if-array-is-sorted)
- [4️⃣ Remove Duplicates from Sorted Array](#4️⃣-remove-duplicates-from-sorted-array)
- [🖥️ C++ Implementation](#️-c-implementation)

---

## 📖 What is an Array?

An **array** is a collection of elements of the same type, stored in **contiguous memory locations**, and accessed using an **index** (starting from `0`).

- Declared with a fixed size: `int arr[5];`
- Each element is accessed in `O(1)` time using its index: `arr[i]`
- Because memory is contiguous, arrays are fast to read but costly to resize or insert/delete in the middle.

---

## 🧭 Problem Solving Approach

Every problem below is solved using a **brute → better → optimal** flow:

1. **Brute Force** — the first, most obvious solution (often involves sorting or extra passes).
2. **Better** — an improvement that avoids unnecessary work.
3. **Optimal** — the most efficient solution, usually a **single pass** with `O(1)` extra space.

This mirrors how you're expected to think out loud in an interview — start simple, then optimize.

---

## 1️⃣ Largest Element in an Array

**Question:** Given an array of integers, find the **largest element** in it.

**Test Case 1**
```
Input: arr = [2, 5, 1, 3, 0]
Output: 5
```

**Test Case 2**
```
Input: arr = [8, 8, 8, 8]
Output: 8
```

### Solution

- **Brute Force:** Sort the array, then the last element is the largest. Cost: `O(n log n)`.
- **Optimal:** Do a **single pass**, keeping track of the maximum value seen so far. Cost: `O(n)`, no extra space.

---

## 2️⃣ Second Largest Element (Without Sorting)

**Question:** Given an array of integers, find the **second largest** distinct element without sorting the array.

**Test Case 1**
```
Input: arr = [8, 8, 3, 5, 6, 6, 8, 9]
Output: 8   (largest is 9, second largest distinct is 8)
```

**Test Case 2**
```
Input: arr = [1, 2]
Output: 1
```

### Solution

- **Brute Force:** Sort the array, then scan backward from the end for the first element **different from the largest**. Cost: `O(n log n)`.
- **Better:** Two passes — first pass finds the largest, second pass finds the largest element **smaller than** that. Cost: `O(2n)`.
- **Optimal:** **Single pass** — maintain two variables, `largest` and `secondLargest`.
  - If the current element is greater than `largest`, update `secondLargest = largest`, then `largest = current`.
  - Else if the current element is greater than `secondLargest` (and not equal to `largest`), update `secondLargest = current`.
  - Cost: `O(n)`, no extra space.

---

## 3️⃣ Check if Array is Sorted

**Question:** Given an array, check whether it is sorted in **non-descending order**.

**Test Case 1**
```
Input: arr = [1, 2, 2, 3, 4]
Output: true
```

**Test Case 2**
```
Input: arr = [5, 3, 4, 1]
Output: false
```

### Solution

- **Optimal (only approach needed):** Walk through the array once, comparing every element with the **next** one.
  - If `arr[i] > arr[i+1]` at any point, the array is **not sorted** — return `false` immediately.
  - If the loop completes without finding such a pair, the array **is sorted** — return `true`.
  - Cost: `O(n)`, no extra space.

---

## 4️⃣ Remove Duplicates from Sorted Array

**Question:** Given a **sorted** array, remove duplicates **in-place** so each element appears only once, and return the count of unique elements.

**Test Case 1**
```
Input: arr = [1, 1, 2, 2, 2, 3, 3]
Output: 3   → array becomes [1, 2, 3, ...]
```

**Test Case 2**
```
Input: arr = [1, 1, 1, 1]
Output: 1   → array becomes [1, ...]
```

### Solution

- **Brute Force:** Insert every element into a **Set** (auto-removes duplicates), then copy the set's contents back into the array. Cost: `O(n log n)`, extra `O(n)` space.
- **Optimal — Two Pointers:** Since the array is already **sorted**, duplicates are always adjacent.
  - Maintain a pointer `i` marking the last confirmed-unique position (start at `0`).
  - Walk through the array with a second pointer `j` from `1` to `n-1`.
  - Whenever `arr[j] != arr[i]`, it's a new unique value — increment `i` and set `arr[i] = arr[j]`.
  - The final unique count is `i + 1`.
  - Cost: `O(n)` time, `O(1)` extra space — done **in-place**.

---

## 🖥️ C++ Implementation

See [`arrays_basics.cpp`](./arrays_basics.cpp)
