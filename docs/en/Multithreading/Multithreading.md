# Multithreading in C++ - Complete Technical Guide

## 1. Introduction: The Era of Concurrency

In modern computing, where Moore's Law no longer applies to processor frequency but to the number of cores, parallel programming is a mandatory skill. In C++11, the language received a standard memory model and built-in support for threads (`<thread>`), ending the reliance on OS-specific APIs like `pthreads` (Linux) or `WinAPI` (Windows).

---

## 2. Anatomy of the Thread (The `std::thread`)

A Thread is the smallest unit of execution that can be managed by the operating system. In C++, a thread starts as soon as the object is created.

```cpp
void worker(int x) { ... }
std::thread t(worker, 10); // Starts immediately!
```

### 2.1. Lifecycle: Join vs Detach
If the `std::thread` destructor is called while the thread is still active (joinable), the program **crashes** (`std::terminate`).
*   **`t.join()`**: The main thread blocks and waits for the child thread to finish. This is the safe way to synchronize.
*   **`t.detach()`**: The thread "detaches" and runs independently in the background (daemon).
    *   ⚠️ **Danger:** If main() finishes, all detached threads are forcefully killed without being given a chance to clean up their resources.

---

## 3. Concurrency Issues (Race Conditions)

⚠️ **CRITICAL FOR INTERVIEWS:** When two threads access the same memory simultaneously and at least one of them writes, a **Data Race** occurs. This is Undefined Behavior.

### 3.1. Synchronization with Mutex (Mutual Exclusion)
A mutex (`std::mutex`) is a "key".
```cpp
std::mutex mtx;
// ...
mtx.lock();
// Critical section (only one thread can be here)
shared_data++;
mtx.unlock();
```

### 3.2. RAII: `lock_guard` and `scoped_lock`
Never call `lock()` and `unlock()` manually! If an exception occurs between them, the mutex remains locked forever (**Deadlock**).
*   **`std::lock_guard`**: Locks in the constructor, unlocks in the destructor.
*   **`std::scoped_lock` (C++17)**: Can lock **multiple** mutexes simultaneously without danger of Deadlock (deadlock avoidance algorithm).

---

## 4. Asynchronous Results: Futures and Promises

If you want to start a task and get a result from it ("return value") later, threads are inconvenient. We use `<future>`.

### 4.1. `std::async`
This is a high level of abstraction.
```cpp
// Starts a task (maybe in a new thread)
std::future<int> result = std::async([]{ return 42; });

// ... do something else ...

// Blocks until the result is ready
std::cout << result.get() << std::endl; 
```

---

## 5. Atomic Operations (`std::atomic`)

For simple counters or flags, mutexes are too heavy (require context switch at OS level).
`std::atomic<int>` uses special CPU instructions (like `LOCK XCHG` on x86) to safely modify memory.

```cpp
std::atomic<int> counter = 0;
counter++; // This is safe from multiple threads!
```

### 5.1. Memory Ordering (For Experts)
By default, atomics guarantee the strictest ordering (`memory_order_seq_cst`). For extreme optimization, you can use `relaxed`, but this requires a deep understanding of cache coherence.

---

## 6. Communication: `std::condition_variable`

How does one thread wait for another without wasting CPU in a "busy wait" loop?
*   Thread A "sleeps" on a Condition Variable (`cv.wait(lock)`).
*   Thread B "wakes" the waiting threads (`cv.notify_one()`) when there is new data.

This is the basis of the **Producer-Consumer** model.

---

## 7. Professional Traps

1.  **Deadlock:** Thread 1 holds A and waits for B. Thread 2 holds B and waits for A. The program freezes forever.
2.  **False Sharing:** When two threads modify different variables that accidentally happen to be in the same cache line (64 bytes) of the processor. Cores fight for ownership of the cache line, killing performance.
    *   **Solution:** `alignas(64)` to align data.

---

## 8. Professional Summary

*   Prefer **`std::async`** and parallel algorithms over raw threads.
*   Use **`std::atomic`** for simple flags.
*   Always use **`std::scoped_lock`** for mutexes.
*   Think of data as "Immutables" where possible – they don't need synchronization.