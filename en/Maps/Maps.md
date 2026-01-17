# Maps in C++

## 1. Introduction

`std::map` is an associative container that stores elements as **Key-Value pairs**.

*   **Keys** are unique and used for sorting and searching.
*   **Values** are associated with keys.

Implemented as a **Red-Black Tree**.

### Characteristics:
*   **Sorted:** By key.
*   **Complexity:** O(log N).
*   **Unique Keys.**

---

## 2. Basic Operations

```cpp
#include <map>
#include <iostream>

int main() {
    std::map<std::string, int> ages;

    // 1. Operator []
    ages["Alice"] = 25;
    ages["Bob"] = 30;

    // 2. Insert pair
    ages.insert({"Charlie", 20});

    std::cout << ages["Alice"]; // 25
    return 0;
}
```

---

## 3. Access

### 3.1. Operator `[]`
If key doesn't exist, it creates it with default value (0).

### 3.2. `at()`
Throws exception if key missing.

---

## 4. Search

```cpp
if (ages.find("Bob") != ages.end()) { /* Found */ }
```

---

## 5. Iteration

Iterates in sorted order.

```cpp
for (const auto& [name, age] : ages) {
    std::cout << name << ": " << age << "\n";
}
```

---

## 6. Summary

*   Use for Key-Value associations.
*   Sorted by key.
*   O(log N).

```