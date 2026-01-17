# Arrays in C++

## 1. Introduction

An array is one of the most fundamental data structures in programming. It represents a **collection of elements of the same type, stored sequentially in memory**.

In C++, arrays have a **fixed size**, meaning the number of elements must be known at compile time (for static arrays) and cannot change during program execution.

### Key Characteristics:
*   **Homogeneity:** All elements are of the same type (e.g., only `int` or only `double`).
*   **Contiguous Memory:** Elements are stored one after another, ensuring extremely fast access.
*   **Random Access:** Access to any element takes constant time O(1) via its index.

---

## 2. Declaration and Initialization

### 2.1. Declaration
Syntax is `type name[size];`.

```cpp
int numbers[5]; // Declares an array of 5 integers
// Values are currently undefined (garbage values)!
```

### 2.2. Initialization
We can assign initial values during declaration.

```cpp
// Full initialization
int arr1[5] = {10, 20, 30, 40, 50};

// Partial initialization (rest become 0)
int arr2[5] = {1, 2}; // {1, 2, 0, 0, 0}

// Automatic size deduction
int arr3[] = {1, 2, 3}; // Size automatically becomes 3

// Initialize with zeros (C++11)
int arr4[5] = {}; // {0, 0, 0, 0, 0}
```

---

## 3. Accessing Elements

Elements are accessed via **index** inside square brackets `[]`.
**Important:** In C++, indexing starts at **0**.

```cpp
int nums[3] = {100, 200, 300};

// Read
std::cout << nums[0]; // 100 (first element)
std::cout << nums[2]; // 300 (last element)

// Write
nums[1] = 500; // Changes second element to 500
```

⚠️ **Warning:** C++ **DOES NOT** perform bounds checking.
If you try to access `nums[5]`, the program will read/write memory it doesn't own, leading to **Undefined Behavior** or a crash (Segfault).

---

## 4. Arrays in Memory

Since arrays are contiguous, the address of element `i` is easily calculated:
`Address[i] = Start_Address + (i * Type_Size)`

Example with `int arr[3]` (assuming `sizeof(int) = 4` bytes):
*   `arr[0]` is at address `0x1000`
*   `arr[1]` is at address `0x1004`
*   `arr[2]` is at address `0x1008`

This explains why access is so fast.

---

## 5. Iterating Through Arrays

Most common way to work with arrays is via loops.

### 5.1. Classic `for` loop
Gives access to the index.

```cpp
int arr[5] = {10, 20, 30, 40, 50};

for (int i = 0; i < 5; i++) {
    std::cout << "Element at index " << i << ": " << arr[i] << std::endl;
}
```

### 5.2. Range-based `for` loop (C++11)
Modern and safer way if index isn't needed.

```cpp
for (int val : arr) {
    std::cout << val << " "; // Works with copy of value
}

for (int& val : arr) {
    val *= 2; // Use reference to modify elements
}
```

---

## 6. Arrays and Functions

When passing an array to a function in C++, it **is not copied**. Instead, it "decays" to a **pointer to its first element**.

This implies two things:
1.  Function can modify the original array.
2.  Function **loses size information**. Size must be passed as a separate parameter.

```cpp
// Parameter int arr[] is equivalent to int* arr
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    // sizeof(arr) here returns pointer size (4 or 8), not array size!
}

int main() {
    int myArr[] = {1, 2, 3, 4, 5};
    // Calculate size: Total size / Element size
    int size = sizeof(myArr) / sizeof(myArr[0]);
    
    printArray(myArr, size);
}
```

---

## 7. Multidimensional Arrays

Arrays can have more than one dimension. Most common are 2D arrays (matrices).

```cpp
// 3x3 Matrix
int matrix[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

std::cout << matrix[1][1]; // Access row 1, col 1 (value 5)
```

(More details in "2D Arrays" topic).

---

## 8. Modern Alternative: `std::array`

In modern C++, "C-style" arrays (`int arr[5]`) are often replaced by the `std::array` container (from `<array>`).

### Advantages of `std::array`:
*   Knows its size (`.size()`).
*   Does not decay to pointer automatically.
*   Safer (`.at()` method checks bounds).
*   Same performance as C-style array.

```cpp
#include <array>
#include <iostream>

int main() {
    std::array<int, 5> nums = {1, 2, 3, 4, 5};

    std::cout << "Size: " << nums.size() << std::endl;

    // Safe access (throws exception on error)
    try {
        nums.at(10) = 5; 
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
```

---

## 9. Common Problems

1.  **Buffer Overflow:** Writing outside array bounds. Most common security vulnerability.
2.  **Forgotten Size:** Since functions don't know C-array size, it's easy to iterate too far.
3.  **Returning Local Array:** Never return a C-array from a function unless dynamically allocated or static.

```cpp
// ERROR!
int* createArray() {
    int arr[5] = {1, 2, 3, 4, 5};
    return arr; // Returns pointer to destroyed stack memory
}
```

---

## 10. Summary

Arrays are fast and efficient but require careful memory and index management. For modern C++ code:
*   `std::array` for fixed size.
*   `std::vector` for variable (dynamic) size.
*   C-style arrays mostly for compatibility with old libs or embedded systems.
