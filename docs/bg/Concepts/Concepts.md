# Концепти (Concepts) в C++20 - Пълно техническо ръководство

## 1. Въведение: Проблемът на "Слепите" шаблони

Преди C++20, шаблоните (Templates) бяха изключително мощни, но напълно лишени от семантична проверка. Ако подадете грешен тип на шаблон (напр. `std::sort` върху `std::list`), грешката се появява дълбоко в неговата имплементация, което води до стотици редове неразбираем текст, известен като "Template Error Hell".

**Концептите** са механизъм за налагане на ограничения (Constraints) върху шаблоните параметри още в тяхната декларация. Те действат като "договори" за типове.

---

## 2. Философия: Duck Typing на ниво компилация

Концептите позволяват да кажете: *"Не ме интересува какъв точно е типа `T`, стига той да може да се събира (`+`), да има метод `print()` и да може да се копира"*. Това е статичен полиморфизъм с ясни правила.

---

## 3. Синтаксис и Употреба

Има три начина да използвате концепт.

### 3.1. Кратък синтаксис (Terse Syntax)
Това е най-четеният вариант. Заместваме `typename` с името на концепта.
```cpp
template <std::integral T>
T add(T a, T b) { return a + b; }
```
Тук `std::integral` е стандартен концепт, който ограничава `T` само до целочислени типове (`int`, `long`, `char`).

### 3.2. Клаузата `requires` (Requires Clause)
Позволява по-сложни логически изрази (`&&`, `||`).
```cpp
template <typename T>
requires std::integral<T> || std::floating_point<T>
T add(T a, T b) { return a + b; }
```

### 3.3. В края на декларацията (Trailing Requires)
```cpp
template <typename T>
T add(T a, T b) requires std::integral<T> { ... }
```

---

## 4. Дефиниране на собствени Концепти (Expert Level)

Можете да създавате свои концепти, комбинирайки съществуващи или пишейки нови правила.

### 4.1. Атомарни ограничения
```cpp
template <typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<size_t>; // Трябва да има hash
};
```

### 4.2. Съставни изисквания (Compound Requirements)
Това е най-мощната част. Проверяваме синтаксис и връщани типове.
```cpp
template <typename T>
concept Drawable = requires(T v) {
    v.x;          // Трябва да има валидна операция v.x (член или метод)
    v.draw();     // Трябва да има метод draw()
    { v.area() } -> std::same_as<double>; // draw() трябва да връща double
    typename T::ColorType; // Трябва да има дефиниран вътрешен тип ColorType
};
```

---

## 5. Overloading с Концепти

Концептите участват в **Overload Resolution**. Компилаторът избира функцията с "най-строгия" (most constrained) концепт.

```cpp
void process(auto x) { 
    std::cout << "Generic\n"; 
}

void process(std::integral auto x) { 
    std::cout << "Integral\n"; 
}

process(3.14); // Извиква Generic (не е integral)
process(10);   // Извиква Integral (по-специфичен е)
```
Това елиминира нуждата от `std::enable_if` и SFINAE магиите.

---

## 6. Стандартни концепти в `<concepts>`

C++20 идва с богата библиотека от готови концепти:
*   **Core:** `std::same_as`, `std::derived_from`, `std::convertible_to`.
*   **Arithmetic:** `std::integral`, `std::floating_point`, `std::signed_integral`.
*   **Object:** `std::movable`, `std::copyable`, `std::semiregular`.
*   **Comparison:** `std::equality_comparable`, `std::totally_ordered`.
*   **Iterator:** `std::input_iterator`, `std::random_access_iterator` (в `<iterator>`).

---

## 7. Професионално обобщение

1.  **По-бърза компилация:** Компилаторът спира веднага, ако концептът не е удовлетворен, вместо да се опитва да инстанцира шаблона.
2.  **Документация:** `template <Sortable T>` казва много повече от `template <typename T>`.
3.  **Бъдещето:** Концептите са основата на C++20 Ranges и всички бъдещи библиотеки.
4.  **Auto:** Ключовата дума `auto` във функции (Abbreviated Function Templates) всъщност е "най-слабият" концепт (приема всичко). `void func(Sortable auto x)` е напълно валиден C++20 синтаксис.

---
*(Документацията е подготвена за проекта "Ключови концепции в C++".
*Версия: 3.0 - Експертна детайлност)*