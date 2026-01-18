# Arrays in C++ - The Ultimate Technical Guide

## 1. Concept: The Foundation of Sequential Data
An array is the most primitive and, simultaneously, the most efficient data structure. It represents a **contiguous** block of memory consisting of elements of the same type. This continuity is the key to its performance.

---

## 2. Memory Anatomy (Physical Layer)

### 2.1. Address Calculation (O(1) Access)
Accessing an element by index is not a search. It is pure mathematics. The compiler calculates the address of `arr[i]` using:
`Address = BaseAddress + (index * sizeof(Type))`
This explains why indexing starts at **0** – zero is the offset from the beginning.

### 2.2. Cache Locality
CPUs perform best with arrays. When you load `arr[0]`, the hardware automatically fetches the entire **Cache Line** (usually 64 bytes) into the L1 cache. This means `arr[1]`, `arr[2]`, etc., are already inside the processor before you even request them. This makes arrays thousands of times faster than linked lists for large datasets.

---

## 3. Static vs. Dynamic Arrays

### 3.1. Static Arrays (Stack)
Size must be known at compile time.
```cpp
constexpr int SIZE = 100;
int stackArr[SIZE]; // Allocated on the Stack - lightning fast but limited in size.
```

### 3.2. Dynamic Arrays (Heap)
Size is determined at runtime.
```cpp
int n;
std::cin >> n;
int* heapArr = new int[n]; // Allocated on the Heap - slower but with large capacity.
delete[] heapArr; // ⚠️ ALWAYS use delete[] for arrays!
```

---

## 4. Arrays and Pointers (The Decay Rule)
In C++, the name of the array automatically "decays" to a pointer to its first element in almost all cases.
*   `sizeof(arr)` returns the total size of the array in bytes (only for static arrays).
*   When passed to a function, an array **always** becomes a pointer and loses its size information.

---

## 5. Modern Alternatives (Modern C++)

### 5.1. `std::array<T, N>` (C++11)
A wrapper around the C-array that is not slower but adds safety:
*   Knows its size (`.size()`).
*   Supports iterators.
*   Does not decay automatically to a pointer.

### 5.2. `std::vector<T>`
A dynamic array that manages its own memory. In 99.9% of professional projects, this is the correct choice.

---

## 6. Low-level Pitfalls
1.  **Buffer Overflow:** Reading/writing outside boundaries. C++ does not check bounds for speed, so it is your responsibility.
2.  **Pointer Aliasing:** When two pointers point to parts of the same array, which can prevent compiler optimizations.
3.  **Forgotten `[]` during delete:** Using `delete ptr` instead of `delete[] ptr` results in the destructor being called only for the first element.

---

## 7. Professional Summary
*   Use **Static Arrays** for small, fixed data.
*   Use **`std::vector`** for everything else.
*   Always pass the array size along with the pointer (if not using STL).

---
*(Documentation updated for C++17/20/23 standards)*
