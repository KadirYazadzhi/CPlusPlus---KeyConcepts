# Two-Dimensional Arrays (2D Arrays) in C++ - Complete Technical Guide

## 1. Introduction: Representing Matrices and Tables

A two-dimensional array (matrix) is the tool we use to describe data structures organized in rows and columns – like spreadsheets, images (pixels), or game boards. In C++, understanding how this data is stored in physical memory makes the difference between working software and **high-performance** software.

---

## 2. Physical Model: The Illusion of 2D

⚠️ **KEY CONCEPT:** Computer memory (RAM) is linear (one-dimensional). It is simply a long strip of bytes with addresses from 0 to N.

A two-dimensional array does not exist as a physical "table" or "grid" in memory. C++ arranges elements linearly using the **Row-Major Order** model.

If we have `int a[2][3]` (2 rows, 3 columns), in memory they look like this:
`[0,0], [0,1], [0,2], [1,0], [1,1], [1,2]`

First, all elements of the first row are written, then all of the second, and so on. This is different from Fortran or MATLAB, which use Column-Major Order.

### 2.1. The Indexing Mapping Formula
When you write `matrix[i][j]`, the compiler transforms these two coordinates into a single linear address:

```text
Linear_Index = (i * Number_Of_Columns) + j
Address = Base_Address + (Linear_Index * sizeof(Type))
```

*   `i` is the row index.
*   `j` is the column index.
*   `Number_Of_Columns` is the matrix width (stride).

This explains why when passing an array to a function, you **must** specify the number of columns. Without this number, the compiler doesn't know how big a "row" is and cannot calculate where the next one begins (`i * Number_Of_Columns`).

---

## 3. Declaration and Initialization (All Variants)

### 3.1. Static Matrix (Stack)
Everything is in one block of memory. The fastest option.

```cpp
int matrix[3][3] = {
    {1, 2, 3}, // Row 0
    {4, 5, 6}, // Row 1
    {7, 8, 9}  // Row 2
};

// Partial initialization
int grid[5][5] = { {1, 2}, {3} }; // The rest become 0
```

### 3.2. Dynamic Matrix (Heap) - Array of Pointers Variant
This is the classic but **dangerous and slow** way ("Jagged Array").

```cpp
int rows = 3, cols = 4;
int** matrix = new int*[rows]; // 1. Array of pointers (backbone)
for(int i = 0; i < rows; ++i) {
    matrix[i] = new int[cols]; // 2. Allocate each row separately
}
```

*   **Problem 1 (Fragmentation):** Each row can be anywhere in memory. No guarantee of contiguity.
*   **Problem 2 (Cache Misses):** Jumping from row to row kills performance.
*   **Problem 3 (Memory Leak):** Requires a complex loop for deallocation:
    ```cpp
    for(int i = 0; i < rows; ++i) delete[] matrix[i];
    delete[] matrix;
    ```

### 3.3. Dynamic Matrix - Professional Approach (Contiguous Block)
Allocate everything at once to be fast.

```cpp
int* flatMatrix = new int[rows * cols];
// Access: flatMatrix[i * cols + j]
```

---

## 4. Optimization: Traversal and Cache Locality

The way you traverse the matrix can change your code speed **drastically** (from 2 to 20 times slower).

### 4.1. Cache-friendly (Correct)
Always iterate the way memory is laid out – row by row.

```cpp
// i = row, j = column
for(int i = 0; i < rows; ++i) {
    for(int j = 0; j < cols; ++j) {
        sum += matrix[i][j]; 
    }
}
```
*   **Why?** The processor loads part of the row into the cache. Subsequent iterations of `j` read directly from L1 cache (instantaneously).

### 4.2. Cache-hostile (Wrong)
Iterating by columns is a performance disaster.

```cpp
for(int j = 0; j < cols; ++j) {     // Outer loop is columns
    for(int i = 0; i < rows; ++i) { // Jumping between rows
        sum += matrix[i][j]; 
    }
}
```
*   **Why?** In each iteration of the inner loop, we jump to address `+ width`. This is likely outside the current cache line. We cause a **Cache Miss** at almost every step, forcing the CPU to wait for slow RAM.

---

## 5. Professional Solution: Flattening and `std::vector`

In modern C++ (Game Dev, High Frequency Trading), we avoid `int**`.
We use wrapper classes or "splatting" (flattening).

### 5.1. 1D Vector as 2D Matrix
```cpp
class Matrix {
    std::vector<int> data;
    int cols;
public:
    Matrix(int r, int c) : data(r * c), cols(c) {}
    
    int& at(int r, int c) {
        return data[r * cols + c];
    }
};
```
**Advantages:**
1.  **Single allocation:** Only one `new` (hidden inside the vector).
2.  **RAII:** Memory is cleaned up automatically.
3.  **Speed:** Maximum cache locality.

---

## 6. Passing 2D Arrays to Functions

If using static arrays, the syntax is specific.

```cpp
// We must know all dimensions except the first one!
void process(int mat[][10], int rows); 

// Or with template to catch both sizes:
template <size_t R, size_t C>
void process(int (&mat)[R][C]) {
    // R and C are constants here
}
```

---

## 7. Multidimensional Arrays (3D, 4D...)
The logic is the same. `int space[X][Y][Z]` unrolls as:
`Address = Z + Width*Y + Width*Height*X ...`
The more dimensions, the more complex the arithmetic and the more important cache locality becomes.

---

## 8. Summary

1.  **Memory is linear.** 2D arrays are an abstraction.
2.  **Always iterate by rows** (the rightmost dimension should change fastest in the inner loop).
3.  **Avoid `int**`** (array of pointers) due to fragmentation.
4.  Use **Flattening** (1D array with arithmetic) for serious tasks.
5.  Remember: **Strides** are expensive, sequential access is cheap.