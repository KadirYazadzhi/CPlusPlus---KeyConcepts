# Bit Manipulation in C++

## 1. Introduction

Low-level operations on individual bits using `&`, `|`, `^`, `~`, `<<`, `>>`.

---

## 2. Common Idioms

*   **Set bit:** `flags |= MASK`
*   **Check bit:** `if (flags & MASK)`
*   **Clear bit:** `flags &= ~MASK`

---

## 3. C++20 <bit>

Standardized bit operations.

```cpp
#include <bit>
int count = std::popcount(0b1101); // 3
```

---

## 4. Summary

Fast and memory-efficient. Vital for systems programming.
