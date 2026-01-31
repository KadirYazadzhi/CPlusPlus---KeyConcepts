# Build Системи и CMake - Пълно техническо ръководство

## 1. Въведение: Защо ни трябва "Build System"?

В началото на вашето обучение, компилацията изглежда проста: `g++ main.cpp -o app`. Но реалният свят е жесток. Един средно голям C++ проект съдържа стотици `.cpp` файлове, десетки хедъри, външни библиотеки (като Boost, OpenCV), ресурсни файлове (икони, шейдъри) и тестове.

Опитът да се управлява това ръчно или с прост shell скрипт води до катастрофа.
**Build System** е софтуерен архитект, който знае как да сглоби всички тези парчета в работещо приложение.

### Основни задачи на Build системата:
1.  **Dependency Tracking:** "Ако променя `User.h`, кои 50 `.cpp` файла трябва да се прекомпилират?"
2.  **Platform Abstraction:** "Как да компилирам това на Windows с MSVC и на Linux с GCC без да променям кода?"
3.  **Third-party Management:** "Къде се намира библиотеката `OpenSSL` на тази машина?"

---

## 2. CMake: Де факто стандартът

CMake (Cross-platform Make) не е билд система в класическия смисъл. Той е **генератор на билд системи**. Вие описвате проекта си на абстрактен език (`CMakeLists.txt`), а CMake генерира "рецептата" за конкретната платформа:
*   **Linux:** Генерира `Makefile` (за `make`) или `build.ninja` (за `Ninja`).
*   **Windows:** Генерира `.sln` (за Visual Studio) или `MinGW Makefiles`.
*   **MacOS:** Генерира `Xcode` проект.

Това означава, че научавайки CMake, вие можете да билдвате софтуер за всяка ОС на планетата (включително Android и iOS).

---

## 3. Структура на Професионален Проект

Добрият CMake файл започва с добра файлова структура.

```text
MyProject/
├── CMakeLists.txt          (Root конфигурация)
├── src/
│   ├── CMakeLists.txt      (Конфигурация за сорса)
│   ├── main.cpp
│   └── game.cpp
├── include/
│   └── myproject/
│       └── game.h
├── tests/
│   ├── CMakeLists.txt
│   └── test_game.cpp
└── external/               (Външни библиотеки)
```

---

## 4. Модерен CMake (Target-Based Approach)

Преди версия 3.0, CMake разчиташе на глобални променливи (`include_directories`). Това беше грешка. Модерният CMake (3.15+) работи с **Targets** (Цели). Всяка библиотека или изпълним файл е обект, който носи своите свойства със себе си.

### 4.1. Основен CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.15)

# Дефиниция на проекта и версията
project(SuperGame VERSION 1.0.0 LANGUAGES CXX)

# Задължително: C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Изключва компилаторни разширения (като -std=gnu++20)

# Добавяне на поддиректории
add_subdirectory(src)
add_subdirectory(tests)
```

### 4.2. Дефиниране на Библиотека (src/CMakeLists.txt)

```cmake
# Създаваме библиотека (STATIC или SHARED)
add_library(GameEngine STATIC 
    game.cpp
    physics.cpp
)

# Alias namespaces (добра практика за чистота)
add_library(MyProject::GameEngine ALIAS GameEngine)

# Къде са хедърите?
# PUBLIC: И за мен, и за тези, които ме ползват.
# PRIVATE: Само за мен (скрити зависимости).
target_include_directories(GameEngine PUBLIC 
    "${CMAKE_SOURCE_DIR}/include"
)

# Компилаторни флагове (Warnings)
if(MSVC)
    target_compile_options(GameEngine PRIVATE /W4 /WX)
else()
    target_compile_options(GameEngine PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
```

### 4.3. Дефиниране на Executable (src/CMakeLists.txt)

```cmake
add_executable(GameApp main.cpp)

# Свързване с библиотеката
target_link_libraries(GameApp PRIVATE MyProject::GameEngine)
```

---

## 5. Управление на Зависимости (Dependency Management)

Това е най-сложната част. CMake предлага няколко начина:

### 5.1. `find_package` (Системни библиотеки)
Търси библиотека, инсталирана на ОС (напр. чрез `apt install` или `vcpkg`).
```cmake
find_package(OpenCV 4.5 REQUIRED)

# Ако е намерена, добавяме я
target_link_libraries(GameApp PRIVATE opencv_core opencv_highgui)
```

### 5.2. `FetchContent` (Модерният начин)
Изтегля и компилира библиотеката директно от Git по време на конфигурацията. Няма нужда потребителят да инсталира нищо предварително!

```cmake
include(FetchContent)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
)

FetchContent_MakeAvailable(json)

target_link_libraries(GameApp PRIVATE nlohmann_json::nlohmann_json)
```

---

## 6. Тестване и Инсталация

### 6.1. CTest
CMake има вграден тест рънър.

```cmake
enable_testing()
add_test(NAME CoreTest COMMAND TestsExecutable)
```
Сега можете да пуснете всички тестове с командата `ctest`.

### 6.2. Инсталация
Какво става, когато потребителят напише `make install`?

```cmake
install(TARGETS GameApp DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)
```

---

## 7. Генератори и Билдване (Workflow)

Професионалистите **никога** не билдват в сорс директорията. Това се нарича "Out-of-source build".

**Стъпка 1: Конфигурация**
```bash
mkdir build && cd build
# Използване на Ninja (много по-бърз от Make)
cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release ..
```

**Стъпка 2: Билдване**
```bash
# --build абстрахира конкретния инструмент (make, ninja, msbuild)
cmake --build . --parallel 8  # Ползвай 8 ядра
```

---

## 8. CMake Presets (C++20 ера)

Вместо да помните дълги командни редове (`-DCMAKE_BUILD_TYPE=Release -G Ninja ...`), създайте файл `CMakePresets.json` в корена.

```json
{
  "version": 3,
  "configurePresets": [
    {
      "name": "windows-release",
      "generator": "Visual Studio 17 2022",
      "binaryDir": "${sourceDir}/out/build/x64-release",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Release"
      }
    }
  ]
}
```
Сега билдвате просто с: `cmake --preset windows-release`.

---

## 9. Професионално обобщение

1.  **Scope е всичко:** Научете разликата между `PRIVATE`, `PUBLIC` и `INTERFACE`. Това определя видимостта на хедъри и флагове.
2.  **Globbing е зло:** Не използвайте `file(GLOB_RECURSE SOURCES *.cpp)`. Ако добавите нов файл, CMake няма да разбере и няма да регенерира билда. Изреждайте файловете ръчно.
3.  **CCache:** За големи проекти, настройте `find_program(CCACHE_PROGRAM ccache)` и го активирайте. Това намалява времето за прекомпилация с до 90%.
4.  **Static Analysis:** Интегрирайте `clang-tidy` директно в CMake чрез `set(CMAKE_CXX_CLANG_TIDY "clang-tidy;...")`.

---
*(Този документ е част от "The Ultimate C++ Mastery Framework".)*
