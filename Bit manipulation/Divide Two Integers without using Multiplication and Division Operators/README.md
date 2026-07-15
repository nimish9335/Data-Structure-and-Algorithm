# Divide Two Integers (Bit Manipulation)

## Problem
Divide two integers without using multiplication (`*`), division (`/`), or modulo (`%`) operators.

---

## Idea

Instead of subtracting the divisor one by one, repeatedly subtract the **largest power of two multiple** of the divisor.

Find the maximum `k` such that:

```
(divisor << k) <= dividend
```

Then:

- Add `2^k` to the answer.
- Subtract `(divisor << k)` from the dividend.
- Repeat until the remaining dividend becomes smaller than the divisor.

This reduces the complexity from **O(N)** to **O(log² N)**.

---

## Steps

1. Handle overflow case.
2. Store the final sign.
3. Convert both numbers to positive (`long long`).
4. Find the largest valid shifted divisor.
5. Update answer and remaining dividend.
6. Apply the sign.

---

## Edge Cases

- `INT_MIN / -1 → INT_MAX`
- `INT_MIN / 1 → INT_MIN`
- Negative numbers
- Divisor greater than dividend
- Division by powers of two

---

## Complexity

- **Time:** `O(log² N)`
- **Space:** `O(1)`

---

## Pattern

- Bit Manipulation
- Binary Shifting
- Greedy