# Optional, Variant и Any (Алгебрични типове) - Пълно техническо ръководство

## 1. Въведение: Типобезопасният съюз

C++17 въведе три нови типа в стандарта (`<optional>`, `<variant>`, `<any>`), които промениха начина, по който моделираме данни. Те решават стари проблеми като връщане на грешки, обединения (unions) и полиморфизъм, но по модерен и безопасен начин.

---

## 2. `std::optional<T>`: Може да има нещо, може и да няма

Замества използването на "магически стойности" (напр. връщане на `-1` или `nullptr` за грешка) или изходни параметри.

```cpp
std::optional<User> findUser(int id) {
    if (db.has(id)) return db.get(id);
    return std::nullopt; // Ясно казваме: няма резултат
}

auto user = findUser(10);
if (user) { // bool conversion
    std::cout << user->name;
} else {
    std::cout << "Not found";
}
```

### Методи
*   `value()`: Връща стойността или хвърля `std::bad_optional_access`, ако е празен.
*   `value_or(default)`: Връща стойността или дефолтна стойност.
*   **Performance:** `optional` заделя паметта директно в себе си (на стека, обикновено `sizeof(T) + 1` байт за флага). Няма динамична алокация!

---

## 3. `std::variant<T...>`: Модерният `union`

Това е "Sum Type" (или Tagged Union). Променлива, която може да държи стойност от един от изброените типове в даден момент.
За разлика от C-style `union`, `std::variant` знае какво държи и извиква правилните деструктори.

```cpp
std::variant<int, float, std::string> v;
v = 10;
v = "Hello"; // Старата стойност (int) се унищожава коректно
```

### Pattern Matching с `std::visit`
Най-мощният начин за работа с variant е Visitor pattern.

```cpp
// Helper за създаване на visitor от ламбди (C++17 magic)
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

std::visit(overloaded {
    [](int arg) { std::cout << "Int: " << arg; },
    [](float arg) { std::cout << "Float: " << arg; },
    [](const std::string& arg) { std::cout << "String: " << arg; }
}, v);
```
Това е изключително бързо (често компилира до jump table / switch case) и е алтернатива на полиморфизма (Inheritance) без виртуални функции и динамична памет.

---

## 4. `std::any`: Типобезопасният `void*`

`std::any` може да държи *всякакъв* тип данни (които могат да се копират).
За разлика от `void*`, той знае типа и не позволява грешен cast.

```cpp
std::any a = 10;
a = std::string("Test");

// Четене
try {
    std::string s = std::any_cast<std::string>(a);
} catch (const std::bad_any_cast& e) {
    // Ако 'a' не е string
}
```

**Цена:** `std::any` почти винаги използва **динамична алокация** на памет (освен за много малки типове) и виртуални функции вътрешно. Използвайте го само ако `variant` не върши работа (т.е. наборът от типове е отворен и безкраен).

---

## 5. `std::expected<T, E>` (C++23)

Наследникът на `optional`. Той или съдържа резултат `T`, или съдържа грешка `E` (която описва *защо* няма резултат). Това е модерният начин за Error Handling (алтернатива на Exceptions).

```cpp
std::expected<int, std::string> divide(int a, int b) {
    if (b == 0) return std::unexpected("Division by zero");
    return a / b;
}
```

---

## 6. Сравнение и Употреба

| Тип | Какво е? | Кога да ползвам? | Памет |
| :--- | :--- | :--- | :--- |
| `optional<T>` | T или Нищо | Функция, която може да не намери резултат. | Stack (T + bool) |
| `variant<A, B>` | A или B | Краен набор от възможни типове (State Machine, JSON node). | Stack (Max(A,B) + index) |
| `any` | Всичко | Когато не знам типа предварително (напр. property bag). | Heap (често) |
| `expected<T, E>`| T или Error | Обработка на грешки. | Stack (Union T/E + bool) |

---

## 7. Професионално обобщение

*   **Избягвайте `void*`:** Никога не ползвайте `void*` в модерен C++. `std::any` или `std::variant` са безопасните алтернативи.
*   **Избягвайте C-unions:** Те са опасни (Undefined Behavior, ако прочетете грешното поле). `std::variant` е безопасен.
*   **Polymorphism vs Variant:** Ако имате фиксиран брой класове (напр. Shape: Circle, Square), `std::variant` е по-бърз от виртуалните функции (по-добра кеш локалност, без алокации). Използвайте наследяване само ако потребителите трябва да могат да добавят *нови* класове към системата (Open Set).

---
*(Този документ е част от "The Ultimate C++ Mastery Framework".)*