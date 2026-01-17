# Operator Overloading in C++ - The Ultimate Guide

## 1. Introduction: Natural Syntax
Operator overloading allows your own classes to use standard symbols like `+`, `-`, `*`, `==`, and `<<`. This makes the code much more readable and intuitive (e.g., `c = a + b` instead of `c = a.add(b)`).

---

## 2. Rules and Constraints
1.  **You cannot create new operators** (e.g., `**` for exponentiation).
2.  **At least one operand must be of a user-defined type.**
3.  **Precedence and associativity** of operators remain the same.
4.  Some operators **cannot** be overloaded: `.`, `.*`, `::`, `?:`, `sizeof`.

---

## 3. Member Function vs. Global Function

*   **Member Function:** The left operand is the object itself (`this`). Suitable for operators that modify the object (`+=`, `++`).
*   **Global Function (friend):** Necessary when the left operand is not of your class type (e.g., `cout << obj`).

---

## 4. Example: Stream Insertion Operator (<<)
```cpp
friend ostream& operator<<(ostream& os, const MyClass& obj) {
    os << obj.data;
    return os;
}
```

---

## 5. Assignment Operator (=)
This is one of the most important operators. If your class manages dynamic memory, you must write your own assignment operator to avoid "shallow copy" issues.

---

## 6. Increment (++)
*   **Prefix (++obj):** `MyClass& operator++()`
*   **Postfix (obj++):** `MyClass operator++(int)` (uses a dummy `int` parameter).

---
*(This document is part of the "C++ Key Concepts" course)*