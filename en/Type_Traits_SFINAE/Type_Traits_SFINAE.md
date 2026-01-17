# Type Traits and SFINAE in C++

## 1. Introduction

Metaprogramming tools to inspect and manipulate types at compile-time.

---

## 2. Type Traits

```cpp
#include <type_traits>
static_assert(std::is_integral<int>::value);
```

---

## 3. SFINAE

**Substitution Failure Is Not An Error.**
Allows enabling/disabling template overloads based on properties.

```cpp
template <typename T>
enable_if_t<is_integral_v<T>> func(T x) { /* ... */ }
```

---

## 4. Summary

Essential for library authors. Mostly replaced by **Concepts** in C++20.
