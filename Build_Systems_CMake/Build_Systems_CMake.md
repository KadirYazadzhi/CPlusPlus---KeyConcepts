# Build Системи и CMake (Build Systems - CMake) в C++

## 1. Защо ни е Build система?

Когато пишем проста програма ("Hello World"), можем да я компилираме директно:
`g++ main.cpp -o app`

Но в реален проект имаме:
*   Стотици `.cpp` файлове.
*   Зависимости между тях.
*   Външни библиотеки (Boost, Qt, OpenCV).
*   Различни настройки за Debug и Release.
*   Необходимост да работи на Windows (Visual Studio), Linux (Make/Ninja), macOS (Xcode).

Ръчното управление на това е невъзможно. Тук идва **CMake**.

---

## 2. Какво е CMake?

CMake (Cross-platform Make) не е компилатор. Той е **генератор** на build файлове.
Вие описвате проекта си в `CMakeLists.txt`, а CMake генерира:
*   `Makefile` (за Linux/Unix)
*   `.sln` проект (за Visual Studio)
*   `build.ninja` (за Ninja)

Това ви позволява да напишете конфигурацията веднъж и тя да работи навсякъде.

---

## 3. Основи на CMakeLists.txt

Всеки CMake проект започва с файл `CMakeLists.txt` в коренната директория.

### 3.1. Минимален пример

```cmake
# 1. Изисквана версия на CMake
cmake_minimum_required(VERSION 3.10)

# 2. Име на проекта и език
project(MyProject VERSION 1.0 LANGUAGES CXX)

# 3. Стандарт на C++ (C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 4. Създаване на изпълним файл (Executable)
# app е името на файла, main.cpp е сорс кодът
add_executable(app main.cpp utils.cpp)
```

### 3.2. Добавяне на библиотеки

Ако имате разделение на код, добра практика е да правите библиотеки.

```cmake
# Създава статична библиотека (libmathlib.a / mathlib.lib)
add_library(mathlib STATIC math.cpp geometry.cpp)

# Свързване на библиотеката с главната програма
target_link_libraries(app PRIVATE mathlib)
```

---

## 4. Управление на зависимости (Include Directories)

Когато имате хедър файлове в подпапки (напр. `include/`), трябва да кажете на CMake къде да ги търси.

```cmake
# Структура:
# /src (cpp файлове)
# /include (h файлове)

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/include)
```

---

## 5. Как се компилира с CMake?

Процесът винаги е в две стъпки: **Configure** и **Build**.
Препоръчва се "Out-of-source build" (в отделна папка), за да не замърсявате кода.

```bash
# 1. Създаване на папка за build
mkdir build
cd build

# 2. Генериране (Configure)
# .. сочи към папката, където е CMakeLists.txt
cmake .. 

# 3. Компилиране (Build)
cmake --build .
```

---

## 6. Variables и Cache

CMake има променливи.
*   `${CMAKE_SOURCE_DIR}`: Къде е сорс кодът.
*   `${PROJECT_NAME}`: Името на проекта.

Можете да подавате опции от командния ред:
`cmake .. -DCMAKE_BUILD_TYPE=Release`

В кода:
```cmake
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG_MODE)
endif()
```

---

## 7. find_package (Външни библиотеки)

Ако искате да ползвате инсталирана библиотека (напр. OpenCV или Boost).

```cmake
find_package(OpenCV REQUIRED)

add_executable(vision_app main.cpp)

# Свързване с намерената библиотека
target_link_libraries(vision_app PRIVATE ${OpenCV_LIBS})
```

---

## 8. Обобщение

*   CMake е стандартът за C++ проекти.
*   Никога не използвайте директни пътища (`C:\Users\John...`), използвайте относителни пътища и променливи.
*   Разделяйте проекта на малки библиотеки (`add_library`) вместо един огромен изпълним файл.
*   Винаги правете build в отделна директория (`build/`).
