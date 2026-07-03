# 🔢 Bit Manipulation — Complete Notes

> 📺 Based on **Striver's Bit Manipulation Playlist** (Introductory Lecture)
> 📚 A one-stop guide covering Number Systems, Memory Representation, Complements, Bitwise Operators, Shift Operators, and Negative Number Representation.
> 💻 Full C++ implementation available in [`BitManipulation.cpp`](./BitManipulation.cpp)

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![Topic](https://img.shields.io/badge/DSA-Bit%20Manipulation-orange.svg)
![Status](https://img.shields.io/badge/Notes-Complete-brightgreen.svg)

---

## 📑 Table of Contents

1. [Number System Conversion](#1-number-system-conversion)
2. [Computer Memory & Storage](#2-computer-memory--storage)
3. [1's and 2's Complement](#3-1s-and-2s-complement)
4. [Bitwise Operators (AND, OR, XOR)](#4-bitwise-operators-and-or-xor)
5. [Shift Operators (Left & Right Shift)](#5-shift-operators-left--right-shift)
6. [Negative Number Representation](#6-negative-number-representation)
7. [NOT Operator](#7-not-operator)
8. [Summary Table](#8-summary-table)

---

## 1. Number System Conversion

Computers understand only **Binary (Base-2)**, while we humans work with **Decimal (Base-10)**. Bit manipulation starts with knowing how to convert between the two.

### 🔹 Decimal → Binary
- Keep **dividing the number by 2** and store the remainders.
- Read the remainders in **reverse order (bottom to top)** to get the binary equivalent.

**Example:** `13 → 1101`
```
13 / 2 = 6   remainder 1
 6 / 2 = 3   remainder 0
 3 / 2 = 1   remainder 1
 1 / 2 = 0   remainder 1
Reverse → 1101
```

### 🔹 Binary → Decimal
- Multiply each bit by `2^(position)` starting from the rightmost bit (position 0) and sum them up.

**Example:** `1101 → 13`
```
1*2^3 + 1*2^2 + 0*2^1 + 1*2^0 = 8 + 4 + 0 + 1 = 13
```

### ⏱️ Time & Space Complexity
| Conversion       | Time Complexity | Space Complexity |
|-------------------|-----------------|-------------------|
| Decimal → Binary  | O(log₂ N)       | O(log₂ N)         |
| Binary → Decimal  | O(N) (N = no. of bits) | O(1)        |

---

## 2. Computer Memory & Storage

- Computers store data in **bits (0s and 1s)** because hardware is built using transistors that have exactly two stable states — **ON (1)** and **OFF (0)**.
- An **integer in C++** typically occupies **32 bits (4 bytes)** of memory.
- Out of these 32 bits, the **Most Significant Bit (MSB)** is reserved as the **sign bit**:
  - `0` → Positive number
  - `1` → Negative number
- This is why binary is called the **"machine language"** — every instruction, character, and number ultimately reduces to a sequence of bits.

---

## 3. 1's and 2's Complement

Computers use complements to represent **negative numbers** in binary.

### 🔹 1's Complement
- Simply **flip every bit** (0 → 1 and 1 → 0).
- Example: `0000 1101` → `1111 0010`

### 🔹 2's Complement
- Take the **1's complement** and then **add 1** to it.
- This is the **actual method computers use** to store negative numbers.
- Example: `0000 1101 (13)`
  - 1's complement → `1111 0010`
  - Add 1 → `1111 0011` → this represents **-13**

---

## 4. Bitwise Operators (AND, OR, XOR)

| Operator | Symbol | Rule                                             |
|----------|--------|---------------------------------------------------|
| AND      | `&`    | Result bit is `1` only if **both** bits are `1`    |
| OR       | `\|`   | Result bit is `1` if **at least one** bit is `1`   |
| XOR      | `^`    | Result bit is `1` only if bits are **different**   |

**Example:** `a = 5 (0101)`, `b = 3 (0011)`
```
a & b = 0001 = 1
a | b = 0111 = 7
a ^ b = 0110 = 6
```

### 💡 Common Tricks
- **Swap two numbers without a temp variable** using XOR.
- **Check even/odd**: `n & 1` → `1` means odd, `0` means even.

---

## 5. Shift Operators (Left & Right Shift)

### 🔹 Left Shift (`<<`)
- Shifts all bits to the **left** by `n` positions and fills `0`s from the right.
- **Equivalent to multiplying by `2^n`**.
- Example: `5 << 1` → `10` (5 * 2)

### 🔹 Right Shift (`>>`)
- Shifts all bits to the **right** by `n` positions.
- **Equivalent to dividing by `2^n`** (integer division).
- Example: `10 >> 1` → `5` (10 / 2)

### ⚠️ Bit Overflow
- Since `int` is 32-bit, shifting left too many times can push bits **beyond the 32nd position**, causing them to be **lost/discarded** — this is called **overflow**, and it can silently give incorrect results.

---

## 6. Negative Number Representation

- The leftmost bit (**MSB**) of a signed integer is the **sign bit**.
  - `0` → number is **positive**
  - `1` → number is **negative**
- Negative numbers are stored using **2's Complement** of their positive binary form.

**Example: Represent -13 as a 32-bit integer**
```
Step 1: Write 13 in binary     -> 00000000 00000000 00000000 00001101
Step 2: Take 1's complement    -> 11111111 11111111 11111111 11110010
Step 3: Add 1 (2's complement) -> 11111111 11111111 11111111 11110011  = -13
```

This method allows a single circuit to handle **both addition and subtraction**, since subtracting a number is the same as adding its 2's complement.

---

## 7. NOT Operator

- The **bitwise NOT (`~`)** operator **flips every bit** of the number (0 → 1, 1 → 0).
- Because integers are stored in **2's complement** form, applying NOT to a number `n` gives:
  
  ```
  ~n = -(n + 1)
  ```

**Example:**
```
n  = 5   -> 0000 0101
~n = -6  -> 1111 1010
```

---

## 8. Summary Table

| Topic                        | Key Idea                                        | Complexity            |
|-------------------------------|--------------------------------------------------|------------------------|
| Decimal ↔ Binary              | Divide/Multiply by powers of 2                   | O(log N)               |
| Memory Storage                | 32-bit integers, MSB = sign bit                   | O(1)                   |
| 1's Complement                | Flip all bits                                     | O(N)                   |
| 2's Complement                | 1's complement + 1                                | O(N)                   |
| AND / OR / XOR                | Bit-by-bit comparison                             | O(1)                   |
| Left Shift `<<`               | Multiply by `2^n`                                 | O(1)                   |
| Right Shift `>>`               | Divide by `2^n`                                   | O(1)                   |
| Negative Numbers               | Stored as 2's complement                          | O(1)                   |
| NOT `~`                        | `~n = -(n+1)`                                     | O(1)                   |

---

### 📌 Credits
Notes prepared from **Striver's Bit Manipulation Playlist** — Introductory Lecture. Great starting point before moving on to problems like Single Number, Power of Two, Counting Set Bits, etc.

📂 All corresponding function implementations are available in [`BitManipulation.cpp`](./BitManipulation.cpp).

⭐ If these notes helped you, consider starring the repo!
