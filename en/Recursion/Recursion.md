# Recursion in C++

## 1. Introduction

Recursion is when a function calls itself.
Requires:
1.  **Base Case:** Stop condition.
2.  **Recursive Step:** Call with modified arguments.

---

## 2. Factorial Example

```cpp
int factorial(int n) {
    if (n <= 1) return 1; // Base case
    return n * factorial(n - 1); // Recursive step
}
```

---

## 3. Risks

**Stack Overflow:** If recursion is too deep.
**Performance:** Function call overhead.

---

## 4. Summary

Elegant for Tree/Graph traversal.
Watch out for stack depth.
