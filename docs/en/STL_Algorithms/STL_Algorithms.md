# STL Algorithms in C++ - Complete Technical Guide

## 1. Introduction: The Heart of the Standard Template Library

One of the core principles of C++ is: **"Don't write raw loops if there is an algorithm for it"**.
The `<algorithm>` library contains over 100 highly optimized, generic functions. They separate the **logic** (what we do) from the **structure** (what we do it on).

Why use them?
1.  **Efficiency:** Written by experts and often use SIMD instructions.
2.  **Correctness:** No off-by-one errors or invalid iterators.
3.  **Readability:** `std::sort` says more than 10 lines of `for` loops.

---

## 2. The Philosophy of Iterators

C++ algorithms don't "know" anything about containers (`vector`, `list`). They work on **Ranges**, defined by two iterators: `[first, last)`.
*   `first`: Points to the first element.
*   `last`: Points **after** the last element (Past-the-end).

**Iterator Categories:**
Algorithms require a specific level of access:
*   **Input Iterator:** `std::find` (one-pass read).
*   **Forward Iterator:** `std::replace` (one-pass write).
*   **Bidirectional Iterator:** `std::reverse` (needs `--it`).
*   **Random Access Iterator:** `std::sort` (needs `it + 5`).

---

## 3. Algorithm Categories (Deep Dive)

### 3.1. Non-modifying (Read-Only)
They only analyze data.
*   **`std::all_of` / `any_of` / `none_of`**: Predicate logic.
    ```cpp
    bool hasZero = std::any_of(v.begin(), v.end(), [](int i){ return i == 0; });
    ```
*   **`std::count` / `count_if`**: Counting.
*   **`std::find` / `find_if`**: Linear search.

### 3.2. Modifying (Write/Reorder)
Change content or order.
*   **`std::copy` / `copy_if`**: Copying.
*   **`std::transform`**: Map operation (applies a function to each element).
    ```cpp
    std::transform(v.begin(), v.end(), v.begin(), [](int x) { return x * x; });
    ```
*   **`std::remove_if`**: Moves "deleted" elements to the end (Erase-Remove Idiom).

### 3.3. Sorting and Binary Search
This is the "heavy artillery".
*   **`std::sort`**: O(N log N). Uses IntroSort (Mix of QuickSort, HeapSort, and InsertionSort).
*   **`std::partial_sort`**: Sorts only the first K elements (useful for Top 10).
*   **`std::binary_search`**: Returns `true/false`.
*   **`std::lower_bound`**: Returns an iterator to the first element `>= val`.

---

## 4. Parallel Algorithms (C++17)

With the advent of multi-core processors, C++17 added "Execution Policies" in `<execution>`.

```cpp
#include <execution>
#include <algorithm>

std::sort(std::execution::par, v.begin(), v.end()); // Parallel sort!
```

**Policies:**
1.  **`seq`**: Sequential (standard).
2.  **`par`**: Parallel (multi-threaded).
3.  **`par_unseq`**: Parallel and vectorized (SIMD). Requires very pure functions without side effects.

---

## 5. C++20 Ranges: The Future

In C++20, algorithms were reimagined. The `<ranges>` library allows composition (Pipe syntax) and lazy execution (Lazy Evaluation).

```cpp
// Old:
std::sort(v.begin(), v.end());

// C++20:
std::ranges::sort(v);

// Composition (Pipeline):
auto result = v | std::views::filter([](int i){ return i % 2 == 0; })
                | std::views::transform([](int i){ return i * i; });
```
This makes code declarative and readable like SQL or LINQ.

---

## 6. Professional Summary

1.  **Know the library:** Review the list of algorithms at least once (`cppreference.com`). Often there is a specialized algorithm for your need (e.g., `std::rotate`).
2.  **Lambdas:** Use them actively for custom predicates.
3.  **Binary Search:** If data is sorted, always use `std::lower_bound` instead of `std::find`. The difference is O(log N) vs O(N).
4.  **Erase-Remove:** Don't forget to call `v.erase()` after `std::remove()`, otherwise the vector size won't change.