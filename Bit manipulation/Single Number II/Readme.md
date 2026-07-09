# Single Number II

## Problem

Given an integer array where:

- Every element appears exactly **three times**
- Only one element appears **once**

Return the element that appears only once.

---

# Approach 1: Hashing

Store the frequency of every element using a hash map.

### Algorithm

1. Traverse the array.
2. Store frequency of every number.
3. Return the element whose frequency is `1`.

### Complexity

- **Time:** `O(N)`
- **Space:** `O(N)`

---

# Approach 2: Count Set Bits

Instead of counting numbers, count the set bits at every bit position.

Since every duplicate number appears **3 times**, the count of every repeated bit will always be divisible by **3**.

If a bit count is **not divisible by 3**, then that bit belongs to the unique number.

### Algorithm

1. Traverse all 32 bit positions.
2. Count set bits for every position.
3. If `count % 3 != 0`, set that bit in the answer.

### Example

```text
nums = [2,2,3,2]

Binary

2 -> 0010
2 -> 0010
3 -> 0011
2 -> 0010

Bit Count

Bit 0 -> 1
Bit 1 -> 4

1 % 3 = 1
4 % 3 = 1

Answer = 0011 = 3
```

### Complexity

- **Time:** `O(32 × N)`
- **Space:** `O(1)`

---

# Approach 3: Sorting

Sort the array.

Every repeated element will form a group of three.

Traverse the sorted array in jumps of three.

If a triplet is broken, the unmatched element is the answer.

### Example

```text
Before Sorting

2 3 2 2 5 5 5

After Sorting

2 2 2 3 5 5 5

3 does not belong to any triplet.

Answer = 3
```

### Complexity

- **Time:** `O(N log N)`
- **Space:** `O(1)`

---

# Approach 4: Bucket Method (Optimal)

This is the most efficient solution.

Maintain two variables:

- `ones`
- `twos`

Each bit moves through three states:

```text
0 occurrence
↓

1 occurrence  -> ones

↓

2 occurrences -> twos

↓

3 occurrences -> removed
```

For every number:

```cpp
ones = (ones ^ x) & (~twos);
twos = (twos ^ x) & (~ones);
```

After processing the complete array,

```text
ones
```

contains the required answer.

### Example

```text
nums = [2,2,3,2]

After processing

ones = 3
twos = 0

Answer = 3
```

### Complexity

- **Time:** `O(N)`
- **Space:** `O(1)`

---

# Comparison

| Approach | Time | Space |
|----------|------|-------|
| Hashing | `O(N)` | `O(N)` |
| Count Set Bits | `O(32 × N)` | `O(1)` |
| Sorting | `O(N log N)` | `O(1)` |
| Bucket Method | `O(N)` | `O(1)` |

---

# Key Observations

- Hashing is simple but uses extra memory.
- Counting bits is a common bit manipulation technique.
- Sorting works without hashing but increases time complexity.
- The Bucket Method is the **optimal interview solution** with **O(N)** time and **O(1)** space.

---

# Key Takeaway

> When every element appears **3 times except one**, the Bucket Method (`ones` and `twos`) is the best solution because it processes every bit in constant space while maintaining linear time complexity.# Single Number II

