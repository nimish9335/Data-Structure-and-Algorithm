# 🔢 Bit Manipulation — Complete Notes & C++ Code

> 📺 Based on **Striver's Bit Manipulation Playlist** (Introductory Lecture)
> 📚 A one-stop guide covering Number Systems, Memory Representation, Complements, Bitwise Operators, Shift Operators, and Negative Number Representation — with working C++ code for every concept.

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
8. [Full C++ Demo File](#8-full-c-demo-file)
9. [Summary Table](#9-summary-table)

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

### 💻 C++ Code
```cpp
#include <bits/stdc++.h>
using namespace std;

// Decimal to Binary
string decimalToBinary(int n) {
    if (n == 0) return "0";
    string binary = "";
    while (n > 0) {
        binary += (char)('0' + (n % 2));
        n /= 2;
    }
    reverse(binary.begin(), binary.end());
    return binary;
}

// Binary to Decimal
int binaryToDecimal(string binary) {
    int decimal = 0;
    int power = 0;
    for (int i = binary.size() - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            decimal += pow(2, power);
        }
        power++;
    }
    return decimal;
}

int main() {
    cout << "13 in Binary: " << decimalToBinary(13) << endl;      // 1101
    cout << "1101 in Decimal: " << binaryToDecimal("1101") << endl; // 13
    return 0;
}
```

---

## 2. Computer Memory & Storage

- Computers store data in **bits (0s and 1s)** because hardware is built using transistors that have exactly two stable states — **ON (1)** and **OFF (0)**.
- An **integer in C++** typically occupies **32 bits (4 bytes)** of memory.
- Out of these 32 bits, the **Most Significant Bit (MSB)** is reserved as the **sign bit**:
  - `0` → Positive number
  - `1` → Negative number
- This is why binary is called the **"machine language"** — every instruction, character, and number ultimately reduces to a sequence of bits.

### 💻 C++ Code — Checking Size & Bit Representation
```cpp
#include <bits/stdc++.h>
using namespace std;

void printBits(int n) {
    for (int i = 31; i >= 0; i--) {
        cout << ((n >> i) & 1);
        if (i % 4 == 0) cout << " "; // spacing for readability
    }
    cout << endl;
}

int main() {
    cout << "Size of int: " << sizeof(int) << " bytes (" 
         << sizeof(int) * 8 << " bits)" << endl;

    int num = 13;
    cout << "32-bit representation of 13: ";
    printBits(num);

    int negNum = -13;
    cout << "32-bit representation of -13: ";
    printBits(negNum);

    return 0;
}
```

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

### 💻 C++ Code
```cpp
#include <bits/stdc++.h>
using namespace std;

string onesComplement(string binary) {
    string result = "";
    for (char b : binary)
        result += (b == '0') ? '1' : '0';
    return result;
}

string twosComplement(string binary) {
    string ones = onesComplement(binary);
    int n = ones.size();
    int carry = 1;
    for (int i = n - 1; i >= 0 && carry; i--) {
        if (ones[i] == '1') {
            ones[i] = '0'; // 1 + 1 = 10 -> carry continues
        } else {
            ones[i] = '1'; // 0 + 1 = 1 -> carry stops
            carry = 0;
        }
    }
    return ones;
}

int main() {
    string bin = "00001101"; // 13
    cout << "Original:        " << bin << endl;
    cout << "1's Complement:  " << onesComplement(bin) << endl;
    cout << "2's Complement:  " << twosComplement(bin) << endl;
    return 0;
}
```

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

### 💻 C++ Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int a = 5, b = 3; // 0101, 0011

    cout << "a & b = " << (a & b) << endl; // AND -> 1
    cout << "a | b = " << (a | b) << endl; // OR  -> 7
    cout << "a ^ b = " << (a ^ b) << endl; // XOR -> 6

    // Common Trick: Swap two numbers using XOR (without temp variable)
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    cout << "After XOR Swap -> a: " << a << ", b: " << b << endl;

    // Common Trick: Check if a number is even or odd using AND
    int n = 7;
    if (n & 1) cout << n << " is Odd" << endl;
    else cout << n << " is Even" << endl;

    return 0;
}
```

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

### 💻 C++ Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 5;

    cout << n << " << 1 = " << (n << 1) << endl; // 5*2  = 10
    cout << n << " << 2 = " << (n << 2) << endl; // 5*4  = 20

    int m = 20;
    cout << m << " >> 1 = " << (m >> 1) << endl; // 20/2 = 10
    cout << m << " >> 2 = " << (m >> 2) << endl; // 20/4 = 5

    // Overflow demonstration
    int x = 1;
    cout << "1 << 31 = " << (x << 31) << endl; // overflow -> becomes negative (sign bit set)

    return 0;
}
```

---

## 6. Negative Number Representation

- The leftmost bit (**MSB**) of a signed integer is the **sign bit**.
  - `0` → number is **positive**
  - `1` → number is **negative**
- Negative numbers are stored using **2's Complement** of their positive binary form.

**Example: Represent -13 as a 32-bit integer**
```
Step 1: Write 13 in binary   -> 00000000 00000000 00000000 00001101
Step 2: Take 1's complement  -> 11111111 11111111 11111111 11110010
Step 3: Add 1 (2's complement) -> 11111111 11111111 11111111 11110011  = -13
```

This method allows a single circuit to handle **both addition and subtraction**, since subtracting a number is the same as adding its 2's complement.

### 💻 C++ Code
```cpp
#include <bits/stdc++.h>
using namespace std;

void showSignBit(int n) {
    unsigned int mask = 1u << 31;
    int signBit = (n & mask) ? 1 : 0;
    cout << n << " -> Sign bit: " << signBit 
         << (signBit ? " (Negative)" : " (Positive)") << endl;
}

int main() {
    showSignBit(13);
    showSignBit(-13);
    showSignBit(0);
    return 0;
}
```

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

### 💻 C++ Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 5;
    cout << "n  = " << n << endl;
    cout << "~n = " << (~n) << endl;   // -6
    cout << "Formula check -(n+1) = " << -(n + 1) << endl; // -6

    int m = -6;
    cout << "~(-6) = " << (~m) << endl; // 5

    return 0;
}
```

---

## 8. Full C++ Demo File

A single runnable file combining every concept above — save this as `BitManipulation.cpp`.

```cpp
#include <bits/stdc++.h>
using namespace std;

