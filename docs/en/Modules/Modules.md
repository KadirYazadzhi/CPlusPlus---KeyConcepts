# Modules in C++20 - Complete Technical Guide

## 1. Introduction: The End of a 40-Year Legacy

Since its inception in the 70s, C++ (inheriting from C) has relied on `#include` – a mechanism for **pure textual copying**.
When you write `#include <vector>`, the preprocessor copies 10,000+ lines of code into your file. If you have 100 files and each includes the vector, the compiler parses these 10,000 lines 100 times. This is O(N*M) complexity of compilation.

**Modules** are the biggest change in the physical architecture of C++. They replace textual insertion with logical loading of precompiled binary interfaces.

---

## 2. Anatomy of a Module

Modules introduce new file extensions (`.ixx` for MSVC, `.cppm` for Clang/GCC) and new keywords.

### 2.1. Primary Module Interface Unit
This is the file that defines what the world "sees".

```cpp
// math.cppm
export module math; // 1. Declaration: "I am module math"

// 2. Exporting a function (visible to importers)
export int add(int a, int b) {
    return a + b;
}

// 3. Hidden function (invisible from outside)
// No need for "static" or anonymous namespaces!
int helper() { return 42; } 

export struct Point { int x, y; }; // Exporting a type
```

### 2.2. Consumption (Client Code)
```cpp
// main.cpp
import math;      // Loads the binary interface (BMI)
import <iostream>; // The standard library also becomes modular (C++23)

int main() {
    std::cout << add(1, 2); 
    // helper(); // ERROR: helper is not exported
}
```

---

## 3. Module Partitioning

For large libraries, one file is not enough. Modules can be divided into "partitions" starting with `:`.

```cpp
// math_geometry.cppm
export module math:geometry; // Partition "geometry" of module "math"
export struct Shape { /*...*/ };

// math_algebra.cppm
export module math:algebra;
export int calc() { /*...*/ }

// math.cppm (Primary Interface)
export module math;
export import :geometry; // Re-exports partitions
export import :algebra;
```
The user writes only `import math;` and gets everything.

---

## 4. Global and Private Module Fragments

Sometimes you need "old" headers inside a module (e.g., `<windows.h>`). They must not leak outside.

```cpp
module; // Global module fragment
#include <cstdio> // Textual inclusion (only allowed here)

export module mylog;

export void log(const char* msg) {
    printf("%s", msg); // printf is visible here, but not to the one who does 'import mylog'
}
```

---

## 5. Benefits for Large Systems (The Why)

### 5.1. Compilation Speed (Performance)
When a module is compiled, it creates a **BMI (Binary Module Interface)** file (`.pcm` / `.ifc`).
*   Each `import` simply loads this binary file (like Deserialize).
*   Parsing happens **only once**.
*   In real projects (like LLVM or Qt), this reduces build time by **40-80%**.

### 5.2. Isolation (Macro Hygiene)
Macros `#define` defined inside a module **DO NOT leak** outside.
End of conflicts where `windows.h` defines `min/max` and breaks `std::min`.

### 5.3. No Header Guards
No need for `#pragma once` or `#ifndef`. The module system guarantees single loading.

---

## 6. Professional Summary

1.  **Transition:** You don't have to rewrite everything. You can mix `#include` and `import` in one project.
2.  **Build Systems:** CMake supports modules experimentally since version 3.26+. Requires some setup (`FILE_SET CXX_MODULES`).
3.  **The Future:** `import std;` (C++23) is the ultimate goal – a single line that gives access to the entire STL, compiled in fractions of a second.
4.  **ODR Rule:** Modules do not save you from the One Definition Rule, but they make it much harder to violate accidentally.

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*