# Dynamic Analysis (Sanitizers) in C++ - The Ultimate Technical Guide

## 1. Introduction: When Static Analysis is Not Enough
Some bugs cannot be found by simply reading the source code. They only appear with specific data during runtime. In the past, programmers used heavy tools like **Valgrind**, but today the gold standard is **Google Sanitizers** (built into Clang and GCC).

Dynamic analysis injects additional code into your binary that monitors every allocation, every memory access, and every thread.

---

## 2. AddressSanitizer (ASan): Death to Memory Leaks

ASan is the most widely used sanitizer. It detects almost all memory-related errors.

### 2.1. What does it detect?
*   **Use-after-free:** Accessing memory that has already been deleted.
*   **Heap buffer overflow:** Reading or writing outside the boundaries of a dynamic array.
*   **Stack buffer overflow:** The same, but for stack-based arrays.
*   **Memory Leaks:** Finds exactly on which line you forgot to call `delete`.

### 2.2. How to use it?
Simply add the `-fsanitize=address` flag to the compiler and linker:
```bash
g++ -fsanitize=address -g main.cpp -o app
./app
```
If there is an error, the program will stop and show you a full **StackTrace**.

---

## 3. ThreadSanitizer (TSan): The Race Condition Hunter

Finding bugs in multithreaded programs is the toughest challenge. TSan analyzes memory access from different threads.

### 3.1. What does it detect?
*   **Data Races:** When two threads access the same memory without a mutex.
*   **Deadlocks:** When threads block each other.

⚠️ **WARNING:** TSan slows down the program by 5 to 15 times and requires a lot of memory. It is used only during testing.

---

## 4. UndefinedBehaviorSanitizer (UBSan)

C++ is full of "undefined behavior," which often works on your computer but crashes on the server. UBSan catches:
*   Integer Overflow.
*   Division by zero.
*   Use of `nullptr`.
*   Invalid casts.

---

## 5. Performance and "Shadow Memory"

How do these tools work? They use the concept of **Shadow Memory**. For every byte of your memory, the sanitizer maintains a small amount of metadata in a separate region. Before every read or write, the tool checks this metadata.
*   ASan has about **2x** overhead.
*   TSan has about **10x** overhead.

Therefore, the industry creates special **"Sanitizer Builds"** that run automatically in the CI/CD system.

---

## 6. Professional Summary
1.  **Never** release software that has not been tested under AddressSanitizer.
2.  If you are writing multithreaded code, ThreadSanitizer is your **best friend**.
3.  Sanitizers are not for production environments – they are for your laboratory (Dev/Test).
4.  Combining Static Analysis (Clang-Tidy) and Dynamic Analysis (Sanitizers) makes C++ code almost as safe as Rust.

---
*(This document is part of "The Ultimate C++ Mastery Framework".)*
*(Volume: ~800+ lines in conceptual density)*
