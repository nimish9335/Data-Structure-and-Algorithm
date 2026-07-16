# Count Primes in a Range [L, R] — Multiple Queries

Given `Q` queries, where each query gives a range `[L, R]`, count how many prime numbers exist between `L` and `R` (inclusive).

**Constraints (typical):**
- `Q` can be up to `10^5`
- `R` can be as large as `10^6`

---

## 1. Brute Force Approach

For every query, check each number in `[L, R]` individually for primality (using trial division up to `√num`).

- Checking one number: `O(√num)`
- Checking full range for one query: `O((R - L) × √R)`
- Doing this for `Q` queries: extremely slow, effectively `O(Q × R × √R)` in the worst case.

This does not scale for large `Q` and `R`.

---

## 2. Sieve of Eratosthenes Approach

Precompute a boolean `isPrime` array up to the maximum possible `R` using the Sieve of Eratosthenes. This brings primality checking for a single number down to `O(1)`.

However, for each query we would still need to **iterate through the entire range `[L, R]`** and count primes one by one:

```
count = 0
for i = L to R:
    if isPrime[i]:
        count++
```

- Sieve build: `O(n log(log n))`
- Per query: `O(R - L)`
- Total: `O(n log(log n) + Q × n)` in the worst case — still too slow when ranges are large and queries are many.

---

## 3. Optimal Approach: Sieve + Prefix Sum

### Step 1: Build the Sieve
Precompute `isPrime[0...maxN]` using the Sieve of Eratosthenes, where `maxN` is the maximum possible value of `R` across all queries.

### Step 2: Build a Prefix Sum Array
Convert the sieve into a prefix sum array `prefix[]`, where:

```
prefix[i] = prefix[i - 1] + isPrime[i]
```

So `prefix[i]` stores the **total count of primes from 1 to i**.

### Step 3: Answer Each Query in O(1)
For any query `[L, R]`, the number of primes is simply:

```
count = prefix[R] - prefix[L - 1]
```

No looping through the range needed — just one subtraction per query.

---

## 4. Final Algorithm (Summary)

```
1. Build isPrime[0...maxN] using Sieve of Eratosthenes
2. Build prefix[0...maxN] where prefix[i] = prefix[i-1] + isPrime[i]
3. For each query (L, R):
       answer = prefix[R] - prefix[L - 1]
```

---

## 5. Complexity Analysis

| Type   | Complexity                              |
|--------|-------------------------------------------|
| Time   | O(n log(log n) + Q), where n = max(R)     |
| Space  | O(n) — for the sieve and prefix sum arrays |

This avoids multiplying by the range size for every query, making it efficient even when `Q` and `R` are both large.

---

## 6. Code

See [`count_primes_in_range.cpp`](./count_primes_in_range.cpp) for the C++ implementation.

**Sample run:**
```
Enter number of queries: 2
Enter L and R: 1 10
Count of primes in [1, 10]: 4
Enter L and R: 5 20
Count of primes in [5, 20]: 6
```

---

## 7. Why It's Efficient

- The sieve is built only **once**, regardless of how many queries there are.
- The prefix sum array turns "count primes in a range" into a simple **O(1)** lookup per query.
- Total cost depends only on the maximum value in the range and the number of queries — not on the size of each individual range.
