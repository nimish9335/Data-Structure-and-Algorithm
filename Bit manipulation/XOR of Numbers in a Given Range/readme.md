# XOR of Numbers in a Range

## Problem

Given two integers **L** and **R**, find the XOR of all numbers in the range **[L, R]**.

```
L ^ (L+1) ^ ... ^ R
```

---

# Brute Force

Traverse from **L** to **R** and keep taking XOR.

**Time Complexity:** `O(R - L + 1)`

---

# Observation

Instead of finding the XOR of every number, first understand the XOR from **1 to N**.

A repeating pattern appears after every **4 numbers**.

| N % 4 | XOR(1...N) |
|:-----:|:----------:|
| 0 | N |
| 1 | 1 |
| 2 | N + 1 |
| 3 | 0 |

---

# Pattern

```
          N
          │
      N % 4 ?
          │
   ┌───┬───┬───┬───┐
   │0  │1  │2  │3  │
   ├───┼───┼───┼───┤
   │N  │1  │N+1│0  │
   └───┴───┴───┴───┘
```

---

# Range XOR

To calculate the XOR from **L** to **R**,

```
XOR(L...R)
=
XOR(1...R)
^
XOR(1...(L-1))
```

The common prefix cancels out because

```
A ^ A = 0
```

Visualization:

```
1 ... (L-1)  L ... R
│────────────│──────│
      XOR(1...R)

^

1 ... (L-1)
│────────────│
 XOR(1...(L-1))

↓

L ... R
```

---

# Algorithm

1. Find `XOR(1...R)` using the modulo-4 pattern.
2. Find `XOR(1...(L-1))` using the same pattern.
3. XOR both answers.

---

# Complexity

| Time | Space |
|------|-------|
| O(1) | O(1) |

---

# Key Properties

- `A ^ A = 0`
- `A ^ 0 = A`
- XOR is **Commutative**
- XOR is **Associative**

---

## Summary

Whenever a problem asks for the XOR of a range, never iterate through every element. Use the repeating **modulo-4 pattern** to compute the prefix XORs and combine them to obtain the answer in **constant time**.