# Ranges in C++20 - Complete Technical Guide

## 1. Introduction: The Pipeline Paradigm

The **Ranges** library (`<ranges>`) is the biggest evolution in the STL since its inception in the 90s. It fundamentally changes the way we work with collections by moving from an imperative style (how to traverse) to a **declarative style** (what to do).

**The Core Idea:** Instead of manually manipulating iterators, we create "pipelines" of operations that transform data. This makes C++ look like a high-level language (Python, Rust, C# LINQ).

---

## 2. Views: The Magic of Lazy Evaluation

⚠️ **ENGINEERING VIEW:** Views are lightweight objects that **do not own data**. They are simply "smart windows" into existing collections. Copying a View is O(1) and cheap.

### 2.1. Lazy Evaluation
Operations in Ranges are lazy.
```cpp
std::vector<int> nums = {1, 2, 3, 4, 5};
auto heavy_calc = nums 
                | std::views::filter(is_even)      // 1. Not executed immediately
                | std::views::transform(super_heavy_func); // 2. Not executed immediately

// The real calculation starts ONLY HERE:
int first_result = *heavy_calc.begin(); 
```
This saves CPU time if you don't use all results (e.g., you only look for the first one).

---

## 3. Composition via Pipeline Operator (`|`)

C++20 overloads the bitwise OR operator (`|`) to allow Unix-style composition.

```cpp
#include <ranges>
#include <vector>
#include <iostream>

namespace rv = std::ranges::views; // Alias for brevity

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};

    auto result = numbers 
                | rv::filter([](int n){ return n % 2 == 0; }) // Take evens: 2, 4, 6
                | rv::transform([](int n){ return n * n; })   // Square them: 4, 16, 36
                | rv::reverse                                 // Reverse: 36, 16, 4
                | rv::take(2);                                // Take first 2: 36, 16

    for (int n : result) std::cout << n << " ";
}
```

---

## 4. Algorithms with Ranges (std::ranges)

Old algorithms required `begin(), end()`. The new ones (`std::ranges::`) work directly with the container.

### 4.1. Dangling Iterators Protection
Old algorithms didn't know about object lifetimes.
```cpp
auto it = std::find(getTemporaryVector().begin(), ...); // ERROR: Returns iterator to a dead vector
```
New Ranges algorithms detect this and return a special iterator `std::ranges::dangling`, which cannot be dereferenced, protecting you from bugs.

---

## 5. Projections: Goodbye to Complex Lambdas

Ranges allow you to pass a "projection" of the data – a function that is applied to the element *before* it is compared.

**Old Way:**
```cpp
std::sort(people.begin(), people.end(), [](const Person& a, const Person& b) {
    return a.name < b.name;
});
```

**New Way (with Projection):**
```cpp
// 1. Container, 2. Comparator (default {}), 3. Projection
std::ranges::sort(people, {}, &Person::name); 
```
This is extremely elegant for arrays of structures.

---

## 6. Creating Custom Views

You can write your own View by inheriting from `std::ranges::view_interface`. You just need to define `begin()` and `end()`.

```cpp
template<std::ranges::input_range R>
class AddOneView : public std::ranges::view_interface<AddOneView<R>> {
    // ... implementation of iterator that adds +1 on *it ...
};
```

---

## 7. Professional Summary

1.  **Safety:** Ranges algorithms (Constrained Algorithms) use Concepts to give meaningful errors if you pass the wrong type.
2.  **Performance:** Ranges are often **faster** than hand-written loops because they avoid creating intermediate buffers (`std::vector` after each step).
3.  **Limitations:** Not all STL containers support all Ranges operations. For example, `std::list` is not a Random Access Range, so it cannot be sorted with `ranges::sort`.
4.  **Infinite Sequences:** Ranges allow working with infinite streams (e.g., a number generator), as long as you use `views::take(N)`.

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*