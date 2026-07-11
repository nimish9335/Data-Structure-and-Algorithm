# Single Number III — LeetCode 260

> Notes based on **take U forward** channel's explanation of Single Number III.

## Problem Statement

Given an integer array `nums`, in which **every element appears exactly twice**
except for **two elements** that appear only **once**, find those two
unique elements. You may return the answer in any order.

**Example**

```
Input:  nums = [1, 2, 1, 3, 2, 5]
Output: [3, 5]
```

---

## Approach 1: Brute Force (Hash Map)

**Video timestamp:** `1:21 - 5:57`

### Idea
1. Traverse the array once and store the frequency of every number in a
   hash map / ordered map.
2. Traverse the map again and pick out the two keys whose frequency is `1`.

```
nums = [1, 2, 1, 3, 2, 5]

Pass 1 (build frequency map):
1 -> 2
2 -> 2
3 -> 1
5 -> 1

Pass 2 (pick freq == 1):
Answer -> [3, 5]
```

### Complexity
| Metric | Value |
|---|---|
| Time  | `O(N log M)` — M = number of distinct elements (map ops cost `log M`) |
| Space | `O(M)` — extra space for the map |

This works, but it's not optimal — we can do it in a single pass with
**no extra space** using bit manipulation.

---

## Approach 2: Optimized — Bit Manipulation (XOR + Bucketing)

**Video timestamp:** `6:05 - 23:35`

This is the interview-favorite approach. It relies on two XOR properties:

```
a ^ a = 0      (a number XORed with itself cancels out)
a ^ 0 = a      (XOR with 0 leaves the number unchanged)
XOR is commutative & associative (order doesn't matter)
```

### Step 1 — XOR everything

**Timestamp:** `6:47 - 7:25`

If we XOR every element of the array together, every duplicate pair
cancels itself out (`a ^ a = 0`), leaving behind:

```
xorAll = uniqueA ^ uniqueB
```

```
nums = [1, 2, 1, 3, 2, 5]

1 ^ 2 ^ 1 ^ 3 ^ 2 ^ 5
= (1^1) ^ (2^2) ^ 3 ^ 5
=    0  ^   0   ^ 3 ^ 5
= 3 ^ 5
```

So `xorAll` now holds the XOR of the two **unique** numbers — but we
still need to separate them.

### Step 2 — Find a differentiating (rightmost set) bit

**Timestamp:** `8:43 - 11:27`

Since `uniqueA != uniqueB`, `xorAll` is guaranteed to be **non-zero**,
which means at least one bit position differs between the two numbers.

We isolate the **rightmost set bit** of `xorAll` using the two's
complement trick:

```
rightmostSetBit = xorAll & (-xorAll)
```

**Why this works (bit diagram):**

```
Suppose xorAll = 6  ->  binary: 0 1 1 0
             -xorAll  =  ...1 0 1 0   (two's complement: invert + 1)

  xorAll   :  0 1 1 0
 -xorAll   :  1 0 1 0
 -----------------------  AND
 result    :  0 0 1 0   -> rightmost set bit isolated (value = 2)
```

This single bit is guaranteed to be **set in one unique number** and
**unset in the other** — that's exactly the "differentiating bit" we
need to split the array into two groups.

### Step 3 — Bucket the array using that bit

**Timestamp:** `13:17 - 16:36`

Now traverse the *original* array again. For every number, check if
the `rightmostSetBit` is set:

```
if (num & rightmostSetBit) -> put it in Bucket 1
else                       -> put it in Bucket 2
```

Because **duplicate numbers are identical**, both copies of any
duplicate always land in the **same bucket** — so XOR-ing within each
bucket cancels all duplicates, leaving exactly one unique number per
bucket.

```
nums = [1, 2, 1, 3, 2, 5]
xorAll = 3 ^ 5 = 6 (0110)
rightmostSetBit = 2 (0010)

Check bit 1 (value 2) for each number:
 1 (0001) -> bit not set -> Bucket 2
 2 (0010) -> bit set     -> Bucket 1
 1 (0001) -> bit not set -> Bucket 2
 3 (0011) -> bit set     -> Bucket 1
 2 (0010) -> bit set     -> Bucket 1
 5 (0101) -> bit not set -> Bucket 2

Bucket 1: 2 ^ 3 ^ 2 = 3   (2's cancel, 3 remains)
Bucket 2: 1 ^ 1 ^ 5 = 5   (1's cancel, 5 remains)

Answer -> [3, 5]  ✅
```

### Diagram — full flow

```
        ┌────────────────────────────┐
        │   XOR all elements of nums │
        │  xorAll = uniqueA ^ uniqueB│
        └──────────────┬─────────────┘
                        │
                        ▼
        ┌────────────────────────────┐
        │ Isolate rightmost set bit  │
        │ rightmostSetBit =          │
        │   xorAll & (-xorAll)       │
        └──────────────┬─────────────┘
                        │
                        ▼
        ┌────────────────────────────┐
        │ Split nums into 2 buckets  │
        │ based on that bit          │
        └───────┬────────────┬───────┘
                 │            │
                 ▼            ▼
        ┌────────────┐ ┌────────────┐
        │  Bucket 1  │ │  Bucket 2  │
        │  XOR all   │ │  XOR all   │
        │ = uniqueA  │ │ = uniqueB  │
        └────────────┘ └────────────┘
```

### Complexity
| Metric | Value |
|---|---|
| Time  | `O(N)` — two linear passes over the array |
| Space | `O(1)` — only a handful of extra variables |

---

## ⚠️ Key Pitfall: Integer Overflow

**Timestamp:** `22:04 - 23:25`

Computing `-xorAll` (the two's complement negation) can **overflow**
if `xorAll` equals `INT_MIN` (`-2147483648`), because there is no
corresponding positive value representable in a 32-bit signed `int`
(`-(-2147483648)` overflows).

**Fix:** store `xorAll` (and the negation) as a `long` (or `long long`
in C++) instead of `int`. This gives enough headroom so the negation
never overflows.

```cpp
long xorAll = 0;             // use long, NOT int
for (int num : nums) xorAll ^= num;

long rightmostSetBit = xorAll & (-xorAll);  // safe now
```

---

## Files

| File | Description |
|---|---|
| `SingleNumberIII.cpp` | Full C++ implementation of both approaches, with test cases (including the `INT_MIN` overflow edge case) |

## Complexity Summary

| Approach | Time | Space |
|---|---|---|
| Brute Force (Hash Map) | `O(N log M)` | `O(M)` |
| Bit Manipulation (Optimal) | `O(N)` | `O(1)` |

## How to Run

```bash
g++ -std=c++17 -O2 SingleNumberIII.cpp -o solution
./solution
```

## Reference

- take U forward — Single Number III walkthrough (video timestamps noted above)
- LeetCode 260: https://leetcode.com/problems/single-number-iii/
