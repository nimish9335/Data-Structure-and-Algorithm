# Power Set (Generate All Subsets)

## Problem

Given an array of `n` elements, generate all possible subsets (Power Set).

---

## Idea

Every element has two choices:

- Include it
- Exclude it

So, an array of size `n` has:

```text
2^n subsets
```

Each subset can be represented using a **bitmask**.

- Bit = `1` → Include the element
- Bit = `0` → Exclude the element

---

## Algorithm

1. Calculate total subsets using `1 << n`.
2. Iterate from `0` to `(1 << n) - 1`.
3. For every number, check each bit:
   - If `(mask & (1 << i))` is non-zero, include `nums[i]`.
4. Store the generated subset.

---

## Example

```text
nums = [1, 2, 3]

Mask 000 -> {}
Mask 001 -> {1}
Mask 010 -> {2}
Mask 011 -> {1,2}
Mask 100 -> {3}
Mask 101 -> {1,3}
Mask 110 -> {2,3}
Mask 111 -> {1,2,3}
```

---

## Complexity

- **Time:** `O(n × 2^n)`
- **Space:** `O(n × 2^n)`

---

## Key Takeaway

> Every number from `0` to `(2^n - 1)` represents one subset.  
> The binary representation of the number decides which elements are included.