# Stacks in C++

## 1. Introduction

A Stack is a fundamental data structure of type **LIFO (Last-In, First-Out)**. Imagine a stack of plates: you can only add a new plate on top, and you can only take the top plate off.

### Key Applications:
*   Function Call Stack management.
*   DFS (Depth First Search) algorithms.
*   Expression parsing (balanced parentheses).
*   Undo/Redo features.

---

## 2. Basic Operations

Stack supports limited operations, all with **O(1)** complexity:

1.  **push:** Add element to top.
2.  **pop:** Remove top element.
3.  **top (or peek):** View top element.
4.  **empty:** Check if empty.
5.  **size:** Get count.

⚠️ **Warning:** Calling `pop()` or `top()` on an empty stack is Undefined Behavior. Always check `empty()`.

---

## 3. Using `std::stack`

C++ STL provides `std::stack` in `<stack>`.

```cpp
#include <iostream>
#include <stack>

int main() {
    std::stack<int> s;

    // 1. Add (Push)
    s.push(10); // Stack: [10]
    s.push(20); // Stack: [10, 20] (20 is top)
    s.push(30);

    // 2. Size
    std::cout << "Size: " << s.size() << std::endl; // 3

    // 3. Top
    std::cout << "Top: " << s.top() << std::endl; // 30

    // 4. Remove (Pop)
    s.pop(); // Removes 30
    std::cout << "New Top: " << s.top() << std::endl; // 20

    // 5. Iterate (destroys stack)
    while (!s.empty()) {
        std::cout << s.top() << " ";
        s.pop();
    }
    // Output: 20 10
    
    return 0;
}
```

---

## 4. Implementation Details

`std::stack` is a **container adapter**. It doesn't manage memory directly but uses another container (default is `std::deque`) underneath.

You can swap the underlying container:
```cpp
#include <vector>
std::stack<int, std::vector<int>> vectorStack;
```

---

## 5. Example: Balanced Parentheses

Check if `{[()]}` is valid.

**Algorithm:**
1.  Iterate string.
2.  If open bracket `(`, `{`, `[`, push to stack.
3.  If closed bracket:
    *   Stack empty -> Error.
    *   Top matches? Pop.
    *   Mismatch -> Error.
4.  Stack empty at end -> Valid.

```cpp
#include <iostream>
#include <stack>
#include <string>

bool isValid(std::string expression) {
    std::stack<char> s;

    for (char c : expression) {
        if (c == '(' || c == '{' || c == '[') {
            s.push(c);
        } else {
            if (s.empty()) return false;
            
            char top = s.top();
            if ((c == ')' && top == '(') ||
                (c == '}' && top == '{') ||
                (c == ']' && top == '[')) {
                s.pop();
            } else {
                return false;
            }
        }
    }
    return s.empty();
}
```

---

## 6. Stack Overflow

Occurs when the system Call Stack (fixed size) runs out of memory, usually due to infinite recursion. `std::stack` uses Heap memory, so it is limited only by RAM.

---

## 7. Summary

*   LIFO structure.
*   Use `std::stack`.
*   Check `!empty()` before access.
*   Complexity: O(1).
