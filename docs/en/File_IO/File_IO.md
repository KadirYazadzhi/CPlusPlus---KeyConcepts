# File I/O in C++ - Complete Technical Guide

## 1. Introduction: Streams as an Abstraction

In C++, working with external storage (disks) is abstracted through the concept of "streams". The `<fstream>` library provides classes that mimic the behavior of standard `cin` and `cout`, but directed towards the file system.
This is one of the best examples of the power of OOP design in C++: polymorphism allows us to write code that works equally well with the console, files, or strings.

---

## 2. Key Classes and Their Roles

All classes inherit from `std::ios_base`.

### 2.1. `std::ifstream` (Input File Stream)
Used exclusively for reading.
*   Has `operator>>` defined for formatted reading.
*   `get()` method for reading characters.
*   `read()` method for binary blocks.

### 2.2. `std::ofstream` (Output File Stream)
Used for creating and writing to files.
*   By default, opening it **truncates** the content of an existing file, unless specified otherwise.

### 2.3. `std::fstream` (Bidirectional)
Allows simultaneous reading and writing to the same file object. Extremely useful for low-level databases or log files that need to be read and appended to.

---

## 3. Operating Modes (Open Modes)

When opening a file (via constructor or `open()`), we pass bitwise flags:

*   **`std::ios::in`**: Open for reading (Default for `ifstream`).
*   **`std::ios::out`**: Open for writing (Default for `ofstream`).
*   **`std::ios::app` (Append):** All writes guarantee to go to the end of the file. You cannot move the write pointer back.
*   **`std::ios::ate` (At End):** Opens the file and immediately moves the pointer to the end, but allows you to move it freely afterwards.
*   **`std::ios::trunc` (Truncate):** Deletes content upon opening.
*   **`std::ios::binary`**: **Critically important!** Disables the transformation of newlines (e.g., `\n` -> `\r\n` on Windows). Mandatory for images, audio, and binary data.

---

## 4. Positioning (Seeking)

In C++, files are not read only sequentially. You can "jump" to arbitrary bytes.

*   **`seekg(offset, direction)`**: (Seek Get) Moves the read pointer.
*   **`seekp(offset, direction)`**: (Seek Put) Moves the write pointer.
*   **`tellg() / tellp()`**: Returns the current position (in bytes from the beginning).

**Directions:**
*   `std::ios::beg` (Beginning).
*   `std::ios::cur` (Current position).
*   `std::ios::end` (End).

**Example (File Size):**
```cpp
std::ifstream file("data.bin", std::ios::binary | std::ios::ate);
std::streamsize size = file.tellg(); // We are already at the end because of 'ate'
```

---

## 5. Binary Files vs Text Files

### 5.1. Text Mode
Convenient for humans. Numbers are converted to text ("123" is 3 bytes).
```cpp
file << "Score: " << 100 << std::endl;
```

### 5.2. Binary Mode
Convenient for machines. Fast and compact. Writes raw bits from RAM memory.
```cpp
int x = 12345;
file.write(reinterpret_cast<const char*>(&x), sizeof(x)); // Exactly 4 bytes
```
⚠️ **Danger:** Binary files are not portable between different processors (due to **Endianness** - Little vs Big Endian) or compilers (due to Padding in structures).

---

## 6. C++17 Filesystem (`<filesystem>`)

This is the modern way to work with the file system (creating folders, copying, iterating).
*   `std::filesystem::path`: Abstraction for path (works with both `/` and `\`).
*   `std::filesystem::exists()`: Check if a file exists.
*   `std::filesystem::directory_iterator`: Folder traversal.

```cpp
for (const auto& entry : std::filesystem::directory_iterator(".")) {
    std::cout << entry.path() << std::endl;
}
```

---

## 7. Professional Tips and Traps

1.  **Check for Success:** Always check `if (file.is_open())` or simply `if (file)`.
2.  **Buffering:** `std::endl` not only puts a new line but also **flushes the buffer**. This is slow when writing to a file. Use `\n`.
3.  **Stringstreams:** To parse complex text in memory, use `<sstream>`. It's like a file but lives in `std::string`.
4.  **Race Conditions:** The standard library does not guarantee safety if two threads write to the same file.

---

## 8. Professional Summary

*   Use **RAII** for file management (the destructor closes the file).
*   Use **`std::filesystem`** for navigation.
*   For configurations, use JSON/XML libraries, do not write your own parsers with `fstream`.
*   For huge files (GBs), consider **Memory Mapped Files** (OS-specific), as they are faster than streams.