# Functions in C++ - The Ultimate Guide

## 1. Function Architecture
A function is a self-contained block of code that performs a specific logical task. In C++, functions are the primary tool for achieving code modularity and reusability.

### 1.1. Declaration vs. Definition
*   **Declaration (Prototype):** Informs the compiler about the function name, return type, and parameters. Typically found in header files (.h).
*   **Definition:** Contains the actual implementation code.

---

## 2. Parameter Passing Mechanisms

This is one of the most performance-critical aspects of C++.

### 2.1. Pass by Value
A local copy of the object is created. Suitable only for small types (int, double, char).
```cpp
void swap(int a, int b); // Copies are swapped, originals remain unchanged
```

### 2.2. Pass by Reference
Uses `&`. The function works directly with the original object.
```cpp
void increment(int& val) { val++; }
```

### 2.3. Pass by Const Reference
**The Golden Rule of C++:** Pass large objects (string, vector, classes) by `const T&`. It avoids copying and ensures safety.
```cpp
void printData(const std::vector<int>& data); 
```

### 2.4. Pass by Pointer
Used when the argument is optional (can be `nullptr`).

---

## 3. Advanced Concepts

### 3.1. Function Overloading
You can have functions with the same name but different parameters. The compiler distinguishes them via a process called **Name Mangling**.

### 3.2. Default Arguments
```cpp
void log(string msg, int level = 1); 
// Can be called as log("Hi") or log("Hi", 2)
```

### 3.3. Inline Functions
The `inline` keyword is a request to the compiler to replace the function call with its code to save stack overhead.

---

## 4. Lambda Expressions - C++11/14/17/20

Lambdas are anonymous function objects. They changed the way we write modern C++.

### 4.1. Capture Clause Syntax
*   `[]` - nothing is captured.
*   `[=]` - capture all local variables by value.
*   `[&]` - capture all by reference.
*   `[x, &y]` - x by value, y by reference.

```cpp
auto multiplier = [factor = 10](int val) { return val * factor; };
```

---

## 5. Function Objects and std::function

The `<functional>` library allows us to treat functions as objects.

```cpp
#include <functional>
std::function<int(int, int)> op;
op = [](int a, int b) { return a + b; };
```

---

## 6. Recursion and the Call Stack

Every function call creates a **Stack Frame** in memory, containing:
1.  Local variables.
2.  Parameters.
3.  Return address.

⚠️ **Tail Call Optimization (TCO):** Some compilers can optimize recursion into a loop if the recursive call is the very last operation.

---

## 7. Best Practices

1.  **Single Responsibility Principle:** A function should do exactly one thing.
2.  **Length:** If a function exceeds 50-100 lines, it should likely be split.
3.  **Const Correctness:** Mark methods that don't modify the object as `const`.
4.  **Noexcept:** Use `noexcept` for functions guaranteed not to throw (improves performance).

---
*(This document is part of the "C++ Key Concepts" course)*