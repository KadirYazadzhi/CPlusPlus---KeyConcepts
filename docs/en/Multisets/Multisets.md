# Multisets in C++ - The Ultimate Guide

## 1. Concept: Set with Duplicates
`std::multiset` is an associative container that contains **sorted** elements, but unlike `std::set`, it **allows duplicate values**.

---

## 2. Implementation
Typically implemented using a **Red-Black Tree**. Duplicate elements are stored as adjacent nodes within the tree.

### 2.1. Complexity
*   **Insertion (insert):** O(log N).
*   **Search (find/count):** O(log N).
*   **Deletion (erase):** O(log N).

---

## 3. Deletion Specifics

The `erase()` method has two important behaviors:
1.  **s.erase(value):** Deletes **ALL** occurrences of that value.
2.  **s.erase(iterator):** Deletes only the specific element pointed to by the iterator.

---

## 4. Search Methods
*   **count(val):** Returns the number of occurrences of `val`.
*   **equal_range(val):** Returns the range (iterators) of all copies of `val`.

---

## 5. When to Use Multiset?
*   When you need data that is always sorted (e.g., a list of race results).
*   When duplicates are valid data (e.g., multiple students with the same grade).
*   When you want to quickly find how many times a certain value appears in a sorted sequence.

---
*(This document is part of the "C++ Key Concepts" course)*