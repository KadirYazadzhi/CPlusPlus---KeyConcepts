# SOLID Principles in C++ - Complete Technical Guide

## 1. Introduction: Philosophy of Sustainable Code

Designing a large software system in C++ is a challenge. It's easy to write code that works today. It's hard to write code that will work 5 years from now, after 10 other programmers have added new features.

**SOLID** are the five fundamental laws of object-oriented design, formulated by Robert Martin (Uncle Bob). They help us avoid "Code Rot":
1.  **Rigidity:** The code is hard to change.
2.  **Fragility:** A change in one place breaks something in a completely different place.
3.  **Immobility:** The code cannot be reused.

---

## 2. Breakdown of Principles

### 2.1. S - Single Responsibility
**"A class should have one, and only one, reason to change."**

**Violation:** A `Player` class that:
1.  Keeps health and coordinates.
2.  Draws the sprite on screen (`Render()`).
3.  Saves state to a file (`Save()`).

If we change the graphics library, we change `Player`. If we change the file format, we change `Player`. This is a **God Object**.

**Solution:**
*   `Player`: Only data and game logic.
*   `PlayerRenderer`: Knows how to draw.
*   `PlayerSerializer`: Knows how to save.

### 2.2. O - Open/Closed
**"Software entities should be open for extension, but closed for modification."**

The idea is to add new features by **adding new code**, not by changing old code.

**Violation:**
```cpp
void drawAll(vector<Shape*> shapes) {
    for (auto s : shapes) {
        if (s->type == CIRCLE) drawCircle(s);
        else if (s->type == SQUARE) drawSquare(s); // Must touch here for every new shape!
    }
}
```

**Solution (Polymorphism):**
Make `draw()` a virtual function. Adding `class Triangle` does not require changing `drawAll`.

### 2.3. L - Liskov Substitution
**"Objects of a superclass shall be replaceable with objects of its subclasses without breaking the application."**

This is the mathematical definition of inheritance.
**Classic Example:** The Square and Rectangle problem.
*   In geometry, a square is a rectangle.
*   In programming, if `Square` inherits `Rectangle` and `setWidth()` changes height too (to remain square), you break the expectations of a user who holds a pointer to `Rectangle` and expects width and height to be independent.

### 2.4. I - Interface Segregation
**"Many client-specific interfaces are better than one general-purpose interface."**

Clients should not depend on methods they do not use.
**Violation:** Interface `IMachine` with methods `Print()`, `Scan()`, `Fax()`.
If you have a simple printer, it must implement `Scan()` and `Fax()` as empty or throwing error. This is bad.

**Solution:** Split into `IPrinter`, `IScanner`, `IFax`. The multifunctional machine will inherit all three.

### 2.5. D - Dependency Inversion
**"Depend upon abstractions, [not] concretions."**

High-level modules (Business Logic) should not depend on low-level modules (Database, UI). Both should depend on abstractions (Interfaces).

**Violation:**
```cpp
class Game {
    MySQLDatabase db; // Hard dependency! Cannot test without a real DB.
};
```

**Solution (Dependency Injection):**
```cpp
class Game {
    IDatabase* db; // Abstraction
public:
    Game(IDatabase* _db) : db(_db) {} // Injection
};
```

---

## 3. Benefits for Professionals

1.  **Testability:** DIP allows using **Mock objects** for Unit tests.
2.  **Parallel Work:** Team A works on the interface, Team B on the implementation.
3.  **Refactoring:** Adhering to SRP makes classes small and easy to understand.

---

## 4. Professional Summary

*   SOLID is not a dogma, but a **diagnostic tool**. If your code is hard to test, you are likely violating DIP or SRP.
*   If you have too many `if/else` checks for object type, you are violating OCP.
*   Good design takes more time initially but saves thousands of hours in maintenance.

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*