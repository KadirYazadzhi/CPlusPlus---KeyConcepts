# Sets in C++

## 1. Introduction

`std::set` is an associative container storing **sorted** and **unique** elements. Defined in `<set>`.

### Characteristics:
*   **Uniqueness:** No duplicates allowed.
*   **Sorted:** Elements are always sorted (default: ascending).
*   **Implementation:** Red-Black Tree.
*   **Complexity:** O(log N) for search/insert/delete.

---

## 2. Operations

### 2.1. Insert

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> s;
    s.insert(10);
    s.insert(5);
    s.insert(10); // Duplicate ignored

    // Set is: {5, 10}
    return 0;
}
```

### 2.2. Custom Sort
Use a comparator.

```cpp
std::set<int, std::greater<int>> descSet; // Descending
```

---

## 3. Search

### 3.1. `find()`
Returns iterator.

```cpp
if (s.find(10) != s.end()) { /* Found */ }
```

### 3.2. `count()`
Returns 1 or 0.

---

## 4. Erase

```cpp
s.erase(10); // By value
s.erase(s.begin()); // By iterator
```

---

## 5. Iteration

Elements are `const`. Cannot modify directly (would break sort order).

```cpp
for (int x : s) std::cout << x << " ";
```

---

## 6. Summary

*   Use when you need **uniqueness** and **order**.
*   O(log N).
*   Immutable elements.
*   For O(1) without order, use `std::unordered_set`.
