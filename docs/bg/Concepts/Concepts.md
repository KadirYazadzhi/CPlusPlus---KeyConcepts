# C++20 Concepts (Концепти) - Пълно техническо ръководство

## 1. Въведение: Краят на "Template Error Hell"

Шаблоните (Templates) направиха C++ най-мощния език за генерично програмиране. Но те имаха една фатална слабост: **Липса на договори**.
Ако напишете функция `template<typename T> void sort(T& c)` и подадете `std::list` (който няма Random Access), компилаторът ще избълва 500 реда грешки, сочещи някъде дълбоко в имплементацията на `std::sort`, вместо да ви каже просто: "Този тип не поддържа индексиране!".

**Concepts (C++20)** решават това. Те са начин да кажем на компилатора какви *изисквания* имаме към типа `T`.

---

## 2. Проблемът със съобщенията за грешки

За да разберете стойността на Концептите, трябва да сте виждали "The Wall of Text" грешка на C++ шаблоните.
Без концепти, грешката изглежда така:
`Error: no matching function for call to 'swap(std::_List_iterator...)'`
`... (50 реда вътрешни STL детайли) ...`
`... no member named 'value_type' in 'std::iterator_traits<...>'`

С концепти, грешката е кратка и ясна:
`Error: T does not satisfy 'Sortable'.`
`Reason: T does not satisfy 'RandomAccessIterator'.`

Това спестява часове дебъгване.

---

## 3. Синтаксис и Употреба

Има три основни начина да използвате концепт.

### 3.1. Клаузата `requires` (Най-експресивният начин)
```cpp
template <typename T>
requires std::integral<T> || std::floating_point<T> // Булева логика
T add(T a, T b) {
    return a + b;
}
```

### 3.2. Terse Syntax (Съкратен синтаксис)
Вместо `typename`, пишем името на концепта. Това прави кода много четим.
```cpp
template <std::integral T>
T add(T a, T b) { return a + b; }
```

### 3.3. Abbreviated Function Templates (Най-краткият)
Дори не е нужно да пишем `template<>`.
```cpp
void print(std::integral auto x) {
    std::cout << x;
}
```

---

## 4. Стандартна библиотека `<concepts>`

C++20 идва с огромна библиотека от готови концепти. Не пишете свои, преди да проверите тези:

*   **Core:** `std::same_as`, `std::convertible_to`, `std::derived_from`.
*   **Arithmetic:** `std::integral`, `std::unsigned_integral`, `std::floating_point`.
*   **Layout:** `std::movable`, `std::copyable`, `std::swappable`.
*   **Comparison:** `std::equality_comparable`, `std::totally_ordered` (поддържа "<, >, <=, >=").
*   **Ranges (Iterators):** `std::input_iterator`, `std::random_access_iterator`, `std::range`.

---

## 5. Писане на Собствени Концепти

Силата на C++ е в дефинирането на семантични изисквания за вашия домейн.
Концептът е просто `constexpr bool` променлива, която проверява дали даден израз е валиден (compiles).

### 5.1. Прост пример
Искаме тип, който може да се конвертира към `string`.
```cpp
template <typename T>
concept Stringable = requires(T v) {
    { v.toString() } -> std::convertible_to<std::string>;
};
```

### 5.2. Комплексен пример (Hashable & Equality)
```cpp
template <typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>; // Трябва да има hash
};

template <typename T>
concept MapKey = Hashable<T> && std::equality_comparable<T>; // Композиция
```

---

## 6. Концептите като заместител на SFINAE

Преди C++20, използвахме `std::enable_if`, за да имаме различни версии на функция според типа. Това беше грозно и бавно.
С Концептите, това става чрез просто претоварване (Overloading).

```cpp
// Версия за цели числа
void process(std::integral auto x) {
    std::cout << "Processing int: " << x << "\n";
}

// Версия за плаваща запетая
void process(std::floating_point auto x) {
    std::cout << "Processing float: " << x << "\n";
}

// Версия за всичко останало (Fallback)
void process(auto x) {
    std::cout << "Generic processing\n";
}
```
Компилаторът винаги избира "най-специфичния" (most constrained) концепт.

---

## 7. Професионално обобщение

1.  **Ползвайте ги навсякъде:** Концептите не забавят компилацията (дори я ускоряват, защото спират грешките рано) и нямат runtime цена.
2.  **Документация:** `template<Sortable T>` казва много повече на читателя от `template<typename T>`.
3.  **Auto:** Свикнете с `void func(auto x)`. Това е модерният начин за писане на шаблони ("Abbreviated Templates").
4.  **Semantic Meaning:** Не проверявайте само синтаксис (`has_plus`), а семантика (`Addable`). `std::string` има `+`, и `int` има `+`, но те правят различни неща.

---
*(Този документ е част от "The Ultimate C++ Mastery Framework".)*