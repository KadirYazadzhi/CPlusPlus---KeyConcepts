# Vectors in C++

## 1. Introduction

`std::vector` is the most used container. It's a **dynamic array** that resizes automatically. Defined in `<vector>`.

### Advantages:
*   **Dynamic Size.**
*   **Fast Access:** O(1) by index.
*   **Contiguous Memory:** Compatible with C APIs.

---

## 2. Basic Operations

```cpp
#include <vector>
std::vector<int> v = {1, 2, 3};

// Add to end - O(1)
v.push_back(4); 

// Remove from end - O(1)
v.pop_back();

// Access
std::cout << v[0];      // Unsafe
std::cout << v.at(0);   // Safe (throws)
```

---

## 3. Size vs Capacity

*   **Size:** Number of elements.
*   **Capacity:** Allocated memory.

When size > capacity, vector reallocates (copies everything to new memory). Expensive.
Use `reserve()` to prevent this.

```cpp
v.reserve(1000); // Allocates memory for 1000 ints upfront
```

---

## 4. Iteration

```cpp
// Range-based for
for (int x : v) std::cout << x;
```

---

## 5. 2D Vectors

```cpp
std::vector<std::vector<int>> matrix(3, std::vector<int>(4, 0));
matrix[0][1] = 5;
```

---

## 6. Summary

*   Default choice for arrays.
*   O(1) access.
*   Use `reserve()`.
*   Avoid inserting at beginning (O(N)).
