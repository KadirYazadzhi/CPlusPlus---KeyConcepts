# Smart Pointers in C++

## 1. Introduction

Raw pointers (`new`/`delete`) are prone to memory leaks.
Smart pointers (C++11) use **RAII** to manage memory automatically.

---

## 2. std::unique_ptr

Exclusive ownership. Cannot be copied, only moved.

```cpp
#include <memory>
std::unique_ptr<int> p = std::make_unique<int>(10);
// std::unique_ptr<int> p2 = p; // Error!
```

---

## 3. std::shared_ptr

Shared ownership. Reference counting.

```cpp
std::shared_ptr<int> p1 = std::make_shared<int>(10);
std::shared_ptr<int> p2 = p1; // Count = 2
```

---

## 4. std::weak_ptr

Non-owning observer. Breaks circular references.

---

## 5. Summary

*   Use `unique_ptr` by default.
*   Use `shared_ptr` only when ownership is shared.
*   Never use `new`.
