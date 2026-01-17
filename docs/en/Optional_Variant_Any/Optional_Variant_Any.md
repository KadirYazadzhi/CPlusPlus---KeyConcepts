# Optional, Variant, and Any (C++17)

## 1. Introduction

Type-safe containers for values that might be missing or have multiple types.

---

## 2. std::optional

For values that might not exist.

```cpp
std::optional<int> find(int id) {
    if (id == 1) return 42;
    return std::nullopt;
}
```

---

## 3. std::variant

A type-safe union.

```cpp
std::variant<int, string> v = 10;
v = "Hello";
```

---

## 4. std::any

Can hold **any** type.

---

## 5. Summary

Eliminates the need for `nullptr` and unsafe `void*`.
