# Unordered Maps in C++ - The Ultimate Technical Guide

## 1. Introduction: The Speed Revolution
`std::unordered_map` (introduced in C++11) changed the way C++ programmers work with large volumes of data. While the traditional `std::map` relies on ordering, `std::unordered_map` relies on **extreme speed**. It is implemented via a **Hash Table**, making it the ideal choice for cache systems, dictionaries, and any scenario where searching is the most frequent operation.

---

## 2. How Does a Hash Table Work? (Under the Hood)

### 2.1. Hashing and Buckets
The process is as follows:
1.  The key is taken (e.g., "User123").
2.  A **Hash Function** is applied, which converts the string into a large integer.
3.  This integer is modulated by the number of internal **buckets**.
4.  The value is stored in the corresponding bucket.

### 2.2. Collisions
When two different keys produce the same hash (or fall into the same bucket), a collision occurs. C++ handles this via **Separate Chaining** – elements within a bucket are arranged in a linked list.

---

## 3. Performance: Average vs. Worst Case

*   **Average Complexity:** **O(1)**. The search is instantaneous, whether you have 100 or 100 million elements.
*   **Worst Case:** **O(N)**. If the hash function is poor and all elements fall into the same bucket, the table degenerates into a list.

---

## 4. Managing the Load Factor
Professional use of `unordered_map` requires understanding two parameters:
1.  **Load Factor:** The ratio `size / bucket_count`. If it exceeds a certain threshold (usually 1.0), the table performs a **Rehash**.
2.  **Rehashing:** A new, larger memory space is allocated, and all elements are recalculated and moved. This is an expensive operation (**O(N)**).

**Tip:** If you know the number of elements, use `reserve()` to avoid Rehashing.

---

## 5. Requirements for Custom Keys
To use your own class as a key, you must provide two things:
1.  **operator==**: So the table can distinguish objects during a collision.
2.  **Hash Function**: A specialization of `std::hash`.

```cpp
struct Point { int x, y; };

namespace std {
    template <>
    struct hash<Point> {
        size_t operator()(const Point& p) const {
            return hash<int>()(p.x) ^ hash<int>()(p.y);
        }
    };
}
```

---

## 6. Comparative Analysis: Map vs. Unordered Map

| Feature | std::map | std::unordered_map |
| :--- | :--- | :--- |
| **Structure** | Red-Black Tree | Hash Table |
| **Speed** | O(log N) | O(1) average |
| **Ordering** | Sorted | Chaotic |
| **Memory** | Less (per element) | More (due to buckets) |
| **Stability** | Predictable | Depends on hash function |

---

## 7. Professional Summary
*   Use `unordered_map` whenever you seek speed and do not need a sorted order.
*   Be careful with iterators – they are **Forward Iterators** (one-way only) and are invalidated during a Rehash.
*   For critical systems, carefully design your hash function to avoid "Hash DoS" attacks.

---
*Documentation prepared for the "C++ Key Concepts" project.*
*Version: 2.0 (Full Detail)*
