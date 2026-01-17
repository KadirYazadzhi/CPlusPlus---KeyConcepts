# Multithreading in C++ - The Ultimate Guide

## 1. Introduction: Concurrency and Parallelism
In modern computer systems, CPUs have multiple cores. Multithreading allows a single program to execute multiple tasks simultaneously, thereby utilizing the hardware's full capacity. Since C++11, the language has a built-in standard library for threading (`<thread>`).

---

## 2. Creating Threads (std::thread)
A thread starts as soon as a `std::thread` object is created and passed a function or a lambda expression.

```cpp
#include <thread>

void task() { /* work */ }

int main() {
    std::thread t1(task);
    t1.join(); // Wait for the thread to finish
}
```

### 2.1. Join and Detach
*   **join():** Blocks the execution of the main thread until the child thread completes.
*   **detach():** Allows the thread to run independently in the background.

---

## 3. Shared Data Issues (Race Conditions)
When two or more threads attempt to modify the same variable simultaneously, a **Data Race** occurs – a state where the final result depends on non-deterministic timing.

### 3.1. Synchronization with std::mutex
A Mutex (Mutual Exclusion) is a mechanism that allows only one thread to access a specific block of code at a time.

```cpp
#include <mutex>
std::mutex mtx;
int counter = 0;

void safe_increment() {
    std::lock_guard<std::mutex> lock(mtx); // Automatically locks and unlocks (RAII)
    counter++;
}
```

---

## 4. Asynchronous Tasks (std::async and futures)
If we want to retrieve a result from a thread later, we use `std::async`. It returns a `std::future` that will hold the value once it is ready.

```cpp
#include <future>
std::future<int> result = std::async(std::launch::async, []() { return 42; });
int val = result.get(); // Blocks until the result is ready
```

---

## 5. Atomic Operations (std::atomic)
For simple types like `int` or `bool`, mutexes can be too slow. `std::atomic` provides low-level synchronization performed directly by the CPU without locking.

---

## 6. Deadlocks
This happens when Thread A waits for a resource held by Thread B, while Thread B waits for a resource held by Thread A. The program freezes indefinitely. Always use `std::scoped_lock` (C++17) to lock multiple mutexes simultaneously.

---
*(This document is part of the "C++ Key Concepts" course)*