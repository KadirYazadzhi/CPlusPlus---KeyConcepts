# Lock-free Data Structures in C++ - Complete Technical Guide

## 1. Introduction: The Problem with Mutexes

In multithreaded programming, the standard way to protect data is `std::mutex`. However, mutexes are "pessimistic" – they assume conflict and stop the thread.
The problems are serious:
*   **Blocking:** The thread stops and waits, wasting CPU time in context switching.
*   **Priority Inversion:** A low-priority thread can hold a mutex, blocking a critical Real-time thread.
*   **Deadlock:** Risk of eternal blocking with wrong locking order.

**Lock-free** programming allows threads to work on the same structure **without any thread being forcibly stopped** by the OS.

---

## 2. The Heart of Lock-free: CAS (Compare-And-Swap)

All Lock-free structures rely on a special hardware instruction (atomic operation): **Compare-And-Swap**.
In C++, it is accessible via `std::atomic::compare_exchange_weak/strong`.

**Logic:**
*"Read memory at address X. If the value there is equal to `Expected`, write `NewValue`. If not (meaning someone else changed it!), return the new value and write nothing."*

```cpp
std::atomic<int> head(0);

void push(int new_val) {
    int old_head = head.load();
    // Loop until success (Optimistic Concurrency Control)
    while (!head.compare_exchange_weak(old_head, new_val)) {
        // If failure: old_head is automatically updated with the new value
        // and we try again.
    }
}
```

---

## 3. Lock-free Stack Implementation (Treiber Stack)

Here is what the simplest lock-free container looks like.

```cpp
template<typename T>
class LockFreeStack {
    struct Node { T data; Node* next; };
    std::atomic<Node*> head{nullptr};

public:
    void push(const T& val) {
        Node* newNode = new Node{val, head.load()};
        // CAS Loop:
        while (!head.compare_exchange_weak(newNode->next, newNode)); 
    }

    bool pop(T& result) {
        Node* oldHead = head.load();
        // We must check if the stack is not empty
        while (oldHead && !head.compare_exchange_weak(oldHead, oldHead->next));
        
        if (!oldHead) return false; // Empty
        result = oldHead->data;
        // delete oldHead; // ⚠️ DANGER! See ABA problem.
        return true;
    }
};
```

---

## 4. The Challenge: Memory Management (The ABA Problem)

In the `pop` example above, if we delete `oldHead`, another thread might still be reading it (before its CAS).
Even worse is the **ABA problem**:
1.  Thread 1 reads top `A`. Prepares to swap `A` -> `B`. Pauses briefly.
2.  Thread 2 removes `A`, removes `B`, then puts `A` back (same memory address!).
3.  Thread 1 wakes up. CAS sees the top is `A` (as expected) and swaps `A` -> `B`.
4.  **Error:** `B` was deleted long ago! The stack is broken.

**Professional Solutions (Memory Reclamation):**
*   **Hazard Pointers:** Each thread declares in a global array: *"I am reading this pointer, do not delete it!"*.
*   **Epoch-based Reclamation:** Memory is deleted in "batches". A batch is discarded only when all threads have moved to a new execution "epoch".
*   **std::shared_ptr (atomic):** C++20 allows `std::atomic<shared_ptr>`, which solves the problem but is slow.

---

## 5. C++20: Atomic Wait and Notify

Before C++20, if you were waiting for an atomic to change, you had to spin in a loop (`spinlock`), consuming 100% CPU.
C++20 adds a method similar to `condition_variable`, but for atomics (uses `futex` on Linux).

```cpp
std::atomic<int> flag = 0;

void worker() {
    flag.wait(0); // Efficiently sleeps while value is 0
    // ...
}

void signal() {
    flag = 1;
    flag.notify_all(); // Wakes up workers
}
```

---

## 6. Professional Summary

*   **Complexity:** Lock-free code is 10 times harder to write and 100 times harder to debug than mutex code.
*   **Usage:** Use it only for **micro-optimizations** in the hottest spots of the system (e.g., message queue in an HFT system).
*   **Libraries:** Do not write your own Lock-free Queue. Use **Boost.Lockfree** or **Folly** (by Facebook).

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*