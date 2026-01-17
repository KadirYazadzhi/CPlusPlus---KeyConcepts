# Preprocessor and Macros in C++ - The Ultimate Guide

## 1. Introduction: The First Step of Compilation
The preprocessor is a separate tool that processes the source code before the actual compiler. It works through text substitution. All preprocessor commands begin with the `#` symbol.

---

## 2. The #include Directive
Copies the content of one file into another.
*   `<header>` - searches in system directories.
*   `"header.h"` - searches first in the current directory.

---

## 3. Macros (#define)
Macros are simple textual replacements.
```cpp
#define PI 3.14159
#define SQUARE(x) ((x) * (x))
```
⚠️ **Danger:** Macros lack Type Safety and do not respect Scope. In modern C++, always prefer `constexpr` and `inline` templates.

---

## 4. Conditional Compilation (#ifdef, #if)
Allows the inclusion or exclusion of parts of the code based on conditions (e.g., different operating systems or program versions).

```cpp
#ifdef _WIN32
    // Windows-specific code
#else
    // Linux/macOS-specific code
#endif
```

---

## 5. Include Guards and #pragma once
To prevent a header file from being included multiple times, Include Guards or the modern `#pragma once` directive are used.

---

## 6. Built-in Macros
*   `__FILE__`: The name of the current file.
*   `__LINE__`: The current line number.
*   `__func__`: The name of the current function.
These are useful for error logging and debugging.

---
*(This document is part of the "C++ Key Concepts" course)*