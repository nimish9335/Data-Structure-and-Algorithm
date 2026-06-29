<div align="center">

# 🚀 Custom Comparator Sorting in C++

<img src="https://readme-typing-svg.herokuapp.com?font=Poppins&size=28&duration=3000&pause=1000&color=00C2FF&center=true&vCenter=true&width=700&lines=Custom+Sorting;Comparator+Functions;STL+Sort();Competitive+Programming"/>

![Language](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus)
![STL](https://img.shields.io/badge/STL-sort()-blue?style=for-the-badge)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-success?style=for-the-badge)

</div>

---

# 📖 What is Comparator?

A comparator is a function that tells `sort()` **which element should come first**.

Instead of using the default ascending order, we can define our own sorting rule.

```
sort(begin, end, comparator);
```

---

# 🧠 How Comparator Works

Comparator receives **two elements**.

```
bool comparator(a,b)
```

Return

```
true
```

means

```
Place a before b
```

Return

```
false
```

means

```
Place b before a
```

---

# 🔄 Flow

```
sort()

↓

Take Two Elements

↓

Comparator Called

↓

true ?

↓

Yes → Keep Order

No → Swap Order
```

---

# 📚 Types of Custom Sorting

## ✅ Ascending

```cpp
return a < b;
```

---

## ✅ Descending

```cpp
return a > b;
```

---

## ✅ Pair Sorting

```
First  → Ascending

Second → Descending
```

Example

```
(1,9)

(1,5)

(2,8)

(2,4)

(3,1)
```

---

## ✅ String Sorting

```
According to Length
```

```
A

Code

Rahul

Nimish

Programming
```

---

## ✅ Vector Sorting

Example

```
{1,2}

Sum = 3

{5,5}

Sum = 10
```

Sort according to sum.

---

# 🎯 STL Syntax

```cpp
sort(v.begin(), v.end(), comparator);
```

---

# 📊 Time Complexity

| Algorithm | Complexity |
|-----------|------------|
| sort() | O(n log n) |
| Comparator | O(1) (ideally) |

Overall

```
O(n log n)
```

---

# ⚠️ Important Rules

Comparator must satisfy

- Consistent ordering
- No ambiguity
- Should return bool

Never write

```cpp
return a<=b;
```

Correct

```cpp
return a<b;
```

---

# 🚀 Applications

- Pair Sorting
- String Sorting
- Student Ranking
- Employee Salary Sorting
- Custom Objects
- Competitive Programming
- LeetCode
- Codeforces

---

# 📁 Folder Structure

```
CustomComparator

│── CustomComparator.cpp

└── README.md
```

---

# 💡 Interview Questions

### Q1

Sort pair

```
First Ascending

Second Descending
```

---

### Q2

Sort students according to marks.

---

### Q3

Sort strings according to length.

---

### Q4

Sort intervals according to ending point.

---

### Q5

Sort objects according to salary.

---

# ⭐ STL Cheat Sheet

Ascending

```cpp
sort(v.begin(),v.end());
```

Descending

```cpp
sort(v.begin(),v.end(),greater<int>());
```

Custom

```cpp
sort(v.begin(),v.end(),comparator);
```

Lambda

```cpp
sort(v.begin(),v.end(),[](int a,int b){

    return a>b;

});
```

---

<div align="center">

## ⭐ If you found this useful, consider giving the repository a Star!

Made with ❤️ using C++

</div>