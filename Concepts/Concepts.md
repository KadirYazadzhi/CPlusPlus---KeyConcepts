# Концепти (Concepts) в C++20

## 1. Проблемът на Шаблоните

Преди C++20, шаблоните (templates) имаха един огромен недостатък: **ужасни съобщения за грешки**.

Ако се опитвате да сортирате `std::list` със `std::sort` (което е невъзможно, защото sort изисква Random Access Iterator, а list има само Bidirectional), ще получите 500 реда неразбираеми грешки за вътрешността на алгоритъма за сортиране.

Причината: Шаблонът просто се опитва да компилира кода с подадения тип и гърми някъде дълбоко.

**Concepts** решават това, като ни позволяват да ограничим какви типове приема един шаблон.

---

## 2. Синтаксис

Ключовата дума е `requires`.

```cpp
#include <iostream>
#include <concepts>

// Дефинираме функция, която работи САМО с целочислени типове
template <typename T>
requires std::integral<T> 
T add(T a, T b) {
    return a + b;
}

// Алтернативен (кратък) синтаксис
void print(std::integral auto value) {
    std::cout << value << "\n";
}

int main() {
    add(5, 10);     // OK: int е integral
    // add(5.5, 2.3); // ГРЕШКА: double не е integral!
    // Грешката е кратка и ясна: "constraint not satisfied"
}
```

---

## 3. Дефиниране на собствени Концепти

Можем да създаваме свои ограничения. Концептът е просто предикат (условие), което връща `true` или `false` по време на компилация.

```cpp
template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <typename T>
concept HasToString = requires(T v) {
    { v.toString() } -> std::convertible_to<std::string>;
};

// Използване
void logObject(const HasToString auto& obj) {
    std::cout << obj.toString() << "\n";
}
```

В този пример `HasToString` проверява дали типът `T` има метод `toString()`, който връща нещо, конвертируемо към `std::string`. Това се нарича **Duck Typing** на ниво компилация.

---

## 4. Стандартни Концепти

В заглавния файл `<concepts>` има много готови концепции:

*   `std::same_as<T, U>`
*   `std::derived_from<T, Base>`
*   `std::convertible_to<From, To>`
*   `std::default_initializable`
*   `std::copyable`
*   `std::movable`

---

## 5. requires expression

Клаузата `requires` е много мощна. Тя позволява да тествате дали даден код е валиден за даден тип.

```cpp
template <typename T>
concept Addable = requires(T a, T b) {
    a + b; // Трябва да може да се събира
};
```

---

## 6. Обобщение

*   Концептите са най-голямата промяна в C++20 шаблоните.
*   Те правят кода по-документиран (вижда се какво изисква функцията).
*   Правят грешките четими.
*   Ускоряват компилацията (компилаторът спира веднага, ако условието не е изпълнено).

```
