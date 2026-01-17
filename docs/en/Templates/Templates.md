# Templates in C++ - The Ultimate Guide

## 1. Concept: Generic Programming
Templates are the foundation of **Generic Programming** in C++. They allow us to write code once and have it work with any data type (int, double, strings, or custom classes).

---

## 2. Function Templates
Instead of writing separate `add(int, int)` and `add(double, double)` functions, we write a single template.

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}
```

---

## 3. Class Templates
STL containers like `std::vector<T>` are the best examples of class templates.

---

## 4. How It Works (Instantiation)
Templates are not compiled immediately. The compiler generates specific code for each type you use the template with. This process is called **Instantiation**.

⚠️ **WARNING:** Since the compiler must see the entire template definition to generate code, templates are usually written entirely in **header files (.h)**.

---

## 5. Template Specialization
Sometimes you want a specific type to behave differently. You can write a specialized version of the template for a specific type.

```cpp
template <>
class Box<bool> {
    // Optimized version for boolean values
};
```

---

## 6. Variadic Templates
Introduced in C++11, these allow templates to accept an unlimited number of arguments (e.g., `printf`-style functions).

---
*(This document is part of the "C++ Key Concepts" course)*