# STL Algorithms in C++ - The Ultimate Guide

## 1. Introduction: The Power of the Standard Template Library
STL algorithms are the heart of C++. They are highly optimized, well-tested, and flexible functions that operate on data ranges defined by iterators.

**Golden Rule:** Before writing a manual `for` loop, check if a ready-to-use algorithm exists in the `<algorithm>` header.

---

## 2. Algorithm Categories

### 2.1. Non-modifying (Querying)
These only read the data without changing it.
*   **find / find_if:** Searches for an element.
*   **count / count_if:** Counts occurrences.
*   **all_of / any_of / none_of:** Checks conditions for the entire range.

### 2.2. Modifying (Transforming)
These change the data or their order.
*   **sort / stable_sort:** Sorting.
*   **transform:** Applies a function to each element and stores the result.
*   **replace / replace_if:** Replacement.
*   **remove / unique:** Element removal (often used with the container's `erase` method).

---

## 3. Iterators: The Bridge Between Data and Logic
Algorithms do not interact with containers directly. They work with iterators (`begin()` and `end()`). This allows the same algorithm (e.g., `find`) to work equally well with a `vector`, `list`, or `deque`.

---

## 4. Predicates and Lambdas
Most algorithms accept a "predicate" – a function or lambda that defines the search or filtering logic.

```cpp
auto it = std::find_if(v.begin(), v.end(), [](int x) {
    return x > 100;
});
```

---

## 5. Performance
STL algorithms are optimized to the extreme by compiler developers. `std::sort` uses hybrid methods (IntroSort) that are faster than almost any manual implementation.

---

## 6. C++20 Ranges
In the new C++20 standard, algorithms no longer require `begin()` and `end()`. You can pass the entire container:
`std::ranges::sort(v);`

---
*(This document is part of the "C++ Key Concepts" course)*