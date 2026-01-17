# Unordered Maps in C++ - The Ultimate Guide

## 1. Introduction: The Power of Hash Tables
`std::unordered_map` (C++11) stores key-value pairs, but unlike `std::map`, elements are not sorted. Instead, it uses a **Hash Table**, providing exceptional performance.

---

## 2. Performance (Complexity)

*   **Average Case:** O(1) for insertion, search, and deletion.
*   **Worst Case:** O(N) (if the hash function is poor and all elements fall into the same "bucket" - a hash collision).

---

## 3. How Does a Hash Table Work?

1. **Hash Function:** Converts the key into a large integer.
2. **Buckets:** The integer is modulated by the number of "buckets" to determine where to store the value.
3. **Collision Handling:** If two keys have the same hash, C++ typically arranges them in a linked list within the corresponding bucket.

---

## 4. When to Choose Unordered Map?
*   When you are looking for **maximum speed**.
*   When the **order of elements does not matter**.
*   When working with large datasets where O(log N) is too slow.

---

## 5. Key Requirements
To use your own class as a key in an `unordered_map`, you must:
1. Define **operator==** (for collision checking).
2. Define a **hash function** (`std::hash<T>`).

---

## 6. Bucket Management (Load Factor)
You can inspect the table's state:
*   `load_factor()`: Average number of elements per bucket.
*   `rehash(n)`: Changes the number of buckets for optimization.

---
*(This document is part of the "C++ Key Concepts" course)*