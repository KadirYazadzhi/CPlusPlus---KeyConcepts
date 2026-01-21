# Type Traits and SFINAE in C++ - Complete Technical Guide

## 1. Introduction: Programming the Compiler

Metaprogramming in C++ allows us to write code that adapts to data types automatically. While normal functions work with objects and values, template metaprogramming works with **types** at compile time.

**Type Traits** and **SFINAE** (Substitution Failure Is Not An Error) are the tools that allow libraries (like STL or Boost) to be so flexible, safe, and fast. They allow us to ask the compiler: *"Is this type a number?", "Does it have a virtual destructor?", "Can it be copied?"*.

---

## 2. Type Traits: Asking Questions

The `<type_traits>` library (introduced in C++11) provides hundreds of template structures that tell us properties of a type.

### 2.1. Primary Checks (Primary Type Categories)
*   `std::is_integral<T>`: Is T an integer (int, char, long)?
*   `std::is_floating_point<T>`: Is T a float/double?
*   `std::is_pointer<T>`: Is T a pointer?
*   `std::is_class<T>`: Is T a user-defined type?

### 2.2. Type Modification
We can not only ask but also modify types at compile time:
*   `std::remove_const<T>::type`: Removes `const`.
*   `std::remove_reference<T>::type`: Removes `&` or `&&`.
*   `std::decay<T>::type`: Removes everything (const, volatile, ref) and turns arrays into pointers.

### 2.3. Practical Example: `if constexpr` (C++17)
This is the easiest way to use Type Traits. Code that does not meet the condition is **literally deleted** by the compiler and does not compile.

```cpp
template <typename T>
void process(T val) {
    if constexpr (std::is_pointer_v<T>) {
        std::cout << "Processing pointer: " << *val << "\n";
    } else {
        std::cout << "Processing value: " << val << "\n";
    }
}
```

---

## 3. SFINAE (Substitution Failure Is Not An Error)

⚠️ **KEY CONCEPT:** When the compiler tries to find the correct template for a given type and fails during substitution, it **does not give an error immediately**. It simply "removes" this template from the list of candidates and continues looking for others.

This behavior allows us to "enable" and "disable" functions depending on the type.

### 3.1. `std::enable_if`
This is the classic tool (pre-C++20) for SFINAE. It relies on the fact that if the condition is `false`, the inner type `type` does not exist, triggering a substitution error (SFINAE) and the function is ignored.

```cpp
// This function exists ONLY if T is a floating-point number
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type
calculate(T x) { 
    return std::sqrt(x); 
}

// This function exists ONLY if T is an integer
template <typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
calculate(T x) { 
    return x * x; 
}
```

---

## 4. Creating Custom Type Traits

You can write your own Trait to check if a class has a specific method (e.g., `.serialize()`). This uses dark magic with `decltype` and `void_t`.

```cpp
// Check if T has a .serialize() method
template <typename T, typename = void>
struct has_serialize : std::false_type {};

template <typename T>
struct has_serialize<T, std::void_t<decltype(std::declval<T>().serialize())>> : std::true_type {};
```

---

## 5. The Modern Future: Concepts (C++20)

In C++20, most needs for SFINAE and the ugly `enable_if` are replaced by **Concepts**. They are faster, more readable, and give human-readable errors.

```cpp
template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

void print(Number auto x) { // Accepts only numbers
    std::cout << x;
}
```
If you pass `std::string` to `print`, the compiler will say: *"string does not satisfy concept Number"*.

---

## 6. Professional Summary

1.  **Optimization:** Type Traits allow algorithms like `std::copy` to use `memcpy` for simple types (POD) and a loop for complex objects.
2.  **Interfaces:** Use them to impose constraints on your templates.
3.  **Evolution:** Start with `if constexpr`. If not enough, use Concepts (if on C++20). Use `enable_if` only for maintaining old code (C++11/14/17).

---
*(Documentation prepared for the project "Key Concepts in C++".
*Version: 3.0 - Expert Detail)*