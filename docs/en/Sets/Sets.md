# Sets in C++ - The Ultimate Guide

## 1. Concept: Uniqueness and Order
In C++, `std::set` is an associative container that contains unique objects. All elements are automatically maintained in a sorted order. If you attempt to add a duplicate, it will simply be ignored.

---

## 2. Internal Implementation
Almost all compilers implement `std::set` as a **Red-Black Tree** – a type of self-balancing binary search tree.

### 2.1. Complexity
*   **Search:** O(log N)
*   **Insertion:** O(log N)
*   **Deletion:** O(log N)

---

## 3. Key Functions

### 3.1. insert()
Adds an element. Returns a `std::pair` containing an iterator to the element and a boolean value (whether the insertion was successful).

### 3.2. find()
Returns an iterator to the element if found, or `s.end()` if missing.

### 3.3. lower_bound() / upper_bound()
Extremely useful for searching for intervals in sorted data.

---

## 4. Types of Sets

### 4.1. std::set (Standard)
Keeps elements sorted.

### 4.2. std::unordered_set (C++11)
Uses a **Hash Table**. Elements are not ordered, but search speed is **O(1)** on average.

### 4.3. std::multiset
Allows storing duplicates while maintaining sorted order.

---

## 5. Custom Sorting
You can change the ordering criteria by providing a comparator in the template:
```cpp
std::set<int, std::greater<int>> s; // Sorting in descending order
```

---

## 6. Iterators
Elements in `std::set` are constant. You cannot modify an element directly via an iterator, as that would break the tree structure. To "modify" an element, you must erase it and insert a new one.

---
*(This document is part of the "C++ Key Concepts" course)*