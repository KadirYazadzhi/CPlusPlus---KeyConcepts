# File I/O in C++ - The Ultimate Guide

## 1. Introduction: Data Streams
In C++, file interaction is handled through classes in the `<fstream>` header. They operate on the principle of "streams," similar to `std::cin` and `std::cout`.

---

## 2. Key Classes

1.  **ifstream:** (Input File Stream) For reading from a file.
2.  **ofstream:** (Output File Stream) For writing to a file.
3.  **fstream:** For both reading and writing.

---

## 3. Opening and Closing Files

### 3.1. Opening Modes
*   `std::ios::app` - Appends to the end of the file.
*   `std::ios::trunc` - Deletes old content upon opening.
*   `std::ios::binary` - Operates in binary mode.

```cpp
std::ofstream out("data.txt", std::ios::app);
if (out.is_open()) {
    out << "New line\n";
    out.close();
}
```

---

## 4. Reading Data

*   **Word by word:** Uses the `>>` operator.
*   **Line by line:** Uses `std::getline(file, line)`.
*   **Entire file:** Via iterators or `rdbuf()`.

---

## 5. Binary vs. Text Files
Text files store data as characters (human-readable). Binary files store direct bits from memory. They are smaller and faster but require the use of `read()` and `write()` methods.

```cpp
int val = 12345;
file.write(reinterpret_cast<char*>(&val), sizeof(val));
```

---

## 6. Error Handling
Always check the stream state after opening or reading:
*   `fail()`: Returns true on a serious error.
*   `eof()`: Returns true if the end of the file is reached.

---
*(This document is part of the "C++ Key Concepts" course)*