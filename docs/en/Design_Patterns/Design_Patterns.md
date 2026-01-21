# Design Patterns in C++ - Complete Technical Guide

## 1. Introduction: The Language of Software Architects

Design patterns are not ready-made code, but established and time-proven recipes for solving common problems in software architecture. In C++, where memory management and hierarchies are complex, patterns help us adhere to **SOLID** principles and write code that is maintainable.

---

## 2. Creational Patterns

### 2.1. Singleton
Ensures that a class has only one instance and provides a global point of access to it.

**C++ Implementation (Meyers Singleton):**
The safest way in C++11 (Thread-safe initialization).
```cpp
class Logger {
public:
    static Logger& get() {
        static Logger instance; // Initialized only once, safely
        return instance;
    }
    // Disable copying
    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;
private:
    Logger() {} // Private constructor
};
```

### 2.2. Factory Method
Defines an interface for creating objects but lets subclasses decide which class to instantiate. This is key for **Dependency Injection**.

```cpp
class Creator {
public:
    virtual std::unique_ptr<Product> createProduct() = 0;
};
```

---

## 3. Structural Patterns

### 3.1. Adapter
Makes two incompatible interfaces work together. Example: You have an old class `LegacyRectangle` and a new interface `IShape`. The adapter wraps `LegacyRectangle` and presents it as `IShape`.

### 3.2. PIMPL (Pointer to Implementation)
This is a C++ specific idiom (also called "Cheshire Cat").
*   **Problem:** Changing `private` fields of a class in a `.h` file requires recompiling all files that include it.
*   **Solution:** Move all `private` data into a separate structure (`struct Impl`) and keep only a pointer to it in the main class.
    ```cpp
    class Widget {
        struct Impl; // Forward declaration
        std::unique_ptr<Impl> pImpl;
    public:
        Widget();
        ~Widget();
    };
    ```
This drastically reduces compilation time (Compilation Firewall) and ensures binary compatibility (ABI stability).

---

## 4. Behavioral Patterns

### 4.1. Observer
One object (Subject) changes its state and automatically notifies all dependent objects (Observers).
*   **C++ Challenge:** How to avoid dangling pointers if the Observer is deleted before the Subject?
*   **Solution:** Use `std::weak_ptr` in the subscriber list. If `weak_ptr::lock()` returns `nullptr`, then the observer no longer exists, and we remove it from the list.

### 4.2. Strategy
Allows you to select an algorithm at runtime.
Example: A `Sorter` class that accepts `ISortStrategy` (QuickSort, BubbleSort). In C++, this is often done at compile-time via **Policies** (templates), which is faster (no virtual functions).

---

## 5. RAII (Resource Acquisition Is Initialization)

Although not in the GoF book, this is the **most important** pattern in C++.
The idea is simple: every resource (memory, file, mutex, network connection) must be "owned" by a stack object.
1.  **Constructor:** Acquires the resource.
2.  **Destructor:** Releases the resource.

Since C++ guarantees destructor calls (even upon exceptions), RAII makes code robust against errors without needing `finally` blocks.

---

## 6. Professional Tips: Over-engineering

The most common mistake is trying to force patterns everywhere.
*   **KISS (Keep It Simple, Stupid):** Don't make a Factory if a simple `new` works.
*   **YAGNI (You Ain't Gonna Need It):** Don't add flexibility (like Strategy) unless you have at least two different algorithms.

---

## 7. Professional Summary

*   Patterns are a vocabulary for communication ("This is a Singleton").
*   PIMPL is mandatory for large libraries (e.g., Qt, OpenCV).
*   RAII is the religion of C++.
*   Prefer compile-time patterns (Templates/Policies) over runtime patterns (Virtual functions) when speed is critical.