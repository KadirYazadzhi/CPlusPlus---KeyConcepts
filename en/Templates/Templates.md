# Templates in C++

## 1. Introduction

Basis of Generic Programming.

---

## 2. Function Templates

```cpp
template <typename T>
T add(T a, T b) { return a + b; }
```

---

## 3. Class Templates

```cpp
template <typename T>
class Box {
    T value;
};
```

---

## 4. Specialization

Handling specific types differently.

---

## 5. Summary

Code reusability at compile-time.
