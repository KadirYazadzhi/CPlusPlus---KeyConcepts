# Priority Queues in C++

## 1. Introduction

`std::priority_queue` is an adapter where the element with the **highest priority** comes out first. Defined in `<queue>`.

Default: Max-Heap (largest element first).

---

## 2. Operations

Like stack: `push`, `pop`, `top`.

```cpp
std::priority_queue<int> pq;
pq.push(10);
pq.push(30);
pq.push(5);

// Top is 30 (largest)
std::cout << pq.top(); 
pq.pop(); // Removes 30
```

---

## 3. Min-Heap

Smallest first.

```cpp
std::priority_queue<int, std::vector<int>, std::greater<int>> minPQ;
```

---

## 4. Summary

*   Not FIFO. Ordered by priority.
*   O(log N) push/pop.
*   O(1) top.
