# Design Patterns in C++

## 1. Introduction

Solutions to common architectural problems.

---

## 2. Singleton

Ensures one instance.

```cpp
class Singleton {
    static Singleton& get() {
        static Singleton instance;
        return instance;
    }
};
```

---

## 3. Factory

Creates objects without specifying exact class.

---

## 4. Observer

Notification mechanism.

---

## 5. Summary

Don't over-engineer. Use patterns when needed.
