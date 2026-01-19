# Build Systems and CMake - The Ultimate Technical Guide

## 1. Introduction: The "Assembly" Problem
When your project crosses the boundary of a few files, manual compilation with `g++` becomes impossible. You need a system that knows which files to recompile when a change occurs, how to find external libraries (e.g., OpenCV or Boost), and how to generate project files for different IDEs (VS Code, CLion, Visual Studio).

---

## 2. Why is CMake the De Facto Standard?
CMake is not a compiler. It is a **generator** of build systems. You describe your project abstractly in `CMakeLists.txt`, and CMake generates a `Makefile` (for Linux), a `.sln` (for Windows), or an `Xcode` project.

### 2.1. Advantages
*   **Cross-platform:** One code, one CMake file, all operating systems.
*   **Out-of-source builds:** Keeps the source tree clean by compiling everything in a separate folder (e.g., `build/`).
*   **Dependency Management:** Tools like `FetchContent` and `find_package`.

---

## 3. Anatomy of a Professional CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.15)
project(Engine VERSION 1.0.0 LANGUAGES CXX)

# Set a modern standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create a library
add_library(core_lib STATIC src/core.cpp)

# Create an executable
add_executable(game_app main.cpp)

# Linking
target_link_libraries(game_app PRIVATE core_lib)

# Header management
target_include_directories(core_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
```

---

## 4. Transitive Dependencies (Target-based CMake)
Modern CMake operates through **Targets**. When you state that your program depends on a library, it automatically receives its header paths and its compilation flags. This is called "Usage Requirements."

---

## 5. Complex Scenarios

### 5.1. Configuring Files (configure_file)
Allows you to pass versions or settings from CMake directly into C++ code by generating `.h` files.

### 5.2. Profiles (Debug vs. Release)
CMake optimizes code automatically:
*   `Debug`: With debug info enabled, no optimization.
*   `Release`: Maximum speed (`-O3`), no debug symbols.

---

## 6. Professional Summary
*   Never use global variables in CMake.
*   Think in **Targets** (objects), not in directories.
*   Use `target_link_libraries` for everything.
*   CMake is a programming language in itself – learn it to control your build process 100%.

---
*Documentation prepared for the "C++ Key Concepts" project.*
*Version: 2.0 (Full Detail)*
