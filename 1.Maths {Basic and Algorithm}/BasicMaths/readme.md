# Basic Mathematics for DSA — Striver A2Z Sheet

Revision notes for the "Basic Maths" video of the Striver A2Z DSA Course.
Every concept below maps 1:1 to a function in `BasicMaths.cpp`.

---

## 1. Digit Extraction (Timestamp 1:57 - 9:40)

**Function:** `digitExtraction(int n)`

**Logic:**
- Any number's last digit can be extracted using `n % 10`.
- Once extracted, remove that digit from the number using `n = n / 10` (integer division).
- Repeat this in a loop until `n` becomes `0`.

**Why it matters:** This `%10` and `/10` combo is the base building block for almost every other problem in this list — reverse, palindrome, Armstrong, sum of digits, etc.

**Dry Run (n = 1234):**
| Step | n % 10 | n / 10 |
|------|--------|--------|
| 1    | 4      | 123    |
| 2    | 3      | 12     |
| 3    | 2      | 1      |
| 4    | 1      | 0      |

**Time Complexity:** O(number of digits) = O(log₁₀ n)

---

## 2. Count Digits (9:49 - 14:43)

**Functions:** `countDigitsLoop(int n)`, `countDigitsLog(int n)`

**Approach 1 — Loop:**
- Keep dividing `n` by 10 and increment a counter until `n` becomes `0`.
- Simple, intuitive, O(log₁₀ n).

**Approach 2 — Logarithmic (log10):**
- Mathematical shortcut: number of digits in `n` = `floor(log10(n)) + 1`.
- Example: `log10(1234) ≈ 3.09` → `floor(3.09) + 1 = 4` digits.
- Edge case: handle `n = 0` separately since `log10(0)` is undefined (treated as 1 digit).
- This is O(1) since `log10()` is a constant-time library call.

**When to use which:** Loop method is safer/more intuitive for interviews; log method is a good optimization to mention.

---

## 3. Reverse a Number (15:34 - 20:30)

**Function:** `reverseNumber(int n)`

**Logic:**
- Extract the last digit using `n % 10`.
- Build the reversed number: `rev = (rev * 10) + lastDigit`.
- Remove the last digit from `n` using `n = n / 10`.
- Repeat until `n == 0`.

**Dry Run (n = 123):**
| n   | lastDigit | rev            |
|-----|-----------|----------------|
| 123 | 3         | 0*10+3 = 3     |
| 12  | 2         | 3*10+2 = 32    |
| 1   | 1         | 32*10+1 = 321  |
| 0   | -         | stop           |

**Time Complexity:** O(log₁₀ n)

**Watch out for:** Integer overflow when reversing large numbers — use `long long` if the number can be large.

---

## 4. Palindrome Check (20:35 - 23:44)

**Function:** `isPalindrome(int n)`

**Logic:**
- A number is a palindrome if it reads the same forwards and backwards (e.g., 121, 1331).
- Store the original number.
- Reverse it using the `reverseNumber()` logic from concept 3.
- Compare `original == reversed`. If equal → palindrome.

**Time Complexity:** O(log₁₀ n) — dominated by the reverse operation.

---

## 5. Armstrong Numbers (23:45 - 26:22)

**Function:** `isArmstrong(int n)`

**Definition:** A number is an Armstrong number if the sum of its digits, each raised to the power of (number of digits), equals the number itself.
- For 3-digit numbers this simplifies to "sum of cubes of digits."
- Example: `153 = 1³ + 5³ + 3³ = 1 + 125 + 27 = 153` ✅

**Logic:**
- Store the original number.
- Extract each digit using `%10`, cube it, and add to a running `sum`.
- Remove the digit using `/10`.
- After the loop, compare `sum == original`.

**Time Complexity:** O(log₁₀ n)

---

## 6. Print All Divisors (26:24 - 39:43)

**Functions:** `printDivisorsBrute(int n)`, `printDivisorsOptimized(int n)`

**Brute Force:**
- Loop `i` from `1` to `n`, check `n % i == 0`.
- Time Complexity: **O(n)** — too slow for large `n`.

