# Concepts in C++20

## 1. Introduction

Constraints for templates. Fixes bad error messages.

---

## 2. Syntax

```cpp
template<typename T>
requires std::integral<T>
T add(T a, T b) { return a + b; }
```

---

## 3. Summary

Makes templates documented and readable.
