# Lambda Expressions in C++ - Complete Technical Guide

## 1. Introduction: Functions Without Names

Lambda expressions (introduced in C++11) are one of the most impactful tools in modern C++. They allow defining anonymous function objects (**Closures**) directly at the place where they are used. This changed the language paradigm towards more functional programming, allowing cleaner and more expressive code when working with algorithms and asynchronous tasks.

---

## 2. Anatomy of a Lambda Expression

The syntax consists of four main parts:
`[ capture ] ( params ) mutable exception -> return_type { body }`

### 2.1. Capture Clause `[]`
This is the most unique part of C++ lambdas. It allows the function to "see" and use variables from the outer scope.

*   `[]`: **Stateless Lambda**. Sees nothing from the outside. Can be converted to a regular `function pointer`.
*   `[=]`: **Copy Capture**. All used local variables are copied inside the lambda. Safe, but can be expensive for large objects.
*   `[&]`: **Reference Capture**. All variables are accessed by reference. Fast, but dangerous (see "Dangling References").
*   `[x, &y]`: Mixed capture. `x` by value, `y` by reference.
*   `[this]`: Allows access to class members. In C++20, it is recommended to use `[*this]` if you want to copy the entire object.

### 2.2. Mutable Lambdas
By default, the lambda's `()` operator is `const`. This means you cannot modify variables captured by value.
```cpp
int counter = 0;
auto f = [counter]() mutable { 
    counter++; // Possible only because of mutable. Modifies the internal copy.
    return counter; 
};
```

---

## 3. How It Works (Compiler Implementation)

When you write a lambda, the compiler secretly generates a unique, unnamed class (**Closure Type**).

**Your code:**
```cpp
int factor = 10;
auto lambda = [factor](int n) { return n * factor; };
```

**What the compiler sees:**
```cpp
class __Lambda_Unique_Name {
    int _factor; // Copy of the captured variable
public:
    __Lambda_Unique_Name(int f) : _factor(f) {}
    
    int operator()(int n) const {
        return n * _factor;
    }
};
```
This explains why lambdas are so fast – they are inlined objects, not function pointers.

---

## 4. Generic Lambdas (C++14) and constexpr (C++17)

### 4.1. `auto` parameters
Since C++14, lambdas became templates.
```cpp
auto sum = [](auto a, auto b) { return a + b; };
```
This generates a class with a templated `operator()`. You can call `sum(1, 2)` and `sum(std::string("a"), "b")` with the same lambda.

### 4.2. IIFE (Immediately Invoked Function Expression)
A technique borrowed from JavaScript for initializing constants with complex logic.
```cpp
const int result = [&](){
    int val = calculate();
    if (val < 0) return 0;
    return val * 2;
}(); // Called immediately!
```

---

## 5. Lambdas vs `std::function`

This is an important optimization.
*   **`auto f = [](){};`**: Zero overhead. The compiler knows the exact type.
*   **`std::function<void()> f = [](){};`**: Has overhead. Uses Type Erasure, virtual calls, and often allocates memory on the Heap.
**Tip:** Use `std::function` only if you need to store the lambda in a container (e.g., `vector<function>`). Otherwise, use `template` or `auto`.

---

## 6. Professional Hazards: Dangling References

The most common bug in asynchronous code:
```cpp
std::function<void()> getPrinter() {
    std::string text = "Hello";
    // ERROR! 'text' dies at the end of the function.
    // The lambda holds a reference to dead memory.
    return [&text](){ std::cout << text; }; 
}
```
**Golden Rule:** If the lambda will outlive the scope in which it is created (e.g., passed to a Thread or Task Queue), **ALWAYS** capture by value `[=]` or use smart pointers.

---

## 7. Professional Summary

1.  **Algorithms:** Lambdas are the natural partner of STL algorithms (`sort`, `find_if`).
2.  **Move Capture (C++14):** You can move objects into the lambda: `[ptr = std::move(unique_ptr)](){...}`.
3.  **Size:** A lambda without captures takes 1 byte (empty class). A lambda with captures takes the size of the captured data.
4.  **Readability:** Use them for short pieces of code. If the lambda grows over 5 lines, better write a normal method or functor.