# Multimaps in C++

## 1. Introduction

`std::multimap` allows **duplicate keys**.
Sorted by key.

---

## 2. Operations

No `[]` operator (ambiguous).

```cpp
#include <map>
std::multimap<string, string> library;

library.insert({"Tolkien", "Hobbit"});
library.insert({"Tolkien", "LOTR"});

// Find all
auto range = library.equal_range("Tolkien");
for (auto it = range.first; it != range.second; ++it) {
    std::cout << it->second << "\n";
}
```

---

## 3. Summary

Use for 1-to-many relationships.

```
