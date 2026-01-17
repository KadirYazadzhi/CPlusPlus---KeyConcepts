# Lists in C++

## 1. Introduction

`std::list` is a **Doubly Linked List**.
Elements are not contiguous in memory.

### Pros:
*   O(1) insertion/deletion anywhere (with iterator).
*   No invalidation of pointers/references.

### Cons:
*   Slow access (no `[]` operator). O(N) traversal.
*   Cache unfriendly.

---

## 2. Operations

```cpp
#include <list>
std::list<int> l = {10, 20};

l.push_front(5); // {5, 10, 20}
l.push_back(30); // {5, 10, 20, 30}

// Splice (Transfer elements)
std::list<int> l2 = {100};
l.splice(l.begin(), l2); // Moves 100 to start of l
```

---

## 3. Summary

Use only when you need frequent insertion in the **middle** of the sequence. Otherwise `vector` is faster.
