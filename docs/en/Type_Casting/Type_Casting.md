# Type Casting in C++

## 1. Introduction

Avoid C-style casts (`(int)x`). Use C++ casts.

---

## 2. Types

*   `static_cast`: Safe, compile-time.
*   `dynamic_cast`: Runtime check (polymorphism).
*   `const_cast`: Removing const.
*   `reinterpret_cast`: Bitwise reinterpretation (unsafe).

---

## 3. Summary

Prefer `static_cast` for standard conversions.
