# Concepts in C++20 - The Ultimate Guide

## 1. Introduction: The End of Cryptic Errors
Before C++20, templates were "blind" – they accepted any data type and exploded with hundreds of lines of unreadable errors if the type didn't support the required operations. **Concepts** allow us to impose formal requirements on template parameters.

---

## 2. Syntax and the `requires` Clause
We can explicitly state that an `add` function works only for integers:

```cpp
#include <concepts>

template <typename T>
requires std::integral<T>
T add(T a, T b) {
    return a + b;
}
```

If you try to pass a `std::string`, the compiler stops immediately and says: "Type string does not satisfy the integral concept".

---

## 3. Defining Custom Concepts
You can define your own requirements using the `concept` keyword.

```cpp
template <typename T>
concept Printable = requires(T v) {
    std::cout << v; // Checks if the type supports operator <<
};

void log(Printable auto value) {
    std::cout << value << std::endl;
}
```

---

## 4. Advantages of Concepts
1.  **Faster Compilation:** The compiler doesn't attempt to expand complex templates if the type is incorrect.
2.  **Code Documentation:** It is immediately obvious what is expected from the user of your template.
3.  **Overloading:** You can have different versions of a function for different concepts.

---

## 5. Standard Concepts in <concepts>
*   `std::integral`, `std::floating_point`
*   `std::movable`, `std::copyable`
*   `std::derived_from<Derived, Base>`
*   `std::same_as<T, U>`

---
*(This document is part of the "C++ Key Concepts" course)*