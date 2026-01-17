# Time and Filesystem in C++ - The Ultimate Guide

## 1. std::chrono: Working with Time
The `<chrono>` library (C++11/17/20) is the standard for precision time management. It is based on strong typing to prevent errors like "adding seconds to milliseconds."

### 1.1. Core Concepts
*   **Duration:** A span of time (e.g., 5 minutes).
*   **Time Point:** A specific moment (e.g., "now").
*   **Clock:** A source of time (`steady_clock` for intervals, `system_clock` for calendar time).

### 1.2. Example: Performance Measurement
```cpp
auto start = std::chrono::high_resolution_clock::now();
// ... code ...
auto end = std::chrono::high_resolution_clock::now();
std::chrono::duration<double, std::milli> ms = end - start;
```

---

## 2. std::filesystem: Directories and Files
Introduced in C++17, `<filesystem>` provides a cross-platform way to interact with the disk.

### 2.1. Paths and Navigation
*   `path`: An object representing a filesystem path.
*   `exists()`: Checks if a file/folder exists.
*   `create_directory()`: Creates a folder.

### 2.2. Directory Iteration
You can easily loop through all files in a folder:
```cpp
for (auto const& entry : std::filesystem::directory_iterator("src")) {
    std::cout << entry.path() << "\n";
}
```

---

## 3. Why are they important?
1.  **Portability:** Code works identically on Windows and Linux.
2.  **Safety:** Automatically handles path differences (`/` vs `\`).
3.  **Modernity:** Replaces old and unsafe C functions like `time()` and `dirent.h`.

---
*(This document is part of the "C++ Key Concepts" course)*