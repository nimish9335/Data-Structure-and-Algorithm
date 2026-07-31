# Kadane's Algorithm Notes

This file contains the three most common variations of Kadane's Algorithm used in interviews and competitive programming.

---

# 1. Standard Kadane's Algorithm

### Problem

Find the maximum sum subarray.

Subarray length must be **at least 1**.

Example

Input

```
[-2,1,-3,4,-1,2,1,-5,4]
```

Output

```
6
```

Subarray

```
[4,-1,2,1]
```

---

## Idea

At every index we have only two choices.

1. Start a new subarray.
2. Extend the previous subarray.

Transition

```
current = max(arr[i], current + arr[i])
answer = max(answer, current)
```

Time Complexity

```
O(N)
```

Space Complexity

```
O(1)
```

---

# 2. Kadane Supporting All Negative Arrays

Many beginners write Kadane like this

```cpp
sum += arr[i];

if(sum < 0)
    sum = 0;
```

This fails when every element is negative.

Example

```
[-5,-2,-7]
```

Wrong answer

```
0
```

Correct answer

```
-2
```

Therefore we always maintain

```
maximum = INT_MIN
```

before resetting the running sum.

Transition

```
current += arr[i]
maximum = max(maximum,current)

if(current < 0)
    current = 0
```

Time Complexity

```
O(N)
```

Space Complexity

```
O(1)
```

---

# 3. Modified Kadane (Length >= 2)

### Problem

Find the maximum sum subarray having **at least two elements**.

Example

```
[-5,100]
```

Answer

```
95
```

Length 1 subarrays are not allowed.

---

## DP States

We maintain two states.

### end1

Maximum sum subarray ending at current index.

Length >= 1

### end2

Maximum sum subarray ending at current index.

Length >= 2

---

## Transition

For Length >=1

```
end1 = max(arr[i], end1 + arr[i])
```

For Length >=2

Either

- Extend an existing valid subarray

or

- Convert a length 1 subarray into length 2

```
end2 = max(
    end2 + arr[i],
    previousEnd1 + arr[i]
)
```

Finally

```
answer = max(answer,end2)
```

---

## Complexity

Time

```
O(N)
```

Space

```
O(1)
```

---

# Summary

| Algorithm | Allowed Length | Negative Arrays | Time | Space |
|-----------|----------------|-----------------|------|-------|
| Standard Kadane | >=1 | Yes | O(N) | O(1) |
| Kadane (Reset to 0) | >=1 | Yes (with INT_MIN) | O(N) | O(1) |
| Modified Kadane | >=2 | Yes | O(N) | O(1) |

---

# Interview Tip

Whenever a problem asks

- Maximum Sum Subarray
- Maximum Circular Subarray
- Length at least K
- Length exactly K
- Maximum Product Subarray

always think of Kadane's Algorithm or its modified versions first.