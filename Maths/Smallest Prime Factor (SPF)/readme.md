# Prime Factorization Using Smallest Prime Factor (SPF)

Find the prime factorization of a number (including duplicate factors, e.g. `12 = 2 × 2 × 3`) efficiently across **multiple queries**.

---

## 1. The Problem

For each query, we're given a number `n` and need to output its prime factorization.

**Naive approach:** For every query, do trial division — check divisibility starting from `2` up to `√n`, dividing out each prime factor as you find it.

- Per query: `O(√n)`
- For `Q` queries: `O(Q × √n)`

This is inefficient when `Q` is large and `n` can be as big as `10^6` or more, since the work is repeated from scratch every time.

---

## 2. The Optimization: Smallest Prime Factor (SPF)

Instead of recomputing factors for every query, precompute the **smallest prime factor** of every number up to a maximum limit `maxN` — once.

### Step 1: Initialize
Create an array `spf[0...maxN]` and initialize:

```
spf[i] = i   for every i
```

This means initially, every number is assumed to be its own smallest prime factor.

### Step 2: Sieve-Based Computation
Using a Sieve of Eratosthenes-style pass:

```
for i = 2 to √maxN:
    if spf[i] == i:              // i is prime
        for j = i*i to maxN, step i:
            if spf[j] == j:      // not yet assigned a smaller prime factor
                spf[j] = i
```

After this, `spf[x]` holds the smallest prime number that divides `x`.

---

## 3. Answering Queries Efficiently

Once the `spf` array is built, factorizing any number `n` is simple — repeatedly divide `n` by its smallest prime factor until it becomes `1`:

```
factors = []
while n != 1:
    factors.push(spf[n])
    n = n / spf[n]
```

This naturally includes duplicate prime factors (e.g., `12 → 2, 2, 3`).

- **Per query time:** `O(log n)` — since `n` shrinks by at least a factor of `2` at each step.

---

## 4. Final Algorithm (Summary)

```
1. Build spf[0...maxN] where spf[i] = i initially
2. For i = 2 to √maxN:
       if spf[i] == i:
           for j = i*i to maxN, step i:
               if spf[j] == j:
                   spf[j] = i
3. For each query n:
       while n != 1:
           print spf[n]
           n = n / spf[n]
```

---

## 5. Complexity Analysis

| Type              | Complexity                     |
|-------------------|----------------------------------|
| Pre-computation   | O(n log(log n)), n = maxN        |
| Query Time        | O(log n) per query                |
| Space             | O(n) — for the `spf` array        |

Compared to the naive `O(Q × √n)` approach, this is far faster when there are many queries, since the expensive pre-computation is done only once.

---

## 6. Code

See [`spf_prime_factorization.cpp`](./spf_prime_factorization.cpp) for the C++ implementation.

**Sample run:**
```
Enter number of queries: 2
Enter number: 12
Prime factorization of 12: 2 2 3
Enter number: 60
Prime factorization of 60: 2 2 3 5
```

---

## 7. Why It's Efficient

- The `spf` array is built only **once**, regardless of the number of queries.
- Each query then factorizes a number in `O(log n)` by repeated division — no trial division or repeated primality checks needed.
- Makes multi-query prime factorization problems tractable even when `n` and `Q` are both large.
