# Deques in C++

## 1. Introduction

`std::deque` (Double Ended Queue) allows fast insertion at both **front** and **back**.

### Comparison:
*   Like `vector`: Random access `[]`.
*   Unlike `vector`: `push_front` is O(1).
*   Memory: Chunked (not contiguous).

---

## 2. Operations

```cpp
#include <deque>
std::deque<int> d;

d.push_back(10);
d.push_front(5); // O(1)

std::cout << d[0]; // 5
```

---

## 3. Summary

Use when you need a "vector with push_front".
