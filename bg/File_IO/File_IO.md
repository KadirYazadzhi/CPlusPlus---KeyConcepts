# Работа с Файлове (File I/O) в C++

## 1. Въведение

В C++ работата с файлове се извършва чрез потоци (streams), подобно на работата с конзолата (`cin`/`cout`). Класовете са дефинирани в `<fstream>`.

*   `std::ofstream` (Output File Stream): За писане във файлове.
*   `std::ifstream` (Input File Stream): За четене от файлове.
*   `std::fstream`: За четене и писане едновременно.

---

## 2. Писане във Файл

```cpp
#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Отваряне на файл за писане
    // Ако файлът не съществува, се създава.
    // Ако съществува, съдържанието му се изтрива (Truncate), освен ако не ползваме std::ios::app
    std::ofstream outFile("example.txt");

    if (outFile.is_open()) {
        outFile << "Hello, File I/O!\n";
        outFile << "This is line 2.\n";
        outFile << 42 << std::endl;
        
        outFile.close(); // Добра практика, макар че деструкторът го прави автоматично
        std::cout << "File written successfully.\n";
    } else {
        std::cerr << "Error opening file!\n";
    }

    return 0;
}
```

---

## 3. Четене от Файл

```cpp
#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inFile("example.txt");

    if (!inFile) { // Проверка за грешка
        std::cerr << "File not found!\n";
        return 1;
    }

    std::string line;
    // Четене ред по ред
    while (std::getline(inFile, line)) {
        std::cout << line << "\n";
    }
    
    // Алтернатива: Четене дума по дума
    // std::string word;
    // while (inFile >> word) { ... }

    inFile.close();
    return 0;
}
```

---

## 4. Режими на отваряне (File Modes)

Можем да комбинираме флагове с оператора `|`.

*   `std::ios::in`: За четене (по подразбиране за ifstream).
*   `std::ios::out`: За писане (по подразбиране за ofstream).
*   `std::ios::app`: Append (добавяне в края, без триене).
*   `std::ios::trunc`: Изтриване на съдържанието (по подразбиране за out).
*   `std::ios::binary`: Бинарен режим (без преобразуване на `\n`).

```cpp
// Отваряне за добавяне (Append)
std::ofstream logFile("log.txt", std::ios::out | std::ios::app);
logFile << "New log entry\n";
```

---

## 5. Бинарни Файлове

При текстовите файлове числата се записват като символи ("123" са 3 байта). При бинарните се записват директно битовете от паметта (int 123 е 4 байта).

```cpp
struct Data {
    int id;
    double value;
};

// Писане
Data d = {1, 3.14};
std::ofstream binOut("data.bin", std::ios::binary);
binOut.write(reinterpret_cast<char*>(&d), sizeof(Data));
binOut.close();

// Четене
Data inD;
std::ifstream binIn("data.bin", std::ios::binary);
binIn.read(reinterpret_cast<char*>(&inD), sizeof(Data));
```

⚠️ **Внимание:** Бинарното записване на сложни обекти (`std::string`, `std::vector`) е опасно, защото те съдържат указатели. Трябва да се сериализират поле по поле.

---

## 6. Обобщение

*   Използвайте `std::getline` за четене на цели редове.
*   Винаги проверявайте дали файлът е отворен успешно (`is_open()` или `!fail()`).
*   Използвайте `std::ios::binary` за нетекстови данни.

```
