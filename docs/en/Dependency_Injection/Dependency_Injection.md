# Dependency Injection and Inversion of Control (IoC) - Complete Technical Guide

## 1. Introduction: The Problem with "Hard" Dependencies

In poorly designed code, classes create their own dependencies.
Example: Class `Car` internally creates `new V8Engine()`.
This leads to "Tightly Coupled" code:
*   **Impossible Testing:** You cannot test `Car` without the real `V8Engine` (which might be slow or require hardware).
*   **Hard to Change:** If you want an electric engine, you have to rewrite `Car`.

**Inversion of Control (IoC)** is the principle of transferring control over object creation to an external system (Main, Framework, or Container).

---

## 2. Dependency Injection (DI): The Mechanism

DI is the specific way to apply IoC. Instead of the class looking for its dependencies, they are **given** to it.

### 2.1. Constructor Injection (The Gold Standard)
The object declares its dependencies as parameters in the constructor.
*   **Advantage:** The object cannot exist in an invalid state (without an engine).
*   **Interfaces:** Dependencies are abstract classes (`IEngine`), not concrete ones (`V8Engine`).

```cpp
class IEngine { virtual void start() = 0; };

class Car {
    std::shared_ptr<IEngine> engine; // We keep the abstraction
public:
    // Injection via constructor
    Car(std::shared_ptr<IEngine> e) : engine(e) {
        if (!engine) throw std::invalid_argument("Engine cannot be null");
    }
};
```

### 2.2. Setter Injection
Dependencies are set via a method `setEngine()`.
*   **When:** If the dependency is optional or can be changed at runtime.
*   **Risk:** The object might be used before it is fully initialized.

---

## 3. Service Locator: The Anti-Pattern?

An alternative to DI is the **Service Locator**. It is a global registry from which everyone asks for what they need.
```cpp
void Car::start() {
    auto engine = ServiceLocator::get<IEngine>(); // Car looks for it itself
    engine->start();
}
```
*   **Problem:** Hides dependencies. When you look at `new Car()`, you don't know that it secretly requires `IEngine` from the locator. This makes testing difficult.
*   **Conclusion:** Avoid it, except in very old legacy systems.

---

## 4. DI Containers for C++

In small projects (`main.cpp`), you can wire everything manually ("Pure DI").
In large projects (100+ classes), manually wiring `new A(new B(new C()))` becomes a nightmare. Here come the containers.

### 4.1. Google Fruit
Uses metaprogramming to check the dependency graph at compile time. If you forgot to register `IEngine`, the code won't compile.

### 4.2. Boost.DI
A modern, header-only library with zero overhead.
```cpp
auto injector = di::make_injector(
    di::bind<IEngine>.to<ElectricEngine>() // Configuration
);
auto car = injector.create<Car>(); // Automatically creates Engine and Car
```

---

## 5. Mocking and Testing

DI is a mandatory requirement for Unit Testing.
```cpp
class MockEngine : public IEngine {
    MOCK_METHOD(void, start, (), (override));
};

TEST(CarTest, StartsEngine) {
    auto mock = std::make_shared<MockEngine>();
    EXPECT_CALL(*mock, start()); // We expect Car to call start()
    
    Car car(mock); // Inject the fake engine
    car.drive();
}
```

---

## 6. Professional Summary

1.  **DIP (Dependency Inversion Principle):** High-level classes should not depend on low-level classes. Both should depend on abstractions.
2.  **Lifetime:** Be careful who owns the injected object. `std::shared_ptr` is safest, but `T&` (reference) is faster if you are sure the dependency outlives the object.
3.  **Composition Root:** All object wiring should happen in one single place (at the beginning of `main()`).

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*