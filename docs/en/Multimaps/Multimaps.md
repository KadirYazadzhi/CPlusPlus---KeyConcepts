# Multimaps in C++ - The Ultimate Technical Guide

## 1. Introduction: The "One-to-Many" Relationship
The standard map (`std::map`) requires key uniqueness. In the real world, however, we often need a structure that allows a single key to be associated with multiple values (e.g., an author with many books or a filename with many paths). `std::multimap` is the associative container designed specifically for these scenarios.

---

## 2. Architecture: Sorted Tree with Duplicates
Like the `map`, the multimap uses a **Red-Black Tree**. The key difference lies in the insertion algorithm – it does not check for the existence of the key; it simply inserts the new pair at the correct position relative to the sort order.

### 2.1. Ordering of Duplicates
An important guarantee of the C++ standard: elements with the same key are stored in the order of their insertion (**Stable order** for duplicates).

---

## 3. Operations and Working with Ranges

### 3.1. Why is there no `operator[]`?
This is the most frequent question. Since there can be 10 values for a single key, the expression `m[key]` would be ambiguous. Therefore, access is only possible via iterators.

### 3.2. Finding All Values (Equal Range)
The professional way to access data in a multimap is via `std::equal_range`. It returns a pair of iterators marking the range of all values for the given key.

```cpp
auto range = my_map.equal_range("Key1");
for (auto it = range.first; it != range.second; ++it) {
    std::cout << it->second << std::endl;
}
```

---

## 4. Performance (Complexity)
*   **Searching for the first element:** O(log N)
*   **Insertion:** O(log N)
*   **Finding the entire range:** O(log N)

---

## 5. Professional Tips
1.  **Deletion:** Be careful! `m.erase("Key")` deletes **ALL** entries with that key. If you want to delete only one specific entry, you must use an iterator.
2.  **Vector Alternative:** Sometimes `std::map<Key, std::vector<Value>>` is a better architecture than `std::multimap`, especially if you frequently need access to all values at once and memory is a priority.

---
*Documentation prepared for the "C++ Key Concepts" project.*
*Version: 2.0 (Full Detail)*
