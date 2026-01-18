# Multisets in C++ - The Ultimate Technical Guide

## 1. Concept: When Repetitions Matter
`std::multiset` is a version of the set that allows storing duplicate values. Although this sounds like an ordinary list, the key difference is that the data is **always sorted**. This is ideal for competition results, grades, or price bids where you want to know the rank of each value.

---

## 2. Implementation and Memory
Based on a **Red-Black Tree**, the multiset ensures logarithmic complexity.

### 2.1. Order of Duplicates
C++ guarantees that if you insert two identical values, they will maintain their order of entry. This is important when working with objects that have the same "sort key" but different other data.

---

## 3. Critical Method Differences

### 3.1. erase(val) vs. erase(iterator)
This is the trap into which many fall:
*   `s.erase(10)` – Deletes **ALL** elements with the value 10.
*   `s.erase(it)` – Deletes **ONLY ONE** specific element.

### 3.2. count(val)
Unlike a regular set, here `count()` is a real operation that can take **O(log N + K)** time (where K is the number of duplicates).

---

## 4. Comparative Analysis (The Trade-off)

| Operation | std::vector (sorted) | std::multiset |
| :--- | :--- | :--- |
| **Insertion** | O(N) | O(log N) |
| **Search** | O(log N) | O(log N) |
| **Memory** | Minimal | High (pointers) |

**Conclusion:** Use `multiset` only if you insert and delete elements dynamically. If data is filled once and only read, a sorted vector is much faster.

---

## 5. Summary
*   `multiset` keeps data **sorted**.
*   Beware of bulk deletion by value.
*   Ideal for dynamic ranking systems (leaderboards).

---
*Documentation prepared for the "C++ Key Concepts" project.*
*Version: 2.0 (Full Detail)*
