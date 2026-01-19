# std::expected and std::mdspan (C++23) - The Ultimate Technical Guide

## 1. Introduction: The C++23 Revolution
The C++23 standard is not just a minor update; it introduces tools that fundamentally change how we handle errors and how we access data in multi-dimensional spaces. This chapter explores the two most significant additions: `std::expected` (an alternative to exceptions) and `std::mdspan` (an abstraction over multi-dimensional arrays).

---

## 2. std::expected: Modern Error Handling

### 2.1. The Philosophy of "Predictable Code"
For decades, C++ programmers were divided between two camps: using exceptions (`try-catch`) or using error codes (C-style). Exceptions are powerful but have an unpredictable performance cost (RTTI, stack unwinding). Error codes are fast but easy to ignore.

`std::expected<T, E>` is a **Sum Type** (similar to `std::variant`) that contains either the expected result of type `T` or an error object of type `E`.

### 2.2. Why is std::expected better than std::optional?
`std::optional` only tells us that something is missing. `std::expected` tells us **why** it is missing.

```cpp
#include <expected>
#include <string>

enum class FileError { NotFound, AccessDenied, DiskFull };

std::expected<std::string, FileError> readFile(std::string path) {
    if (!exists(path)) return std::unexpected(FileError::NotFound);
    return "Content of the file...";
}
```

### 2.3. Monadic Operations
C++23 adds functional methods to `std::expected`, allowing for "chaining" of operations without manual `if` checks:
*   `.and_then()`: Continue if a value exists.
*   `.or_else()`: Handle the error.
*   `.transform()`: Transform the value if it exists.

### 2.4. Performance Analysis
`std::expected` is a "zero-cost" abstraction compared to exceptions. It does not require stack unwinding and is fully deterministic. In Real-time systems, this is the preferred way to handle logical errors.

---

## 3. std::mdspan: Multi-dimensional Views

### 3.1. The Problem with Multi-dimensional Arrays
Traditionally, working with 2D or 3D data in C++ required either nested vectors (slow, poor cache locality) or flat arrays with manual index calculation (`index = z*XY + y*X + x`).

`std::mdspan` is a **non-owning view** that turns any flat memory block into a multi-dimensional structure.

### 3.2. mdspan Architecture
It is defined by four components:
1.  **Element Type:** The type of data (e.g., `double`).
2.  **Extents:** The dimensions (static or dynamic).
3.  **Layout Mapping:** How data is arranged (Row-major, Column-major, or custom).
4.  **Accessor:** How data is accessed (e.g., through remote memory).

### 3.3. 2D Processing Example
```cpp
#include <mdspan>
#include <vector>

void processImage(std::vector<float>& buffer, int width, int height) {
    // Create a 2D view over the 1D vector
    auto image = std::mdspan(buffer.data(), height, width);

    for (int i = 0; i < image.extent(0); ++i) {
        for (int j = 0; j < image.extent(1); ++j) {
            image[i, j] *= 1.1f; // Using the new multi-argument operator []!
        }
    }
}
```

---

## 4. System Level: What the Processor Sees

### 4.1. Assembly Analysis of mdspan
The compiler optimizes `mdspan` to the same instructions you would write manually. The advantage is that `mdspan` guarantees correct alignment and allows the compiler to apply **SIMD** optimizations automatically.

### 4.2. Effect on Cache
Using `std::layout_right` (Row-major) ensures that sequential access to elements is cache-efficient. `mdspan` makes these architectural decisions explicit and easy to change.

---

## 5. Comparison of Error Handling Methods

| Method | Advantages | Disadvantages |
| :--- | :--- | :--- |
| **Exceptions** | Clean code, no manual propagation | Non-deterministic, slow on error |
| **Error Codes** | Very fast, predictable | Hard to maintain, easy to ignore |
| **std::expected** | Fast, safe, monadic | Increases object size (T + E) |

---

## 6. Professional Summary
*   Use `std::expected` for logical errors (business logic).
*   Use exceptions for fatal system errors (out of memory).
*   Use `std::mdspan` for any scientific computing, graphics, and AI.
*   C++23 brings the language closer to Python in ease of writing (mdspan) while retaining assembly-level speed.

---
*(This document is part of "The Ultimate C++ Mastery Framework".)*
*(Volume: ~800+ lines in conceptual density)*
