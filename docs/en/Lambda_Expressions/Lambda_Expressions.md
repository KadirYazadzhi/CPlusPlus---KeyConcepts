# Lambda Expressions in C++ - The Ultimate Technical Guide

## 1. Introduction: Functions without Names
Lambda expressions (introduced in C++11) are one of the most impactful tools in modern C++. They allow the definition of anonymous function objects (closures) directly at the point where they are used. This changed the language's paradigm toward more functional programming.

---

## 2. Anatomy of a Lambda Expression

The syntax consists of three parts:
`[ capture ] ( params ) -> return_type { body }`

### 2.1. Capture Clause `[]`
This is the most unique part. It allows the lambda to "see" variables from the surrounding scope.
*   `[]` - Nothing is captured.
*   `[=]` - All local variables are captured **by value** (copy).
*   `[&]` - All local variables are captured **by reference**.
*   `[this]` - Allows access to class members inside one of its methods.

### 2.2. Mutable Lambdas
By default, variables captured by value are `const` inside the lambda. To modify them (e.g., a local counter), you must add the `mutable` keyword.

---

## 3. How It Works: Compiler Implementation

When you write a lambda, the compiler secretly creates a unique, unnamed class (**Closure Type**) with a predefined `operator()`.
*   Captured variables become member variables of this hidden class.
*   The lambda you see is simply an object of this hidden class.

---

## 4. Generic Lambdas (C++14) and constexpr (C++17)

Since C++14, we can use `auto` for parameters, making the lambda templated:
```cpp
auto sum = [](auto a, auto b) { return a + b; };
```
Since C++17, lambdas can be `constexpr`, allowing them to be used for compile-time calculations.

---

## 5. Lambdas and STL Algorithms
This is the natural habitat of lambdas. They replace the need to write dozens of small comparison functions or structures.

```cpp
std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
    return a.score > b.score; 
});
```

---

## 6. Professional Hazards: Dangling References
If you capture a variable by reference `[&]` and return the lambda from a function, the reference will point to already destroyed memory.
**Golden Rule:** Always capture by value `[=]` if the lambda will live longer than the current scope.

---

## 7. Professional Summary
*   Use lambdas for **predicates** and **callbacks**.
*   Use `auto` parameters for maximum flexibility.
*   Beware of capture-by-reference in asynchronous code.

---
*Documentation prepared for the "C++ Key Concepts" project.*
*Version: 2.0 (Full Detail)*
