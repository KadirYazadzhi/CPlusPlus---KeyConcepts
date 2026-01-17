# Coroutines in C++20 - The Ultimate Guide

## 1. Introduction: Functions that Can "Sleep"
A coroutine is a function that can suspend its execution, return control to the caller, and later be resumed exactly where it left off. Unlike threads, coroutines are **stackless** and extremely lightweight – you can have millions of coroutines running on a single machine.

---

## 2. Keywords in C++20
A function automatically becomes a coroutine if it contains at least one of the following keywords:
*   **co_await:** Suspends execution until an asynchronous task completes.
*   **co_yield:** Returns a value and suspends execution (ideal for generators).
*   **co_return:** Completes execution and returns a final result.

---

## 3. Anatomy of a Coroutine
C++20 defines only the framework. For a coroutine to work, you must define a type that contains:
1.  **promise_type:** An object that stores the state and the result.
2.  **std::coroutine_handle:** A pointer used to control the coroutine from the outside.

---

## 4. Applications

### 4.1. Generators (Lazy Sequences)
Instead of calculating thousands of elements and keeping them in memory, a coroutine produces the next element only when requested.
```cpp
Generator<int> counter() {
    for (int i = 0; ; ++i) co_yield i;
}
```

### 4.2. Asynchronous I/O
Allows writing non-blocking network code that looks like standard sequential code, avoiding "Callback Hell."

---

## 5. Advantages
*   **Performance:** Much cheaper than threads (no kernel-level context switching).
*   **Code Clarity:** Asynchronous logic becomes easy to read and debug.
*   **Scalability:** Perfect for high-load servers.

---
*(This document is part of the "C++ Key Concepts" course)*