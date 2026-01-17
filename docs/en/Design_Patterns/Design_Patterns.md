# Design Patterns in C++ - The Ultimate Guide

## 1. Introduction: The Language of Software Architecture
Design patterns are established, proven solutions to common problems in software design. They are not ready-made code but abstract models that help in building flexible and maintainable systems.

---

## 2. Classification of Patterns (GoF)

### 2.1. Creational
Focus on the mechanism of object creation.
*   **Singleton:** Ensures only one instance of a class exists.
*   **Factory Method:** Defines an interface for creating objects but lets subclasses decide the type.
*   **Builder:** For constructing complex objects step by step.

### 2.2. Structural
Concerned with the composition of classes and objects.
*   **Adapter:** Allows incompatible interfaces to work together.
*   **Decorator:** Adds new functionality to an object dynamically.
*   **Facade:** Provides a simple interface to a complex system of classes.

### 2.3. Behavioral
Focus on communication between objects.
*   **Observer:** A mechanism to notify multiple objects about changes in another object.
*   **Strategy:** Defines a family of algorithms and makes them easily interchangeable.
*   **Command:** Encapsulates a request as an object.

---

## 3. C++ Specific Patterns

### 3.1. RAII (Resource Acquisition Is Initialization)
The most important pattern in C++. Resources are acquired in the constructor and released in the destructor. This guarantees no leaks even in the presence of exceptions.

### 3.2. CRTP (Curiously Recurring Template Pattern)
A technique for achieving static polymorphism (at compile-time), which is faster than virtual functions.

---

## 4. Why Use Them?
1.  **Reusability:** You don't reinvent the wheel.
2.  **Common Language:** Developers understand each other better ("Use a Factory here").
3.  **Flexibility:** Systems become easier to change without breaking legacy code (Open/Closed Principle).

---
*(This document is part of the "C++ Key Concepts" course)*