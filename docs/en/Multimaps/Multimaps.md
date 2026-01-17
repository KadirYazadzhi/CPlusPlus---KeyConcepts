# Multimaps in C++ - The Ultimate Guide

## 1. Concept: Map with Duplicates
`std::multimap` is an associative container, similar to `std::map`, but with one key difference: it **allows the same key to occur multiple times**. Each element is a (key, value) pair, and the elements are ordered by key.

---

## 2. Key Differences from std::map

1.  **No operator[]:** Since one key can have multiple values, `m[key]` would be ambiguous (which of all values should it return?). Therefore, `insert()`, `find()`, or `equal_range()` must always be used.
2.  **Duplicates:** `insert()` always adds a new element, even if the key already exists.

---

## 3. Search Methods

To work with multiple values for a single key, `std::multimap` provides:
*   **count(key):** Returns how many times the key occurs.
*   **find(key):** Returns an iterator to the **first** element with that key.
*   **equal_range(key):** Returns a pair of iterators (`first` and `second`) marking the range of all elements with that key.

```cpp
auto range = m.equal_range("Tolkien");
for (auto it = range.first; it != range.second; ++it) {
    std::cout << it->second << std::endl;
}
```

---

## 4. Implementation and Complexity
Like `map`, it is implemented using a **Red-Black Tree**.
*   **Search:** O(log N)
*   **Insertion:** O(log N)
*   **Deletion:** O(log N)

---

## 5. Applications
*   **Dictionary:** One word (key) can have multiple meanings (values).
*   **Phone Book:** One person can have multiple numbers.
*   **Database:** Indexes where values are not unique.

---
*(This document is part of the "C++ Key Concepts" course)*