# Modules in C++20

## 1. Introduction

C++20 Modules are a modern replacement for the legacy `#include` system. They address slow compilation times and macro isolation issues.

---

## 2. Basic Syntax

**math.cppm (Module Interface)**
```cpp
export module math;
export int add(int a, int b) { return a + b; }
```

**main.cpp (Usage)**
```cpp
import math;
int main() { return add(2, 2); }
```

---

## 3. Benefits

*   **Speed:** Modules are compiled once into a binary format.
*   **Isolation:** Macros defined in a module don't leak out.
*   **No Header Guards:** No more `#ifndef HEADER_H`.

---

## 4. Summary

The biggest change to C++ physical structure. Use `export` for public API and `import` to use it.
