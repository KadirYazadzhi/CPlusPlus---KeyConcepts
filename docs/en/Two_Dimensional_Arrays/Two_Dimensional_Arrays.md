# Two Dimensional Arrays (2D Arrays) in C++ - The Ultimate Technical Guide

## 1. Introduction: Representing Matrices
A two-dimensional array (matrix) is the tool used to describe structures composed of rows and columns. In C++, understanding how this data is stored in physical memory is the difference between working software and **high-performance** software.

---

## 2. The "Row-Major Order" Model (Row after Row)

⚠️ **KEY CONCEPT:** Computer memory is linear (one-dimensional). A 2D array is not a physical table in the RAM. C++ arranges elements one after another, row by row.

If we have `int a[2][3]`, in memory they look like this:
`[row0,col0], [row0,col1], [row0,col2], [row1,col0], [row1,col1], [row1,col2]`

### 2.1. Mathematical Access Formula
To find element `a[i][j]`, the compiler does not search in a table. It performs a single arithmetic operation:
`Address = Start + (i * Column_Count + j) * sizeof(Type)`

This explains why, when passing an array to a function, you **must** specify the number of columns. Without this number, the compiler does not know how large a "row" is and cannot "jump" to the next one.

---

## 3. Declaration and Initialization (All Variants)

### 3.1. Static (Stack)
```cpp
int matrix[3][3] = {
    {1, 2, 3}, // Row 0
    {4, 5, 6}, // Row 1
    {7, 8, 9}  // Row 2
};
```

### 3.2. Dynamic (Heap) - Complex Variant
For a truly dynamic matrix, we use a pointer to an array of pointers:
```cpp
int** matrix = new int*[rows]; // Array of pointers to rows
for(int i = 0; i < rows; ++i) {
    matrix[i] = new int[cols]; // Allocation of each row
}

// Deallocation (In reverse order!)
for(int i = 0; i < rows; ++i) delete[] matrix[i];
delete[] matrix;
```
⚠️ **Problem:** This method is **slow** because the rows are scattered in memory, killing the CPU cache performance.

---

## 4. Optimization: Traversal and Cache Locality

The way you traverse a matrix can change the speed of your code **hundreds of times over**.

### 4.1. Cache-friendly (Fast)
Always iterate over rows first, then columns:
```cpp
for(int i = 0; i < rows; ++i)
    for(int j = 0; j < cols; ++j)
        sum += matrix[i][j]; // Reading memory sequentially.
```

### 4.2. Cache-hostile (Slow)
Iterating by columns (outer loop over columns) is disastrous for speed:
```cpp
for(int j = 0; j < cols; ++j)
    for(int i = 0; i < rows; ++i)
        sum += matrix[i][j]; // Jumping across memory. The CPU waits for RAM.
```

---

## 5. Professional Solution: Flattening (Flat Matrix)
In high-performance systems (Games, AI), `int**` is rarely used. Instead, a single 1D array is used and treated as a 2D array:
```cpp
std::vector<int> flat_matrix(rows * cols);
// Access (row i, column j):
int value = flat_matrix[i * cols + j];
```
**Why?** Only one allocation, contiguous memory, maximum speed.

---

## 6. 2D Arrays and Functions
When passing a 2D array to a function, you must specify the size of the second dimension (columns).
```cpp
void print(int arr[][3], int rows); // OK
// void print(int arr[][], int rows); // ERROR!
```

---

## 7. Summary
*   C++ matrices are **linear** under the hood.
*   **Traversal order** is critical for speed.
*   Use **Flattening** for professional applications.
*   Always prefer `std::vector<std::vector<T>>` over raw pointers unless performance is the ultimate priority.

---
*Documentation prepared for the "C++ Key Concepts" project.*
*Version: 3.0 - Encyclopedic*
