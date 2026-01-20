# Multimaps in C++ - Complete Technical Guide

## 1. Introduction: The "One-to-Many" Relation

The standard map (`std::map`) requires strict uniqueness of the key. In the real world, however, we often need a structure that allows a single key to be associated with multiple values.

**Real-World Examples:**
*   **Library:** One author -> Many books.
*   **School:** One student -> Many grades.
*   **File System:** One filename -> Many paths (duplicates in different folders).
*   **DNS Server:** One domain name -> Many IP addresses.

`std::multimap` is the associative container designed exactly for these scenarios.

---

## 2. Architecture: Sorted Tree with Duplicates

Similar to `map`, the multimap uses a **Red-Black Tree**.
The key difference is in the insertion algorithm – it does not check for the existence of the key, but simply inserts the new pair at the correct position relative to the order.

### 2.1. Stability of Duplicates (Stable Ordering)
This is a critical guarantee of the C++ standard (since C++11):
Elements with the **same key** are stored in the order of their insertion.
If you insert `("Key", 1)`, then `("Key", 2)`, upon traversal you are guaranteed to get 1 first, then 2. This makes the structure predictable.

---

## 3. Operations and Range Handling

### 3.1. Why no `operator[]`?
This is the most common interview question.
In `std::map`, `m["Key"]` returns a reference to the *single* value.
In `std::multimap`, for key "Key" there can be 0, 1, or 100 values. Which one should the operator return? There is no correct answer. Therefore, `operator[]` and `at()` are removed to avoid ambiguity.

### 3.2. Data Access: `equal_range`
The professional way to access data in a multimap is not `find`, but `equal_range`. It returns a pair of iterators (`pair<iterator, iterator>`) that delimit the beginning and end of all elements with the given key.

```cpp
std::multimap<string, int> scores;
scores.insert({"Player1", 100});
scores.insert({"Player1", 200});
scores.insert({"Player1", 50});

auto range = scores.equal_range("Player1");

// Iterate only through "Player1" records
for (auto it = range.first; it != range.second; ++it) {
    std::cout << "Score: " << it->second << std::endl;
}
```

### 3.3. Counting and Searching
*   `count(key)`: Returns the number of elements with this key. Be careful: this is **O(log N + Count)**, so if you have millions of duplicates, it might be slow.
*   `find(key)`: Returns an iterator to the **first** element with this key.

---

## 4. Performance (Complexity Analysis)

*   **Insertion:** **O(log N)**. Always adds a new node.
*   **Deletion:** **O(log N + K)**, where K is the number of deleted elements.
*   **Search:** **O(log N)**.

---

## 5. Professional Tips and Traps

### 5.1. The `erase` Trap
Be careful!
*   `m.erase("Key")` deletes **ALL** records with this key.
*   If you want to delete only **one specific** record (e.g., only the grade 50 of Player1), you must first find it with an iterator and pass the iterator to `erase`.

```cpp
// Deleting only the first encountered "50" of Player1
auto range = m.equal_range("Player1");
for (auto it = range.first; it != range.second; ++it) {
    if (it->second == 50) {
        m.erase(it);
        break; // Important! Iterator becomes invalid after deletion.
    }
}
```

### 5.2. Architectural Alternative
Sometimes `std::multimap<Key, Value>` is not the best solution.
Consider `std::map<Key, std::vector<Value>>`.
*   **Vector Advantage:** Better cache locality for values. Less memory overhead (only one tree node per key).
*   **Multimap Advantage:** Easier addition of single elements (no need to find vector, push_back, etc.). Sorted values are "flat".

---

## 6. Summary

Use `std::multimap` when:
1.  You need a "Many-to-Many" or "One-to-Many" relationship.
2.  You want data to be always sorted by key.
3.  You want to preserve insertion order for duplicates.

If sorting is not required, consider `std::unordered_multimap` for O(1) access.