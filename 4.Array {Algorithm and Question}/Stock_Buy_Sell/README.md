# Best Time to Buy and Sell Stock

## Question

Given an array `prices` where `prices[i]` is the price of a given stock on day `i`, find the maximum profit that can be achieved by buying the stock on one day and selling it on a later day. Only one transaction is allowed (i.e., you must buy before you sell, and you can only buy once and sell once). If no profit is possible, return `0`.

### Test Case 1
**Input:**
```
6
7 1 5 3 6 4
```
**Output:**
```
5
```
*(Buy on day 2 at price 1, sell on day 5 at price 6, profit = 5)*

### Test Case 2
**Input:**
```
5
7 6 4 3 1
```
**Output:**
```
0
```
*(Prices only decline, so no profit is possible; buying and never selling gives profit 0)*

## Solution Explanation

This problem and its solution are explained in Striver's video that kicks off his series on **Dynamic Programming on Stocks**, a set of six commonly asked interview problems. The instructor stresses that mastering these problems, especially their space-optimized versions, is important for interviews.

### Problem Statement
Given an array of stock prices across several days, the goal is to maximize profit by buying the stock on one day and selling it on a later day, with only one transaction allowed.

### Intuition
To maximize profit when selling on a particular day, the stock must have been bought at the lowest possible price among all the preceding days. In other words, for every day considered as a potential "sell day," the best possible "buy day" is whichever earlier day had the minimum price.

### Algorithm
The approach involves a single pass through the array while keeping track of the minimum price seen so far:
- Maintain a variable `minPrice` that stores the lowest price encountered up to (and including) the current day.
- For each day, calculate the potential profit as the difference between the current day's price and `minPrice`.
- Keep track of the maximum profit seen across all days.
- Update `minPrice` as you move forward, since a new lower price might appear on a later day, opening up better buying opportunities for future days.

By the end of the traversal, the maximum profit recorded is the answer.

### Complexity Analysis
- **Time Complexity:** `O(n)`, since the array is traversed only once.
- **Space Complexity:** `O(1)`, since only a couple of variables (`minPrice` and `maxProfit`) are used, with no extra data structures.
