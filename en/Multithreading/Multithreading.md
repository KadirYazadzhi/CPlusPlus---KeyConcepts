# Multithreading in C++

## 1. Introduction

Parallel execution using `<thread>`.

---

## 2. Basic Thread

```cpp
std::thread t([]{ cout << "Thread"; });
t.join(); // Wait for finish
```

---

## 3. Synchronization

Use `std::mutex` and `std::lock_guard` to prevent race conditions.

---

## 4. Summary

Always join or detach threads. Protect shared data.
