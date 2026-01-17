# Exception Handling in C++

## 1. Introduction

Managing runtime errors.

---

## 2. Syntax

```cpp
try {
    throw std::runtime_error("Error");
} catch (const std::exception& e) {
    std::cout << e.what();
}
```

---

## 3. RAII and Stack Unwinding

Objects are automatically destroyed when an exception is thrown.

---

## 4. Summary

Use for exceptional conditions, not control flow.
