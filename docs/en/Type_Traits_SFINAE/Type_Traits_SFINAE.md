# Type Traits and SFINAE in C++ - The Ultimate Guide

## 1. Introduction: Compiler Introspection
Metaprogramming in C++ allows us to write code that makes decisions at compile-time. `Type Traits` and `SFINAE` are the tools that make this possible.

---

## 2. Type Traits: Type Inspection
The `<type_traits>` library allows us to ask the compiler questions about a given type:
*   `std::is_integral<T>`: Is it an integer?
*   `std::is_pointer<T>`: Is it a pointer?
*   `std::is_const<T>`: Is it constant?

These are used alongside `if constexpr` (C++17) to optimize algorithms.

---

## 3. SFINAE: Substitution Failure Is Not An Error
This rule states: "If an invalid type is formed during template substitution, do not issue an error; simply ignore that template."

This allows for the creation of **enable_if** – a mechanism to enable/disable functions based on type properties.

---

## 4. C++20: The Modern Path
In C++20, `SFINAE` is largely replaced by **Concepts** (Topic 34), which are much more readable and faster to compile. However, understanding SFINAE remains important for maintaining legacy codebases.

---
*(This document is part of the "C++ Key Concepts" course)*