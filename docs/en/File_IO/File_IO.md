# File I/O in C++

## 1. Introduction

Using `<fstream>` for reading/writing files.

---

## 2. Writing

```cpp
std::ofstream out("file.txt");
out << "Hello";
```

---

## 3. Reading

```cpp
std::ifstream in("file.txt");
std::string line;
while (std::getline(in, line)) { ... }
```

---

## 4. Summary

Check `is_open()` before operations.
