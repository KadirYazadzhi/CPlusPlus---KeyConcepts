# Classes and Objects in C++ - The Ultimate Guide

## 1. Introduction: The Philosophy of OOP
Object-Oriented Programming (OOP) models the real world through **objects** that contain **data** (state) and **functions** (behavior). In C++, a **class** is the blueprint (template), while an **object** is the specific instance created from that blueprint.

---

## 2. Anatomy of a Class

### 2.1. Data Members
These are the attributes of the class. They describe what the object "knows".

### 2.2. Methods (Member Functions)
These define what the object "does".

---

## 3. Encapsulation and Access Levels

This is the principle of hiding the internal implementation from the outside world.

1.  **public:** Accessible to everyone. Used for the class interface.
2.  **private:** Accessible only within the class itself. By default, everything in a C++ `class` is private.
3.  **protected:** Related to inheritance (see Topic 19).

**Best Practice:** Keep all data `private` and provide access through `getters` and `setters`.

---

## 4. Object Lifecycle

### 4.1. Constructors
Special methods called automatically when an object is created.
*   **Default Constructor:** No parameters.
*   **Parameterized Constructor:** Initializes the object with specific values.
*   **Member Initializer List:** The most efficient way to initialize in C++.
    ```cpp
    Person(string n, int a) : name(n), age(a) {} // Faster than assignment in body
    ```

### 4.2. Destructors
Called automatically when an object is destroyed. The ideal place for releasing dynamic memory or closing files.

---

## 5. The `this` Pointer
Inside every member function, there is a hidden pointer `this` that points to the current object. It is useful for resolving naming conflicts with parameters.

---

## 6. Static Members
Variables or functions marked as `static` belong to the **class** itself, not to a specific object. They are shared among all instances.

---

## 7. Difference between Struct and Class
In C++, the only difference is the default access level:
*   In a `class`, everything is **private** by default.
*   In a `struct`, everything is **public** by default.

---
*(This document is part of the "C++ Key Concepts" course)*