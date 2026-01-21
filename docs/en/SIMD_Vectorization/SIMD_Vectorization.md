# SIMD and Vectorization in C++ - Complete Technical Guide

## 1. Introduction: Beyond Sequential Thinking

Traditional programming follows the **SISD** (Single Instruction, Single Data) model – one instruction processes one number. This is intuitive but slow.
**SIMD** (Single Instruction, Multiple Data) allows the processor to process an entire vector of numbers (e.g., 4, 8, or 16) with a single instruction. This is the secret behind the speed of graphics cards (GPUs), video compression, cryptography, and AI algorithms.

---

## 2. Hardware Registers (SSE, AVX, NEON)

Modern processors have special wide registers, distinct from standard `RAX/RBX`:

*   **SSE (128-bit):** Can hold 4 `float` numbers (32-bit) or 2 `double`.
*   **AVX / AVX2 (256-bit):** Holds 8 `float` or 4 `double`.
*   **AVX-512 (512-bit):** The newest standard (Intel server CPUs), processing 16 numbers simultaneously.
*   **NEON (128-bit):** The equivalent on ARM processors (Apple M1/M2, Android).

---

## 3. Auto-vectorization

The compiler (GCC/Clang/MSVC) is very smart. If you write a simple loop without dependencies, it will try to vectorize it automatically.

**Example:**
```cpp
void add_arrays(float* a, float* b, float* c, int n) {
    // #pragma omp simd // Hint to the compiler
    for (int i = 0; i < n; ++i) {
        c[i] = a[i] + b[i];
    }
}
```
If you compile with `-O3 -mavx2`, the compiler will not generate `fadd`. It will generate `vaddps` (Vector Add Packed Single), which adds 8 pairs of numbers at once.

---

## 4. Manual Vectorization (Intrinsics)

Sometimes the compiler isn't brave enough (due to pointer aliasing or complex logic). Then the programmer uses **Intrinsics** – C-functions that map directly to specific assembly instructions.

```cpp
#include <immintrin.h> // Header for AVX

void manual_avx_add(float* a, float* b, float* c) {
    // Load 8 numbers from memory into YMM register
    __m256 va = _mm256_loadu_ps(a); 
    __m256 vb = _mm256_loadu_ps(b);
    
    // Add them simultaneously
    __m256 vr = _mm256_add_ps(va, vb); 
    
    // Store result back to memory
    _mm256_storeu_ps(c, vr);
}
```

---

## 5. Obstacles to Vectorization (Data Hazards)

Why isn't all code vectorized?

1.  **Data Alignment:** For maximum speed, data in memory must start at an address that is a multiple of 32 (for AVX) or 64 (for AVX-512).
    *   Use `alignas(32) float array[1024];`.
    *   Use `std::aligned_alloc`.
2.  **Pointer Aliasing:** If the compiler fears that arrays `a` and `c` overlap, it will not vectorize because writing to `c` might change `a`.
    *   Solution: The `__restrict` keyword (or `restrict` in C).
3.  **Branching:** An `if` inside a loop is a SIMD killer. SIMD instructions work on all data equally. To simulate an `if`, the processor must calculate both branches and blend them with a mask (**Masked execution**).

---

## 6. High-Performance Libraries

Instead of writing complex and non-portable intrinsics, use abstractions:
*   **Eigen:** C++ linear algebra library. Used in TensorFlow.
*   **xsimd:** Wrapper library allowing you to write single code that compiles for both AVX and NEON.
*   **Google Highway:** Library that guarantees runtime dispatch (chooses the best instructions based on the CPU running the program).

---

## 7. Professional Summary

*   **SoA (Structure of Arrays):** Organize your data to be SIMD-friendly (flat arrays), not arrays of objects.
*   **Benchmark:** Always measure. Sometimes vector instructions are slower if data is small (due to loading overhead).
*   Vectorization can speed up your software by **4 to 16 times** without changing the algorithm, just by using the hardware correctly.

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*