# Queues in C++ - The Ultimate Guide

## 1. Concept: FIFO Structure
The queue is a linear data structure that follows the **First-In, First-Out (FIFO)** principle. The first element added is the first one to be processed. This is exactly like a queue in a store or at a bus stop.

---

## 2. Basic Operations

Operations have a time complexity of **O(1)**:

1.  **push (enqueue):** Adds an element to the end of the queue.
2.  **pop (dequeue):** Removes the element from the beginning.
3.  **front:** Accesses the first element.
4.  **back:** Accesses the last element.
5.  **empty / size:** Status checks.

---

## 3. Types of Queues

### 3.1. Standard Queue (`std::queue`)
Used for sequential processing. Like the stack, it is an adapter over `std::deque`.

### 3.2. Double-Ended Queue (`std::deque`)
Allows adding and removing from both ends.

### 3.3. Circular Queue
Solves the "wasted memory" problem in static arrays by connecting the end of the array to its beginning using modular arithmetic: `index = (index + 1) % size`.

---

## 4. Applications

*   **BFS (Breadth First Search):** Level-order traversal in graphs – uses a queue to maintain the order of visited nodes.
*   **Buffer Management:** Network packets, video streaming.
*   **Task Scheduling:** Managing tasks in an operating system.

---

## 5. Priority Queue (`std::priority_queue`)

A special form of queue where elements do not leave in arrival order, but according to their "importance" (priority). Typically implemented using a **Heap** structure.

```cpp
#include <queue>
std::priority_queue<int> pq; // Largest element comes out first
```

---
*(This document is part of the "C++ Key Concepts" course)*