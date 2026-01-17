# Optional, Variant и Any (C++17)

## 1. Въведение

C++17 въведе три нови типа контейнери за стойности, които решават класически проблеми с типовата безопасност и "липсващите" стойности. Намират се в `<optional>`, `<variant>` и `<any>`.

---

## 2. std::optional (Може би има стойност)

Използва се, когато една функция може да върне валиден резултат, но може и да не върне нищо (например "търсене в база данни"). Замества връщането на `nullptr` или специални стойности като `-1`.

```cpp
#include <optional>
#include <iostream>

std::optional<int> findUserAge(int id) {
    if (id == 1) return 25;
    return std::nullopt; // Няма стойност
}

int main() {
    auto age = findUserAge(99);

    if (age.has_value()) { // Или просто if (age)
        std::cout << "Age: " << *age << "\n";
    } else {
        std::cout << "User not found\n";
    }

    // value_or: Връща стойността или дефолтна стойност
    std::cout << "Age: " << age.value_or(-1) << "\n"; 
}
```

---

## 3. std::variant (Type-safe Union)

`std::variant` може да съдържа стойност от един от няколко предварително зададени типа. Това е безопасна алтернатива на C-style `union`.

```cpp
#include <variant>

int main() {
    std::variant<int, std::string, double> data;

    data = 10;
    std::cout << std::get<int>(data) << "\n"; // 10

    data = "Hello";
    std::cout << std::get<std::string>(data) << "\n"; // Hello

    // data = true; // ГРЕШКА! bool не е в списъка.

    // Проверка какво има вътре
    if (std::holds_alternative<std::string>(data)) {
        std::cout << "It holds a string\n";
    }
}
```

### std::visit
Най-добрият начин за работа с variant е чрез Visitor pattern.

```cpp
std::visit([](auto&& arg) {
    std::cout << "Value: " << arg << "\n";
}, data);
```

---

## 4. std::any (Какъвто и да е тип)

`std::any` може да съдържа стойност от **абсолютно всеки** тип (стига да е копируем). Това е най-гъвкавият тип, но и най-бавният, защото често използва динамична памет. Прилича на `Object` в Java/C#.

```cpp
#include <any>

int main() {
    std::any a = 1;
    a = std::string("Test");
    a = 3.14;

    // За да използваме стойността, трябва да знаем типа и да го кастнем
    try {
        std::cout << std::any_cast<double>(a) << "\n";
    } catch (const std::bad_any_cast& e) {
        std::cout << "Wrong type!\n";
    }
}
```

---

## 5. Обобщение

*   **`std::optional`**: За променливи, които могат да липсват.
*   **`std::variant`**: Когато знаете точното множество от възможни типове (int ИЛИ string). Много ефективно.
*   **`std::any`**: Когато не знаете типа предварително. Избягвайте го, ако е възможно.

```