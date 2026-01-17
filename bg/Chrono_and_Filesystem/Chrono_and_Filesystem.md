# Време и Файлова Система (Chrono and Filesystem) в C++

## 1. std::chrono (Библиотека за време)

Въведена в C++11, `<chrono>` е стандартният начин за работа с време, продължителност и часовници. Тя е строго типизирана, което предотвратява грешки (напр. събиране на секунди с милисекунди без преобразуване).

### 1.1. Основни компоненти
*   **Durations (Продължителност):** Разлика между два момента (`seconds`, `milliseconds`).
*   **Time Points (Точки във времето):** Конкретен момент (`now`).
*   **Clocks (Часовници):** `system_clock` (стенен часовник), `steady_clock` (монотонен, за измерване на интервали).

### 1.2. Пример: Измерване на производителност

```cpp
#include <iostream>
#include <chrono>
#include <thread>

void heavyWork() {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    
    heavyWork();

    auto end = std::chrono::high_resolution_clock::now();
    
    // Пресмятане на разликата
    std::chrono::duration<double> diff = end - start;
    
    std::cout << "Time taken: " << diff.count() << " s\n";
    
    // Преобразуване в милисекунди (integer)
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    std::cout << "Time taken: " << ms.count() << " ms\n";
}
```

---

## 2. std::filesystem (Файлова система)

Въведена в C++17, `<filesystem>` предоставя модерен, крос-платформен начин за работа с файлове и директории. Замества старите C-функции и Boost.Filesystem.

### 2.1. Пътища (Paths)

```cpp
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

int main() {
    fs::path p = "/home/user/docs/file.txt";

    std::cout << "Filename: " << p.filename() << "\n";      // file.txt
    std::cout << "Extension: " << p.extension() << "\n";    // .txt
    std::cout << "Parent: " << p.parent_path() << "\n";     // /home/user/docs
}
```

### 2.2. Манипулация на файлове

```cpp
// Проверка дали файл съществува
if (fs::exists("config.txt")) {
    // Копиране
    fs::copy("config.txt", "config.bak", fs::copy_options::overwrite_existing);
    
    // Преименуване / Местене
    fs::rename("config.bak", "backup/config.bak");
    
    // Размер на файл
    std::cout << "Size: " << fs::file_size("config.txt") << " bytes\n";
}
```

### 2.3. Обхождане на директории

```cpp
// Рекурсивно обхождане на папка
for (const auto& entry : fs::recursive_directory_iterator("src")) {
    if (entry.is_regular_file() && entry.path().extension() == ".cpp") {
        std::cout << "Found CPP source: " << entry.path() << "\n";
    }
}
```

---

## 3. Обобщение

*   Използвайте `std::chrono` за всичко свързано с време. Никога не ползвайте `int` за секунди, защото губите мерните единици.
*   Използвайте `std::filesystem` за навигация по диска. Той се грижи за разликите между `/` (Linux) и `\` (Windows).

```