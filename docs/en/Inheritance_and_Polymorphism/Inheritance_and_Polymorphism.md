# Inheritance and Polymorphism in C++ - Complete Technical Guide

## 1. Inheritance: The Hierarchy of Life

Inheritance is a mechanism that allows creating a new class (Derived) based on an existing one (Base). In professional design, this is used to model the **"Is-A"** relationship (e.g., "A Dog *is* an Animal").

⚠️ **Architectural Advice:** Beginners often overuse inheritance. If the relationship is "Has-A" (e.g., "A Car *has* an Engine"), use **Composition**, not inheritance. Composition is more flexible and reduces coupling.

---

## 2. Polymorphism: The Dynamic Face of C++

Polymorphism is the ability of objects to behave differently depending on their actual type, even when accessed through a pointer to the base class.

### 2.1. Virtual Functions
When you mark a function with `virtual` in the base class, you tell the compiler: *"Do not decide which function to call now (Static Binding). Wait until Runtime, see what the actual object type is, and call its version (Dynamic Binding)."*

### 2.2. How Does It Work Under the Hood? (The V-Table Mechanics)
This is the most important technical detail for C++ programmers.
1.  For every class that has at least one virtual function, the compiler creates a hidden static table (**V-Table**). It contains pointers to the addresses of the virtual functions.
2.  Every object of this class gets a hidden member pointer (**vptr**), which points to the V-Table of its class.
3.  When calling `ptr->draw()`, the processor does the following:
    *   Goes to the object's address.
    *   Reads `vptr`.
    *   Goes to the V-Table.
    *   Finds the address of the `draw` function.
    *   Jumps to that address (`CALL`).

This adds a small overhead (one dereference + some memory), but makes polymorphism possible.

---

## 3. Abstract Classes and Interfaces

In C++, there is no `interface` keyword (like in Java/C#). We use **Pure Virtual Functions**.

```cpp
class IShape {
public:
    virtual void draw() = 0; // Pure virtual
    virtual ~IShape() = default;
};
```
*   If a class has at least one pure virtual function, it becomes **Abstract**.
*   You cannot create instances of an abstract class (`new IShape` is an error).
*    inheritors are **obliged** to implement the function, otherwise they also remain abstract.

---

## 4. Virtual Destructor: The Safety Law

⚠️ **CRITICAL FOR INTERVIEWS AND PRACTICE:**
If a class is intended to be inherited polymorphically, its destructor **MUST** be `virtual`.

**Disaster Scenario:**
```cpp
Base* p = new Derived();
delete p; // If ~Base() is not virtual...
```
*   If `~Base()` is not virtual, the compiler calls only the `Base` destructor.
*   The `Derived` destructor is **NEVER** executed.
*   All resources (memory, files) allocated in `Derived` leak (Memory Leak).

---

## 5. Multiple Inheritance and The Diamond Problem

C++ is one of the few languages allowing a class to have two parents.
`class Liger : public Lion, public Tiger { ... };`

**The Diamond Problem:**
If `Lion` and `Tiger` inherit from a common ancestor `Animal`, then `Liger` will have **two copies** of `Animal` inside it.
*   **Solution:** Virtual inheritance (`class Lion : public virtual Animal`). This forces the compiler to merge the copies into one. It is expensive and complex – avoid it if possible.

---

## 6. Modern Tools: `override` and `final` (C++11)

These keywords are not mandatory but are a sign of professionalism.

1.  **`override`:** Placed after the function declaration in the derived class (`void draw() override`).
    *   **Benefit:** If you mess up the function name or parameters (e.g., `draaw()`), the compiler will give you an error instead of creating a new, hidden function.
2.  **`final`:**
    *   On a function: Forbids further classes from overriding it.
    *   On a class (`class A final`): Forbids inheritance from this class. Allows the compiler to perform optimizations (Devirtualization).

---

## 7. Professional Summary

1.  **Liskov Substitution Principle:** The derived class must be able to substitute the parent without breaking the program.
2.  **V-Table Cost:** Virtual functions are fast, but not free. Do not use them for functions called billions of times per second in a tight loop (unless necessary).
3.  **Destructors:** Always `virtual ~Base()`.
4.  **Composition over Inheritance:** If in doubt, choose composition.