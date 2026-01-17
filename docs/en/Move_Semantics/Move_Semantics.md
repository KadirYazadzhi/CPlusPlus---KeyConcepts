# Move Semantics in C++ - The Ultimate Guide

## 1. Introduction: Why Move is Better Than Copy
Before C++11, the only way to transfer data from one object to another was via copying. For large objects (like vectors with millions of elements), this requires allocating new memory and copying every byte, which is very slow.

**Move Semantics** allows us to "steal" resources from a temporary object instead of copying them.

---

## 2. L-values and R-values

To understand moving, you must understand value categories:
*   **L-value:** An object that has a name and a memory address (e.g., a variable).
*   **R-value:** A temporary value that has no name and is about to be destroyed (e.g., the result of `5 + 10`).

---

## 3. R-value References (&&)
C++11 introduced a new type of reference denoted by `&&`. It can only bind to temporary objects.

```cpp
void process(int& x);  // L-value reference
void process(int&& x); // R-value reference - allows moving
```

---

## 4. std::move()
The `std::move` function does not physically move anything. It simply casts an L-value object into an R-value, telling the compiler: "You can take the resources of this object; I won't use it anymore."

---

## 5. Move Constructor and Move Assignment
To support moving, your class must implement:
1.  **Move Constructor:** Takes `MyClass&& other`, copies the pointers, and nulls out the originals.
2.  **Move Assignment:** An `=` operator that does the same.

⚠️ **IMPORTANT:** Always mark these methods as `noexcept` to allow STL containers to use them optimally.

---

## 6. Rule of Five
If you define a Move constructor, you must define (or explicitly request from the compiler) the other 4 special member functions:
*   Destructor
*   Copy Constructor
*   Copy Assignment
*   Move Constructor
*   Move Assignment

---
*(This document is part of the "C++ Key Concepts" course)*