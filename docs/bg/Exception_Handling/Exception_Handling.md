# Обработка на Изключения (Exception Handling) в C++

## 1. Въведение

Изключенията са механизъм за справяне с грешки по време на изпълнение (Run-time errors) по контролиран начин. Вместо програмата да "крашне" или да проверяваме кодове за грешки след всяка функция, ние "хвърляме" изключение и го "хващаме" на безопасно място.

Основни ключови думи: `try`, `catch`, `throw`.

---

## 2. Синтаксис

```cpp
#include <iostream>
#include <stdexcept> // За std::runtime_error

double divide(double a, double b) {
    if (b == 0) {
        // Хвърляме грешка (string, int или обект)
        throw "Division by zero!"; 
    }
    return a / b;
}

int main() {
    try {
        // Опасен код
        std::cout << divide(10, 2) << std::endl;
        std::cout << divide(5, 0) << std::endl; // Тук ще гръмне
        std::cout << "This will not run\n";     // Пропуска се
    }
    catch (const char* msg) {
        // Обработка на грешката
        std::cerr << "Error: " << msg << std::endl;
    }

    std::cout << "Program continues...\n";
    return 0;
}
```

---

## 3. Стандартни Изключения

C++ предоставя йерархия от класове за грешки в `<stdexcept>`. Всички те наследяват от `std::exception`.

*   `std::exception` (Базов клас)
    *   `std::logic_error` (Грешки в логиката на програмата)
        *   `std::out_of_range` (Достъп извън масива)
        *   `std::invalid_argument` 
    *   `std::runtime_error` (Грешки, които не могат да се предвидят)
        *   `std::overflow_error`

**Добра практика:** Винаги хвърляйте обекти, наследяващи `std::exception`, и ги хващайте по референция.

```cpp
try {
    std::vector<int> v(5);
    v.at(10) = 100; // Хвърля out_of_range
}
catch (const std::exception& e) {
    // Методът what() връща описание на грешката
    std::cerr << "Standard exception: " << e.what() << '\n';
}
catch (...) {
    // Хваща ВСИЧКО друго (catch-all)
    std::cerr << "Unknown error occurred\n";
}
```

---

## 4. Stack Unwinding (Развиване на стека)

Когато се хвърли изключение, C++ започва да търси `catch` блок нагоре по стека с извиквания. Докато излиза от функциите, той **автоматично унищожава** всички локални обекти (извиква техните деструктори).

Това е гаранцията, че **RAII** обектите (като `std::unique_ptr` или `std::vector`) ще освободят паметта си дори при грешка.

```cpp
void riskyFunction() {
    std::unique_ptr<int> p = std::make_unique<int>(5);
    throw std::runtime_error("Boom!");
    // p ще бъде унищожен правилно тук автоматично
}
```

---

## 5. noexcept

Ако сте сигурни, че дадена функция никога не хвърля изключение, маркирайте я с `noexcept`. Това позволява на компилатора да прави допълнителни оптимизации.

```cpp
void safeFunction() noexcept {
    // Този код не трябва да хвърля грешки
}
```

Деструкторите по подразбиране са `noexcept`. **Никога** не хвърляйте изключение от деструктор! Ако това се случи по време на Stack Unwinding, програмата ще бъде прекратена незабавно (`std::terminate`).

---

## 6. Обобщение

*   Използвайте изключения за обработка на **изключителни** ситуации (грешки), а не за нормален контрол на потока.
*   Хващайте по **const reference** (`const std::exception& e`).
*   Разчитайте на RAII за почистване на ресурси при грешка.

```
