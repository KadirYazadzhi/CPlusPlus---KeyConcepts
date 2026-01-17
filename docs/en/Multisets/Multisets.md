# Multisets in C++

## 1. Introduction

`std::multiset` is a sorted container allowing **duplicate values**.

---

## 2. Operations

```cpp
#include <set>
std::multiset<int> ms;

ms.insert(10);
ms.insert(10); // OK

std::cout << ms.count(10); // 2
```

**Erase:** `ms.erase(10)` removes **all** instances of 10. Use iterator to remove one.

---

## 3. Summary

Sorted collection with duplicates.
