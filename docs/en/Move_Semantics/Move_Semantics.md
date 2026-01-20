# Move Semantics in C++ - Complete Technical Guide

## 1. Introduction: Why is Move Better Than Copy?

Until 2011 (C++98/03), C++ had a major structural problem: transferring data between objects required a full copy.
If you had a vector with 1 million elements and returned it from a function, old C++ would:
1.  Allocate memory for the new vector.
2.  Copy all 1 million elements.
3.  Delete the old vector.

**Move Semantics** (C++11) changed this fundamentally. It allows the program to recognize that the old object is "dying" and simply **steal** its internal pointer to memory. The cost drops from O(N) to O(1).

---

## 2. Value Categories: L-values vs R-values

To understand moving, you must know Value Categories:

### 2.1. L-value (Left Value)
An object that has a **name** and a permanent **address** in memory. You can take its address with `&`.
*   `int x = 5;` -> `x` is an l-value.
*   `std::string s;` -> `s` is an l-value.

### 2.2. R-value (Right Value)
A Temporary object that has no name and will be destroyed at the end of the expression. You cannot take its address.
*   `5` (literal).
*   `x + y` (result of expression).
*   `FunctionReturningValue()` (result of function).

### 2.3. R-value Reference (`T&&`)
This is the "detector" for temporary objects.
*   `void func(int& x)` -> accepts only l-values (real variables).
*   `void func(int&& x)` -> accepts only r-values (temporaries we can rob).

---

## 3. The Magic of `std::move()`

⚠️ **MISCONCEPTION:** `std::move` **moves nothing**. It does not generate machine code for moving.

Physically, it is just a **cast** (`static_cast<T&&>`).
Its only purpose is to trick the compiler: *"Hey, treat this named object (l-value) as temporary (r-value), so I can call its Move Constructor."*

```cpp
std::string s1 = "Hello World";
std::string s2 = std::move(s1); 
// 1. std::move says "s1 is an r-value".
// 2. string(string&&) is called.
// 3. s2 takes s1's buffer.
// 4. s1 becomes an empty (but valid) string.
```

---

## 4. Implementing Move Semantics

To make your class "movable", you must write two special methods.

### 4.1. Move Constructor
```cpp
class Buffer {
    int* data;
    size_t size;
public:
    // Move Constructor
    Buffer(Buffer&& other) noexcept 
        : data(other.data), size(other.size) { // 1. Steal the resource
        
        // 2. Reset the source (VERY IMPORTANT)
        other.data = nullptr;
        other.size = 0;
    }
    
    ~Buffer() { delete[] data; } // Deleting nullptr is safe
};
```

### 4.2. Move Assignment Operator (`operator=`)
We must handle the existing resource in `this` before stealing the new one.
```cpp
Buffer& operator=(Buffer&& other) noexcept {
    if (this != &other) {          // 1. Self-assignment check
        delete[] data;             // 2. Release current resource
        
        data = other.data;         // 3. Steal new one
        size = other.size;
        
        other.data = nullptr;      // 4. Reset source
        other.size = 0;
    }
    return *this;
}
```

### 4.3. Why `noexcept`?
Always mark Move methods with `noexcept`. If `std::vector` needs to expand (reallocate), it will use the Move constructors of elements **only if** they are `noexcept`. If not, it will copy them (for safety), which kills performance.

---

## 5. Perfect Forwarding and `std::forward`

In Template programming, we often want to pass an argument to another function, preserving its category (if it was r-value, stay r-value).

**Universal Reference (`T&&` in template):**
Accepts both l-value and r-value.

```cpp
template<typename T>
void wrapper(T&& arg) {
    // std::forward preserves the category
    worker(std::forward<T>(arg)); 
}
```
*   If we pass `lvalue` -> `forward` returns `lvalue`.
*   If we pass `rvalue` -> `forward` returns `rvalue` (and allows move).

---

## 6. Professional Summary

1.  **Rule of Five:** If you define a destructor, copy, or move, define all 5 methods.
2.  **Move after Use:** After `std::move(x)`, object `x` is in a "valid but unspecified state". Do not use it, except to assign a new value or destroy it.
3.  **Return by Value:** Do not return `std::move(local_var)`. This prevents **RVO** (Return Value Optimization). Just return `local_var`.