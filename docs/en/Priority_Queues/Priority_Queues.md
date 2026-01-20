# Priority Queues in C++ - Complete Technical Guide

## 1. Concept: When Order Does Not Depend on Time

In a standard queue (`std::queue`), first-in is first-out (FIFO). In `std::priority_queue`, however, the first one out is the one with the **highest priority**, regardless of when it was added.

This is the perfect abstraction for systems where "urgency" is the driving factor:
*   **Emergency Room:** A patient with a heart attack (arrived 5 mins ago) enters before a patient with a cold (arrived 1 hour ago).
*   **OS Scheduler:** A system process (kernel task) preempts a user process (browser).

---

## 2. Internal Structure: Binary Heap

⚠️ **ENGINEERING VIEW:** `std::priority_queue` is not magic. It is simply `std::vector` + heap ordering algorithms (Heap Algorithms).

### 2.1. What is a Heap?
It is a binary tree that satisfies a simple rule (**Heap Property**):
*   **Max-Heap:** The parent is always greater than or equal to its children. The root is the largest element.
*   **Min-Heap:** The parent is smaller. The root is the smallest.

`std::priority_queue` does **NOT** keep the entire array sorted. That would be too slow (O(N) on insertion). It only maintains the heap structure, which is enough to know who is the "most important".

### 2.2. Index Mathematics (Implicit Data Structure)
Instead of using expensive pointers (`Node* left, right`), we keep the tree in a flat array:
For a node at index `i`:
*   **Left Child:** `2 * i + 1`
*   **Right Child:** `2 * i + 2`
*   **Parent:** `(i - 1) / 2`

This makes the structure extremely compact and Cache-Friendly.

---

## 3. Operations and Complexity

| Operation | Complexity | Description |
| :--- | :--- | :--- |
| **push()** | **O(log N)** | Adds to the end and "floats" up (Sift Up / Swim). |
| **pop()** | **O(log N)** | Removes the root, places the last element there and "sinks" it down (Sift Down / Sink). |
| **top()** | **O(1)** | Returns `vector[0]`. |

---

## 4. Min-Heap and Custom Comparators

By default, C++ creates a **Max-Heap** (the largest number is on top).

### 4.1. Creating a Min-Heap
To reverse the order (e.g., for Dijkstra's algorithm), you must change the comparator:
```cpp
// Type, Container, Comparator
std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
```

### 4.2. Custom Structures
If you store complex objects (e.g., `Task`), you must define how they compare.
```cpp
struct Task {
    int priority;
    string name;
    
    // Overriding operator<
    bool operator<(const Task& other) const {
        // Warning: priority_queue pops the LARGEST.
        // If we want a task with a smaller number to exit first (like priority 1),
        // we must reverse the logic:
        return priority > other.priority; 
    }
};
```
Or with a Functor:
```cpp
struct CompareTask {
    bool operator()(const Task& a, const Task& b) {
        return a.priority > b.priority;
    }
};
std::priority_queue<Task, std::vector<Task>, CompareTask> pq;
```

---

## 5. make_heap, push_heap, pop_heap

STL gives you access to the raw algorithms via the `<algorithm>` header. You can turn *any* vector into a heap and back.

```cpp
std::vector<int> v = {10, 20, 5, 30};

std::make_heap(v.begin(), v.end()); // Rearranges vector into Heap (O(N))
// v.front() is now 30

v.push_back(40);
std::push_heap(v.begin(), v.end()); // Fixes the heap after addition (O(log N))
// v.front() is 40

std::pop_heap(v.begin(), v.end()); // Moves the largest (40) to the very back
v.pop_back(); // Actually removes it from the vector
```
This is useful if you want access to the entire array, not just the top.

---

## 6. Real-World Applications

1.  **Dijkstra's Algorithm and A*:** Finding the shortest path. The queue keeps unvisited nodes, sorted by current distance.
2.  **Huffman Coding:** Data compression. Uses Min-Heap to combine the least frequent symbols.
3.  **K-th Largest Elements:** If you need the top 10 results out of 1 million, maintain a Min-Heap of size 10. If a new element is larger than the top, remove the top and insert the new one.

---

## 7. Professional Summary

*   `std::priority_queue` is the fastest way to maintain the "current leader" in a data stream.
*   **Watch the `<` logic**: In `priority_queue`, "less" means "lower in the pyramid".
*   No iterators. You cannot traverse the queue without destroying it (unless using `make_heap` on your own vector).
*   Save memory via `reserve()` on the internal container.