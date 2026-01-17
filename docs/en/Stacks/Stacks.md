# Stacks in C++ - The Ultimate Guide

## 1. Concept: LIFO Structure
The stack is an abstract data structure that operates on the **Last-In, First-Out (LIFO)** principle. This means the last element added is the first one to be removed. Imagine a stack of plates or a deck of cards – you can only add to the top and take from the top.

---

## 2. Operations and Complexity

All basic stack operations are extremely fast (**O(1)**):

1.  **push:** Adds an element to the top.
2.  **pop:** Removes the top element.
3.  **top:** Returns the value of the top element without removing it.
4.  **empty:** Checks if the stack is empty.
5.  **size:** Returns the number of elements.

⚠️ **Warning:** In C++, `pop()` does not return a value (it is `void`). You must call `top()` first if you want to see the value before removing it.

---

## 3. Using std::stack (STL)

In the STL, `std::stack` is not a container itself but a **container adapter**. This means it wraps another container (default is `std::deque`) and restricts its interface.

```cpp
#include <stack>
#include <vector>

// We can change the underlying container to a vector:
std::stack<int, std::vector<int>> s;
```

---

## 4. Manual Implementation (Deep Dive)

To understand how a stack works, it is useful to see how it is implemented using an array.

```cpp
template <typename T>
class MyStack {
    T* data;
    int top_index;
    int capacity;

public:
    MyStack(int size) : capacity(size), top_index(-1) {
        data = new T[capacity];
    }
    ~MyStack() { delete[] data; }

    void push(T val) {
        if (top_index >= capacity - 1) throw std::overflow_error("Stack Overflow");
        data[++top_index] = val;
    }

    void pop() {
        if (top_index < 0) return;
        top_index--;
    }

    T top() { return data[top_index]; }
};
```

---

## 5. Real-world Applications

1.  **Call Stack:** Managing function calls in the CPU.
2.  **Reverse Polish Notation (RPN):** Calculating mathematical expressions.
3.  **Undo/Redo:** In text editors like VS Code or Word.
4.  **DFS (Depth First Search):** Traversing graphs.
5.  **Bracket Balancing:** Checking if brackets in code are correctly closed.

---

## 6. Common Issues

*   **Stack Overflow:** When adding too many elements to a fixed-size stack (often during infinite recursion).
*   **Empty Access:** Attempting to call `top()` or `pop()` on an empty stack leads to a crash. Always check `!s.empty()`.

---
*(This document is part of the "C++ Key Concepts" course)*