**Optimized (Square Root) Approach:**
- Key Observation: Divisors always come in **pairs** — if `i` divides `n`, then `n/i` also divides `n`.
- So you only need to loop `i` from `1` to `sqrt(n)`. For every `i` that divides `n`, both `i` and `n/i` are divisors.
- Special case: if `i == n/i` (perfect square case), add it only once to avoid duplicates.
- Sort the collected divisors at the end if you need them in order.

**Example (n = 36):**
- `i=1` → pair (1, 36)
- `i=2` → pair (2, 18)
- `i=3` → pair (3, 12)
- `i=4` → pair (4, 9)
- `i=6` → pair (6, 6) → add only once
- Loop stops when `i*i > 36` (i.e., i=7)

**Time Complexity:** O(√n)

---

## 7. Check for Prime (39:49 - 44:46)

**Function:** `isPrime(int n)`

**Definition:** A number is prime if it has exactly 2 divisors: 1 and itself.

**Logic (Optimized using square root):**
- Same idea as divisor counting — loop `i` from `1` to `sqrt(n)`.
- Count divisors found (remember pairs `i` and `n/i`).
- If total divisor count == 2 at the end → prime.
- Special handling: `n <= 1` is never prime.

**Why sqrt works:** If `n` had a divisor greater than `sqrt(n)`, it must also have a corresponding divisor smaller than `sqrt(n)`. So checking up to `sqrt(n)` is enough to know if more than 2 divisors exist.

**Time Complexity:** O(√n) — much better than brute force O(n).

---

## 8. GCD / HCF (44:48 - 1:02:22)

**Functions:** `gcdBrute(int n1, int n2)`, `gcdEuclidean(int n1, int n2)`

**Definition:** GCD (Greatest Common Divisor) / HCF (Highest Common Factor) is the largest number that divides both `n1` and `n2`.

**Brute Force:**
- Loop `i` from `1` to `min(n1, n2)`.
- If `i` divides both numbers, update `gcd = i`.
- Time Complexity: O(min(n1, n2)) — slow for large inputs.

**Euclidean Algorithm (Optimized):**
- Core idea: `gcd(n1, n2) = gcd(n1 - n2, n2)` if `n1 > n2` — and this can be sped up using modulo instead of repeated subtraction: `gcd(n1, n2) = gcd(n1 % n2, n2)`.
- Keep reducing the larger number using modulo with the smaller number until one of them becomes `0`.
- Whichever number is non-zero at that point is the GCD.

**Dry Run (n1 = 20, n2 = 8):**
| n1 | n2 |
|----|----|
| 20 | 8  |
| 4  | 8 (20%8=4, now n1<n2 so swap roles) |
| 4  | 0 (8%4=0) |

Result: GCD = 4

**Time Complexity:** O(log(min(n1, n2))) — extremely fast even for large numbers.

---

## Quick Revision Table

| # | Concept              | Key Trick                          | Time Complexity |
|---|----------------------|-------------------------------------|------------------|
| 1 | Digit Extraction     | `%10` and `/10`                     | O(log n)         |
| 2 | Count Digits         | Loop OR `log10(n) + 1`              | O(log n) / O(1)  |
| 3 | Reverse a Number     | `rev = rev*10 + lastDigit`          | O(log n)         |
| 4 | Palindrome Check     | Compare number with its reverse     | O(log n)         |
| 5 | Armstrong Number     | Sum of (digit ^ number_of_digits)   | O(log n)         |
| 6 | Print All Divisors   | Loop till `sqrt(n)`, take pairs     | O(√n)            |
| 7 | Check for Prime      | Count divisors till `sqrt(n)` == 2  | O(√n)            |
| 8 | GCD / HCF            | Euclidean Algorithm (`%` based)     | O(log(min(a,b))) |

---

## Next Topics in the Course
- Basic Recursion
- Basic Hashing

---

### How to use this repo
- `BasicMaths.cpp` — All functions implemented, no `main()`, ready to import/test in any driver file.
- `README.md` (this file) — Concept-wise notes for quick revision before interviews or contests.
