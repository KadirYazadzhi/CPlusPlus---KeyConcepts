# Operator Overloading in C++ - Complete Technical Guide

## 1. Introduction: The Syntactic Sugar of C++

Operator overloading is a powerful feature of C++ that allows your user-defined classes to behave like primitive types. Instead of writing clumsy code like `matrixA.add(matrixB).multiply(matrixC)`, you can write elegant code like `(matrixA + matrixB) * matrixC`.

This is not just for aesthetics – it is critical for writing mathematical libraries (Linear Algebra), physics engines, Smart Pointers, and iterators.

---

## 2. The Golden Rules of Design

Before writing a single line of code, you must know the limitations:
1.  **You cannot create new operators:** You cannot define `operator@`. Only existing ones (`+`, `-`, `*`, `[]`, `->`, etc.).
2.  **You cannot change precedence:** `*` will always execute before `+`, regardless of what your functions do.
3.  **You cannot change arity:** Unary `!` will always take one argument.
4.  **At least one operand must be a user-defined type:** You cannot change how `int + int` works.

---

## 3. Member Function vs Global (Friend) Function

### 3.1. Member Function
Defined inside the class.
*   **Syntax:** `Complex operator+(const Complex& other) const;`
*   **Feature:** The left operand (`*this`) is **mandatorily** an object of your class.
*   **When:** For operators that modify the object's state (`+=`, `-=`, `=`, `[]`, `->`, `()`).

### 3.2. Global Function (Non-member / Friend)
Defined outside the class (often marked as `friend` for access to `private` data).
*   **Syntax:** `friend Complex operator+(const Complex& lhs, const Complex& rhs);`
*   **Advantage:** Allows **Implicit Conversion** of the left operand.
    *   If `operator+` is a member, `c1 + 5` works, but `5 + c1` **DOES NOT work** (because `5` has no `operator+` method).
    *   If it is global, both work!

---

## 4. Special Operators: Deep Dive

### 4.1. Input/Output (`<<` and `>>`)
These must always be global `friend` functions.
*   **Why?** The left operand is `std::ostream` (`cout`), and you cannot add methods to the `std::ostream` class.
```cpp
friend std::ostream& operator<<(std::ostream& os, const MyClass& obj) {
    os << obj.data;
    return os; // Return the stream for chaining (cout << a << b)
}
```

### 4.2. Assignment (`operator=`) and Rule of Five
This is the most complex operator. It must handle:
1.  **Self-assignment check:** `a = a;` should do nothing (or at least not break the object).
2.  **Resource Management:** Must delete old memory and allocate new (or steal the resource in `move assignment`).
3.  **Return `*this`:** To allow `a = b = c;`.

### 4.3. Indexing (`operator[]`)
Usually, you need to define **two** versions:
1.  `T& operator[](size_t index);` - For writing (`vec[0] = 5`).
2.  `const T& operator[](size_t index) const;` - For reading from constant objects.

### 4.4. Functor (`operator()`)
Makes the object look like a function. This is the basis of lambda expressions and many STL algorithms.

---

## 5. Increment and Decrement (`++`, `--`)

How does the compiler distinguish prefix (`++i`) from postfix (`i++`)? Through a dummy `int` parameter.

1.  **Prefix (`++i`):**
    *   Increments and returns a reference to the new state.
    *   Fast and efficient.
    *   `Type& operator++();`

2.  **Postfix (`i++`):**
    *   Makes a copy of the old state, increments the object, returns the copy.
    *   **Slow!** Creates a temporary object.
    *   `Type operator++(int);` // int is dummy

**Tip:** Always prefer the prefix operator (`++it`) in loops.

---

## 6. Professional Summary

1.  **Semantics:** Do not overload `+` to do subtraction. Follow mathematical intuition.
2.  **Chaining:** Always return `Type&` for operators that modify the object (`+=`, `=`) to allow chaining.
3.  **Efficiency:** Operators `+`, `-`, `*` return a new object by value. Operators `+=`, `-=` return a reference. It is often more efficient to implement `+=` and then define `+` using it.
    ```cpp
    T operator+(T lhs, const T& rhs) { // lhs is a copy
        lhs += rhs;
        return lhs;
    }
    ```