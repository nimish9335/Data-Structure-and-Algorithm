# 🚀 Merge Sort (Divide and Conquer)

<p align="center">

<img src="https://img.shields.io/badge/Algorithm-Merge%20Sort-blue?style=for-the-badge"/>

<img src="https://img.shields.io/badge/Time-O(nlogn)-success?style=for-the-badge"/>

<img src="https://img.shields.io/badge/Space-O(n)-orange?style=for-the-badge"/>

<img src="https://img.shields.io/badge/Stable-Yes-brightgreen?style=for-the-badge"/>

</p>

---

# 📖 Introduction

Merge Sort is a **Divide and Conquer** sorting algorithm.

Instead of sorting the complete array directly, it recursively divides the array into smaller halves until every subarray contains only one element.

Since a single element is already sorted, Merge Sort starts merging these smaller sorted arrays while maintaining sorted order.

The final merged array becomes completely sorted.

---

# 🧠 Algorithm

1. Divide the array into two halves.
2. Recursively sort the left half.
3. Recursively sort the right half.
4. Merge the two sorted halves.
5. Repeat until the complete array becomes sorted.

---

# 🔄 Working

```

                 Original Array

           8 3 5 4 7 6 1 2

                    │

      ┌─────────────┴─────────────┐

          8 3 5 4          7 6 1 2

      ┌──────┴──────┐   ┌──────┴──────┐

        8 3   5 4       7 6     1 2

      ┌─┴─┐ ┌─┴─┐      ┌─┴─┐   ┌─┴─┐

      8  3 5  4        7  6   1  2

             ▼

          Start Merging

      3 8    4 5    6 7    1 2

             ▼

        3 4 5 8   1 2 6 7

             ▼

      1 2 3 4 5 6 7 8

```

---

# 🌳 Recursive Tree

```

mergeSort(0,7)

│

├── mergeSort(0,3)

│      ├── mergeSort(0,1)

│      │      ├── mergeSort(0,0)

│      │      └── mergeSort(1,1)

│      └── mergeSort(2,3)

│

└── mergeSort(4,7)

       ├── mergeSort(4,5)

       └── mergeSort(6,7)

```

---

# ⚙️ Merge Function

Two already sorted arrays

```

Left

2 5 9

Right

1 4 10

```

Comparison

```

2 vs 1 → 1

2 vs 4 → 2

5 vs 4 → 4

5 vs 10 → 5

9 vs 10 → 9

Remaining → 10

```

Result

```

1 2 4 5 9 10

```

---

# 💻 Code

```cpp
void mergeSort(vector<int>& arr,int low,int high){

    if(low>=high)
        return;

    int mid=low+(high-low)/2;

    mergeSort(arr,low,mid);

    mergeSort(arr,mid+1,high);

    merge(arr,low,mid,high);
}
```

---

# ⏱️ Complexity Analysis

| Case | Time Complexity |
|------|-----------------|
| Best | O(n log n) |
| Average | O(n log n) |
| Worst | O(n log n) |

---

# 💾 Space Complexity

```
Auxiliary Space : O(n)

Recursive Stack : O(log n)
```

Overall

```
O(n)
```

---

# ✅ Advantages

- Guaranteed O(n log n)
- Stable Sorting Algorithm
- Predictable Performance
- Excellent for Linked Lists
- Easy to Parallelize
- Performs Well on Large Data

---

# ❌ Disadvantages

- Requires Extra Memory
- Not In-place
- Slightly Slower than Quick Sort in Practice

---

# 📌 Properties

| Property | Value |
|----------|-------|
| Technique | Divide and Conquer |
| Stable | ✅ Yes |
| In-place | ❌ No |
| Recursive | ✅ Yes |
| Comparison Sort | ✅ Yes |

---

# 🎯 Applications

- External Sorting
- Linked List Sorting
- Inversion Count
- Parallel Computing
- Large Dataset Processing
- Stable Sorting Requirement

---

# 📝 Example

Input

```
8 3 5 4 7 6 1 2
```

Output

```
1 2 3 4 5 6 7 8
```

---

# 📚 Folder Structure

```
Sorting
│
├── MergeSort.cpp
└── README.md
```

---

<div align="center">

### ⭐ If you found this helpful, consider giving this repository a Star!

Made with ❤️ using C++

</div>