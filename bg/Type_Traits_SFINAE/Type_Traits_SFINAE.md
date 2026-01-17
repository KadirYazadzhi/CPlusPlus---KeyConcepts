# Type Traits и SFINAE в C++

## 1. Въведение в Метапрограмирането

Метапрограмирането е писане на код, който генерира друг код по време на компилация. В C++ това става чрез шаблони.

**Type Traits** (Характеристики на типовете) е библиотека (`<type_traits>`), която ни позволява да задаваме въпроси за типовете на данните.

---

## 2. Type Traits

Това са шаблонни структури, които връщат `true` или `false` (чрез члена `::value`).

```cpp
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::is_integral<int>::value << "\n";      // true
    std::cout << std::is_integral<float>::value << "\n";    // false
    
    std::cout << std::is_pointer<int*>::value << "\n";      // true
    std::cout << std::is_const<const int>::value << "\n";   // true
}
```

Можем да използваме това, за да оптимизираме алгоритми.

```cpp
template <typename T>
void process(T val) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "Optimized integer path\n";
    } else {
        std::cout << "Generic path\n";
    }
}
```

---

## 3. SFINAE (Substitution Failure Is Not An Error)

Това е един от най-страшните акроними в C++, но концепцията е проста: **"Ако един шаблон не става за даден тип, не давай грешка, а просто го игнорирай и пробвай следващия."**

Това ни позволява да имаме няколко функции с едно и също име, но за различни *категории* типове.

### std::enable_if
Най-честият инструмент за SFINAE. Позволява функцията да съществува само ако дадено условие е изпълнено.

```cpp
// Тази функция съществува САМО за целочислени типове
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
printNum(T x) {
    std::cout << "Integer: " << x << "\n";
}

// Тази функция съществува САМО за числа с плаваща запетая
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
printNum(T x) {
    std::cout << "Float: " << x << "\n";
}

int main() {
    printNum(10);   // Вика първата
    printNum(3.14); // Вика втората
    // printNum("Hi"); // ГРЕШКА: Нито един шаблон не пасва!
}
```

В C++20 това до голяма степен се заменя от **Concepts** (`requires`), които са много по-четими, но SFINAE все още се ползва в стари кодови бази.

---

## 4. Обобщение

*   **Type Traits** ви дават информация за типовете по време на компилация.
*   **SFINAE** и `enable_if` позволяват да включвате/изключвате функции от компилацията базирано на типовете.
*   Използвайте `if constexpr` (C++17) или Concepts (C++20) вместо SFINAE, където е възможно.

```