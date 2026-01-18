# Priority Queues in C++ - The Ultimate Technical Guide

## 1. Concept: The Abstraction of "Important Data"
`std::priority_queue` is an adapter that provides access only to the largest (or smallest) element. In professional software, this is the structure that drives system schedulers and complex AI (e.g., Pathfinding).

---

## 2. Anatomy of the Binary Heap

Almost always, `priority_queue` is implemented as a **Binary Heap** over an array (`std::vector`).
*   **Advantage:** Extremely efficient memory usage.
*   **Ordering:** Not a full sort! It only maintains the property that a parent is larger than its children.

### 2.1. Complexity
*   `push()`: **O(log N)** - Places the element at the end and "bubbles it up."
*   `pop()`: **O(log N)** - Removes the top and reorganizes the pyramid (Heapify).
*   `top()`: **O(1)** - Returns the first element of the vector.

---

## 3. Min-Heap vs. Max-Heap

By default, C++ creates a **Max-Heap**.
To create a **Min-Heap** (smallest number on top), use the following declaration:
```cpp
std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
```

---

## 4. Complex Objects and Comparators
In professional applications, the priority is often a complex object.
```cpp
struct Task {
    int priority;
    long timestamp;
    bool operator<(const Task& other) const {
        if (priority != other.priority) return priority < other.priority;
        return timestamp > other.timestamp; // Older tasks take precedence
    }
};
```

---

## 5. Professional Summary
*   Use `priority_queue` for algorithms like **Dijkstra** or **A***.
*   Remember that you have no access to elements in the middle.
*   If you need to frequently change priorities, you likely need a different structure (e.g., a manually managed Heap).

---
*(Documentation updated for C++17/20/23 standards)*
