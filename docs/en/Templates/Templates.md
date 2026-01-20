# Templates in C++ - Complete Technical Guide

## 1. Introduction: The Generic Programming Paradigm

Templates are the "nuclear weapon" of C++. They allow writing code that is independent of data type (**Generic Programming**). Unlike Java/C# Generics, which work with Type Erasure at runtime, C++ templates are a **Compile-time** mechanism.

**How does it work?** A template is not code. It is a "blueprint". When you use `std::vector<int>`, the compiler takes the vector blueprint and generates (instantiates) a completely new class `Vector_Int`, optimized specifically for integers.

---

## 2. Function Templates

Instead of overloading a function 10 times for `int`, `float`, `double`, we define a template:

```cpp
template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}
```

### 2.1. Template Type Deduction
You don't need to write `maximum<int>(5, 10)`. The compiler is smart enough to figure out that 5 and 10 are `int`, and automatically instantiates the correct version.

---

## 3. Class Templates

This is the backbone of the STL (`vector`, `map`, `list`).

```cpp
template <typename T, size_t N>
class Array {
    T data[N]; // The size N is known at compile time!
public:
    size_t getSize() const { return N; }
};

Array<int, 5> arr; // Creates a unique type Array_int_5
```

⚠️ **Important:** Non-type template parameters (like `size_t N`) allow the compiler to perform crazy optimizations (e.g., loop unrolling) because it knows the exact size of the array before the program starts.

---

## 4. Template Specialization

Sometimes the generic algorithm doesn't work for all types. Example: You want `Box<T>` to work for everything, but `Box<bool>` to be optimized to take up 1 bit, not 1 byte.

```cpp
// 1. Primary template
template <typename T>
class Box { T val; };

// 2. Full specialization
template <>
class Box<bool> {
    unsigned char data; // Bitwise operations...
};
```
This is what makes `std::vector<bool>` so different from `std::vector<int>`.

---

## 5. Variadic Templates - C++11

Allow a template to accept an arbitrary number of arguments. This is the basis of `std::printf`-like functions and `std::tuple`.

### 5.1. Fold Expressions (C++17)
Before C++17, we had to write recursion. Now it's magic:

```cpp
template<typename... Args>
auto sum(Args... args) {
    return (... + args); // Sums all arguments: (arg1 + arg2 + arg3...)
}

int total = sum(1, 2, 3, 4, 5); // 15
```

---

## 6. Template Metaprogramming (TMP)

Since templates are Turing-complete, you can write programs that execute **during compilation**.

### 6.1. SFINAE (Substitution Failure Is Not An Error)
This is the old technique (pre-C++20) for filtering types. "If type `T` does not have a method `quack()`, don't crash with an error, just remove this function from the list of candidates."

```cpp
// Enabled only if T is arithmetic
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
add(T a, T b) { return a + b; }
```

---

## 7. Modern C++: Concepts - C++20

Concepts killed SFINAE. They make code readable and give clear error messages.

```cpp
template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <Number T>
T add(T a, T b) { return a + b; }
```
If you pass a `string`, the compiler will say: *"Error: string does not satisfy concept Number"*, instead of spitting out 10 pages of template errors.

---

## 8. Professional Summary

1.  **Header-Only:** Templates must be defined entirely in `.h` / `.hpp` files. If you put them in `.cpp`, the linker won't find them.
2.  **Code Bloat:** Be careful. `Array<int, 1>`, `Array<int, 2>`... `Array<int, 100>` will generate 100 different classes in the binary file.
3.  **Performance:** Templates are the fastest way for polymorphism (Static Polymorphism) because they avoid virtual tables.
4.  **Use C++20 Concepts:** They are the future of clean API design.