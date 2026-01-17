# Bit Manipulation in C++ - The Ultimate Guide

## 1. Introduction: The Power of Bits
Bit manipulation allows working with data at the lowest level – individual bits (0 and 1). This is critical for systems programming, driver development, cryptography, and memory optimization, where every byte counts.

---

## 2. Bitwise Operators

*   **AND (`&`):** Result is 1 only if both bits are 1. (Used for checking flags).
*   **OR (`|`):** Result is 1 if at least one of the bits is 1. (Used for setting flags).
*   **XOR (`^`):** Result is 1 if bits are different. (Used for toggling states).
*   **NOT (`~`):** Inverts all bits.
*   **Shifts (`<<`, `>>`):** Move bits left or right. `x << 1` is equivalent to multiplying by 2.

---

## 3. Common Techniques (Bit Hacks)

### 3.1. Checking if a number is even
```cpp
bool is_even = (n & 1) == 0;
```

### 3.2. Checking if a number is a power of two
```cpp
bool is_power_of_two = n && !(n & (n - 1));
```

### 3.3. Working with masks (Flags)
```cpp
const unsigned int FLAG_A = 1 << 0;
const unsigned int FLAG_B = 1 << 1;

unsigned int my_flags = 0;
my_flags |= FLAG_A; // Enable
if (my_flags & FLAG_A) { /* Activated */ }
```

---

## 4. C++20 `<bit>` Library
The new standard standardizes many functions that were previously compiler-specific:
*   `std::popcount`: Counts the number of set bits (ones).
*   `std::countl_zero`: Counts leading zeros.
*   `std::bit_cast`: Safely converts bits from one type to another (e.g., `double` to `long`).

---

## 5. std::bitset
If you need an array of bits of arbitrary size, use `std::bitset<N>`. It provides a convenient interface for working with bits like an array.

---
*(This document is part of the "C++ Key Concepts" course)*