# Bit Manipulation in C++ - Complete Technical Guide

## 1. Introduction: The Language of Electrons

Bit manipulations allow the C++ programmer to work directly with the smallest unit of information – the bit (0 or 1). In a world dominated by high-level abstractions, the ability to manipulate memory at the bit level remains a critical skill for systems programming, cryptography, driver development, network protocols, and game engines (where every byte counts).

---

## 2. Fundamental Operators (The Toolbox)

### 2.1. Logical Operators
*   **AND (`&`):** Result is 1 only if both input bits are 1.
    *   *Application:* **Masking** (extracting specific bits). `x & 0xFF` takes only the last byte.
*   **OR (`|`):** Result is 1 if at least one of the bits is 1.
    *   *Application:* **Setting flags**. `flags | READ_ONLY`.
*   **XOR (`^`):** Result is 1 if the bits are different.
    *   *Application:* **Toggling** and encryption. `x ^ x` is always 0.
*   **NOT (`~`):** Bitwise negation. Flips all 0s to 1s and vice versa.

### 2.2. Bitwise Shifts
*   **Left Shift (`<<`):** Moves bits to the left, filling with 0 from the right.
    *   `x << N` is equivalent to `x * 2^N`.
*   **Right Shift (`>>`):** Moves bits to the right.
    *   `x >> N` is equivalent to `x / 2^N`.
    *   ⚠️ **Warning:** For `signed` types (e.g., `int`), behavior depends on the compiler (Arithmetic Shift – preserves sign, or Logical Shift). Always use `unsigned` for bitwise operations!

---

## 3. Bit Hacks (Expert Techniques)

These are classic algorithms that avoid slow branching (`if/else`).

### 3.1. Basic Manipulation of the N-th Bit
```cpp
// Check if bit N is 1
bool is_set = (value & (1 << n)) != 0;

// Set bit N to 1
value |= (1 << n);

// Clear bit N (Set to 0)
value &= ~(1 << n);

// Toggle bit N
value ^= (1 << n);
```

### 3.2. Mathematical Tricks
*   **Even/Odd:** `(x & 1) == 0` (faster than `x % 2`).
*   **Power of Two:** `(n > 0) && ((n & (n - 1)) == 0)`.
*   **Swap without temp (XOR Swap):**
    ```cpp
    a ^= b; b ^= a; a ^= b;
    ```

---

## 4. Modern C++: The `<bit>` Library (C++20)

Before C++20, programmers used compiler-specific intrinsics (e.g., `__builtin_popcount` in GCC). Now we have a portable standard:

*   **`std::popcount(n)`:** Returns the number of bits set to 1 (Population Count / Hamming Weight).
*   **`std::countl_zero(n)`:** Counts leading zeros (Count Leading Zeros). Important for logarithmic algorithms.
*   **`std::bit_width(n)`:** The minimum number of bits to represent the number.
*   **`std::bit_cast<T>(u)`:** The fastest and safest way to type cast by reinterpreting bits (e.g., from `float` to `uint32_t` for fast inverse square root).

---

## 5. Bit-fields and std::bitset

### 5.1. C-Style Bit-fields
Allows packing data into a structure:
```cpp
struct PacketHeader {
    uint32_t version : 4;  // 4 bits
    uint32_t type    : 4;  // 4 bits
    uint32_t id      : 24; // 24 bits
}; // Total 32 bits (4 bytes)
```

### 5.2. std::bitset
A C++ class for working with an array of bits. More convenient than `int` because it supports `operator[]` and `to_string()`.
```cpp
std::bitset<8> b("10101010");
b.flip(0); // 10101011
```

---

## 6. Endianness

How is `0x12345678` stored in memory?
*   **Big-Endian:** `12 34 56 78` (Most significant byte first - Network standard).
*   **Little-Endian:** `78 56 34 12` (Least significant first - x86/ARM standard).

C++20 adds `std::endian::native` to check your system at compile time.

---

## 7. Professional Summary

1.  **Unsigned:** Always use `uint32_t` / `uint64_t` for bitmasks.
2.  **Performance:** Bitwise operations are **constant time (O(1))** and execute in 1 CPU cycle. They are faster than addition and multiplication.
3.  **Flags:** Use `enum class` with bitwise operators for type-safe flags.