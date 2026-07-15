# Print All Prime Factors of a Number

Revision notes for finding and printing all prime factors of a given number `n`.
Every approach below maps 1:1 to a function in `PrimeFactors.cpp`.

---

## Helper: Prime Check

**Function:** `isPrimeHelper(int n)`

Standard O(√n) prime check — loop `i` from `1` to `sqrt(n)`, count divisors using the `i` / `n/i` pair trick, and return `true` only if exactly 2 divisors exist. This helper is reused by the naive and square-root approaches below.

---

## 1. Naive Approach

**Function:** `primeFactorsNaive(int n)`

**Logic:**
- Loop `i` from `2` to `n`.
- For every `i`, check two conditions:
  1. Is `i` a divisor of `n`? (`n % i == 0`)
  2. Is `i` itself prime? (using `isPrimeHelper`)
- If both are true, `i` is a prime factor — print it.

**Why it's slow:** For every single value of `i` in the range `[2, n]`, we're doing an O(√i) prime check. This makes the approach heavy for large `n`.

**Time Complexity:** O(n × √n) — the outer loop is O(n), and each prime check inside is O(√n).

---

## 2. Optimized Approach (Square Root)

**Function:** `primeFactorsSqrt(int n)`

**Logic:**
- Key Observation: Just like divisors, factors come in pairs — if `i` divides `n`, then `n/i` also divides `n`.
- So instead of looping all the way to `n`, loop `i` only from `1` to `sqrt(n)`.
- For each `i` that divides `n`, check both `i` and `n/i`:
  - If `i` is prime → add it to the factors list.
  - If `n/i` is prime (and different from `i`) → add it too.
- Sort the collected factors before printing (since pairs come out of order).

**Improvement over Naive:** The outer loop now only runs O(√n) times instead of O(n) times. Each iteration still does an O(√n) prime check, but overall this is a big improvement.

**Time Complexity:** O(√n × √n) = O(n) in the worst case — better than naive, but still not optimal.

---

## 3. School-Method Optimization (Most Efficient)

**Function:** `primeFactorsSchoolMethod(int n)`

**Logic (the "long division" method taught in school):**
- Loop `i` from `2` to `sqrt(n)`.
- For each `i`, keep dividing `n` by `i` **as long as it's divisible** (`while (n % i == 0)`), and push `i` into the factors list every time.
- This automatically skips composite multiples — since we've already divided out all `2`s before reaching `4`, `4` can never divide `n` again after that point, so we never even need to check if `i` itself is prime.
- After the loop ends, if `n != 1`, it means the remaining value of `n` is a prime number larger than `sqrt(original n)` — push it as the final factor.

**Why the final `if (n != 1)` check matters:**
- The loop only checks `i` up to `sqrt(n)` (and `n` shrinks as we divide it).
- If the original number has one large prime factor greater than its square root (e.g., `n = 2 * 13`, where `13 > sqrt(26)`), the loop will divide out the `2` but exit before reaching `13`.
- Without this final check, that large prime factor would be missed entirely.

**Dry Run (n = 780):**
| i | n before | n % i == 0? | Action                  | n after |
|---|----------|-------------|--------------------------|---------|
| 2 | 780      | yes         | factor=2, divide         | 390     |
| 2 | 390      | yes         | factor=2, divide         | 195     |
| 2 | 195      | no          | move to next i           | 195     |
| 3 | 195      | yes         | factor=3, divide         | 65      |
| 3 | 65       | no          | move to next i           | 65      |
| 4 | 65       | no          | move to next i           | 65      |
| 5 | 65       | yes         | factor=5, divide         | 13      |
| 5 | 13       | no          | loop ends (i*i > 13)     | 13      |
| — | 13       | n != 1      | push 13 as final factor  | —       |

**Result:** Prime factors of 780 → `2, 2, 3, 5, 13`

**Why this beats the square-root approach:** We never re-check primality separately — dividing `n` down as we go guarantees that by the time we reach any `i`, all smaller prime factors are already removed, so any `i` that still divides `n` *must* be prime automatically. This also shrinks `n` itself during the loop, which further reduces the number of iterations needed.

**Time Complexity:**
- Worst case: O(√n) — happens when `n` itself is a prime number (the loop runs all the way to `sqrt(n)` without ever dividing anything, then the final check adds `n` itself).
- Much faster in practice for composite numbers, since `n` keeps shrinking as factors are divided out, meaning the effective loop range shrinks too.

-

## Quick Comparison Table

| Approach                | Core Idea                                          | Time Complexity     |
|--------------------------|-----------------------------------------------------|-----------------------|
| Naive                    | Check every `i` up to `n`, verify prime              | O(n√n)                |
| Optimized (Square Root)  | Loop till `√n`, check `i` and `n/i`                  | O(n)                  |
| School Method            | Divide out factors as found, final `n != 1` check    | O(√n) worst case      |

---

## Edge Cases to Remember
- `n = 1` → no prime factors at all (loop never runs, and final check `n != 1` fails, so nothing is added).
- `n` is itself prime (e.g., `n = 13`) → loop condition `i*i <= n` fails immediately, and the final `if (n != 1)` check correctly adds `13` as the only factor.
- Repeated prime factors (e.g., `n = 8 = 2*2*2`) → handled correctly by the `while` loop inside the school method, since it keeps dividing by the same `i` until it no longer divides evenly.

---

### How to use this repo
- `PrimeFactors.cpp` — All three approaches implemented, no `main()`, ready to import/test in any driver file.
- `README.md` (this file) — Concept-wise notes with dry run and complexity comparison for quick revision.
