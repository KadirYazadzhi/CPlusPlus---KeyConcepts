# Lambda Expressions in C++ - The Ultimate Guide

## 1. Introduction: Anonymous Functions
Lambda expressions (introduced in C++11) are one of the most powerful tools in modern C++. They allow the definition of anonymous functions (functions without a name) directly at the point where they are used. This makes the code more compact and readable, especially when working with algorithms.

---

## 2. Lambda Expression Syntax

`[ capture ] ( params ) -> return_type { body }`

1.  **Capture Clause `[]`:** Defines which variables from the surrounding scope are accessible inside the lambda.
2.  **Parameter List `()`:** Function arguments.
3.  **Return Type `->`:** (Optional) The result type. Usually, the compiler deduces it automatically.
4.  **Body `{}`:** The function's code.

---

## 3. Capturing Variables

This is the most unique part of lambdas.
*   `[]` - nothing is captured.
*   `[=]` - captures all local variables **by value** (copy).
*   `[&]` - captures all local variables **by reference**.
*   `[x, &y]` - `x` by value, `y` by reference.

---

## 4. Mutable Lambdas
By default, variables captured by value are constant inside the lambda. If you want to modify them (their local copies), you must add the `mutable` keyword.

```cpp
int x = 10;
auto f = [x]() mutable { x++; return x; };
```

---

## 5. Usage with STL Algorithms
Lambdas are perfect as predicates in algorithms like `std::sort`, `std::find_if`, and `std::for_each`.

```cpp
std::vector<int> v = {1, 5, 2, 4, 3};
std::sort(v.begin(), v.end(), [](int a, int b) {
    return a > b; // Sorting in descending order
});
```

---

## 6. Generic Lambdas (C++14)
Since C++14, you can use `auto` for lambda parameters, creating a "templated" lambda.

```cpp
auto generic_add = [](auto a, auto b) { return a + b; };
```

---
*(This document is part of the "C++ Key Concepts" course)*