# Power Exponentiation — pow(x, n)

Revision notes for computing `x^n` efficiently.
Every approach below maps 1:1 to a function in `PowerExponentiation.cpp`.

---

## Problem Statement

Given a base `x` (double) and an exponent `n` (integer, can be negative), compute `x^n`.

---

## 1. Naive Approach

**Function:** `powNaive(double x, int n)`

**Logic:**
- Multiply `x` by itself `|n|` times in a loop, storing the result in `ans`.
- If `n` was negative, take the reciprocal of `ans` at the end (`1 / ans`).

**Why it's slow:** The loop runs `n` times regardless of any pattern in the exponent, doing one multiplication per iteration.

**Time Complexity:** O(n)
**Space Complexity:** O(1)

---

## 2. Optimal Approach (Binary Exponentiation)

**Function:** `powOptimal(double x, int n)`

**Core Idea:** Instead of multiplying `x` one step at a time, repeatedly **square the base** and **halve the exponent**. This works because of two simple identities:

- **If `n` is even:** `x^n = (x*x)^(n/2)`
  → Square the base, halve the exponent. The answer doesn't change, but the number of remaining multiplications drops drastically.

- **If `n` is odd:** `x^n = x * x^(n-1)`
  → Multiply one factor of `x` directly into the answer, then reduce `n` by 1 (making it even) so the even-case optimization can be applied on the next iteration.

**Step-by-step logic:**
1. Initialize `ans = 1.0`.
2. Convert `n` to its absolute value and store it in a `long long nn` (to safely handle `n = INT_MIN`, whose absolute value overflows a normal `int`).
3. Loop while `nn > 0`:
   - If `nn` is odd → multiply `ans` by `x`, then decrement `nn` by 1.
   - If `nn` is even → square `x` (`x = x * x`), then divide `nn` by 2.
4. After the loop, if the original `n` was negative, take the reciprocal: `ans = 1.0 / ans`.

**Dry Run (x = 3, n = 13):**
| nn | odd/even | Action                  | x (after) | ans (after) |
|----|----------|--------------------------|-----------|--------------|
| 13 | odd      | ans = 1*3 = 3, nn=12     | 3         | 3            |
| 12 | even     | x = 3*3 = 9, nn=6        | 9         | 3            |
| 6  | even     | x = 9*9 = 81, nn=3       | 81        | 3            |
| 3  | odd      | ans = 3*81 = 243, nn=2   | 81        | 243          |
| 2  | even     | x = 81*81 = 6561, nn=1   | 6561      | 243          |
| 1  | odd      | ans = 243*6561 = 1594323, nn=0 | 6561 | 1594323     |

Result: `3^13 = 1594323` ✅ (computed in just 6 steps instead of 13 naive multiplications)

---

## Edge Cases

### Negative Exponents
- If `n < 0`, the true mathematical answer is `1 / x^|n|`.
- Handled by: computing `x^|n|` normally using the loop above, and then taking the reciprocal (`1.0 / ans`) only at the very end.
- Example: `pow(2, -3) = 1 / (2^3) = 1/8 = 0.125`

### Double Precision
- Since `x` can be a floating-point number (e.g., `2.5`), `ans` **must** be declared as `double` (not `int`), otherwise precision is lost and results get truncated/rounded incorrectly.
- This also matters for the reciprocal step in the negative exponent case — dividing as integers would just give `0`.

### n = INT_MIN
- Taking `abs()` of `INT_MIN` directly overflows a 32-bit `int` (since `INT_MIN` has no positive counterpart in the same range).
- Fix: store the exponent in a `long long nn` before negating it, so the negation stays within range.

---

## Complexity Analysis

| Approach | Time Complexity | Space Complexity |
|----------|------------------|--------------------|
| Naive    | O(n)             | O(1)               |
| Optimal (Binary Exponentiation) | O(log n) | O(1) |

**Why O(log n):** Every iteration of the optimal loop either halves `nn` (even case) or reduces it by 1 followed by a halving on the very next step (odd case). Since the exponent is roughly divided by 2 each time, the total number of iterations is proportional to `log₂(n)`.

**Why O(1) space:** Only a fixed number of variables (`ans`, `x`, `nn`) are used — no recursion stack or extra data structures, so space usage doesn't grow with `n`.

---

### How to use this repo
- `PowerExponentiation.cpp` — Both approaches implemented, no `main()`, ready to import/test in any driver file.
- `README.md` (this file) — Concept-wise notes with dry run and complexity comparison for quick revision.
