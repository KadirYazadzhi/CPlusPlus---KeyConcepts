# Queues in C++

## 1. Introduction

A Queue is a linear data structure following the **FIFO (First-In, First-Out)** principle. Like a queue at a store: the first person to arrive is served first.

### Key Applications:
*   Task Scheduling (OS).
*   Data Buffering (IO, streaming).
*   BFS (Breadth First Search) algorithms.
*   Printer queues.

---

## 2. Basic Operations

Has two ends: **Front** and **Back**. Add to back, remove from front.
Complexity **O(1)**.

1.  **push:** Add to back (enqueue).
2.  **pop:** Remove from front (dequeue).
3.  **front:** View first element.
4.  **back:** View last element.
5.  **empty:** Check if empty.
6.  **size:** Get count.

---

## 3. Using `std::queue`

Defined in `<queue>`.

```cpp
#include <iostream>
#include <queue>

int main() {
    std::queue<std::string> q;

    // 1. Push
    q.push("Client 1");
    q.push("Client 2");

    // 2. Access
    std::cout << "Front: " << q.front() << std::endl; // Client 1
    std::cout << "Back:  " << q.back()  << std::endl; // Client 2

    // 3. Pop
    q.pop(); // Removes Client 1
    
    std::cout << "New Front: " << q.front() << std::endl; // Client 2

    return 0;
}
```

---

## 4. Types of Queues

### 4.1. Deque (Double Ended Queue)
Allows push/pop from both ends.

### 4.2. Priority Queue
Elements ordered by priority, not arrival time.

---

## 5. Example: BFS (Breadth-First Search)

Finding shortest path in graphs.

```cpp
#include <iostream>
#include <vector>
#include <queue>

std::vector<std::vector<int>> adj = { {1, 2}, {0, 3}, {0}, {1} };

void bfs(int start) {
    std::vector<bool> visited(4, false);
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        std::cout << curr << " ";

        for (int neighbor : adj[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}
```

---

## 6. Summary

*   FIFO structure.
*   Use `std::queue`.
*   Key operations: `push`, `pop`, `front`.
*   Essential for asynchronous processing and BFS.
