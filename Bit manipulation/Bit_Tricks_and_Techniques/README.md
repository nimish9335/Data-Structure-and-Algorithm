# Bit Tricks and Techniques

This folder contains commonly used bit manipulation tricks that are useful in coding interviews and competitive programming.

---

## Topics Covered

- Swap Two Numbers
- Check i-th Bit
- Set i-th Bit
- Clear i-th Bit
- Toggle i-th Bit
- Remove Last Set Bit
- Check Power of Two
- Count Set Bits (Naive)
- Count Set Bits (Optimized)

---

## 1. Swap Two Numbers

### Formula

```cpp
a = a ^ b;
b = a ^ b;
a = a ^ b;
```

### Time Complexity

```
O(1)
```

---

## 2. Check i-th Bit

### Method 1

```cpp
n & (1 << i)
```

Returns non-zero if the bit is set.

### Method 2

```cpp
(n >> i) & 1
```

Shifts the required bit to the last position.

### Time Complexity

```
O(1)
```

---

## 3. Set i-th Bit

```cpp
n | (1 << i)
```

Changes the i-th bit to **1**.

### Time Complexity

```
O(1)
```

---

## 4. Clear i-th Bit

```cpp
n & ~(1 << i)
```

Changes the i-th bit to **0**.

### Time Complexity

```
O(1)
```

---

## 5. Toggle i-th Bit

```cpp
n ^ (1 << i)
```

Flips the i-th bit.

- 0 → 1
- 1 → 0

### Time Complexity

```
O(1)
```

---

## 6. Remove Last Set Bit

```cpp
n & (n - 1)
```

Removes the rightmost set bit.

Example

```
110100
110011
------
110000
```

### Time Complexity

```
O(1)
```

---

## 7. Check Power of Two

```cpp
n > 0 && (n & (n - 1)) == 0
```

A power of two always contains exactly one set bit.

### Time Complexity

```
O(1)
```

---

## 8. Count Set Bits (Naive)

```cpp
while(n){
    count += n & 1;
    n >>= 1;
}
```

### Time Complexity

```
O(log N)
```

---

## 9. Count Set Bits (Optimized)

```cpp
while(n){
    count++;
    n = n & (n - 1);
}
```

Each iteration removes one set bit.

### Time Complexity

```
O(Number of Set Bits)
```

---

## Complexity Summary

| Operation | Complexity |
|----------|-----------|
| Swap | O(1) |
| Check Bit | O(1) |
| Set Bit | O(1) |
| Clear Bit | O(1) |
| Toggle Bit | O(1) |
| Remove Last Set Bit | O(1) |
| Check Power of Two | O(1) |
| Count Set Bits (Naive) | O(log N) |
| Count Set Bits (Optimized) | O(Number of Set Bits) |

---

## Notes

- XOR (`^`) is useful for swapping and toggling bits.
- AND (`&`) is mainly used for checking and clearing bits.
- OR (`|`) is used for setting bits.
- Left Shift (`<<`) creates bit masks.
- Right Shift (`>>`) moves bits towards the least significant side.
- The expression `n & (n - 1)` is one of the most important bit manipulation tricks.