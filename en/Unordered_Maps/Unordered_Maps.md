# Unordered Maps in C++

## 1. Introduction

`std::unordered_map` is a **Hash Table**.
It stores key-value pairs like `map`, but **without order**.

### Characteristics:
*   **Complexity:** Average O(1). Worst case O(N).
*   **Order:** Undefined/Random.
*   **Hashing:** Requires a hash function for the key.

---

## 2. Operations

Same API as `std::map` (mostly).

```cpp
#include <unordered_map>
std::unordered_map<std::string, double> products;

products["Laptop"] = 999.99;

if (products.find("Laptop") != products.end()) {
    // Found O(1)
}
```

---

## 3. Map vs Unordered Map

| Feature | Map | Unordered Map |
| :--- | :--- | :--- |
| **Structure** | Tree | Hash Table |
| **Order** | Sorted | Random |
| **Search** | O(log N) | O(1) |

---

## 4. Summary

*   Use for max speed.
*   No order guarantees.
*   Requires Hash function.
