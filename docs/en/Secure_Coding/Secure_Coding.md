# Secure Coding in C++ - Complete Technical Guide

## 1. Introduction: Why is C++ a Target for Hackers?

C++ provides direct memory access and high speed, but does not offer a "safety net" (garbage collection, bounds checking by default). This makes the language powerful, but also extremely vulnerable to attacks if the programmer is not disciplined.
Over 70% of security breaches in software giants (Microsoft, Google) are due to memory management errors in C/C++ code.

---

## 2. Buffer Overflow: The Classic Enemy

This is the most famous vulnerability. It happens when you write more data than the array can hold.

### 2.1. The "Stack Smashing" Attack
Hackers overflow a local array on the stack to overwrite the function's **Return Address**. Thus, instead of returning to normal code, the processor jumps to malicious code (shellcode) injected by the hacker.

### 2.2. Defense (Mitigation)
*   **Rule 1:** Never use forbidden C functions: `gets`, `strcpy`, `strcat`, `sprintf`. They do not check buffer size.
*   **Rule 2:** Use `std::string` and `std::vector`. They manage memory dynamically.
*   **Rule 3:** Always use `.at()` (which throws an exception) or check size before writing with `operator[]`.

```cpp
void risky(const char* input) {
    char buffer[10];
    // strcpy(buffer, input); // ERROR! If input > 10, hack.
    
    // Better:
    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
}
```

---

## 3. Injections and Unvalidated Data

If your program accepts input from the user (e.g., filename, SQL query, or command), it must treat it as **"poisonous"** until validated.

### 3.1. Path Traversal
If you allow a user to open a file by providing a name, they might provide `../../etc/passwd` (Linux) or `..\..\Windows\System32\config\SAM` (Windows) to read system data.
**Defense:** Always use `std::filesystem::canonical` (C++17) to resolve the path and check if it starts with your allowed directory.

### 3.2. Command Injection
Never construct commands for `system()` by concatenating strings.
`system(("ls " + userInput).c_str());` -> If input is `"; rm -rf /"`, you wipe the disk.

---

## 4. Integer Overflows

When you add 1 to the maximum possible number (`unsigned short 65535`), it becomes 0. This often leads to incorrect buffer size calculations.

```cpp
unsigned short count = 65535;
count++; // Becomes 0
// We allocate 0 bytes, but copy data...
char* buffer = new char[count]; 
```
**Defense:** Use the `<numeric>` library or functions like `std::add_sat` (C++26) for saturated arithmetic.

---

## 5. Format String Attack

Never pass user input as the first argument to `printf`.
*   **Wrong:** `printf(userInput);`
    *   The hacker can pass `"%x %x %x %x"` to read your stack (Memory Leak).
    *   Or `"%n"` to write to memory.
*   **Correct:** `printf("%s", userInput);` or `std::print("{}", userInput);`

---

## 6. Modern Hardware and Software Defenses

The professional engineer must know how to enable compiler protections:

1.  **ASLR (Address Space Layout Randomization):** The OS moves stack and heap addresses at every startup.
2.  **DEP / NX (Data Execution Prevention):** Marks data memory as "non-executable". Shellcode cannot run from the stack.
3.  **Stack Canaries:** The compiler (`-fstack-protector-all`) adds a secret "magic number" to the stack before the return address. If you overflow the buffer, you change the canary and the program kills itself before being hacked.

---

## 7. Professional Summary

*   **Zero Trust:** Validate every byte coming from the network or file.
*   **Tools:** Run static analysis (`clang-tidy`) and dynamic analysis (Sanitizers) in the CI/CD pipeline.
*   **RAII:** Proper resource management is the best defense against Use-After-Free vulnerabilities.
*   **Update:** Keep your libraries (OpenSSL, LibXML) updated. Old versions have known CVEs.

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*