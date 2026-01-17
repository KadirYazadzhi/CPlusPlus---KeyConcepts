# Chrono and Filesystem in C++

## 1. std::chrono

Modern library for time measurement.

```cpp
auto start = std::chrono::steady_clock::now();
// ... work ...
auto end = std::chrono::steady_clock::now();
auto diff = end - start;
```

---

## 2. std::filesystem (C++17)

Cross-platform file and directory manipulation.

```cpp
namespace fs = std::filesystem;
if (fs::exists("config.txt")) {
    fs::copy("config.txt", "backup.txt");
}
```

---

## 3. Summary

Use `chrono` for time and `filesystem` for disk operations. Safe and portable.
