# Build Системи и CMake - Пълно техническо ръководство

## 1. Въведение: Проблемът на "Сглобяването"

Когато проектът ви е един файл `main.cpp`, командата `g++ main.cpp` е достатъчна. Но когато проектът порасне до 100 файла, 5 външни библиотеки и поддръжка за Windows и Linux, ръчната компилация става кошмар.
**Build System** е софтуер, който автоматизира този процес. Той следи зависимостите между файловете ("Ако променя `header.h`, кои `.cpp` файлове трябва да се прекомпилират?").

---

## 2. Защо CMake е де факто стандартът?

CMake (Cross-platform Make) **НЕ Е** компилатор. Той е **Meta-Build System**.
Вие описвате проекта си на абстрактен език (`CMakeLists.txt`), а CMake генерира файлове за реалната билд система на вашата платформа:
*   **Linux:** Генерира `Makefile` (за `make`) или `build.ninja` (за `Ninja`).
*   **Windows:** Генерира `.sln` (за Visual Studio) или `MinGW Makefiles`.
*   **MacOS:** Генерира `Xcode` проект.

Това ви позволява да напишете конфигурацията веднъж и да компилирате навсякъде.

---

## 3. Анатомия на професионалния CMakeLists.txt

Ето как изглежда модерният CMake (Target-based подход):

```cmake
# 1. Изискване за версия
cmake_minimum_required(VERSION 3.15)

# 2. Дефиниция на проекта
project(GameEngine VERSION 1.0.0 LANGUAGES CXX)

# 3. Стандарт (C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Дефиниране на изпълним файл
add_executable(my_game src/main.cpp src/player.cpp)

# 5. Включване на директории (за да работят #include "player.h")
target_include_directories(my_game PUBLIC ${CMAKE_SOURCE_DIR}/include)

# 6. Оптимизации (само за Release)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(my_game PRIVATE -O3 -march=native)
endif()
```

---

## 4. Управление на Зависимости (Dependency Management)

Най-трудната част в C++ е добавянето на библиотеки. CMake предлага два мощни механизма:

### 4.1. find_package (За инсталирани библиотеки)
Търси библиотека, която вече е инсталирана в системата (напр. чрез `apt install` или `vcpkg`).
```cmake
find_package(OpenCV REQUIRED)
target_link_libraries(my_game PRIVATE opencv_core opencv_highgui)
```

### 4.2. FetchContent (За изтегляне на сорс код)
Модерен модул (от CMake 3.11), който тегли библиотека от GitHub по време на конфигурацията и я компилира заедно с вашия проект.
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

## 5. Structuring: Targets и Scopes

В модерния CMake всичко е **Target** (изпълним файл или библиотека).
Функциите като `target_include_directories` и `target_link_libraries` имат обхват (Scope):
1.  **PRIVATE:** Настройката важи само за текущия таргет.
2.  **INTERFACE:** Настройката не важи за текущия таргет, но се предава на всеки, който зависи от него (link-ва го).
3.  **PUBLIC:** Важи и за текущия, и за зависимите.

**Пример:** Ако пишете библиотека, която има `.h` файлове в `include/`, използвайте `PUBLIC`, за да може потребителите на библиотеката автоматично да виждат хедърите.

---

## 6. Out-of-Source Builds

Никога не пускайте `cmake .` в коренната директория! Това замърсява сорса с временни файлове.
Правилният начин:
```bash
mkdir build
cd build
cmake ..  # Генериране
cmake --build .  # Компилация
```

---

## 7. Професионално обобщение

1.  **Modern CMake:** Забравете за променливи като `include_directories()`. Използвайте само `target_...` команди.
2.  **Генератори:** Използвайте **Ninja** вместо Make. Той е значително по-бърз при паралелна компилация.
3.  **Tooling:** Интегрирайте `Clang-Tidy` и `CppCheck` директно в CMake скрипта за автоматичен анализ на качеството.
4.  **CCache:** Настройте CMake да ползва `ccache`, за да кешира компилираните обекти и да ускори повторните билдове с 10x.

---
*(Документацията е подготвена за проекта "Ключови концепции в C++".*
*Версия: 3.0 - Експертна детайлност)*