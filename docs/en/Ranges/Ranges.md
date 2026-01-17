# Ranges in C++20

## 1. Introduction

The Ranges library provides a functional way to handle collections. It allows composing algorithms using the pipe (`|`) operator.

---

## 2. Views and Pipelines

Views are lazy (they don't copy data).

```cpp
#include <ranges>
#include <vector>

std::vector<int> v = {1, 2, 3, 4, 5};
auto result = v | std::views::filter([](int n){ return n % 2 == 0; })
                | std::views::transform([](int n){ return n * 2; });
```

---

## 3. Ranges Algorithms

```cpp
std::ranges::sort(v); // Instead of std::sort(v.begin(), v.end())
```

---

## 4. Summary

Makes code more readable, functional, and efficient by avoiding intermediate copies.
