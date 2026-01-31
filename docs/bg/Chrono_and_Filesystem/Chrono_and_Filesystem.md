# Време и Файлова Система в C++ (Chrono & Filesystem) - Пълно ръководство

## 1. std::chrono: Овладяване на Времето

Работата с време в програмирането е пословична със своята сложност. Високосни години, часови зони, секунди на координацията (leap seconds) – всичко това прави простото "колко е часът" трудна задача.
C++ (от стандарта C++11 насам) предлага библиотеката "<chrono>", която е една от най-добре проектираните системи за време в съвременните езици. Тя е **Type-Safe**, което означава, че компилаторът не ви позволява да съберете "секунди" с "метри" или да присвоите "милисекунди" на променлива за "часове" без изрично преобразуване.

### 1.1. Трите основни компонента

Системата се гради върху три концепции:

1.  **Duration (Продължителност):** Интервал от време.
    *   Представя се като `брой тиктакания` + `период на едно тиктакане`.
    *   Примери: `std::chrono::seconds`, `std::chrono::milliseconds`, `std::chrono::hours`.
    *   **Литерали (C++14):** Можете да пишете `auto time = 10s + 500ms;`.

2.  **Time Point (Времева точка):** Конкретен момент във времето.
    *   Представлява продължителност (Duration) спрямо някакво начало (Epoch).
    *   `std::chrono::time_point`.

3.  **Clock (Часовник):** Източникът на "Сега".
    *   **`std::chrono::system_clock`:** Стенен часовник (Wall clock). Показва реалното време (дата и час). Може да се променя от ОС или потребителя. Неподходящ за измерване на интервали.
    *   **`std::chrono::steady_clock`:** Монотонен часовник. Гарантирано върви само напред и с постоянна скорост. Използва се за хронометри (`Stopwatch`) и измерване на производителност.
    *   **`std::chrono::high_resolution_clock`:** Часовникът с най-кратък възможен период на тиктакане на дадената платформа.

### 1.2. Измерване на производителност (Benchmarking)

```cpp
#include <iostream>
#include <chrono>
#include <thread>

void slow_function() {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

int main() {
    auto start = std::chrono::steady_clock::now();
    
    slow_function();
    
    auto end = std::chrono::steady_clock::now();
    
    // Пресмятане на разликата
    // duration_cast е нужен за превръщане в конкретна мерна единица
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Time elapsed: " << diff.count() << " ms" << std::endl;
    return 0;
}
```

### 1.3. Форматиране на дати (C++20)
Преди C++20, принтирането на дати беше ужасно (с C-style `strftime`). Сега имаме модерна поддръжка:

```cpp
#include <chrono>
#include <format> // C++20

auto now = std::chrono::system_clock::now();
std::cout << std::format("Date: {:%Y-%m-%d %H:%M:%S}", now) << std::endl;
```

---

## 2. std::filesystem: Модерна работа с файлове

До C++17, работата с файлове и директории беше кошмар от `#ifdef _WIN32` макроси, за да се справяме с разликите между Windows (`\`) и Linux (`/`). Библиотеката "<filesystem>" абстрахира всичко това.

### 2.1. Класът `std::filesystem::path`
Това е основният градивен блок. Той интелигентно манипулира пътища.

```cpp
namespace fs = std::filesystem;

fs::path p = "/home/user";
p /= "documents"; // Използва правилния разделител (/ или \)
p /= "report.txt";

std::cout << p.filename() << std::endl;      // report.txt
std::cout << p.extension() << std::endl;     // .txt
std::cout << p.parent_path() << std::endl;   // /home/user/documents
```

### 2.2. Основни операции
Всички операции могат да хвърлят изключения (`fs::filesystem_error`) или да връщат `std::error_code` (ако не искате try-catch).

*   **Проверка:** `fs::exists(p)`, `fs::is_directory(p)`, `fs::is_regular_file(p)`.
*   **Създаване:** `fs::create_directory(p)` (една папка) или `fs::create_directories(p)` (целия път, като `mkdir -p`).
*   **Копиране:** `fs::copy(src, dest, fs::copy_options::recursive)`.
*   **Преименуване/Местене:** `fs::rename(old_p, new_p)`.
*   **Изтриване:** `fs::remove(p)` (един файл) или `fs::remove_all(p)` (папка с всичко в нея).

### 2.3. Обхождане на директории (Directory Iterator)
Това е най-честата задача – "обходи всички файлове в папката".

```cpp
void list_cpp_files(const fs::path& dir_path) {
    if (!fs::exists(dir_path) || !fs::is_directory(dir_path)) return;

    // recursive_directory_iterator влиза и в подпапките
    for (const auto& entry : fs::recursive_directory_iterator(dir_path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".cpp") {
            std::cout << "Found source: " << entry.path() 
                      << " Size: " << entry.file_size() << " bytes\n";
        }
    }
}
```

### 2.4. Дисково пространство
```cpp
fs::space_info info = fs::space("/");
std::cout << "Free space: " << info.free / 1024 / 1024 << " MB\n";
```

---

## 3. Често срещани проблеми и решения

### 3.1. Unicode и Cross-Platform пътища
Windows използва UTF-16 (`std::wstring`) за файловата система, докато Linux използва UTF-8 (`std::string`). `std::filesystem::path` се опитва да скрие това, като съхранява "нативния" формат.
*   **Съвет:** Ако пишете крос-платформено приложение, използвайте `path.string()` внимателно. Най-добре ползвайте `path.u8string()` (C++20), ако ви трябва UTF-8 представяне навсякъде.

### 3.2. Timezones (Часови зони)
Стандартната библиотека получи пълна поддръжка на часови зони (`std::chrono::zoned_time`) в C++20. Това включва базата данни на IANA.
```cpp
auto now = std::chrono::system_clock::now();
auto local_time = std::chrono::zoned_time{std::chrono::current_zone(), now};
std::cout << local_time << std::endl;
```

---

## 4. Професионално обобщение

Библиотеките `chrono` и `filesystem` са едни от най-добрите примери за модерна C++ разработка – те превръщат сложни, платформено-зависими задачи в елегантен, четим и безопасен код. Спрете да използвате `ctime`, `windows.h` или `dirent.h`. Модерният стандарт има всичко, от което се нуждаете.

---
*(Този документ е част от "The Ultimate C++ Mastery Framework".)*