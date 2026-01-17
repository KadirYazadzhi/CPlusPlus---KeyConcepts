# Modern Data Types (Optional, Variant, Any) - The Ultimate Guide

## 1. std::optional: Missing Values
`std::optional` (C++17) solves the issue of functions that might not always return a result. You no longer need to use `nullptr` or magic numbers like `-1`.

```cpp
std::optional<int> findUser(int id) {
    if (id == 1) return 42;
    return std::nullopt; // No value
}
```

---

## 2. std::variant: Type-safe Union
`std::variant` is a type that can store one value from a predefined list of types. It is **type-safe** – it always knows what type it currently holds.

```cpp
std::variant<int, std::string> v = "Hello";
v = 10;
int x = std::get<int>(v);
```

### 2.1. std::visit
The most powerful way to work with `variant` is via the Visitor pattern (using lambdas for every possible type).

---

## 3. std::any: Full Flexibility
`std::any` can store **absolutely any** data type. To retrieve the value, you must explicitly cast it (`std::any_cast`).

---

## 4. Summary
*   **optional:** Use for optional results.
*   **variant:** When you know the possible types (e.g., Error OR Success).
*   **any:** When types are completely unknown (rarely recommended).

---
*(This document is part of the "C++ Key Concepts" course)*