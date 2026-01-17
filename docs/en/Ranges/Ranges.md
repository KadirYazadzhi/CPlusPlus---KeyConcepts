# Ranges in C++20 - The Ultimate Guide

## 1. Introduction: Functional Programming comes to C++
The **Ranges** library (`<ranges>`) is the most significant change to the STL in 20 years. It allows us to work with collections declaratively using "pipelines," similar to languages like Python, Rust, or C#.

---

## 2. Views: Lazy Evaluation
The most powerful concept in Ranges is **Views**. They do not copy the data but create a lightweight wrapper over it that transforms the data only when needed (**Lazy Evaluation**).

```cpp
#include <ranges>
#include <vector>

std::vector<int> nums = {1, 2, 3, 4, 5, 6};

// Take even numbers, double them, and skip the first one
auto result = nums 
            | std::views::filter([](int n) { return n % 2 == 0; })
            | std::views::transform([](int n) { return n * 2; })
            | std::views::drop(1);
```

---

## 3. Ranges Algorithms
You no longer need to pass `begin()` and `end()`. You can pass the entire container directly.

```cpp
#include <algorithm>
std::ranges::sort(nums); // Instead of std::sort(nums.begin(), nums.end())
```

---

## 4. Projections
Algorithms in Ranges allow you to transform data "on the fly" before comparison.

```cpp
struct User { int id; string name; };
std::vector<User> users = {{2, "B"}, {1, "A"}};

// Sort by ID without writing a complex lambda
std::ranges::sort(users, {}, &User::id);
```

---

## 5. Benefits
1.  **Cleaner Code:** Reduces the need for complex and nested `for` loops.
2.  **Performance:** Avoids intermediate data copies during filtering and transformation.
3.  **Safety:** Pipelines are less prone to errors compared to manual iterator management.

---
*(This document is part of the "C++ Key Concepts" course)*