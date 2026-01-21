# Time and Filesystem in C++ - Complete Technical Guide

## 1. std::chrono: Precision and Type Safety

The `<chrono>` library (C++11) is one of the best examples of a strongly typed system in C++. It prevents errors like "added milliseconds to seconds" by making such operations impossible to compile without explicit conversion.

In old C++ (and C), time was just a `long` (timestamp). In `std::chrono`, time is an **object**.

### 1.1. The Three Pillars of Chrono

1.  **Durations:** Represents a time interval (e.g., "5 minutes").
    *   `std::chrono::seconds`, `std::chrono::milliseconds`.
    *   You can add different types: `auto total = 1min + 5s;` (automatically becomes 65s).
    *   Stored as `count` (number) and `ratio` (fractional part, e.g., 1/1000 for ms).

2.  **Clocks:** Sources of time.
    *   **`system_clock`:** "Wall Clock". Shows real astronomical time. Can be changed by the user or NTP server (i.e., can go backwards!). Not suitable for measuring intervals.
    *   **`steady_clock`:** Monotonic clock. Never goes backwards. Guaranteed to "tick" at a constant rate (e.g., time since PC boot). This is the **only correct choice** for a `Stopwatch`.
    *   **`high_resolution_clock`:** Clock with the smallest possible tick (often `steady_clock` under the hood).

3.  **Time Points:** A specific moment in time relative to an epoch.
    *   `time_point = clock::now();`
    *   `duration = end - start;`

### 1.2. Conversion (Duration Cast)
When you want to convert seconds to milliseconds, it happens automatically (no data loss).
When you want the reverse (ms -> sec), you must be explicit because there is loss (rounding).

```cpp
auto ms = 1500ms;
// auto s = ms; // ERROR!
auto s = std::chrono::duration_cast<std::chrono::seconds>(ms); // 1s
```

---

## 2. std::filesystem: Cross-Platform Navigation

Introduced in C++17, the `<filesystem>` library ends the suffering with `MAX_PATH`, `opendir`, and the difference between `/` and `\`. It provides an object-oriented interface to the file system.

### 2.1. The `std::filesystem::path` Object
This is the heart of the library. It is not just a string.
*   **Parsing:** Understands `C:\Windows\System32` and `/usr/bin` equally.
*   **Concatenation:** Uses operator `/`.
    ```cpp
    path p = "folder";
    p /= "subfolder"; // Adds the correct separator automatically
    p /= "file.txt";
    ```
*   **Methods:** `stem()` (name without extension), `extension()`, `parent_path()`.

### 2.2. Manipulation and Queries
*   `exists(p)`: Check if the file exists.
*   `is_directory(p)` / `is_regular_file(p)`.
*   `create_directory(p)`: Creates a folder (returns false if it already exists).
*   `copy(src, dest, options)`: Powerful copying (recursive, overwrite).
*   `remove(p)` / `remove_all(p)`: Deletion (all is equivalent to `rm -rf`).

### 2.3. Recursive Traversal (Directory Iterator)
Before C++17, recursive traversal required 50 lines of code. Now:

```cpp
namespace fs = std::filesystem;
for (auto const& entry : fs::recursive_directory_iterator(".")) {
    if (entry.is_regular_file() && entry.path().extension() == ".cpp") {
        std::cout << entry.file_size() << " bytes\n";
    }
}
```

---

## 3. Professional Summary

1.  **Chrono:** Use `steady_clock` for performance tests. Use `system_clock` only if you need to show a date to the user.
2.  **Filesystem:** Never manipulate paths as `std::string` (searching for commas, etc.). Always use `std::filesystem::path`.
3.  **Exceptions:** Functions in filesystem throw exceptions on error (e.g., Access Denied). They also have `nothrow` versions that accept `std::error_code&` as a parameter.

---
*(Documentation prepared for the project "Key Concepts in C++".
*Version: 3.0 - Expert Detail)*