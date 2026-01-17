# Functions in C++

## 1. Introduction

Functions are the building blocks of any C++ program. They are named blocks of code that perform a specific task. Using functions allows for:
*   **Modularity:** Breaking complex problems into smaller, manageable parts.
*   **Reusability:** Code written once can be called multiple times.
*   **Abstraction:** Hiding implementation details (knowing *what* it does, not *how*).

---

## 2. Structure of a Function

A C++ function consists of a signature (prototype) and a body.

```cpp
// Return Type   Name      Parameters
//      |          |           |
//      v          v           v
       int        sum(int a, int b) {
           // Body
           int result = a + b;
           return result; // Return value
       }
```

### 2.1. Declaration vs Definition
*   **Declaration (Prototype):** Tells compiler about function existence, name, parameters, and return type. Usually in `.h` files.
    ```cpp
    int sum(int a, int b); // Semicolon at end
    ```
*   **Definition:** Contains the actual code.
    ```cpp
    int sum(int a, int b) { return a + b; }
    ```

---

## 3. Parameter Passing

### 3.1. Pass by Value
Default. Creates a **copy** of the argument. Changes inside function **do not affect** the original.

```cpp
void modify(int x) {
    x = 10; // Modifies local copy only
}
```

### 3.2. Pass by Reference
Uses `&`. Function works directly with the original variable. Used for modification or avoiding copying large objects.

```cpp
void modify(int& x) {
    x = 10; // Modifies original
}
```

### 3.3. Pass by const Reference
Best for passing large objects (like `std::string`, `std::vector`) that shouldn't be changed. Saves memory (no copy) and is safe (read-only).

```cpp
void printMessage(const std::string& msg) {
    std::cout << msg << std::endl;
}
```

### 3.4. Default Arguments
Values used if the caller omits the argument. Must be last in the list.

```cpp
void greet(std::string name, std::string title = "Mr./Ms.") {
    std::cout << "Hello, " << title << " " << name << std::endl;
}
// greet("John"); -> Hello, Mr./Ms. John
```

---

## 4. Return Values

### 4.1. Return by Value
Standard. Returns a copy.

### 4.2. Void Functions
Return nothing. Used for actions. Use `return;` for early exit.

### 4.3. Returning Multiple Values
C++ functions return one thing. To return more:
*   Reference output parameters.
*   `std::pair` or `std::tuple`.
*   `struct`.

```cpp
#include <tuple>
std::tuple<int, int> getCoordinates() {
    return {10, 20};
}
// Usage: auto [x, y] = getCoordinates();
```

---

## 5. Function Overloading

C++ allows multiple functions with the **same name** if parameter lists differ (count or type). Return type doesn't matter.

```cpp
int area(int side) { return side * side; } // Square
int area(int w, int h) { return w * h; }   // Rectangle
double area(double r) { return 3.14 * r * r; } // Circle
```

---

## 6. Inline Functions

The `inline` keyword suggests the compiler replace the call with the function body code. Eliminates call overhead but increases binary size. Good for small functions (getters).

```cpp
inline int max(int a, int b) {
    return (a > b) ? a : b;
}
```

---

## 7. Function Templates

For generic programming (working with different types).

```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}
// add<int>(5, 10);
// add<double>(5.5, 2.3);
```

---

## 8. Lambda Expressions - C++11

Anonymous functions defined in-place.

Syntax: `[capture](parameters) -> return_type { body }`

```cpp
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nums = {4, 1, 3};
    
    // Sort descending with lambda
    std::sort(nums.begin(), nums.end(), [](int a, int b) {
        return a > b; 
    });
}
```

---

## 9. Recursive Functions

Functions calling themselves. Must have a **base case** to stop, otherwise Stack Overflow occurs.

---

## 10. Static Variables

A `static` variable inside a function initializes once and retains value between calls.

```cpp
void counter() {
    static int count = 0;
    count++;
    std::cout << count << " ";
}
// counter(); -> 1
// counter(); -> 2
```

---

## 11. Summary

*   Functions are essential for clean code.
*   Understand Pass by Value vs Reference.
*   Modern C++ relies on Templates and Lambdas.
*   Separate declaration from definition in large projects.
