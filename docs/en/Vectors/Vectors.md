# Vectors in C++ - The Ultimate Guide

## 1. Introduction: The Dynamic Array of C++
`std::vector` is the most important and frequently used container in the Standard Template Library (STL). It represents a dynamic array that can automatically resize itself. Unlike regular arrays, a vector manages its own memory on the Heap while retaining the advantage of contiguous storage.

---

## 2. Memory Management (Size vs. Capacity)

Understanding the difference between `size` and `capacity` is crucial for writing high-performance code.

*   **Size:** The number of elements currently stored in the vector.
*   **Capacity:** The number of elements the vector has allocated memory for.

### 2.1. The Reallocation Process
When you add an element and `size == capacity`, the vector:
1. Allocates a new, larger block of memory (typically 1.5x or 2x the current size).
2. Moves (or copies) the existing elements into the new block.
3. Frees the old memory.

⚠️ **IMPORTANT:** Reallocation is an expensive O(N) operation and invalidates all existing iterators, pointers, and references to the vector's elements.

---

## 3. Optimization with reserve() and shrink_to_fit()

To avoid unnecessary reallocations, use `reserve()` if you know the approximate number of elements in advance.

```cpp
std::vector<int> v;
v.reserve(1000); // Allocates memory for 1000 elements immediately.
// The next 1000 push_back() operations will be O(1).
```

---

## 4. Element Access

1.  **operator[]:** Fast access without bounds checking (unsafe).
2.  **at():** Access with bounds checking. If the index is invalid, it throws `std::out_of_range`.
3.  **front() / back():** Returns a reference to the first/last element.
4.  **data():** Returns a direct pointer to the internal array (useful for C-APIs).

---

## 5. Modern Features (C++11 and beyond)

### 5.1. emplace_back() vs. push_back()
`emplace_back` constructs the object directly inside the vector's memory, avoiding a temporary copy.

```cpp
struct Person {
    string name;
    Person(string n) : name(n) {}
};

vector<Person> people;
people.push_back(Person("John")); // Creates object, copies it, deletes temporary
people.emplace_back("John");      // Constructs object directly in the vector
```

---

## 6. Iterators and Erasure (Erase-Remove Idiom)

Deleting an element from the middle of a vector is O(N) because all subsequent elements must be shifted left.

To efficiently erase elements by condition before C++20:
```cpp
v.erase(std::remove(v.begin(), v.end(), val), v.end());
```
In C++20, this is replaced by the simpler:
```cpp
std::erase(v, val);
```

---

## 7. Performance (Complexity)

*   Index Access: **O(1)**
*   Insert/Delete at end: **O(1)** (amortized)
*   Insert/Delete at beginning/middle: **O(N)**
*   Search (unsorted): **O(N)**

---
*(This document is part of the "C++ Key Concepts" course)*