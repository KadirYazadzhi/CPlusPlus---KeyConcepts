# Coroutines in C++20 - The Ultimate Technical Guide

## 1. Introduction: Functions with Memory
The Coroutine is the most revolutionary addition in C++20. It is a function that can be suspended (**Suspend**) and later resumed (**Resume**), preserving its state. Unlike threads, coroutines are **stackless** – they are extremely lightweight and managed entirely by the compiler, without operating system kernel intervention.

---

## 2. Keywords of the Future
A function becomes a coroutine if it contains:
*   `co_await`: Suspends execution until an event completes.
*   `co_yield`: Returns a value (like a generator) and suspends until the next request.
*   `co_return`: Finalizes the coroutine and returns a result.

---

## 3. Anatomy of a Coroutine (The Promise Object)

⚠️ **ENGINEERING PERSPECTIVE:** A coroutine is not just a function. It is an automated **State Machine**.

The compiler transforms your code into objects:
1.  **Promise Object:** The coroutine communicates with the calling code through this. It holds the result or exception.
2.  **Coroutine Handle:** A pointer through which you can manually start or destroy the coroutine.
3.  **Coroutine State:** A hidden structure in Heap memory that stores local variables and the current point of execution.

---

## 4. Application 1: Lazy Generators
Coroutines are perfect for generating sequences that do not fit in memory (e.g., all prime numbers).
```cpp
Generator<int> counter() {
    for (int i = 0; ; ++i) co_yield i; // Generates numbers only upon request
}
```

---

## 5. Application 2: Asynchronous I/O (Asio / Networking)
This is where coroutines shine. They allow asynchronous code to look like synchronous code. No "Callback Hell," just clear and sequential code.
```cpp
auto data = co_await socket.async_read(); // Suspends here until data arrives
process(data);
```

---

## 6. Professional Summary
*   Coroutines are **very fast** (millions on a single machine).
*   They are **difficult to write** from scratch – typically, you will use ready-made libraries (like `cppcoro` or `std::generator` in C++23).
*   Use them for **network communication**, **game logic**, and **processing large data streams**.

---
*Documentation prepared for the "C++ Key Concepts" project.*
*Version: 2.0 (Full Detail)*
