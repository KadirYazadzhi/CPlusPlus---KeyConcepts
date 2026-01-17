# Two Dimensional Arrays (2D Arrays) in C++

## 1. Introduction

A two-dimensional array (2D array) in C++ is the simplest form of a multidimensional array. It is best visualized as a **table** or **matrix** having rows and columns.

Technically, in C++, a 2D array is an "array of arrays". This means each element of the main array is an array itself.

---

## 2. Declaration and Initialization

### 2.1. Declaration
Syntax: `type name[rows][columns];`

```cpp
int matrix[3][4]; 
// Declares a matrix with 3 rows and 4 columns.
// Total 3 * 4 = 12 integers.
```

### 2.2. Initialization
We can initialize during declaration in several ways.

**Option 1: Nested Braces (Recommended)**
Most readable, visually separates rows.

```cpp
int matrix[3][3] = {
    {1, 2, 3},  // Row 0
    {4, 5, 6},  // Row 1
    {7, 8, 9}   // Row 2
};
```

**Option 2: Linear List**
Since memory is contiguous, we can list all elements linearly. Compiler fills row by row.

```cpp
int matrix[2][3] = {1, 2, 3, 4, 5, 6};
// Result:
// 1 2 3
// 4 5 6
```

**Option 3: Partial Initialization**

```cpp
int matrix[2][2] = {{1}, {2, 3}};
// Result:
// 1 0 (uninitialized become 0)
// 2 3
```

---

## 3. Accessing Elements

Access is via two indices: `array[row][col]`.

```cpp
int grid[3][3] = {
    {10, 20, 30},
    {40, 50, 60},
    {70, 80, 90}
};

int val = grid[1][2]; // Row 1, Col 2 -> Value 60
grid[0][0] = 999;     // Modify first element (top-left)
```

⚠️ **Important:** Indices always start at 0.
*   Rows: `0` to `rows - 1`.
*   Columns: `0` to `cols - 1`.

---

## 4. Memory Layout

In C++, 2D arrays are stored in **Row-Major Order**. This means elements of the first row are stored sequentially, immediately followed by the second row, and so on.

For `mat[2][3]`:
`{ (0,0), (0,1), (0,2), (1,0), (1,1), (1,2) }`

This is important for performance (CPU Cache Locality). Iterating row by row (inner loop over columns) is faster.

---

## 5. Iterating Through a 2D Array

Standard way is via **nested for loops**.

```cpp
#include <iostream>

int main() {
    int mat[3][2] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };

    // Outer loop: Rows
    for (int i = 0; i < 3; i++) {
        // Inner loop: Columns
        for (int j = 0; j < 2; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl; // New line after each row
    }

    return 0;
}
```

---

## 6. 2D Arrays and Functions

Passing a 2D array to a function has a quirk: **you must specify the number of columns**. Row count can be omitted, but column count is needed for address calculation arithmetic.

```cpp
const int COLS = 3;

// Correct: Columns specified
void printMatrix(int matrix[][COLS], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Wrong: void func(int matrix[][]) - Compiler doesn't know row width
```

---

## 7. Dynamic 2D Arrays

If dimensions aren't known at compile time, use dynamic memory. This involves pointers to pointers.

### 7.1. Creation
```cpp
int rows, cols;
std::cin >> rows >> cols;

// 1. Allocate array of pointers (rows)
int** matrix = new int*[rows];

// 2. Allocate memory for each row
for (int i = 0; i < rows; i++) {
    matrix[i] = new int[cols];
}

// Usage
matrix[0][0] = 5;
```

### 7.2. Deletion
Must free in reverse order.

```cpp
// 1. Free each row
for (int i = 0; i < rows; i++) {
    delete[] matrix[i];
}

// 2. Free pointer array
delete[] matrix;
```

### 7.3. Modern Alternative (std::vector)
The code above is error-prone. In modern C++, prefer `std::vector` of vectors.

```cpp
#include <vector>

int rows = 5, cols = 5;
// Create 5x5 matrix initialized to 0
std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols, 0));

matrix[2][3] = 10; // Works like array, handles memory automatically
```

---

## 8. Application: Matrix Multiplication

Classic example.

```cpp
void multiply(int A[2][2], int B[2][2], int C[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            C[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
```

---

## 9. Summary

*   2D arrays are for tabular data.
*   Memory is sequential (Row-Major).
*   Column count is mandatory when passing to functions.
*   For dynamic matrices, prefer `std::vector<std::vector<T>>` over `T**` to avoid memory leaks.
