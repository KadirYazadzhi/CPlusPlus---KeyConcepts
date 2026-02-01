# 🇺🇸 English Version

[🇧🇬 Българска Версия](README_bg.md)

# The Ultimate C++ Reference Guide

Welcome to the most comprehensive reference guide for the C++ programming language. This repository is designed with a single goal: **to provide deep, structured, and practical knowledge** for every key concept in the language.

Here, you won't find just dry code snippets. Each topic is explored in detail within its own directory, explaining **how** things work under the hood, **why** they are designed that way, and **when** to use them in real-world projects.

## 📂 Project Structure

The project is organized into 9 logical modules, covering the full spectrum of C++ software engineering:

1.  **Fundamental Concepts:** Syntax basics, memory, and data structures.
2.  **OOP:** Principles of Object-Oriented Design.
3.  **Memory Management:** Modern safety techniques and efficiency (RAII).
4.  **Advanced Features:** Templates, lambdas, and exception handling.
5.  **STL & Systems Programming:** Standard library usage and multithreading.
6.  **Engineering Practices:** How to write professional, tested, and maintainable code.
7.  **C++20 Innovations:** The latest standards and revolutionary changes.
8.  **Modern Libraries:** Tools for time, filesystem, and metaprogramming.
9.  **Low-Level & Architecture:** Bit manipulation, optimization, and architectural principles.

---

## 📚 Detailed Table of Contents

### 🟢 Part I: Fundamental Concepts
*The basics you cannot do without. Understanding memory and core structures.*

1.  **[References](docs/en/References/References.md)**
    *   *What:* Variable aliases and alternatives to pointers.
    *   *Why:* For safe data passing without copying and avoiding `nullptr` issues.
2.  **[Pointers](docs/en/Pointers/Pointers.md)**
    *   *What:* Direct memory address manipulation.
    *   *Why:* For dynamic memory allocation, hardware interaction, and understanding computer architecture.
3.  **[Arrays](docs/en/Arrays/Arrays.md)**
    *   *What:* Fixed-size sequential data blocks.
    *   *Why:* The fastest structure for stack-based data storage.
4.  **[2D Arrays](docs/en/Two_Dimensional_Arrays/Two_Dimensional_Arrays.md)**
    *   *What:* Matrices and tabular data.
    *   *Why:* For mathematical computations, image processing, and grids.
5.  **[Functions](docs/en/Functions/Functions.md)**
    *   *What:* Code modularization.
    *   *Why:* Covers pass-by-value/reference, overloading, and inline functions.
6.  **[Stacks](docs/en/Stacks/Stacks.md)**
    *   *What:* LIFO (Last-In, First-Out) structure.
    *   *Why:* For memory management (Call Stack), undo operations, and expression parsing.
7.  **[Queues](docs/en/Queues/Queues.md)**
    *   *What:* FIFO (First-In, First-Out) structure.
    *   *Why:* For data buffering, asynchronous processing, and BFS algorithms.
8.  **[Sets](docs/en/Sets/Sets.md)**
    *   *What:* Collection of unique, sorted elements.
    *   *Why:* For fast lookups (log N) and guaranteeing data uniqueness.
9.  **[Vectors](docs/en/Vectors/Vectors.md)**
    *   *What:* Dynamic arrays that resize automatically.
    *   *Why:* The default container in C++ (fast access, flexibility).
10. **[Priority Queues](docs/en/Priority_Queues/Priority_Queues.md)**
    *   *What:* A queue where the most important element comes out first.
    *   *Why:* For task scheduling, Dijkstra's algorithm, and Huffman coding.
11. **[Maps](docs/en/Maps/Maps.md)**
    *   *What:* Associative array (Dictionary) of Key-Value pairs.
    *   *Why:* For linking data and fast lookups by key.
12. **[Unordered Maps](docs/en/Unordered_Maps/Unordered_Maps.md)**
    *   *What:* Hash tables.
    *   *Why:* For maximum performance (O(1)) when order doesn't matter.
13. **[Lists](docs/en/Lists/Lists.md)**
    *   *What:* Doubly linked lists.
    *   *Why:* For fast insertion/deletion at any position without memory shifting.
14. **[Deques](docs/en/Deques/Deques.md)**
    *   *What:* Hybrid between vector and list.
    *   *Why:* For adding elements at both ends with O(1) complexity.
15. **[Multimaps](docs/en/Multimaps/Multimaps.md)**
    *   *What:* Maps allowing duplicate keys.
    *   *Why:* For dictionaries, indexes, and grouping data.
16. **[Multisets](docs/en/Multisets/Multisets.md)**
    *   *What:* Sets allowing duplicate elements.
    *   *Why:* When storing sorted data with duplicates is required.
17. **[Recursion](docs/en/Recursion/Recursion.md)**
    *   *What:* Functions that call themselves.
    *   *Why:* For solving "Divide and Conquer" problems (tree traversal, sorting).

### 🟡 Part II: Object-Oriented Programming (OOP)
*Building architecture through classes and objects.*

18. **[Classes and Objects](docs/en/Classes_and_Objects/Classes_and_Objects.md)**
    *   *What:* Defining user types, encapsulation, and methods.
    *   *Why:* The foundation of OOP - grouping data and logic.
19. **[Inheritance and Polymorphism](docs/en/Inheritance_and_Polymorphism/Inheritance_and_Polymorphism.md)**
    *   *What:* Class hierarchies and virtual functions.
    *   *Why:* For code reuse and flexible interfaces.
20. **[Operator Overloading](docs/en/Operator_Overloading/Operator_Overloading.md)**
    *   *What:* Using `+`, `-`, `<<` for custom objects.
    *   *Why:* For more readable and intuitive code syntax.

