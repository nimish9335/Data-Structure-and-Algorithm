# Single Number I

## Problem

Given an integer array where every element appears exactly **twice** except for one element, find that single element.

---

## Idea

The **XOR (`^`)** operator has two important properties:

- `x ^ x = 0`
- `x ^ 0 = x`

If we XOR every element of the array:

- Duplicate elements cancel each other.
- Only the unique element remains.

---

## Algorithm

1. Initialize `ans = 0`.
2. Traverse the array.
3. XOR every element with `ans`.
4. Return `ans`.

---

## Example

```text
nums = [4, 1, 2, 1, 2]

ans = 0

0 ^ 4 = 4
4 ^ 1 = 5
5 ^ 2 = 7
7 ^ 1 = 6
6 ^ 2 = 4

Output = 4
```

---

## Complexity

- **Time:** `O(N)`
- **Space:** `O(1)`

---

## Why XOR Works

```text
a ^ a = 0
a ^ 0 = a
```

Example:

```text
2 ^ 3 ^ 2 ^ 4 ^ 3

= (2 ^ 2) ^ (3 ^ 3) ^ 4

= 0 ^ 0 ^ 4

= 4
```

---

## Key Takeaway

> XOR removes every number appearing twice, leaving only the unique element.