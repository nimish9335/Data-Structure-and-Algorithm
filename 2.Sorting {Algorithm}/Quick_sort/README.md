<div align="center">

# ⚡ Quick Sort

<img src="https://readme-typing-svg.herokuapp.com?font=Poppins&size=28&duration=3500&pause=1000&color=00C2FF&center=true&vCenter=true&width=700&lines=Quick+Sort+Algorithm;Divide+%26+Conquer;In-Place+Sorting;Average+O(n+log+n)"/>

<br>

![Language](https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge\&logo=cplusplus)
![Algorithm](https://img.shields.io/badge/Algorithm-Quick%20Sort-blue?style=for-the-badge)
![Technique](https://img.shields.io/badge/Technique-Divide%20and%20Conquer-success?style=for-the-badge)
![Stable](https://img.shields.io/badge/Stable-No-red?style=for-the-badge)
![In Place](https://img.shields.io/badge/In--Place-Yes-brightgreen?style=for-the-badge)

</div>

---

# 📖 Introduction

Quick Sort is one of the most efficient comparison-based sorting algorithms.

Unlike Merge Sort, it **does not merge two sorted arrays**.

Instead, it selects a **Pivot**, places the pivot at its correct sorted position, and recursively sorts the left and right subarrays.

Because it works **in-place**, Quick Sort is usually faster than Merge Sort for arrays.

---

# 🎯 Idea

```
Choose Pivot

↓

Partition Array

↓

Pivot reaches its correct position

↓

Sort Left

↓

Sort Right
```

---

# 🌳 Visualization

```
                 8 4 7 9 3 10 5

                       │

                Pivot = 8

                       │

         5 4 7 3 |8| 10 9

             /            \

        5 4 7 3         10 9

         /    \         /   \

      4 3    7 5      10    9

         ↓

   Continue Recursively

         ↓

3 4 5 7 8 9 10
```

---

# 🔄 Algorithm

1. Choose a Pivot.
2. Partition the array.
3. Move all smaller elements to the left.
4. Move all larger elements to the right.
5. Pivot reaches its final sorted position.
6. Recursively sort both halves.

---

# 🧠 Partition Process

Example

```
Pivot = 8

8 4 7 9 3 10 5

↓

5 4 7 3 8 10 9

```

Notice

```
Left  < Pivot

Right > Pivot
```

The pivot never moves again.

---

# 🔥 Recursive Tree

```
QuickSort()

                    8

          /                   \

      5 4 7 3               10 9

      /     \               /   \

    4 3     7 5           10     9

    / \     / \

   .   .   .   .
```

---

# 📊 Complexity Analysis

| Case    | Time       |
| ------- | ---------- |
| Best    | O(n log n) |
| Average | O(n log n) |
| Worst   | O(n²)      |

---

# 💾 Space Complexity

| Case    | Space    |
| ------- | -------- |
| Average | O(log n) |
| Worst   | O(n)     |

---

# ⚖️ Merge Sort vs Quick Sort

| Feature        | Merge Sort       | Quick Sort       |
| -------------- | ---------------- | ---------------- |
| Technique      | Divide & Conquer | Divide & Conquer |
| Merge Required | ✅ Yes            | ❌ No             |
| Stable         | ✅ Yes            | ❌ No             |
| In-place       | ❌ No             | ✅ Yes            |
| Average        | O(n log n)       | O(n log n)       |
| Worst          | O(n log n)       | O(n²)            |
| Extra Space    | O(n)             | O(log n)         |

---

# 📂 Folder Structure

```
QuickSort/

│── QuickSort.cpp

└── README.md
```

---

# 💻 Code

```cpp
quickSort(arr,0,n-1);
```

The complete implementation is available in

```
QuickSort.cpp
```

---

# 🚀 Applications

* Standard Library Implementations
* Competitive Programming
* Large Arrays
* Internal Sorting
* Database Systems
* Searching Optimization

---

# ✅ Advantages

* Very Fast
* In-place
* Cache Friendly
* Average O(n log n)
* Small Constant Factor

---

# ❌ Disadvantages

* Worst Case O(n²)
* Not Stable
* Pivot Selection Matters

---

# 📌 Properties

| Property         | Value |
| ---------------- | ----- |
| Divide & Conquer | ✅     |
| Stable           | ❌     |
| In-place         | ✅     |
| Comparison Sort  | ✅     |
| Recursive        | ✅     |

---

# 🎓 Interview Questions

* Why is Quick Sort faster than Merge Sort?
* Why can Quick Sort become O(n²)?
* Why is it not stable?
* Difference between Hoare and Lomuto Partition?
* How does Random Pivot improve performance?

---

# 📚 Learning Outcome

After understanding Quick Sort, you should be able to:

* Choose an appropriate Pivot.
* Implement Hoare Partition.
* Implement Lomuto Partition.
* Analyze Time Complexity.
* Explain Best, Average, and Worst Cases.
* Compare Quick Sort with Merge Sort.

---

<div align="center">

## ⭐ If this project helped you, don't forget to Star the Repository!

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:4facfe,100:00f2fe&height=120&section=footer"/>

Made with ❤️ using C++

</div>