### 🔵 Part III: Memory Management & Modern C++
*Safety and efficiency through the RAII idiom.*

21. **[Smart Pointers](docs/en/Smart_Pointers/Smart_Pointers.md)**
    *   *What:* `unique_ptr`, `shared_ptr`, `weak_ptr`.
    *   *Why:* For automatic memory release and eliminating Memory Leaks.
22. **[Move Semantics](docs/en/Move_Semantics/Move_Semantics.md)**
    *   *What:* R-value references and `std::move`.
    *   *Why:* For drastically improving performance by avoiding deep copies.

### 🟣 Part IV: Advanced Features
*Tools for writing flexible and reliable code.*

23. **[Templates](docs/en/Templates/Templates.md)**
    *   *What:* Generic Programming.
    *   *Why:* For writing code that works with any data type.
24. **[Exception Handling](docs/en/Exception_Handling/Exception_Handling.md)**
    *   *What:* `try`, `catch`, `throw`.
    *   *Why:* For controlled error handling at runtime.
25. **[Type Casting](docs/en/Type_Casting/Type_Casting.md)**
    *   *What:* `static_cast`, `dynamic_cast`, `reinterpret_cast`.
    *   *Why:* For safe and explicit data type conversion.
26. **[Lambda Expressions](docs/en/Lambda_Expressions/Lambda_Expressions.md)**
    *   *What:* Anonymous inline functions.
    *   *Why:* For concise code when working with algorithms and callbacks.

### 🟠 Part V: Standard Library & Systems Programming
*Leveraging the full power of STL and hardware.*

27. **[STL Algorithms](docs/en/STL_Algorithms/STL_Algorithms.md)**
    *   *What:* `sort`, `find`, `transform`, and others.
    *   *Why:* For cleaner, faster, and less error-prone code compared to raw loops.
28. **[File I/O](docs/en/File_IO/File_IO.md)**
    *   *What:* Reading and writing via `fstream`.
    *   *Why:* For persisting data and configurations.
29. **[Multithreading](docs/en/Multithreading/Multithreading.md)**
    *   *What:* Threads, mutexes, async tasks.
    *   *Why:* For parallel processing and utilizing multi-core processors.

### 🛠️ Part VI: Engineering Practices & Tools
*How professional software is built.*

30. **[Design Patterns](docs/en/Design_Patterns/Design_Patterns.md)**
    *   *What:* Singleton, Factory, Observer, etc.
    *   *Why:* Established architectural solutions to common problems.
31. **[Unit Testing](docs/en/Unit_Testing/Unit_Testing.md)**
    *   *What:* Writing tests with Google Test.
    *   *Why:* For ensuring quality and preventing regressions.
32. **[Preprocessor and Macros](docs/en/Preprocessor_and_Macros/Preprocessor_and_Macros.md)**
    *   *What:* `#define`, `#include`, conditional compilation.
    *   *Why:* For build configuration and cross-platform code.
33. **[Build Systems - CMake](docs/en/Build_Systems_CMake/Build_Systems_CMake.md)**
    *   *What:* Compilation automation.
    *   *Why:* The industry standard for managing C++ projects.

### 🚀 Part VII: C++20 Innovations
*The future of the language.*

34. **[Concepts](docs/en/Concepts/Concepts.md)**
    *   *What:* Constraints for templates.
    *   *Why:* For clearer compilation errors and better documentation.
35. **[Modules](docs/en/Modules/Modules.md)**
    *   *What:* Replacement for header files (`#include`).
    *   *Why:* For drastically faster compilation and code isolation.
36. **[Ranges](docs/en/Ranges/Ranges.md)**
    *   *What:* Functional approach to algorithms.
    *   *Why:* For composing operations with pipe (`|`) syntax.
37. **[Coroutines](docs/en/Coroutines/Coroutines.md)**
    *   *What:* Asynchronous functions that can suspend and resume.
    *   *Why:* For lightweight and efficient async code and generators.

### 📦 Part VIII: Modern Libraries & Metaprogramming
*Specific tools for advanced users.*

38. **[Chrono and Filesystem](docs/en/Chrono_and_Filesystem/Chrono_and_Filesystem.md)**
    *   *What:* `std::chrono` and `std::filesystem`.
    *   *Why:* For precise timing and file/folder manipulation.
39. **[Optional, Variant, and Any](docs/en/Optional_Variant_Any/Optional_Variant_Any.md)**
    *   *What:* Type-safe containers for optional or polymorphic values.
    *   *Why:* For avoiding `void*` and `null`.
40. **[Type Traits and SFINAE](docs/en/Type_Traits_SFINAE/Type_Traits_SFINAE.md)**
    *   *What:* Type manipulation at compile-time.
    *   *Why:* For creating powerful and adaptive template libraries.

### ⚙️ Part IX: Low-Level & Architecture
*Optimization and high-level design.*

41. **[Bit Manipulation](docs/en/Bit_Manipulation/Bit_Manipulation.md)**
    *   *What:* Bit-level operations and the new `<bit>` library.
    *   *Why:* For embedded systems, compression, and flags.
42. **[Optimization and Cache](docs/en/Optimization_Cache/Optimization_Cache.md)**
    *   *What:* Cache Locality, Data-Oriented Design.
    *   *Why:* For writing code that maximizes hardware usage.
43. **[Data Serialization](docs/en/Data_Serialization/Data_Serialization.md)**
    *   *What:* Converting objects to bits/JSON.
    *   *Why:* For saving to files or network transmission.
44. **[SOLID Principles](docs/en/SOLID_Principles/SOLID_Principles.md)**
    *   *What:* The five laws of good OOP design.
    *   *Why:* For creating software that is easy to maintain and extend.
