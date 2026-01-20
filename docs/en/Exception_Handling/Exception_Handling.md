# Exception Handling in C++ - Complete Technical Guide

## 1. Introduction: The Philosophy of "Exceptional" Situations

In programming, errors are inevitable. Before exceptions, C programmers used error codes (e.g., returning -1 or `NULL`). This led to "spaghetti code" where business logic was mixed with `if (err)` checks on every line.

**Exceptions** in C++ allow:
1.  Separation of error handling logic from the normal flow.
2.  Guarantee that errors cannot be silently ignored.
3.  Automatic propagation of information up the stack.

---

## 2. The Mechanism: Try, Catch, Throw

### 2.1. Throw
When a problem arises that the function cannot solve itself, it "throws" an exception. This terminates the function's execution **immediately**.
```cpp
void connect(string ip) {
    if (ip.empty()) {
        throw std::invalid_argument("IP address cannot be empty!");
    }
    // ... remaining code is not executed on error
}
```

### 2.2. Catch
The exception "flies" up the stack (through all calling functions) until it meets a `catch` block that can handle it.
```cpp
try {
    connect("");
} catch (const std::invalid_argument& e) { // Catch by const reference!
    std::cerr << "Error: " << e.what() << std::endl;
} catch (...) {
    std::cerr << "Unknown error!" << std::endl;
}
```

---

## 3. Stack Unwinding: The Most Important Concept

⚠️ **ENGINEERING VIEW:** What happens to local variables when a function aborts due to a `throw`?

Here comes **Stack Unwinding**. C++ guarantees that for all automatic objects (created on the stack), their destructors will be called.

**Example of RAII Power:**
```cpp
void riskyFunction() {
    std::vector<int> data(1000000); // Allocates memory
    std::ofstream file("log.txt");  // Opens file
    
    throw std::runtime_error("Boom!"); 
    
    // file.close() and delete[] data are NEVER written here explicitly.
    // Destructors are called automatically on throw!
}
```
This makes **RAII** (Resource Acquisition Is Initialization) the only correct way to handle resources in C++ with exceptions.

---

## 4. The Cost of Exceptions (Zero-Cost Exceptions)

Modern compilers (GCC, Clang, MSVC) use the **Zero-Cost Abstractions** model.
*   **If no error:** Code runs at the same speed as if there were no `try-catch`. No `if` checks after every instruction.
*   **If error:** Then (and only then) the system enters an expensive mode. It must read a special table (Exception Table), find the catch handler, and unwind the stack.

**Conclusion:** Use exceptions only for **truly exceptional** events (network down, disk full). Do not use them for flow control (e.g., "end of loop") because they are slow when thrown.

---

## 5. Modern C++: `noexcept`

The `noexcept` keyword (C++11) is a contract.
`void func() noexcept;`

*   **Meaning:** "I promise this function will never throw an exception."
*   **Benefit:** Allows the compiler to perform aggressive optimizations (e.g., not generating Exception Tables for this function).
*   **Risk:** If you lie and the function throws, the program terminates immediately (`std::terminate`).

**Mandatorily use `noexcept` for:**
1.  Destructors (Always!).
2.  Move Constructors.
3.  Swap functions.

---

## 6. Defining Custom Errors

Do not just throw `int` or `string`. Inherit from `std::exception`.

```cpp
class DatabaseError : public std::runtime_error {
public:
    int errorCode;
    DatabaseError(const string& msg, int code) 
        : std::runtime_error(msg), errorCode(code) {}
};
```

---

## 7. Exception Safety Guarantees

When writing a function, you must guarantee one of the following upon error:
1.  **Basic Guarantee:** No memory leaks (thanks to RAII), but the program might be in a modified state.
2.  **Strong Guarantee (Transactional):** The operation either succeeds completely or changes nothing (Rollback). `std::vector::push_back` gives this guarantee.
3.  **No-throw Guarantee:** The function never fails.

---

## 8. Professional Summary

1.  **Throw by value, catch by reference:** Always `catch (const std::exception& e)`. This avoids Object Slicing.
2.  **RAII:** Never use `new/delete` in code with exceptions. Use `unique_ptr`.
3.  **Destructors:** A destructor that throws an exception during Stack Unwinding leads to an immediate crash. Destructors must be "silent".