// ---------- 1. Number System Conversion ----------
string decimalToBinary(int n) {
    if (n == 0) return "0";
    string binary = "";
    while (n > 0) {
        binary += (char)('0' + (n % 2));
        n /= 2;
    }
    reverse(binary.begin(), binary.end());
    return binary;
}

int binaryToDecimal(string binary) {
    int decimal = 0, power = 0;
    for (int i = binary.size() - 1; i >= 0; i--) {
        if (binary[i] == '1') decimal += pow(2, power);
        power++;
    }
    return decimal;
}

// ---------- 2. Memory Representation ----------
void printBits(int n) {
    for (int i = 31; i >= 0; i--) {
        cout << ((n >> i) & 1);
        if (i % 4 == 0) cout << " ";
    }
    cout << endl;
}

// ---------- 3. 1's and 2's Complement ----------
string onesComplement(string binary) {
    string result = "";
    for (char b : binary) result += (b == '0') ? '1' : '0';
    return result;
}

string twosComplement(string binary) {
    string ones = onesComplement(binary);
    int carry = 1;
    for (int i = ones.size() - 1; i >= 0 && carry; i--) {
        if (ones[i] == '1') ones[i] = '0';
        else { ones[i] = '1'; carry = 0; }
    }
    return ones;
}

// ---------- 6. Sign Bit Check ----------
void showSignBit(int n) {
    unsigned int mask = 1u << 31;
    int signBit = (n & mask) ? 1 : 0;
    cout << n << " -> Sign bit: " << signBit
         << (signBit ? " (Negative)" : " (Positive)") << endl;
}

int main() {
    cout << "===== 1. Number System Conversion =====\n";
    cout << "13 in Binary: " << decimalToBinary(13) << endl;
    cout << "1101 in Decimal: " << binaryToDecimal("1101") << endl;

    cout << "\n===== 2. Memory Representation (32-bit) =====\n";
    cout << "13  -> "; printBits(13);
    cout << "-13 -> "; printBits(-13);

    cout << "\n===== 3. 1's and 2's Complement =====\n";
    string bin = "00001101";
    cout << "Original:       " << bin << endl;
    cout << "1's Complement: " << onesComplement(bin) << endl;
    cout << "2's Complement: " << twosComplement(bin) << endl;

    cout << "\n===== 4. Bitwise Operators =====\n";
    int a = 5, b = 3;
    cout << "a & b = " << (a & b) << endl;
    cout << "a | b = " << (a | b) << endl;
    cout << "a ^ b = " << (a ^ b) << endl;

    cout << "\n===== 5. Shift Operators =====\n";
    cout << "5 << 1 = " << (5 << 1) << endl;
    cout << "20 >> 1 = " << (20 >> 1) << endl;

    cout << "\n===== 6. Negative Number Representation =====\n";
    showSignBit(13);
    showSignBit(-13);

    cout << "\n===== 7. NOT Operator =====\n";
    int n = 5;
    cout << "~5 = " << (~n) << endl;

    return 0;
}
```

**Compile & Run:**
```bash
g++ BitManipulation.cpp -o BitManipulation
./BitManipulation
```

---

## 9. Summary Table

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

⭐ If these notes helped you, consider starring the repo!
