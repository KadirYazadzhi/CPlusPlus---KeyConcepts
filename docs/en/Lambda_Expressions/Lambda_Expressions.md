# Lambda Expressions in C++

## 1. Introduction

Anonymous functions.

```cpp
auto add = [](int a, int b) { return a + b; };
```

---

## 2. Captures

*   `[=]`: By value.
*   `[&]`: By reference.

---

## 3. Summary

Essential for STL algorithms.
