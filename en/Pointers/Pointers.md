# Pointers in C++

## 1. Introduction

Pointers are one of the most powerful, yet potentially dangerous features of C++. Essentially, **a pointer is a variable that stores the memory address of another variable**, rather than storing the value itself.

Understanding pointers is key for:
*   Dynamic memory allocation (Heap allocation).
*   Efficient work with arrays and data structures.
*   Polymorphism.
*   Interacting with hardware and the operating system.

---

## 2. Basics and Syntax

### 2.1. Declaration and Initialization
A pointer is declared using the asterisk symbol `*`. To get the address of a variable, we use the ampersand operator `&` (address-of operator).

```cpp
int number = 42;
int* ptr = &number; // ptr stores the address of number
```

In this example:
*   `number` is a variable of type `int` with value 42.
*   `&number` returns the address of `number` in memory (e.g., `0x7ffebc`).
*   `ptr` is a variable of type `int*` (pointer to int) that stores this address.

### 2.2. Dereferencing
To access or modify the value located at the address stored in the pointer, we use the `*` operator before the pointer name. This is called **dereferencing**.

```cpp
#include <iostream>

int main() {
    int val = 100;
    int* p = &val;

    std::cout << "Address: " << p << std::endl;       // Outputs address (e.g. 0x...)
    std::cout << "Value: " << *p << std::endl;       // Outputs 100 (dereference)

    *p = 200; // Change value of val via pointer

    std::cout << "New val: " << val << std::endl;     // 200
    return 0;
}
```

---

## 3. Null Pointers

A pointer that does not point to anything valid must be marked as such.
In modern C++ (C++11 and up), always use the keyword `nullptr`.

```cpp
int* p1 = nullptr; // Recommended in C++11+
int* p2 = NULL;    // Old C-style way (still works, not recommended)
int* p3 = 0;       // Also valid, but can be ambiguous
```

**Why `nullptr`?**
`NULL` is usually just defined as `0`. This can lead to confusion in function overloading (whether you are passing integer `0` or a null pointer). `nullptr` has its own type `std::nullptr_t` and eliminates this ambiguity.

---

## 4. Pointer Arithmetic

Pointers support arithmetic operations, but they work in a specific way depending on the data type pointed to.

If you have `int* p` and execute `p + 1`, the address will not increase by 1 byte, but by the **size of the type** (here `sizeof(int)`, usually 4 bytes).

```cpp
int arr[] = {10, 20, 30};
int* ptr = arr; // Points to arr[0] (10)

std::cout << *ptr << std::endl;       // 10

ptr++; // Moves to next int (increases address by 4 bytes)
std::cout << *ptr << std::endl;       // 20

ptr += 1; // Goes to arr[2]
std::cout << *ptr << std::endl;       // 30
```

This is the basis of iterating through arrays in C style.

---

## 5. Pointers and Arrays

In C++, an array name often behaves like a pointer to its first element ("decay to pointer").

```cpp
int arr[5] = {1, 2, 3, 4, 5};
int* p = arr; // Equivalent to int* p = &arr[0];

// Index access is actually pointer arithmetic:
// arr[i] is equivalent to *(arr + i)
```

**Differences:**
*   `sizeof(arr)` returns the total size of the array in bytes.
*   `sizeof(p)` returns the size of the pointer itself (4 or 8 bytes, OS dependent).
*   A pointer can be redirected (`p = otherArr`), while the array name `arr` is a constant address and cannot be changed.

---

## 6. Void Pointers (void*)

`void*` is a special pointer type that can point to an object of **any type**. It represents a "raw" memory address without data type information.

