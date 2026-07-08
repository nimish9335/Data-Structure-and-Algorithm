# Minimum Bit Flips to Convert Number

## Problem

Given two integers `start` and `goal`, find the minimum number of bit flips required to convert `start` into `goal`.

---

## Idea

A bit flip is needed only when the corresponding bits of `start` and `goal` are different.

The **XOR (`^`)** operator helps identify these positions.

- Same bits → `0`
- Different bits → `1`

```text
start = 10  -> 1010
goal  = 7   -> 0111

XOR = 1101
```

Every set bit (`1`) in the XOR result represents one required flip.

So the problem becomes:

> Count the number of set bits in `(start ^ goal)`.

---

## Algorithm

1. Compute `x = start ^ goal`.
2. Count the number of set bits in `x`.
3. Return the count.

---

## Complexity

- **Time:** `O(log(start ^ goal))`
- **Space:** `O(1)`

---

## Example

```text
Input:
start = 10
goal = 7

XOR = 13 (1101)

Set Bits = 3

Output:
3
```

---

## Key Takeaway

> XOR gives all positions where bits are different.  
> The answer is simply the number of set bits in the XOR result.