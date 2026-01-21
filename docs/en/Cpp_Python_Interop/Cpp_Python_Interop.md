# C++ and Python Interop (pybind11) - Complete Technical Guide

## 1. Introduction: Why Combine the Two Languages?

Python is the king of productivity, Data Science, and Artificial Intelligence (AI). It has a huge ecosystem but is slow (interpreted).
C++ is the king of performance and hardware control, but is difficult for rapid prototyping and scripting.

Professional software often uses a **hybrid model**:
1.  **C++ Core:** Heavy math, graphics engine, networking layer.
2.  **Python Layer:** Game logic, AI models, user scripts.

The **pybind11** library is the modern standard (after Boost.Python) for creating the bridge between them.

---

## 2. How Does pybind11 Work?

pybind11 is a header-only library that uses template metaprogramming (C++11 and up) to generate CPython extensions. It does not require a special preprocessor (like SWIG).

### 2.1. Basic Example (Hello World)
```cpp
#include <pybind11/pybind11.h>

int add(int i, int j) { return i + j; }

// The macro defines the module entry point
PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 example plugin"; // Docstring
    m.def("add", &add, "A function which adds two numbers");
}
```
After compilation, you get `example.cpython-38-x86_64-linux-gnu.so`, which you can import in Python: `import example`.

---

## 3. Data Transfer: STL and Numpy

### 3.1. Automatic Conversion (Copying)
If you include `<pybind11/stl.h>`, pybind11 automatically converts:
*   `std::vector<T>` <-> Python `list`.
*   `std::map<K, V>` <-> Python `dict`.
*   `std::string` <-> Python `str`.

⚠️ **Warning:** This almost always involves **copying** data, which can be expensive for large arrays.

### 3.2. Zero Overhead with Numpy (Buffer Protocol)
If you work with AI (TensorFlow, PyTorch), you will use **Numpy**. pybind11 allows C++ to access Numpy array memory directly, without copying.

```cpp
#include <pybind11/numpy.h>

void process_array(py::array_t<double> input) {
    auto buf = input.request(); // Access raw data
    double* ptr = static_cast<double*>(buf.ptr);
    
    for (size_t i = 0; i < buf.size; i++) {
        ptr[i] *= 2.0; // Modify Python data directly!
    }
}
```

---

## 4. Class Binding

You can wrap an entire C++ class into a Python class, including inheritance and virtual functions.

```cpp
struct Pet {
    std::string name;
    Pet(const std::string &name) : name(name) { }
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }
};

PYBIND11_MODULE(example, m) {
    py::class_<Pet>(m, "Pet")
        .def(py::init<const std::string &>()) // Constructor
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName)
        .def_property("name", &Pet::getName, &Pet::setName); // Python property
}
```

### 4.1. Virtual Methods (Trampolines)
To allow a Python class to inherit from a C++ class and override a virtual function, you must write a special "Trampoline" class in C++ that redirects the call to the Python interpreter.

---

## 5. GIL (Global Interpreter Lock)

⚠️ **CRITICAL FOR MULTITHREADING:** Python has a GIL that allows only one thread to execute Python bytecode at a time.
When your C++ code performs heavy calculations (e.g., image processing), you must **release the GIL** to allow Python scripts to run in parallel.

```cpp
{
    py::gil_scoped_release release; // Release GIL
    heavy_computation(); // C++ runs in parallel with Python
} // GIL is re-acquired automatically here (RAII)
```

---

## 6. Embedding Python

Instead of making a C++ plugin for Python, you can load the entire Python interpreter inside your C++ program.
```cpp
#include <pybind11/embed.h>

int main() {
    py::scoped_interpreter guard{}; // Starts Python VM
    py::exec("print('Hello from embedded Python!')");
}
```

---

## 7. Professional Summary

1.  **Use pybind11**, instead of the old Python C API or SWIG. It is cleaner and safer (RAII, Exceptions).
2.  **Exception Translation:** C++ exceptions are automatically translated into Python errors (e.g., `std::out_of_range` -> `IndexError`).
3.  **Keep objects alive:** Be careful with `return_value_policy`. If you return a pointer to a C++ object, Python needs to know who owns it (whether to delete it with the Garbage Collector or not).

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*