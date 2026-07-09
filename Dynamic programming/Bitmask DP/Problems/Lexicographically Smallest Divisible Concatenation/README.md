# Lexicographically Smallest Divisible Concatenation

## Tags

- Bitmask DP
- State Compression DP
- DFS
- Memoization
- Modulo Arithmetic
- Backtracking

---

# Problem Summary

Given an array `nums` and an integer `k`, arrange the numbers such that after concatenating them, the resulting number is divisible by `k`.

If multiple permutations are valid, return the **lexicographically smallest** one.

---

# Key Observation

Generating every permutation takes

```
O(n!)
```

For

```
n = 13

13! ≈ 6.2 Billion
```

which is impossible.

Instead of generating every permutation independently, we store previously computed states using **Bitmask DP**.

---

# Main Idea

While constructing the permutation, we only need two pieces of information.

1. Which numbers have already been used?
2. What is the current remainder after concatenation?

Hence the DP State becomes

```
dp(mask, remainder)
```

---

# DP State

```
dp(mask, remainder)
```

### mask

Represents which indices are already selected.

Example

```
nums = [3,12,45]

Mask

000 -> Nothing selected

001 -> 3 selected

011 -> 3 and 12 selected

111 -> All selected
```

---

### remainder

Current concatenated number modulo `k`.

Instead of storing the complete number, we only store

```
CurrentNumber % k
```

This keeps the state small.

---

# Transition

Try every unused number.

```
for every unused number

↓

Append it

↓

Update remainder

↓

DFS(newMask, newRemainder)
```

---

# Concatenation Formula

Suppose

```
Current Number

312
```

Append

```
45
```

New Number

```
31245

=

312 × 100 + 45
```

General Formula

```
newNumber

=

oldNumber × 10^(digits) + currentNumber
```

Taking modulo

```
newRem

=

(oldRem × multiplier + currentNumber) % k
```

where

```
multiplier = 10^(number of digits)
```

This formula is the heart of the solution.

---

# Why Sorting?

Before DFS,

```cpp
sort(nums.begin(), nums.end());
```

DFS always tries smaller numbers first.

Therefore,

the **first valid permutation found** is automatically the lexicographically smallest.

No additional comparison is required.

---

# Base Case

When

```
mask == FULL_MASK
```

all numbers have been used.

If

```
remainder == 0
```

then the constructed permutation is valid.

---

# Complexity

Number of Masks

```
2^n
```

Possible Remainders

```
k
```

Transition

```
n
```

Overall

```
Time

O(2^n × n × k)

Space

O(2^n × k)
```

---

# Common Mistakes

### 1. Forgetting to sort the array

Without sorting, the first solution found may not be lexicographically smallest.

---

### 2. Storing the complete concatenated number

Never store

```
3124512345...
```

Always store

```
Number % k
```

---

### 3. Wrong DP State

Correct

```
(mask, remainder)
```

Incorrect

```
(mask)
```

Mask alone cannot determine the future because different remainders produce different answers.

---

### 4. Forgetting Memoization

Without DP

```
O(n!)
```

With DP

```
O(2^n × n × k)
```

Huge optimization.

---

# Pattern Recognition

Think of this approach whenever you see

- `n ≤ 20`
- Every element is used exactly once
- Permutations
- Current answer depends on a small extra state (remainder, last node, sum, xor)

Typical DP States

```
dp(mask)

dp(mask, last)

dp(mask, remainder)

dp(mask, sum)

dp(mask, xor)
```

---

# Similar Problems

- Traveling Salesman Problem
- Hamiltonian Path
- Special Permutations
- Matchsticks to Square
- Beautiful Arrangement
- Can I Win

---

# Key Takeaways

- Represent selected elements using a **Bitmask**.
- Compress the problem state into **(mask, remainder)**.
- Use **DFS + Memoization** to avoid repeated computation.
- Store only the remainder instead of the entire number.
- Sorting guarantees the lexicographically smallest valid permutation.

This problem is an excellent example of **State Compression DP**, where a bitmask and a small auxiliary state together uniquely define the DP state.