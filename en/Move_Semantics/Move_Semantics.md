# Move Semantics in C++

## 1. Introduction

Allows transferring resources from temporary objects (R-values) instead of copying.

---

## 2. R-value References (`&&`)

```cpp
void f(int& x)  { cout << "L-value"; }
void f(int&& x) { cout << "R-value"; }

int main() {
    int a = 5;
    f(a); // L-value
    f(5); // R-value
}
```

---

## 3. std::move

Casts an L-value to an R-value, enabling move.

```cpp
std::string s1 = "Hello";
std::string s2 = std::move(s1); // s1 is now empty
```

---

## 4. Summary

Crucial for performance with heavy objects (`vector`, `string`).
