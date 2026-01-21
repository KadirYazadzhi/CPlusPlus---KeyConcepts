# Concepts in C++20 - Complete Technical Guide

## 1. Introduction: The Problem of "Blind" Templates

Before C++20, Templates were extremely powerful but completely devoid of semantic checking. If you pass the wrong type to a template (e.g., `std::sort` on `std::list`), the error appears deep within its implementation, leading to hundreds of lines of incomprehensible text known as "Template Error Hell".

**Concepts** are a mechanism for imposing Constraints on template parameters right in their declaration. They act as "contracts" for types.

---

## 2. Philosophy: Duck Typing at Compile Time

Concepts allow you to say: *"I don't care exactly what type `T` is, as long as it can be added (`+`), has a `print()` method, and is copyable"*. This is static polymorphism with clear rules.

---

## 3. Syntax and Usage

There are three ways to use a concept.

### 3.1. Terse Syntax
This is the most readable variant. We replace `typename` with the concept name.
```cpp
template <std::integral T>
T add(T a, T b) { return a + b; }
```
Here `std::integral` is a standard concept that restricts `T` only to integer types (`int`, `long`, `char`).

### 3.2. Requires Clause
Allows more complex logical expressions (`&&`, `||`).
```cpp
template <typename T>
requires std::integral<T> || std::floating_point<T>
T add(T a, T b) { return a + b; }
```

### 3.3. Trailing Requires
```cpp
template <typename T>
T add(T a, T b) requires std::integral<T> { ... }
```

---

## 4. Defining Custom Concepts (Expert Level)

You can create your own concepts by combining existing ones or writing new rules.

### 4.1. Atomic Constraints
```cpp
template <typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<size_t>; // Must have hash
};
```

### 4.2. Compound Requirements
This is the most powerful part. We check syntax and return types.
```cpp
template <typename T>
concept Drawable = requires(T v) {
    v.x;          // Must have a valid operation v.x (member or method)
    v.draw();     // Must have a draw() method
    { v.area() } -> std::same_as<double>; // draw() must return double
    typename T::ColorType; // Must have a defined inner type ColorType
};
```

---

## 5. Overloading with Concepts

Concepts participate in **Overload Resolution**. The compiler chooses the function with the "most constrained" concept.

```cpp
void process(auto x) { 
    std::cout << "Generic\n"; 
}

void process(std::integral auto x) { 
    std::cout << "Integral\n"; 
}

process(3.14); // Calls Generic (not integral)
process(10);   // Calls Integral (more specific)
```
This eliminates the need for `std::enable_if` and SFINAE magic.

---

## 6. Standard Concepts in `<concepts>`

C++20 comes with a rich library of ready-made concepts:
*   **Core:** `std::same_as`, `std::derived_from`, `std::convertible_to`.
*   **Arithmetic:** `std::integral`, `std::floating_point`, `std::signed_integral`.
*   **Object:** `std::movable`, `std::copyable`, `std::semiregular`.
*   **Comparison:** `std::equality_comparable`, `std::totally_ordered`.
*   **Iterator:** `std::input_iterator`, `std::random_access_iterator` (in `<iterator>`).

---

## 7. Professional Summary

1.  **Faster Compilation:** The compiler stops immediately if the concept is not satisfied, instead of trying to instantiate the template.
2.  **Documentation:** `template <Sortable T>` says much more than `template <typename T>`.
3.  **The Future:** Concepts are the foundation of C++20 Ranges and all future libraries.
4.  **Auto:** The `auto` keyword in functions (Abbreviated Function Templates) is actually the "weakest" concept (accepts anything). `void func(Sortable auto x)` is perfectly valid C++20 syntax.

---
*(Documentation prepared for the project "Key Concepts in C++".
*Version: 3.0 - Expert Detail)*