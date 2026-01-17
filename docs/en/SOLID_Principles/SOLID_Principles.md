# SOLID Principles in C++ - The Ultimate Guide

## 1. Introduction: The Art of Clean Code
SOLID represents 5 principles of object-oriented design defined by Robert Martin (Uncle Bob). They form the foundation for writing code that is easy to maintain, test, and extend over the years.

---

## 2. The Principles

### 2.1. S - Single Responsibility
A class should have only one reason to change. Do not create "god classes" that do everything.

### 2.2. O - Open/Closed
Code should be open for extension but closed for modification. Use polymorphism to add new features without altering old, working classes.

### 2.3. L - Liskov Substitution
Every derived class object should be able to replace its parent class object without breaking the program's logic. (⚠️ Be careful with inheriting `Square` from `Rectangle`).

### 2.4. I - Interface Segregation
It is better to have many small and specific interfaces rather than one massive one. Don't force classes to implement methods they don't use.

### 2.5. D - Dependency Inversion
High-level modules should not depend on low-level modules. Both should depend on abstractions. (e.g., use Dependency Injection).

---

## 3. Why are they critical for C++?
In C++, design errors are punished severely with memory leaks, cryptic crashes, and excessive compilation times. SOLID principles help reduce "spaghetti code" and make the system modular.

---
*(This document is part of the "C++ Key Concepts" course)*