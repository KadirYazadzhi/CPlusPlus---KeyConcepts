# Maps in C++ - The Ultimate Guide

## 1. Introduction: The Dictionary of C++
`std::map` is an associative container that stores **Key-Value pairs**. Each key is unique and is associated with exactly one value. Like `std::set`, elements in a map are always maintained in a sorted order based on their keys.

---

## 2. Internal Implementation
Maps are implemented as **self-balancing binary search trees** (typically Red-Black Trees).

### 2.1. Complexity
*   **Search:** O(log N)
*   **Insertion:** O(log N)
*   **Deletion:** O(log N)

---

## 3. Access and Modification

### 3.1. Operator []
The easiest way to access values. **Warning:** If the key does not exist, the `[]` operator will automatically create it with a default value (e.g., 0 for int).

```cpp
std::map<string, int> ages;
ages["John"] = 25; // Creates or updates
```

### 3.2. Method at()
Safer than `[]`. If the key is missing, it throws an `std::out_of_range` exception.

---

## 4. Iteration

When iterating, you receive a pair of type `std::pair<const Key, Value>`.

```cpp
for (const auto& [name, age] : ages) { // C++17 Structured Bindings
    std::cout << name << " is " << age << " years old\n";
}
```

---

## 5. Search Methods

1.  **find():** Returns an iterator to the pair.
2.  **count():** Returns 1 or 0 (since keys are unique).
3.  **lower_bound() / upper_bound():** Used for finding ranges of keys.

---

## 6. When to Use Map?
*   When you need an association (e.g., ID -> User).
*   When data must always be sorted.
*   When search must be predictably fast (log N).

---

*(This document is part of the "C++ Key Concepts" course)*
