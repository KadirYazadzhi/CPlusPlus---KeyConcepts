# Classes & Objects in C++ - Complete Technical Guide

## 1. Introduction: The Modeling Paradigm

Object-Oriented Programming (OOP) in C++ is a tool for managing complexity. A class is a **user-defined type** that encapsulates data (state) and functions (behavior) into a single logical unit. An object is the concrete physical instance of this type in memory.

Unlike C (where you only have `struct` with data), C++ classes enforce **invariants** – rules ensuring that data is always valid (e.g., "age is never negative").

---

## 2. Class Anatomy and Memory

### 2.1. Memory Layout
One of the most important concepts for system programmers is exactly how an object looks in RAM.
When you create an object, it occupies memory equal to the sum of the sizes of its **non-static member variables**, plus **Padding**.

⚠️ **IMPORTANT:** Member functions (methods) do **NOT** occupy space inside the object! They exist only once in the program's code section (.text segment). All objects of a class share the same functions.

### 2.2. Padding and Alignment
Processors do not read memory byte by byte, but in "words" (4 or 8 bytes). For fast access, the compiler inserts "holes" (padding).

```cpp
class BadAlignment {
    char a;   // 1 byte
    // --- 3 bytes hidden padding ---
    int b;    // 4 bytes
    char c;   // 1 byte
    // --- 3 bytes hidden padding ---
}; 
// sizeof(BadAlignment) = 12 bytes!

class GoodAlignment {
    int b;    // 4 bytes
    char a;   // 1 byte
    char c;   // 1 byte
    // --- 2 bytes hidden padding ---
};
// sizeof(GoodAlignment) = 8 bytes!
```
**Tip:** Order variables from largest to smallest to minimize memory waste.

---

## 3. Encapsulation and Access Levels

1.  **private (default for `class`):** The heart of encapsulation. Only methods of the class itself have access. This allows you to change the internal implementation without breaking user code.
2.  **protected:** Accessible to the class and its inheritors.
3.  **public (default for `struct`):** The interface through which the world communicates with the object.

**Pro Tip:** Always make data `private`. Use `const` methods for reading (Getters) and methods for writing (Setters) that perform validation.

---

## 4. Lifecycle: The Rule of Five

In modern C++ (C++11 and up), resource management (memory, files, sockets) requires defining 5 key methods:

1.  **Destructor (`~Class()`):** Releases resources. The basis of RAII.
2.  **Copy Constructor:** How is the object copied? (`Class(const Class&)`)
3.  **Copy Assignment Operator:** How is a value assigned? (`operator=(const Class&)`)
4.  **Move Constructor:** How is the object moved efficiently? (`Class(Class&&)`)
5.  **Move Assignment Operator:** How is assignment done via move? (`operator=(Class&&)`)

If you define nothing, the compiler generates them automatically (Rule of Zero). If you define one (e.g., destructor), you must define all 5 to avoid memory leaks or double-free errors.

---

## 5. Specific Concepts

### 5.1. The `this` Pointer
This is a hidden parameter passed automatically to every non-static function. It is a **const pointer** to the current object.
When you write `x = 5;` in a method, the compiler turns it into `this->x = 5;`.

### 5.2. `static` Members
Static variables are not part of the object. They live in global memory (Data Segment) and are shared among **all** instances of the class.
*   Application: Instance counters, shared caches, constants.

### 5.3. `const` Methods
A method marked with `const` (e.g., `int getAge() const`) promises the compiler that it will **not** modify member variables.
*   **Important:** You can only call `const` methods on `const` objects.

---

## 6. Professional Summary

1.  **Invariants:** The class is responsible for the validity of its data.
2.  **RAII:** Use constructors and destructors to automatically manage resource lifetimes.
3.  **Sizeof:** Be mindful of Alignment in high-performance systems.
4.  **Interface:** Public methods must be stable. Internal data (`private`) can change.