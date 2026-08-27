# Sieve of Eratosthenes

An efficient algorithm to find **all prime numbers up to a given number `n`**, without checking every number individually for primality.

---

## 1. The Problem

The brute force way to find primes up to `n` is to check each number from `2` to `n`, and for every number, test whether it is divisible by any number smaller than it.

- For a single number, checking primality this way takes **O(√n)**.
- Doing this for all `n` numbers gives a total time complexity of roughly **O(n × √n)**, which becomes slow for large `n`.

We want something faster.

---

## 2. The Idea Behind the Sieve

Instead of checking each number one by one, we **pre-compute** which numbers are prime using a boolean array. This array acts like a "black box" — once built, checking if any number is prime becomes an **O(1)** lookup.

The core idea: **a prime number's multiples can never be prime.** So instead of testing divisibility, we simply "mark off" every multiple of every prime we find.

---

## 3. Step-by-Step Algorithm

### Step 1: Initialize the array
Create a boolean array `isPrime` of size `n + 1`, and set every value to `1` (assume every number is prime initially).

```
isPrime[0] = isPrime[1] = 0   // 0 and 1 are not prime
```

### Step 2: Mark multiples
Starting from `i = 2`, if `isPrime[i]` is still `1`, then `i` is prime. Mark all multiples of `i` (`2i, 3i, 4i, ...`) as `0` (not prime).

### Step 3 (Optimization 1): Start marking from `i × i`
When marking multiples of `i`, we don't need to start from `2i`. All multiples of `i` smaller than `i × i` (like `2i, 3i, ..., (i-1)i`) would have **already been marked** by smaller primes encountered earlier.

So we start marking from `i * i` instead of `2 * i`.

### Step 4 (Optimization 2): Outer loop only needs to run till `√n`
The outer loop (which picks the number `i`) only needs to run while `i * i <= n`. Beyond `√n`, there are no new multiples left to mark that haven't already been covered.

---

## 4. Final Algorithm (Summary)

```
1. Create isPrime[0...n], set all to 1
2. Set isPrime[0] = isPrime[1] = 0
3. For i = 2 to √n:
      if isPrime[i] == 1:
          for j = i*i to n, step i:
              isPrime[j] = 0
4. All indices i where isPrime[i] == 1 are prime numbers
```

---

## 5. Complexity Analysis

| Type   | Complexity                          |
|--------|--------------------------------------|
| Time   | O(n × log(log n))                    |
| Space  | O(n) — for the boolean `isPrime` array |

This is drastically faster than the brute force `O(n√n)` approach, especially for large values of `n`.

---

## 6. Code

See [`sieve_of_eratosthenes.cpp`](./sieve_of_eratosthenes.cpp) for the C++ implementation.

**Sample run:**
```
Enter the value of n: 30
Prime numbers up to 30:
2 3 5 7 11 13 17 19 23 29
```

---

## 7. Why It's Efficient

- No division/modulo operations needed to check primality of every number individually.
- Each number gets marked only by its smallest prime factor, keeping total work close to linear.
- Once the array is built, checking if any number `≤ n` is prime is an instant array lookup.
