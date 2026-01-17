# Coroutines in C++20

## 1. Introduction

A coroutine is a function that can **suspend** its execution to be resumed later. They are stackless and very efficient.

---

## 2. Keywords

*   `co_await`: Suspend until a task completes.
*   `co_yield`: Return a value and suspend (for generators).
*   `co_return`: Finish execution and return a result.

---

## 3. Usage

Mainly used for:
1.  **Generators:** Producing values lazily.
2.  **Asynchronous I/O:** Non-blocking networking or file access.

---

## 4. Summary

Revolutionary for async programming. Requires specific return types (Promises).
