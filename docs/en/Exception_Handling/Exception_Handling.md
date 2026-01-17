# Exception Handling in C++ - The Ultimate Guide

## 1. Introduction: Managing Errors
Exceptions are a mechanism for transferring control from the point where an error occurs to a place where it can be handled. This separates the program's logic from error-handling logic.

---

## 2. Keywords

1.  **throw:** Throws an exception (an object or variable).
2.  **try:** Defines a block of code that may throw an exception.
3.  **catch:** Catches and handles the exception.

---

## 3. Standard Exceptions (std::exception)
C++ provides a hierarchy of error classes in the `<stdexcept>` header:
*   `std::runtime_error`
*   `std::logic_error`
*   `std::out_of_range` (e.g., invalid vector index)

**Best Practice:** Always catch exceptions by constant reference:
```cpp
catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
}
```

---

## 4. Stack Unwinding
When an exception is thrown, C++ begins destroying local objects in the current function and up the call stack until a matching `catch` block is found. This ensures that destructors of RAII objects (like smart pointers) are called and resources are freed.

---

## 5. noexcept (C++11)
If you are certain a function never throws exceptions, mark it with `noexcept`. This allows the compiler to perform optimizations. If a function marked `noexcept` throws something anyway, the program is terminated immediately.

---

## 6. What NOT to Do
*   **Never throw exceptions from a destructor.** This results in immediate program termination if a stack unwinding process is already active.
*   **Do not use exceptions for normal flow control** (e.g., exiting a loop). They are expensive and slow down the program.

---
*(This document is part of the "C++ Key Concepts" course)*