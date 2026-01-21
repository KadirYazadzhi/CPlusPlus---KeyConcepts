# Dynamic Analysis in C++ - Complete Technical Guide

## 1. Introduction: The Truth Comes Out at Runtime

Static analysis is powerful, but it can't catch everything (e.g., user input or complex network interactions). **Dynamic Analysis** monitors the program while it is running. It acts like an "X-ray" for your process, finding bugs in real-time.

---

## 2. Sanitizers (Google Sanitizers)

These are tools built directly into compilers (GCC and Clang). They instrument the code (add checks) at compile time.

### 2.1. AddressSanitizer (ASan)
The most important tool for the C++ programmer. Detects memory errors.
*   **Buffer Overflow:** Writing out of bounds on stack or heap arrays.
*   **Use-After-Free:** Accessing already freed memory (dangling pointers).
*   **Double Free:** Deleting memory twice.
*   **Memory Leaks:** (via LeakSanitizer).

**How does it work? (Shadow Memory)**
ASan allocates "shadow" memory (1 byte of shadow for every 8 bytes of real memory). When you allocate an array `char a[10]`, ASan marks the area around it as "poisoned". Every memory access is checked against the shadow.
*   **Overhead:** Slows down the program ~2x. Increases memory usage ~3x.

**Activation:**
`g++ -fsanitize=address -g main.cpp`

### 2.2. ThreadSanitizer (TSan)
Detects **Data Races** (when two threads write simultaneously without protection).
*   TSan tracks all atomic operations and mutexes and builds a "Happens-Before" graph. If two operations do not have a "happens-before" relation but access the same memory -> Error.
*   **Overhead:** Slows down the program ~10x. Increases memory usage ~5x.

### 2.3. UndefinedBehaviorSanitizer (UBSan)
Catches things that are not memory errors but break the standard:
*   Signed integer overflow.
*   Division by zero.
*   Null pointer dereference.
*   Alignment issues.

---

## 3. Valgrind (Memcheck)

Valgrind is a legendary tool that works on a different principle than Sanitizers. It is a **Virtual Machine**.
Your program does not run directly on the processor. Valgrind translates it instruction by instruction (JIT Translation).

### 3.1. Advantages over ASan
*   **No Recompilation:** You can analyze any binary application (even if you don't have the source code).
*   **Uninitialized Reads:** Valgrind is much better at detecting if you use a variable before initializing it ("Conditional jump or move depends on uninitialised value(s)").

### 3.2. Disadvantages
*   **Slow:** Slowdown is **20x to 50x**.
*   **False Positives:** Sometimes gets confused by optimized code.

---

## 4. Dr. Memory and Other Tools

*   **Dr. Memory:** Similar to Valgrind, but for Windows.
*   **Heaptrack:** Profiles memory consumption (who allocates the most, where leaks are).

---

## 5. Fuzzing (Fuzz Testing)

Fuzzing is an automated testing technique where you feed **random, invalid data** to the program to see if it crashes.
*   **LLVM libFuzzer:** Integrates with ASan. Generates inputs that traverse new paths in the code (Coverage-guided fuzzing).

---

## 6. Professional Summary (Best Practices)

1.  **Debug Builds:** Always compile your Debug versions with `-fsanitize=address,undefined`. This will catch 90% of bugs immediately.
2.  **CI/CD:** Run your tests (Unit Tests) under ASan and TSan in the pipeline.
3.  **Valgrind:** Use it for deep investigation when you suspect uninitialized memory or when you cannot recompile a library.
4.  **Performance:** Do not run Sanitizers in Production (unless you have a very specific need), as they slow down the system.

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*