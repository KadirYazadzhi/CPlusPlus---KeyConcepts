# C++20 Modules (Модули) - Пълно техническо ръководство

## 1. Въведение: Краят на Хедър файловете

От 1970-те години насам (наследено от C), включването на код ставаше чрез `#include`. Това е проста директива за Copy-Paste.
Това води до огромни проблеми:
1.  **Бавна компилация:** Ако `vector` се ползва в 1000 файла, той се парсва (компилира) 1000 пъти.
2.  **Липса на изолация:** Макроси от един хедър могат да "изтекат" и да счупят друг хедър (позорният проблем с `windows.h` и `min/max`).
3.  **ODR Violations:** Нарушаване на One Definition Rule при грешно включване.

**Модулите (C++20)** са решението. Те въвеждат истинска компонентна архитектура, подобна на Python, Java или C#.

---

## 2. Сравнение с други езици

За да разберете модулите, е полезно да ги сравните с това, което познавате от други езици.

*   **Java:** В Java `import java.util.List` казва на компилатора да зареди класа `List` от classpath. Това е бързо и изолирано.
*   **Python:** В Python `import math` изпълнява модула веднъж и създава обект с функциите.
*   **C++ (Legacy):** В C++ `#include <vector>` буквално отваря файла `vector` и го изсипва в текущия файл.

C++ Модулите се доближават до модела на Java. Те са предварително компилирани бинарни артефакти (BMI), които се зареждат светкавично, без да замърсяват глобалното пространство с макроси.

---

## 3. Синтаксис: Export и Import

Модулът се дефинира в специален файл (обикновено `.ixx` за MSVC или `.cppm` за Clang).

### 3.1. Създаване на Модул (Interface Unit)

```cpp
// math_engine.cppm
export module MathEngine; // Декларираме, че този файл дефинира модул "MathEngine"

// Този import остава скрит (не изтича към потребителите)
import <vector>; 

// Експортваме функция (публичен интерфейс)
export int add(int a, int b) {
    return a + b;
}

// Експортваме цял клас
export class Calculator {
public:
    int multiply(int a, int b) { return a * b; }
};

// Тази функция е видима само ВЪТРЕ в модула (като static/private)
void helper_internal() { 
    // ... 
}
```

### 3.2. Използване на Модул (Client)

```cpp
// main.cpp
import MathEngine; // Зареждаме вече компилирания бинарен интерфейс
import <iostream>;

int main() {
    std::cout << add(5, 3) << "\n";
    
    // helper_internal(); // ГРЕШКА! Не е намерен.
}
```

---

## 4. Дялове на Модули (Module Partitions)

За големи библиотеки, не искаме целият код да е в един гигантски файл. Можем да разделим модула на части (partitions).

```cpp
// math_geometry.cppm
export module MathEngine:Geometry; // Дял "Geometry"
export struct Point { int x, y; };

// math_algebra.cppm
export module MathEngine:Algebra; // Дял "Algebra"
export int solve_equation() { return 42; }

// MathEngine.cppm (Главен файл)
export module MathEngine; // Основният модул

// Ре-експортваме дяловете, за да са видими за клиента
export import :Geometry;
export import :Algebra;
```
Потребителят вижда само `import MathEngine;`, но отдолу структурата е разделена.

---

## 5. Глобален Модулен Фрагмент (Global Module Fragment)

Светът все още не е пренаписан на модули. Често трябва да ползвате стари библиотеки (OpenSSL, Windows API, POSIX) вътре в новия си модул.
За целта се използва специална секция в началото на файла:

```cpp
module; // Начало на Global Module Fragment

#include <windows.h> // Тук може да ползваме #include
#include <openssl/ssl.h>

export module SecureNet; // Същинското начало на модула

import <string>;

export void connect() {
    // Тук можем да ползваме символи от windows.h и openssl
    // Но те НЕ изтичат навън към този, който прави 'import SecureNet'
}
```

---

## 6. Професионално обобщение

1.  **Скорост:** В големи проекти (милиони редове), модулите могат да намалят времето за компилация с 50-80%.
2.  **Изолация:** Няма повече замърсяване с макроси. `import` е хигиеничен.
3.  **Build Systems:** Поддръжката в CMake (3.26+) и MSBuild е вече добра, но все още изисква внимание. Linux поддръжката (GCC/Clang) напредва бързо.
4.  **Бъдещето:** `import std;` (C++23) ще ви даде достъп до целия STL с един ред, компилиран за части от секундата. Това е бъдещето на C++.

---
*(Този документ е част от "The Ultimate C++ Mastery Framework".)*
