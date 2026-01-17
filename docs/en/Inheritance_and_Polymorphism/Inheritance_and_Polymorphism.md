# Inheritance and Polymorphism in C++ - The Ultimate Guide

## 1. Inheritance: The "Is-A" Relationship
Inheritance allows the creation of a new class (derived) based on an already existing one (base). The derived class automatically receives all properties and methods of the base class, and can add new ones or override existing ones.

### 1.1. Types of Inheritance
*   **Public (most common):** Public members of the base remain public in the derived.
*   **Protected:** Members become protected.
*   **Private:** Everything becomes private.

---

## 2. Polymorphism: Many Forms
Polymorphism allows objects of different classes to be treated as objects of a common base type. This is achieved through **virtual functions**.

### 2.1. Virtual Functions
The `virtual` keyword tells the compiler: "Wait until execution (Runtime) to decide exactly which function to call."

```cpp
class Base {
public:
    virtual void show() { cout << "Base"; }
};

class Derived : public Base {
public:
    void show() override { cout << "Derived"; }
};
```

---

## 3. Abstract Classes and Interfaces
If a virtual function is defined as "pure" (`virtual void func() = 0;`), the class becomes **abstract**. You cannot create objects from it. It serves only as a foundation for other classes.

---

## 4. Virtual Destructor: The Golden Rule
⚠️ **IMPORTANT:** If a class has at least one virtual function, its destructor **must** be virtual. Otherwise, when deleting a derived object via a base pointer, you will have a memory leak.

---

## 5. Override and Final (C++11)
*   **override:** Ensures you are indeed overriding a base function (protects against typos).
*   **final:** Disallows further inheritance of the class or method.

---
*(This document is part of the "C++ Key Concepts" course)*