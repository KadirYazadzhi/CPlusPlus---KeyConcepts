# Coroutines in C++20 - Complete Technical Guide

## 1. Introduction: Functions with Memory

The coroutine is the most revolutionary addition in C++20. It is a function that can be **Suspended** and later **Resumed**, preserving its entire internal state (local variables, current execution line).

Unlike threads, coroutines are **stackless**.
*   **Thread:** Has a reserved stack in the OS (1-2 MB). Heavy to Context Switch.
*   **Coroutine:** Has a small memory block in the Heap (a few dozen bytes). Extremely lightweight and fast. Managed by the compiler, not the kernel.

---

## 2. The Keywords of the Future

A function automatically becomes a coroutine if it contains at least one of the following keywords:

1.  **`co_await`**: Suspends coroutine execution until the awaited event completes. Returns control to the Caller.
2.  **`co_yield`**: Returns an intermediate value and suspends the coroutine (Generator).
3.  **`co_return`**: Finalizes the coroutine, destroys its state, and returns a final result.

---

## 3. Anatomy of a Coroutine (Under the Hood)

⚠️ **ENGINEERING VIEW:** When the compiler sees a coroutine, it "slices" it into pieces and creates a **State Machine**.

It consists of three main components:

### 3.1. Promise Object
This is the "brain" of the coroutine. It is created inside it and serves for communication with the outside world.
*   What to do at start (`initial_suspend`)?
*   What to do at end (`final_suspend`)?
*   How to handle exceptions (`unhandled_exception`)?
*   How to return a value (`return_value` / `yield_value`)?

### 3.2. Coroutine Handle (`std::coroutine_handle`)
This is the "remote control" for the coroutine. It is a lightweight pointer (like `void*`) that allows external code to:
*   Resume the coroutine (`resume()`).
*   Destroy it (`destroy()`).
*   Check if it's done (`done()`).

### 3.3. Coroutine State (Frame)
A hidden block in dynamic memory (Heap) that stores:
*   The Promise object.
*   Function arguments (copied or moved).
*   Local variables.
*   The suspension point (Instruction Pointer).

This frame is allocated with `operator new` (unless the compiler applies HALO - Heap Allocation Elision).

---

## 4. Generator Implementation (Step-by-Step)

Here is how to write the simplest generator (before C++23 added `std::generator`):

```cpp
#include <coroutine>
#include <iostream>

struct Generator {
    struct promise_type {
        int current_value;
        
        Generator get_return_object() { 
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)}; 
        }
        std::suspend_always initial_suspend() { return {}; } // Suspends immediately on start
        std::suspend_always final_suspend() noexcept { return {}; } // Suspends before destruction
        void return_void() {} // End of function
        void unhandled_exception() { std::terminate(); }
        
        std::suspend_always yield_value(int value) { // On co_yield
            current_value = value;
            return {};
        }
    };

    std::coroutine_handle<promise_type> handle;
    
    Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Generator() { if (handle) handle.destroy(); } // RAII

    int next() {
        handle.resume(); // Resumes until next co_yield
        return handle.promise().current_value;
    }
};

Generator counter() {
    for (int i = 0; i < 3; ++i) {
        co_yield i; // Suspends and returns i
    }
}

int main() {
    auto gen = counter();
    std::cout << gen.next(); // 0
    std::cout << gen.next(); // 1
    std::cout << gen.next(); // 2
}
```

---

## 5. Asynchronous I/O and Awaitables

The most powerful use of coroutines is turning "Callback Hell" into linear code.
For something to be `co_await`-ed, it must be **Awaitable** (have methods `await_ready`, `await_suspend`, `await_resume`).

```cpp
// Example logic (pseudocode with library like Asio)
Task processNetwork() {
    try {
        auto socket = co_await connect("127.0.0.1", 8080);
        auto data = co_await socket.async_read();
        co_await socket.async_write("OK");
    } catch (const std::exception& e) {
        // Error handling exactly like synchronous code!
        std::cerr << e.what();
    }
}
```

---

## 6. Professional Traps

1.  **Dangling References:** Coroutines copy their arguments into the frame, but if you pass a reference to a temporary object, the coroutine might hang.
2.  **Forgotten `co_return`:** If the coroutine finishes without `co_return` (falls off the end), `return_void` is called. If the Promise object doesn't have such a method, the compiler gives an error.
3.  **Heap Allocation:** Coroutines always use the Heap (except with optimizations). In very tight loops, this can be an issue.

---

## 7. Professional Summary

*   Coroutines are not threads. They execute in the thread that calls them (unless you transfer them with `co_await executor`).
*   Use them for **Generators** (Lazy sequences) and **Asynchronous Tasks**.
*   In C++23, use `std::generator` instead of writing your own Promise type.

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*