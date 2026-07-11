# Single Number III

## Problem

Given an array where every element appears **exactly twice** except **two elements** that appear only once, find those two unique numbers.

---

# Brute Force

Store the frequency of every element using a hash map.

After counting, return the elements whose frequency is **1**.

**Time Complexity:** `O(N)`

**Space Complexity:** `O(N)`

---

# Optimized Idea

The XOR of all elements removes every duplicate.

```
a ^ a = 0
```

Only the two unique numbers remain.

```
xor = x ^ y
```

Since `x ≠ y`, at least one bit of `xor` must be set.

---

# Step 1

Find the XOR of the complete array.

```
xor = x ^ y
```

---

# Step 2

Find the **rightmost set bit**.

```
mask = xor & (-xor)
```

This bit is different in the two unique numbers.

---

# Visualization

```
          xor = x ^ y
               │
               │
      Rightmost Set Bit
               │
        mask = xor & (-xor)
```

---

# Step 3

Divide all numbers into two groups.

```
                mask
                 │
        ┌────────┴────────┐
        │                 │
     Bit = 1           Bit = 0
        │                 │
      x, pairs         y, pairs
```

Duplicate numbers always go into the same group, so they cancel each other.

```
a ^ a = 0
```

Finally,

```
Group 1 XOR = x

Group 2 XOR = y
```

---

# Algorithm

1. XOR every element.
2. Find the rightmost set bit.
3. Divide numbers into two groups using this bit.
4. XOR each group separately.
5. The two XOR values are the required answers.

---

# Complexity

| Time | Space |
|------|-------|
| O(N) | O(1) |

---

# Important Note

While extracting the rightmost set bit, use a wider integer type if needed to safely handle edge cases involving the minimum integer value.

---

# Key Properties

- `a ^ a = 0`
- `a ^ 0 = a`
- XOR is **Commutative**
- XOR is **Associative**

---

## Summary

Whenever exactly **two unique elements** exist and every other element appears **twice**, compute the XOR of the array, isolate one distinguishing bit, split the elements into two groups, and XOR each group independently to obtain both unique numbers in **O(N)** time and **O(1)** extra space.