# WebAssembly (Wasm) and C++ - Complete Technical Guide

## 1. Introduction: C++ in the Browser

WebAssembly (Wasm) is a binary instruction format that allows C++ code to run in a web browser at near-native speed. This opens the door for heavy applications like Photoshop, AutoCAD, Unity, and Unreal Engine directly in Chrome or Firefox.

---

## 2. Emscripten: The Wizard Compiler

Emscripten is an LLVM-based SDK that compiles C++ code to `.wasm` files and generates the necessary JavaScript "glue code".

### 2.1. Hello World
```bash
emcc main.cpp -o index.html
```
This command generates an HTML, JS, and WASM file. When you open the HTML, you will see your program's console output.

---

## 3. Embind: Binding to JavaScript

The most powerful part of Emscripten is **Embind**. It allows direct calling of C++ functions from JS and vice versa.

### 3.1. Exporting a C++ Class
```cpp
#include <emscripten/bind.h>

class Calculator {
public:
    int add(int a, int b) { return a + b; }
};

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::class_<Calculator>("Calculator")
        .constructor<>()
        .function("add", &Calculator::add);
}
```

### 3.2. Usage in JavaScript
```javascript
var instance = new Module.Calculator();
console.log(instance.add(10, 20)); // 30
instance.delete(); // Manual cleanup!
```

---

## 4. Memory and Limitations

### 4.1. Linear Memory
The Wasm module views memory as one huge array of bytes (`ArrayBuffer` in JS).
*   **Challenge:** Pointers in WASM are 32-bit (currently), limiting memory to 4GB.
*   **Sharing:** You can share this buffer between C++ and JS to pass images (Texture data) without copying.

### 4.2. File System
The browser does not have access to `/home/user`. Emscripten simulates a virtual file system (**MEMFS**) that lives in RAM.
*   `std::ofstream("file.txt")` writes to virtual memory.

---

## 5. Performance and Optimization

1.  **`-O3`**: Always use maximum optimization for Release.
2.  **SIMD:** WebAssembly supports 128-bit SIMD instructions (enabled with `-msimd128`), speeding up math.
3.  **Multithreading:** Wasm supports threads via `Web Workers` and `SharedArrayBuffer`. C++ code with `std::thread` can be compiled almost without changes (with `-pthread` flag).

---

## 6. Debugging

*   **Source Maps:** Emscripten can generate maps that allow Chrome DevTools to show the original C++ code while debugging the WASM.
*   **Sanitizers:** ASan and UBSan also work with Emscripten!

---

## 7. Professional Summary

*   **Wasm does not replace JS:** It complements it for heavy computations.
*   **Portability:** The same C++ code can run on Desktop, Mobile, and Web.
*   **Security:** Wasm runs in a Sandbox. It cannot break the user's computer.

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*