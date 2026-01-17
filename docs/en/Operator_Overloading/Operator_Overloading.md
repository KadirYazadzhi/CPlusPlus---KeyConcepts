# Operator Overloading in C++

## 1. Introduction

Allows custom types to use operators like `+`, `-`, `<<`.

---

## 2. Syntax

```cpp
class Vector2 {
public:
    int x, y;
    Vector2 operator+(const Vector2& other) {
        return {x + other.x, y + other.y};
    }
};
```

---

## 3. Stream Operators

Must be friend functions.

```cpp
friend std::ostream& operator<<(std::ostream& os, const Vector2& v) {
    os << v.x << " " << v.y;
    return os;
}
```

---

## 4. Summary

Makes code readable. Don't abuse it.
