# Priority Queues in C++ - The Ultimate Guide

## 1. Concept: Not Just FIFO
Unlike a standard queue, which follows the "First-In, First-Out" principle, `std::priority_queue` orders elements based on their value. The element with the highest priority (by default, the largest value) is always at the top and is removed first.

---

## 2. Internal Structure: Binary Heap
A priority queue is typically implemented as a **Binary Heap** over a `std::vector`. This allows efficient priority management without requiring a full sort of the entire container.

### 2.1. Complexity
*   **Insertion (push):** O(log N)
*   **Removal of top (pop):** O(log N)
*   **Peek top (top):** O(1)

---

## 3. Min-Heap vs. Max-Heap

By default, C++ creates a **Max-Heap** (largest element on top).

### 3.1. How to create a Min-Heap (smallest on top)?
You need to change the template declaration:
```cpp
#include <queue>
#include <vector>
#include <functional>

std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
```

---

## 4. Working with Custom Objects

To use `std::priority_queue` with your own classes, you must define how objects are compared.

### 4.1. Overloading operator<
```cpp
struct Task {
    int priority;
    string description;

    // Important: priority_queue uses < for ordering.
    bool operator<(const Task& other) const {
        return priority < other.priority;
    }
};
```

---

## 5. Why No Iterators?
`std::priority_queue` does not support iterators. You cannot traverse the elements or modify those in the middle. This is because any modification could violate the Heap property. The only way to see all elements is to extract them one by one using `pop()`.

---

## 6. Applications
*   **Dijkstra's Algorithm:** Finding the shortest path.
*   **Prim's Algorithm:** Finding the minimum spanning tree.
*   **Task Scheduling (OS):** Always execute the task with the highest priority first.
*   **Huffman Compression.**

---
*(This document is part of the "C++ Key Concepts" course)*