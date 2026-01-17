# Inheritance and Polymorphism in C++

## 1. Inheritance

Creating new classes from existing ones.

```cpp
class Animal {
public:
    virtual void speak() { cout << "Noise"; }
};

class Dog : public Animal {
public:
    void speak() override { cout << "Woof"; }
};
```

---

## 2. Polymorphism

Using a Base pointer to call Derived methods.

```cpp
Animal* a = new Dog();
a->speak(); // "Woof" (Runtime binding)
delete a;
```

**Virtual Destructor:** Essential for base classes!

---

## 3. Abstract Classes

Classes with pure virtual functions (`= 0`). Cannot be instantiated.

```cpp
class Shape {
    virtual void draw() = 0;
};
```

---

## 4. Summary

*   Inheritance = "Is-A" relationship.
*   Polymorphism requires `virtual`.
