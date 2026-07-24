# Apple Pile Division

## Problem

Andrei has a pile containing `n` apples.

He can divide any pile of `x` apples into two smaller piles:

```text
floor(x / 2)   and   ceil(x / 2)
```

Each division takes exactly:

```text
1 minute
```

Andrei wants to obtain **at least one pile containing exactly `k` apples**.

We need to find the **minimum number of divisions** required to obtain a pile of size `k`.

If it is impossible, return:

```text
-1
```

---

## Division Rule

### If `x` is Even

Both piles have the same size.

```text
x → x/2 , x/2
```

Example:

```text
10 → 5 , 5
```

### If `x` is Odd

The two piles differ by `1`.

```text
x → floor(x/2) , ceil(x/2)
```

Example:

```text
11 → 5 , 6
```

---

## Example 1

```text
n = 10
k = 3
```

Possible divisions:

```text
10
↓
5
↓
2 , 3
```

A pile containing exactly `3` apples is obtained after:

```text
2 divisions
```

Therefore:

```text
Answer = 2
```

---

## Example 2

```text
n = 11
k = 5
```

First division:

```text
11
↓
5 , 6
```

We immediately obtain a pile containing `5` apples.

```text
Answer = 1
```

---

## Example 3

```text
n = 21
k = 4
```

The possible pile sizes generated from `21` include:

```text
21, 10, 11, 5, 6, 2, 3, 1
```

A pile containing exactly `4` apples can never be obtained.

Therefore:

```text
Answer = -1
```

---

## Example 4

```text
n = 1000000000
k = 1
```

The pile size roughly halves after every division.

Eventually a pile containing exactly `1` apple can be obtained.

```text
Answer = 29
```

---

## Constraints

```text
1 <= t <= 10^4

1 <= n, k <= 10^9
```
