# Build Systems and CMake - Complete Technical Guide

## 1. Introduction: The Problem of "Assembly"

When your project is a single `main.cpp` file, the command `g++ main.cpp` is sufficient. But when the project grows to 100 files, 5 external libraries, and support for Windows and Linux, manual compilation becomes a nightmare.
A **Build System** is software that automates this process. It tracks file dependencies ("If I modify `header.h`, which `.cpp` files must be recompiled?").

---

## 2. Why is CMake the De Facto Standard?

CMake (Cross-platform Make) is **NOT** a compiler. It is a **Meta-Build System**.
You describe your project in an abstract language (`CMakeLists.txt`), and CMake generates files for the actual build system of your platform:
*   **Linux:** Generates `Makefile` (for `make`) or `build.ninja` (for `Ninja`).
*   **Windows:** Generates `.sln` (for Visual Studio) or `MinGW Makefiles`.
*   **MacOS:** Generates `Xcode` project.

This allows you to write the configuration once and compile everywhere.

---

## 3. Anatomy of a Professional CMakeLists.txt

Here is what modern CMake looks like (Target-based approach):

```cmake
# 1. Version requirement
cmake_minimum_required(VERSION 3.15)

# 2. Project definition
project(GameEngine VERSION 1.0.0 LANGUAGES CXX)

# 3. Standard (C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Defining an executable
add_executable(my_game src/main.cpp src/player.cpp)

# 5. Include directories (to make #include "player.h" work)
target_include_directories(my_game PUBLIC ${CMAKE_SOURCE_DIR}/include)

# 6. Optimizations (Release only)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(my_game PRIVATE -O3 -march=native)
endif()
```

---

## 4. Dependency Management

The hardest part in C++ is adding libraries. CMake offers two powerful mechanisms:

### 4.1. find_package (For Installed Libraries)
Searches for a library that is already installed on the system (e.g., via `apt install` or `vcpkg`).
```cmake
find_package(OpenCV REQUIRED)
target_link_libraries(my_game PRIVATE opencv_core opencv_highgui)
```

### 4.2. FetchContent (For Downloading Source Code)
A modern module (since CMake 3.11) that downloads a library from GitHub during configuration and compiles it together with your project.
```cmake
include(FetchContent)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)
target_link_libraries(my_game PRIVATE nlohmann_json::nlohmann_json)
```

---

## 5. Structuring: Targets and Scopes

In modern CMake, everything is a **Target** (executable or library).
Functions like `target_include_directories` and `target_link_libraries` have a Scope:
1.  **PRIVATE:** The setting applies only to the current target.
2.  **INTERFACE:** The setting does not apply to the current target but is propagated to anyone depending on it (linking it).
3.  **PUBLIC:** Applies to both the current target and dependents.

**Example:** If you write a library that has `.h` files in `include/`, use `PUBLIC` so library users can automatically see the headers.

---

## 6. Out-of-Source Builds

Never run `cmake .` in the root directory! This pollutes the source with temporary files.
The correct way:
```bash
mkdir build
cd build
cmake ..  # Generation
cmake --build .  # Compilation
```

---

## 7. Professional Summary

1.  **Modern CMake:** Forget about variables like `include_directories()`. Use only `target_...` commands.
2.  **Generators:** Use **Ninja** instead of Make. It is significantly faster for parallel compilation.
3.  **Tooling:** Integrate `Clang-Tidy` and `CppCheck` directly into the CMake script for automatic quality analysis.
4.  **CCache:** Configure CMake to use `ccache` to cache compiled objects and speed up recompilation by 10x.

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*