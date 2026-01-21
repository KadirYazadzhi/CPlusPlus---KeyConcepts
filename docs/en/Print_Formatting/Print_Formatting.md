# std::print and Formatting in C++ - Complete Technical Guide

## 1. Introduction: The Evolution of Output in C++

For 40 years, C++ programmers were torn between two worlds:
1.  **C-style `printf`:** Fast and compact syntax, but completely **Type Unsafe**. If you mistake `%d` for `%s`, the program crashes.
2.  **C++ `iostream` (`std::cout`):** Type-safe and extensible, but extremely **clumsy**, slow, and difficult to format. It requires manipulators like `std::setprecision`, `std::fixed`, making the code unreadable.

C++20 (with `<format>`) and C++23 (with `<print>`) introduced a revolution that combines the speed of `printf`, the safety of `iostream`, and the convenience of Python f-strings.

---

## 2. `std::format` (C++20): The Modern String

`std::format` does not print anything. It returns a `std::string` with formatted content. This makes it ideal for generating logs, error messages, or UI text.

### 2.1. Basic Syntax
It uses curly braces `{}` as placeholders.
```cpp
#include <format>
std::string msg = std::format("Hello, {}! You have {} messages.", "Ivan", 5);
```

### 2.2. Format Specifiers
Syntax: `{ [index] : [fill] [align] [width] [.precision] [type] }`

*   **Indices:** `"{1} before {0}"` -> swaps arguments.
*   **Alignment:**
    *   `{:>10}`: Right align (width 10).
    *   `{:<10}`: Left align.
    *   `{:^10}`: Center.
*   **Fill:** `{:*^10}` -> Center with asterisks (`**text***`).
*   **Numbers:**
    *   `{:.2f}`: Two decimal places (Fixed point).
    *   `{:04x}`: Hex with leading zeros (e.g., `00af`).
    *   `{:b}`: Binary format.

---

## 3. `std::print` and `std::println` (C++23)

While `std::format` allocates memory for a `string`, `std::print` writes directly to the output buffer (or file).

### 3.1. Why is it better than `std::cout`?
1.  **Less code:** No `<<` operators.
2.  **Stateless:** `std::cout` keeps state. If you change precision on `cout`, it stays changed forever, potentially breaking other parts of the program. `std::print` is stateless.
3.  **Speed:** Direct system calls (`write`), avoiding `ostream` virtual functions.

### 3.2. Unicode (UTF-8) on Windows
This is the "Killer Feature".
`std::print` guarantees that a UTF-8 string will print correctly on the console, even on Windows (where `cout` often outputs garbage due to Codepages).

```cpp
#include <print>
int main() {
    // Works perfectly everywhere!
    std::println("Hello, World! Temperature is {:.1f}°C", 23.5);
}
```

---

## 4. Extending the Library (Custom Formatters)

Professional C++ code requires the ability to print our own classes in the same way as built-in types.

### 4.1. Example for a Custom Class
```cpp
struct Point { int x, y; };

template <>
struct std::formatter<Point> {
    // 1. Parse: Reads format specs (e.g., "{:p}" or "{:j}")
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin(); // Ignoring specs for now
    }

    // 2. Format: Performs the writing
    auto format(const Point& p, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "({}, {})", p.x, p.y);
    }
};

// Usage:
std::print("Hero location: {}", Point{10, 20});
```

---

## 5. Performance: Benchmark Analysis

*   **Binary Size:** Using `iostream` adds hundreds of kilobytes to the executable due to heavy templates. `<print>` is much lighter.
*   **Compile Time:** `<format>` compiles significantly faster than `<iostream>`.
*   **Runtime:** In many tests, `std::print` is faster even than `printf` because format parsing happens at compile-time (for string literals), while `printf` does it at runtime.

---

## 6. Professional Summary

1.  **Migrate:** Start replacing `cout` and `printf` with `std::print` (if using C++23) or `fmt::print` (the `{fmt}` library, which is the basis of the standard).
2.  **Safety:** If you write `std::print("{:d}", "string")`, the code **will not compile**. This is a huge advantage over `printf`, which would crash at runtime.
3.  **Logging:** `std::format` is the ideal tool for creating structured logs.

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*