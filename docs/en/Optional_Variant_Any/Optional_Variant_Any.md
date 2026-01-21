# Optional, Variant and Any (C++17) - Complete Technical Guide

## 1. Introduction: Goodbye void* and Null

Before C++17, working with "missing", "alternative", or "dynamic" data types required dangerous techniques like `nullptr`, `void*`, or clumsy `union` structures.
C++17 introduced three new "vocabulary types" (value containers), inspired by functional programming (Haskell, Rust), making code type-safe and expressive.

---

## 2. `std::optional`: Values That May Not Exist

The most commonly used of the three. It solves the classic problem: *"What should a function return if it finds no result?"*

### 2.1. Why Is It Better Than nullptr or -1?
*   **Semantics:** `std::optional<int>` says: "There might be an int, or there might not". `int*` says: "This is an address".
*   **Safety:** No need for dynamic memory (`new int`). The value is stored inside the object (on the stack).

```cpp
std::optional<User> findUser(int id) {
    if (db.hasUser(id)) return db.getUser(id);
    return std::nullopt; // Equivalent to "nothing"
}

auto user = findUser(10);
if (user) { // bool conversion
    print(user->name); // operator->
} else {
    print("User not found");
}
```

### 2.2. Monadic Operations (C++23)
C++23 added methods like `.and_then()` and `.transform()`, allowing chain calls without `if` checks.

---

## 3. `std::variant`: Algebraic Data Types (Sum Types)

`std::variant<A, B, C>` is the modern, type-safe version of a `union`. It can hold a value of **exactly one** type from the list at any given time.

### 3.1. How Does It Work?
Variant stores the largest possible object (via `union` under the hood) and a hidden index (`size_t`) that remembers which type is currently active.

### 3.2. `std::visit`: The Visitor Pattern
This is the professional way to work with `variant`. It eliminates the need for `if (holds_alternative<int>)` checks.

```cpp
using VarType = std::variant<int, float, std::string>;

struct Printer {
    void operator()(int i) { cout << "Int: " << i; }
    void operator()(float f) { cout << "Float: " << f; }
    void operator()(const string& s) { cout << "Str: " << s; }
};

VarType v = "Hello";
std::visit(Printer{}, v); // Calls operator()(string)
```

**Overloaded Lambdas:** Often used with a helper struct `overloaded` to define lambdas in place.

---

## 4. `std::any`: Full Dynamism

`std::any` is a container that can hold **absolutely any** type (as long as it is copyable).
It is the equivalent of `Object` in Java/C# or `void*` in C, but with type information preserved (RTTI).

### 4.1. Usage and Cast
To get the value, you must know the exact type:
```cpp
std::any a = 10;
a = std::string("Test");

// Safe extraction
try {
    std::string s = std::any_cast<std::string>(a);
} catch (const std::bad_any_cast& e) {
    // Wrong type!
}
```

⚠️ **WARNING:** Since `std::any` often uses dynamic allocation (Heap) for large objects, it is much slower than `variant` and should be avoided unless types are truly unknown (e.g., property system in a Game Engine).

---

## 5. Comparative Analysis (Memory & Performance)

| Type | Purpose | Memory | Speed |
| :--- | :--- | :--- | :--- |
| **std::optional<T>** | 0 or 1 value | `sizeof(T)` + `bool` (alignment) | Excellent (Stack) |
| **std::variant<A, B>** | One of N options | `max(sizeof(A), sizeof(B))` + `idx` | Very Good (Stack) |
| **std::any** | Any possible type | Heap allocation (often) | Slow (RTTI + Heap) |

---

## 6. Professional Summary

1.  **Optional:** Use it for returning results that might be missing, and for "lazy" initialization of fields.
2.  **Variant:** Use it for state machines, parsing JSON/XML (value can be number or string), and error handling (`variant<Result, Error>`).
3.  **Any:** Use only as a last resort when you need `void*` with type safety.

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*