**Limitations:**
*   Cannot be dereferenced directly (compiler doesn't know how many bytes to read).
*   Does not support arithmetic.

To use it, you must explicitly cast it to a concrete type.

```cpp
int a = 10;
void* vPtr = &a;

// std::cout << *vPtr; // ERROR!
std::cout << *(static_cast<int*>(vPtr)); // OK: 10
```

---

## 7. Dynamic Memory

This is one of the primary uses of pointers. Stack variables are destroyed automatically when they go out of scope. If we want data to live longer or determine size at runtime, we use the Heap via operators `new` and `delete`.

```cpp
// Allocate single int
int* p = new int; 
*p = 50;

// Allocate array
int size;
std::cin >> size;
int* arr = new int[size]; // Size determined at runtime

// ... use ...

// FREE MEMORY (Critically important!)
delete p;       // For single object
delete[] arr;   // For array
```

**Memory Leaks:**
If you forget to call `delete`, allocated memory remains occupied until the program ends. This is called a "memory leak" and is a serious issue in servers and long-running apps.

---

## 8. Function Pointers

C++ allows creating pointers to functions. This allows passing logic (algorithms) as parameters (callback functions).

```cpp
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }

// Type definition for easier reading
using Operation = int(*)(int, int); 

void execute(int x, int y, Operation op) {
    std::cout << "Result: " << op(x, y) << std::endl;
}

int main() {
    execute(5, 3, add); // Result: 8
    execute(5, 3, sub); // Result: 2
}
```

---

## 9. Smart Pointers - Modern C++

In modern C++ (C++11/14/17/20), using "raw" pointers (`new`/`delete`) for ownership management is considered **bad practice**. Instead, use Smart Pointers from the `<memory>` library. They automatically release memory when no longer needed (RAII idiom).

### 9.1. `std::unique_ptr`
Represents **exclusive ownership**. Cannot be copied, only moved. When `unique_ptr` goes out of scope, it automatically calls `delete` on the object.

```cpp
#include <memory>

void example() {
    std::unique_ptr<int> uPtr = std::make_unique<int>(100);
    // std::unique_ptr<int> copy = uPtr; // ERROR! Cannot copy.
    
    std::cout << *uPtr << std::endl;
} // uPtr destroyed here, memory freed automatically.
```

### 9.2. `std::shared_ptr`
Represents **shared ownership**. Uses reference counting. Memory is freed only when the last `shared_ptr` pointing to it is destroyed.

```cpp
#include <memory>

void example() {
    std::shared_ptr<int> sPtr1 = std::make_shared<int>(200);
    std::shared_ptr<int> sPtr2 = sPtr1; // Valid. Ref count becomes 2.
    
    // Both point to same location.
} // Ref count 0, memory freed.
```

### 9.3. `std::weak_ptr`
Used with `shared_ptr` to break circular dependencies. Does not own the object and does not affect the ref count.

---

## 10. Common Errors

1.  **Dangling Pointer:** Pointer pointing to freed memory.
    ```cpp
    int* p = new int(5);
    delete p;
    *p = 10; // ERROR! Undefined Behavior.
    ```
    *Solution:* Always set `p = nullptr` after `delete`.

2.  **Memory Leak:** Forgetting `delete`.
    *Solution:* Use `std::unique_ptr` or `std::shared_ptr`.

3.  **Dereferencing Uninitialized Pointer:**
    ```cpp
    int* p; // Value is random address (garbage).
    *p = 5; // ERROR! Can crash program (Segfault).
    ```
    *Solution:* Always initialize pointers (`nullptr` or valid address).

---

## 11. Double Pointer (Pointer to Pointer)

We can have a pointer pointing to another pointer.

```cpp
int a = 10;
int* ptr = &a;
int** ptrToPtr = &ptr;

std::cout << a;          // 10
std::cout << *ptr;       // 10
std::cout << **ptrToPtr; // 10
```
Often used in dynamic 2D arrays or modifying the pointer itself inside a function.

---

## 12. Const and Pointers

There is a subtle difference where the `const` keyword is placed.

1.  **Pointer to const (`const int*`):** Cannot change value pointed to, but can move pointer.
    ```cpp
    const int* p = &a;
    // *p = 5; // ERROR
    p = &b;   // OK
    ```

2.  **Const pointer (`int* const`):** Can change value, but cannot move pointer (address fixed).
    ```cpp
    int* const p = &a;
    *p = 5;   // OK
    // p = &b; // ERROR
    ```

3.  **Const pointer to const (`const int* const`):** Nothing can be changed.

---

## Conclusion

Pointers are the tool giving the C++ programmer direct control over the machine. While modern C++ encourages References and Smart Pointers for safety, deep understanding of "raw" pointers is mandatory for understanding how computers work and building efficient data structures.
