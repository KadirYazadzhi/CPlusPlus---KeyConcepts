# References in C++

## 1. Ontology and Internal Architecture

### 1.1. Definition according to the Standard

According to the C++ standard, a reference is not an object. It is an **alias** (another name) for an existing object or function. Since it is not an object, fundamentally it has no address.

* **Conceptually:** A reference is an entry in the compiler's symbol tables that binds to the same memory address as the original variable.

* **Physically (Implementation detail):** In most cases, when a reference must exist at runtime (e.g., as a class member or function parameter that is not inlined), the compiler implements it as a **constant pointer** (`T* const`).

### 1.2. The Memory Paradox

One of the biggest misconceptions is related to the size of a reference.

```cpp
struct S {
    char& r; // In memory this takes 8 bytes (on 64-bit OS), exactly like a pointer.
};

char c = 'a';
char& ref = c;

// sizeof(ref) returns 1 (the size of char), not 8!

```

**Explanation:** The `sizeof` operator always returns the size of the *referenced type*, not the reference itself. There is no legal way in C++ to get the "size of the reference" or the "address of the reference" directly. Taking the address (`&ref`) returns the address of the object `c`.

## 2. Value Categories and References

To understand references in depth, we must understand the taxonomy of values in C++17/20:

1. **lvalue (locator value):** An object that has an identity (name) and an address in memory.
2. **prvalue (pure rvalue):** A temporary value that has no identity (e.g., literal `5`, result of `x + y`).
3. **xvalue (eXpiring value):** An object that has identity but is marked as "ready to move" (e.g., result of `std::move(x)`).
4. **glvalue (generalized lvalue):** An object with identity (lvalue + xvalue).
5. **rvalue:** An object from which we can "steal" resources (prvalue + xvalue).

### 2.1. L-value References (`T&`)

Can bind only to **glvalue** (things with an address).

* **Usage:** Modification of existing objects.

### 2.2. Const L-value References (`const T&`)

Can bind to **everything** (glvalue, prvalue, xvalue).

* **"Lifetime Extension" Mechanism:** When a `const T&` binds to a temporary object (prvalue), the life of that temporary object is extended to the end of the reference's scope. This is done via a hidden variable on the stack.

```cpp
const int& r = 5 + 5; 
// Compiler generates:
// int __temp = 10;
// const int& r = __temp;

```

### 2.3. R-value References (`T&&`)

Introduced in C++11, they can bind only to **rvalue** (prvalue and xvalue).

* **Purpose:** To detect objects that are about to be destroyed in order to steal their resources (Move Semantics).

## 3. Reference Collapsing and Forwarding References

This is one of the most complex topics in template metaprogramming.

### 3.1. Collapsing Rules

In C++, it is forbidden to define a reference to a reference directly (`int& & x` is an error). But in templates or `typedef`/`using`, this often happens automatically. The compiler applies the following rules (Reference collapsing):

* `T&` + `&`   **`T&`**
* `T&` + `&&`  **`T&`**
* `T&&` + `&`  **`T&`**
* `T&&` + `&&`  **`T&&`**

**Rule:** If there is at least one `&`, the result is an l-value reference. Only `&&` + `&&` yields an r-value reference.

### 3.2. Universal References (Forwarding References)

A term coined by Scott Meyers, officially called "Forwarding references" in the standard.

The syntax `T&&` in a template function does **NOT always** mean r-value reference.

```cpp
template<typename T>
void wrapper(T&& arg) { ... }

```

If `T` needs to be deduced (deduced type):

1. If we pass an **lvalue** (e.g., `int x`), `T` is deduced as `int&`. Then `arg` becomes `int& &&`, which collapses to **`int&`**.
2. If we pass an **rvalue** (e.g., `5`), `T` is deduced as `int`. Then `arg` becomes **`int&&`**.

This allows `std::forward<T>` to work: it preserves the value category (lvalue or rvalue) when passing it on.

## 4. Deep Dissection of std::move and std::forward

### 4.1. std::move is a lie

`std::move` moves nothing. It does not generate machine code to move memory.

