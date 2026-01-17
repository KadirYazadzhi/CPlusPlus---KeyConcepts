# Classes and Objects in C++

## 1. Introduction

Classes are the foundation of Object-Oriented Programming (OOP).
They bundle **data** and **methods**.

---

## 2. Definition

```cpp
class Car {
private:
    int speed; // Encapsulation

public:
    void accelerate() { speed += 10; }
};
```

## 3. Objects

An object is an instance of a class.

```cpp
Car myCar;
myCar.accelerate();
```

---

## 4. Constructors/Destructors

*   **Constructor:** Initializer. `Car()`.
*   **Destructor:** Cleanup. `~Car()`.

---

## 5. Summary

Use classes to model real-world concepts.
Use `private` for data, `public` for interface.
