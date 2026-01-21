# std::expected and std::mdspan (C++23) - Complete Technical Guide

## 1. Introduction: The C++23 Revolution

Standard C++23 is not just a minor update; it introduces tools that fundamentally change how we handle errors and how we access data in multidimensional spaces. This chapter explores the two most significant additions: `std::expected` (an alternative to exceptions) and `std::mdspan` (an abstraction over multidimensional arrays).

---

## 2. std::expected: Modern Error Handling

### 2.1. The Philosophy of "Predictable Code"
For decades, C++ programmers were divided between two camps: using exceptions (`try-catch`) or using error codes (C-style). Exceptions are powerful but have an unpredictable performance cost (RTTI, stack unwinding). Error codes are fast but easy to ignore.

`std::expected<T, E>` is a **Sum Type** (similar to `std::variant`) that contains either the expected result of type `T` or an error object of type `E`. It forces the programmer to check the result before using it.

### 2.2. Why is std::expected better than std::optional?
`std::optional` only tells us that something is missing. `std::expected` tells us **why** it is missing.

```cpp
#include <expected>
#include <string>
#include <fstream>

enum class FileError { NotFound, AccessDenied, DiskFull };

std::expected<std::string, FileError> readFile(std::string path) {
    if (!std::filesystem::exists(path)) 
        return std::unexpected(FileError::NotFound); // Returning error
    
    // ... reading ...
    return "Content of the file..."; // Returning success
}

void process() {
    auto result = readFile("config.json");
    if (result) {
        std::cout << *result; // Access to T
    } else {
        std::cerr << "Error code: " << (int)result.error(); // Access to E
    }
}
```

### 2.3. Monadic Operations
C++23 adds functional methods to `std::expected`, allowing "chaining" of operations without tedious `if` checks (Railway Oriented Programming):

*   **`.and_then(func)`**: Continue with the next step only if the current one is successful.
*   **`.or_else(func)`**: Handle the error or transform it.
*   **`.transform(func)`**: Transform the successful value (e.g., from `string` to `int`), but keep the error if any.

```cpp
auto finalResult = readFile("data.txt")
    .and_then(parseJson)       // Only if file is read
    .and_then(extractUserId)   // Only if JSON is valid
    .or_else(logError);        // If anything breaks along the chain
```

### 2.4. Performance Analysis
`std::expected` is a "zero-cost" abstraction compared to exceptions. It does not require Stack Unwinding and is completely deterministic.
*   **Memory:** Occupies `max(sizeof(T), sizeof(E)) + bool`.
*   **Speed:** Returning `std::expected` is as fast as returning a struct by value. RVO (Return Value Optimization) works perfectly.
*   **Real-time:** In real-time systems (game engines, embedded) where exceptions are forbidden, this is the new standard.

---

## 3. std::mdspan: Multidimensional Views

### 3.1. The Problem with Multidimensional Arrays
Traditionally, working with 2D or 3D data in C++ required either nested vectors (`vector<vector<T>>`), which is a cache nightmare, or flat arrays with manual index calculation (`index = z*XY + y*X + x`).

`std::mdspan` is a **non-owning view** that turns any flat memory block into a multidimensional structure.

### 3.2. mdspan Architecture
It is defined by four components:
1.  **Element Type:** Data type (e.g., `double`).
2.  **Extents:** Dimensions sizes. Can be static (compile-time) or dynamic.
3.  **Layout Mapping:** How data is ordered:
    *   `std::layout_right` (C-style / Row-major): The last dimension is contiguous.
    *   `std::layout_left` (Fortran-style / Column-major): The first dimension is contiguous.
4.  **Accessor:** How data is accessed (e.g., via SIMD vectorization or GPU memory).

### 3.3. 2D Processing Example
```cpp
#include <mdspan>
#include <vector>

void processImage(std::vector<float>& buffer, int width, int height) {
    // Create a 2D view over the 1D vector
    // std::dextents<int, 2> means 2 dynamic dimensions
    auto image = std::mdspan(buffer.data(), height, width);

    for (int i = 0; i < image.extent(0); ++i) { // Rows
        for (int j = 0; j < image.extent(1); ++j) { // Columns
            // New operator [] accepts multiple arguments!
            image[i, j] *= 1.1f; 
        }
    }
}
```

### 3.4. Slicing and Submdspan
One of the most powerful features is `std::submdspan`. It allows taking "slices" of data without copying.
You can take a sub-matrix, a specific row from a 3D tensor, or a diagonal in **O(1)** time.

```cpp
auto subregion = std::submdspan(image, std::pair{10, 20}, std::pair{10, 20});
// subregion is a new, smaller mdspan pointing to the same memory.
```

---

## 4. System Level: What Does the Processor See?

### 4.1. Assembly Analysis of mdspan
The compiler understands the math of `mdspan`. When you write `image[i, j]`, it generates address arithmetic instructions (`base + i*stride + j`) identical to handwritten C code.
The advantage is that `mdspan` allows the compiler to apply **SIMD** optimizations automatically because it knows the memory layout (if you use the correct Layout).

### 4.2. Effect on Cache
Using `std::layout_right` (Row-major) when traversing by rows guarantees **Spatial Locality**. The processor loads an entire cache line, and the next elements are already there. Nested vectors can never achieve this.

---

## 5. Comparison of Error Handling Methods

| Method | Pros | Cons |
| :--- | :--- | :--- |
| **Exceptions** | Clean code, not passed manually | Non-deterministic, slow on error, requires RTTI |
| **Error Codes** | Very fast, predictable | Hard to maintain, easy to ignore, no context |
| **std::expected** | Fast, safe, monadic | Increases return object size |

---

## 6. Professional Summary

1.  **std::expected:** Use it for logical errors (File Not Found, Invalid Input) that are part of the normal workflow.
2.  **Exceptions:** Save them for truly "exceptional" events (Out of Memory, Hardware Failure) that cannot be handled locally.
3.  **std::mdspan:** The standard for scientific computing, graphics, AI tensors, and image processing. Never write `vec[y * w + x]` manually again.
4.  C++23 makes the language closer to Python/NumPy in ease of writing, but keeps the speed of assembly.

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*