* **What it does:** It is simply a `static_cast` that turns any argument into an **xvalue** (r-value reference). This tells the compiler: *"Treat this object as temporary, you can use its move constructor"*.

**Implementation (simplified):**

```cpp
template<typename T>
typename std::remove_reference<T>::type&& move(T&& t) noexcept {
    return static_cast<typename std::remove_reference<T>::type&&>(t);
}

```

### 4.2. std::forward - The Conditional Cast

Used together with Forwarding References. It says: *"Cast to r-value only if the original argument was an r-value"*.

## 5. References and Type Deduction (auto & decltype)

Rules for `auto` are critical when working with references.

```cpp
int x = 10;
int& rx = x;

auto a = rx;  // a is int (copy), reference-ness is lost!
auto& b = rx; // b is int& (new reference to x)

const int cx = 20;
auto c = cx;  // c is int (const is lost during copy)
const auto& d = cx; // d is const int&

```

**decltype** works differently:

* `decltype(var)` returns the exact type of the variable.
* `decltype(expr)` (if it is an expression):
* If expression returns lvalue  adds `&` (e.g., `decltype((x))` is `int&`).
* If expression returns prvalue  pure type.
* If expression returns xvalue  adds `&&`.



## 6. Special Cases and "Undefined Behavior" (UB)

### 6.1. Dangling References

This is the most common source of bugs.

```cpp
const int& getBadRef() {
    int local = 5;
    return local; // UB! local is destroyed, we return an address to the stack which is now invalid.
}

```

### 6.2. Reference Slicing

In polymorphism, if you assign an object of a derived class to a variable of a base class (not a reference), "Slicing" occurs. If you use a reference, polymorphism works.

```cpp
class Base { ... };
class Derived : public Base { ... };

Derived d;
Base b = d;  // Slicing! The Derived part is sliced off. Only Base part is copied.
Base& br = d; // No Slicing. br points to the full object d. V-table works.

```

### 6.3. Null Reference?

In the C++ standard, **a reference cannot be null**. There is no syntax for `int& r = nullptr`.
However, through evil code (UB), it can be achieved:

```cpp
int* p = nullptr;
int& r = *p; // Undefined Behavior, but technically creates a "null reference".
             // Any attempt to use 'r' will crash the program.

```

## 7. std::reference_wrapper`<T>`

References have disadvantages: they are not CopyAssignable (cannot be "re-seated") and cannot be in arrays.
`std::reference_wrapper` (from `<functional>`) solves this. It is an object that:

1. Holds a pointer internally.
2. Has a conversion operator to `T&`.
3. Can be re-seated.
4. Can be put in `std::vector<std::reference_wrapper<T>>`.

## 8. Assembly Analysis (x86-64)

Let's compare a pointer and a reference at the instruction level.

**C++:**

```cpp
void by_ptr(int* p) { *p = 10; }
void by_ref(int& r) { r = 10; }

```

**GCC Output (-O2):**

```assembly
; void by_ptr(int* p)
by_ptr(int*):
    mov DWORD PTR [rdi], 10  ; rdi holds the address, writing 10 directly to memory
    ret

; void by_ref(int& r)
by_ref(int&):
    mov DWORD PTR [rdi], 10  ; Absolutely the same code!
    ret

```

**Conclusion:** For the processor, there is no difference. A reference is **syntactic sugar** with stricter safety rules at the compiler level (type safety check), but generates identical machine code as a pointer.

## 9. Decision Table

| **Situation** | **Decision** | **Why?** |
| --- | --- | --- |
| **Built-in type (int, bool, double)** | Pass by Value (`int x`) | Reference is a pointer (8 bytes), `int` is 4 bytes. Indirection is slower. |
| **Object (std::string, vector, class)** | `const T&` | Avoids deep copying. |
| **Need to modify the object** | `T&` | Allows output parameters. |
| **Object might be missing (optional)** | `T*` (or `std::optional`) | Reference cannot be null. |
| **Move Constructor / Setter** | `T&&` | To steal resources. |
| **Templates / Forwarding** | `T&&` (Universal Ref) | For Perfect Forwarding to work. |
