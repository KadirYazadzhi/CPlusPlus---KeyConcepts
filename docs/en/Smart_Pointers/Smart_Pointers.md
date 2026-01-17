# Smart Pointers in C++ - The Ultimate Guide

## 1. The Problem with Raw Pointers
In traditional C++ (before C++11), memory management via `new` and `delete` was entirely the programmer's responsibility. This often leads to:
*   **Memory Leaks:** Forgetting to call `delete`.
*   **Dangling Pointers:** Using a pointer after the memory it points to has been freed.
*   **Double Free:** Attempting to free the same memory twice.

Smart pointers (introduced in C++11) solve these issues through the **RAII (Resource Acquisition Is Initialization)** idiom. They automatically release memory when they go out of scope.

---

## 2. std::unique_ptr (Exclusive Ownership)
This is the most commonly used smart pointer. It ensures that only one pointer owns the object at any given time.

### 2.1. Characteristics
*   **Non-copyable:** Ownership can only be transferred using `std::move`.
*   **Zero Overhead:** It has the same memory footprint as a raw pointer.

```cpp
#include <memory>
auto ptr1 = std::make_unique<int>(10);
// std::unique_ptr<int> ptr2 = ptr1; // ERROR!
std::unique_ptr<int> ptr2 = std::move(ptr1); // OK: Ownership transferred
```

---

## 3. std::shared_ptr (Shared Ownership)
Allows multiple pointers to own the same object.

### 3.1. How It Works
It uses **Reference Counting**. The object is deleted only when the last `shared_ptr` pointing to it is destroyed.

### 3.2. make_shared vs. new
Always prefer `std::make_shared`. It performs a single allocation for both the object and its control block, making it faster and more memory-efficient.

---

## 4. std::weak_ptr (The Observer)
A weak pointer points to an object owned by a `shared_ptr` but does not increase the reference count.

### 4.1. Circular Dependencies
The primary purpose of `weak_ptr` is to prevent "deadlocks" (Circular Dependencies), where two objects hold `shared_ptr`s to each other and are never deleted.

---

## 5. When to Use What?
1.  **unique_ptr:** By default. Use whenever sharing is not required.
2.  **shared_ptr:** When program logic requires sharing objects (e.g., in graphs or caches).
3.  **weak_ptr:** To break cycles or for temporary observation of objects.

---
*(This document is part of the "C++ Key Concepts" course)*