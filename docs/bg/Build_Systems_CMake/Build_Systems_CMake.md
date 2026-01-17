# Build Системи и CMake в C++ - Пълно ръководство

## 1. Въведение: Защо ни е CMake?
Когато проектът ви порасне над един файл, ръчната компилация става кошмар. Имате нужда от инструмент, който да управлява зависимостите, да намира библиотеки и да генерира инструкции за компилатора. **CMake** е индустриалният стандарт за C++ – той не е компилатор, а генератор на проектни файлове.

---

## 2. Анатомия на CMakeLists.txt
Всеки проект започва с файл `CMakeLists.txt`.

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject VERSION 1.0)

# Задаване на C++ стандарт
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Създаване на изпълним файл
add_executable(MyApp main.cpp utils.cpp)
```

---

## 3. Управление на Библиотеки

### 3.1. Статични и Динамични библиотеки
Можете да разделите кода си на логически части:
```cmake
add_library(MathLib STATIC src/math.cpp)
target_link_libraries(MyApp PRIVATE MathLib)
```

### 3.2. Намиране на външни пакети (find_package)
CMake може автоматично да открива инсталирани библиотеки (напр. OpenCV, Boost, Qt):
```cmake
find_package(OpenCV REQUIRED)
target_link_libraries(MyApp PRIVATE ${OpenCV_LIBS})
```

---

## 4. Include Директории
За да не пишете дълги пътища в `#include`, кажете на CMake къде са хедърите:
```cmake
target_include_directories(MyApp PRIVATE ${CMAKE_SOURCE_DIR}/include)
```

---

## 5. Процесът на Build
Винаги използвайте отделна папка за компилация, за да запазите сорс кода чист:
1. `mkdir build && cd build`
2. `cmake ..` (Генериране)
3. `cmake --build .` (Компилация)

---

## 6. Предимства на CMake
*   **Крос-платформеност:** Работи еднакво добре на Windows, Linux и macOS.
*   **Интеграция:** Поддържа се от всички големи IDE (VS Code, CLion, Visual Studio).
*   **Мащабируемост:** Управлява проекти с хиляди файлове без проблем.

---
*(Този документ е част от курса "Ключови концепции в C++")*