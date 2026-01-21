# Preprocessor & Macros in C++ - Complete Technical Guide

## 1. Introduction: The First Phase of Compilation

Before the compiler (e.g., GCC or Clang) even sees your C++ code, it passes through the **Preprocessor**. This is a simple text processing program that copies files, replaces text, and removes comments.
All directives start with `#`. The preprocessor understands nothing about types, classes, or scope – it only sees text.

---

## 2. The `#include` Directive

It tells the preprocessor: *"Find this file, copy its entire content, and paste it on this line."*

*   `#include <header>`: Searches in system paths (e.g., `/usr/include`). Used for standard libraries.
*   `#include "file.h"`: Searches in the current project directory first. Used for your own files.

⚠️ **Header Hell:** If file A includes B, and B includes C, all of them become part of one huge Translation Unit.

---

## 3. Macros (#define): Why Are They Dangerous?

Macros are "Search & Replace".

### 3.1. Macros for Constants
```cpp
#define PI 3.14159
```
**Problem:** `PI` has no type. It has no namespace. It pollutes the entire code.
**Solution:** Use `constexpr double PI = 3.14159;`.

### 3.2. Macro Functions
```cpp
#define SQUARE(x) x * x
```
**Classic Trap:**
`int res = SQUARE(1 + 2);` expands to `1 + 2 * 1 + 2`. The result is 5, not 9!
**Solution:** Always put parentheses around parameters: `#define SQUARE(x) ((x) * (x))`.
**Even Better Solution:** Use `template` or `inline` functions.

---

## 4. Conditional Compilation

This is the only way to maintain a single source code for multiple platforms (Windows, Linux, Mac).

```cpp
#ifdef _WIN32
    #include <windows.h>
    void clearScreen() { system("cls"); }
#elif defined(__linux__)
    #include <unistd.h>
    void clearScreen() { system("clear"); }
#else
    #error "Unsupported platform!"
#endif
```
This way you can compile different code depending on whether it is a `Debug` or `Release` build.

---

## 5. Include Guards vs `#pragma once`

If you include `header.h` twice (directly and indirectly), you will get a "Redefinition of class" error.

### 5.1. Include Guards (The Standard Way)
```cpp
#ifndef MY_HEADER_H
#define MY_HEADER_H

class MyClass { ... };

#endif
```
Works everywhere but requires a unique name for every file.

### 5.2. `#pragma once` (The Modern Way)
```cpp
#pragma once
class MyClass { ... };
```
Tells the compiler: "Include this file only once". It is faster and less code, but theoretically not part of the ISO standard (though all compilers support it).

---

## 6. Advanced Techniques: Stringification and Token Pasting

### 6.1. Stringification (`#`)
Turns the argument into a C-string.
```cpp
#define PRINT_VAR(x) std::cout << #x << " = " << x << std::endl;
int counter = 42;
PRINT_VAR(counter); // Outputs: counter = 42
```

### 6.2. Token Pasting (`##`)
Glues two tokens together to create a new variable/function name.
```cpp
#define GEN_FUNC(type) void func_##type(type x) { cout << x; }
GEN_FUNC(int); // Generates void func_int(int x) { ... }
```

### 6.3. X-Macros
A technique for generating code (e.g., Enum and array of strings simultaneously) by redefining a macro and including a list multiple times.

---

## 7. Professional Summary

1.  **Avoid `#define`** for constants and logic. Use `constexpr` and `templates`.
2.  **Use the preprocessor** only for:
    *   Including files.
    *   Header Guards.
    *   Conditional compilation (Platform-specific code).
    *   Debugging (`__FILE__`, `__LINE__`).
3.  **Isolation:** If you must use a macro, `#undef` it immediately after use so you don't break other people's code.

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*