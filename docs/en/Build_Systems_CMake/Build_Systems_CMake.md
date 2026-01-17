# Build Systems & CMake in C++ - The Ultimate Guide

## 1. Introduction: Why Do We Need CMake?
When your project grows beyond a single file, manual compilation becomes a nightmare. You need a tool to manage dependencies, find libraries, and generate compiler instructions. **CMake** is the industry standard for C++ – it is not a compiler, but a generator of build files.

---

## 2. Anatomy of CMakeLists.txt
Every project starts with a `CMakeLists.txt` file.

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create executable
add_executable(MyApp main.cpp utils.cpp)
```

---

## 3. Managing Libraries

### 3.1. Static and Dynamic Libraries
You can split your code into logical parts:
```cmake
add_library(MathLib STATIC src/math.cpp)
target_link_libraries(MyApp PRIVATE MathLib)
```

### 3.2. Finding External Packages (find_package)
CMake can automatically discover installed libraries (e.g., OpenCV, Boost, Qt):
```cmake
find_package(OpenCV REQUIRED)
target_link_libraries(MyApp PRIVATE ${OpenCV_LIBS})
```

---

## 4. Include Directories
To avoid writing long paths in `#include`, tell CMake where the headers are:
```cmake
target_include_directories(MyApp PRIVATE ${CMAKE_SOURCE_DIR}/include)
```

---

## 5. The Build Process
Always use a separate directory for building to keep the source tree clean:
1. `mkdir build && cd build`
2. `cmake ..` (Generating)
3. `cmake --build .` (Compiling)

---

## 6. Advantages of CMake
*   **Cross-platform:** Works equally well on Windows, Linux, and macOS.
*   **Integration:** Supported by all major IDEs (VS Code, CLion, Visual Studio).
*   **Scalability:** Manages projects with thousands of files without issues.

---
*(This document is part of the "C++ Key Concepts" course)*