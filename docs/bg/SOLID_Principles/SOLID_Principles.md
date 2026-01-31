# SOLID Принципи в C++ - Пълно техническо ръководство

## 1. Въведение: Архитектура, която издържа на времето

SOLID е акроним на петте основни принципа на обектно-ориентирания дизайн, дефинирани от Робърт Мартин (Uncle Bob).
В света на C++, където компилацията е бавна и зависимостите са сложни, спазването на SOLID е разликата между проект, който живее 10 години, и такъв, който трябва да се пренапише след 6 месеца.

---

## 2. S - Single Responsibility Principle (SRP)

> "Един клас трябва да има само една причина да се променя."

Това не означава "един клас да прави само едно нещо", а "един клас да отговаря за една бизнес концепция".

**Лош пример (God Object):**
```cpp
class User {
public:
    void login();           // Аутентикация
    void saveToDB();        // База данни
    void generateReport();  // Бизнес логика / UI
};
```
Ако променим базата данни, пипаме `User`. Ако променим формата на репорта, пипаме `User`.

**Добър пример:**
```cpp
class User { ... };             // Само данни (DTO)
class AuthManager { ... };      // Логика за вход
class UserRepository { ... };   // Запис в DB
class ReportGenerator { ... };  // Генериране на PDF
```

---

## 3. O - Open/Closed Principle (OCP)

> "Софтуерните единици трябва да са отворени за разширение, но затворени за модификация."

Трябва да можете да добавяте нови функции, без да пипате съществуващия (и тестван) код. В C++ това се постига чрез **Полиморфизъм** (динамичен или статичен).

**Нарушение:**
```cpp
void draw(Shape* s) {
    if (s->type == CIRCLE) drawCircle(s);
    else if (s->type == SQUARE) drawSquare(s);
    // За да добавим триъгълник, трябва да променим тази функция!
}
```

**Решение (Dynamic Polymorphism):**
```cpp
struct Shape { 
    virtual void draw() const = 0; 
    virtual ~Shape() = default;
};

// Добавяме нов файл, без да пипаме старите
struct Triangle : Shape { 
    void draw() const override { ... } 
};
```

---

## 4. L - Liskov Substitution Principle (LSP)

> "Обектите от наследен клас трябва да могат да заместят обектите от базовия клас, без да чупят програмата."

Това е най-математическият принцип. Наследяването е връзка "IS-A" (Е), но тя трябва да е и поведенческа.

**Класическият парадокс "Квадратът е Правоъгълник":**
В математиката квадратът е правоъгълник. В програмирането - **НЕ Е**.
```cpp
class Rectangle {
public:
    virtual void setWidth(int w) { width = w; }
    virtual void setHeight(int h) { height = h; }
};

class Square : public Rectangle {
public:
    // При квадрат промяната на ширината трябва да промени и височината!
    void setWidth(int w) override { width = height = w; }
};

void process(Rectangle& r) {
    r.setWidth(5);
    r.setHeight(10);
    assert(r.area() == 50); // ГРЕШКА при Square! Area ще е 100.
}
```
**Извод:** `Square` не трябва да наследява `Rectangle`, защото нарушава пост-условията на базовия клас.

---

## 5. I - Interface Segregation Principle (ISP)

> "Клиентите не трябва да бъдат принуждавани да зависят от интерфейси, които не използват."

По-добре много малки интерфейси, отколкото един голям.

**Лош пример (Fat Interface):**
```cpp
struct IMachine {
    virtual void print() = 0;
    virtual void scan() = 0;
    virtual void fax() = 0;
};

class SimplePrinter : public IMachine {
public:
    void print() override { ... }
    void scan() override { /* Нямам скенер, хвърлям грешка? */ }
    void fax() override { /* Нямам факс... */ }
};
```

**Решение:** Разделяне на `IPrinter`, `IScanner`, `IFax`.

---

## 6. D - Dependency Inversion Principle (DIP)

> "Модулите от високо ниво не трябва да зависят от модули от ниско ниво. И двата трябва да зависят от абстракции."

Това е основата на **Dependency Injection**.

**Нарушение:**
```cpp
class Car {
    V8Engine engine; // Car зависи директно от конкретния клас V8Engine
};
```

**Решение:**
```cpp
struct IEngine { virtual void start() = 0; };

class Car {
    IEngine& engine; // Car зависи от абстракцията
public:
    Car(IEngine& e) : engine(e) {}
};
```

---

## 7. SOLID и Performance в C++

В C++ понякога нарушаваме SOLID заради скорост.
*   **Virtual Functions (OCP/LSP/DIP):** Добавят цена (vtable lookup, пречат на inlining). В performance-critical код (HFT, Game Engines) често заменяме динамичния полиморфизъм със статичен (Templates / CRTP).
*   **Templates (Static SOLID):** Шаблоните позволяват спазването на OCP/DIP без runtime overhead. `std::sort` е OCP – работи с всякакви итератори, без да наследява базов клас.

---

## 8. Професионално обобщение

1.  **Не прекалявайте:** SOLID е насока, не закон. Ако направите интерфейс за клас, който има само една имплементация и никога няма да има друга, вие усложнявате кода (YAGNI).
2.  **Тестваемост:** Ако спазвате SOLID, кодът ви ще бъде лесен за Unit тестване (особено DIP и SRP).
3.  **Refactoring:** Не се опитвайте да напишете перфектния SOLID код от ден 1. Напишете го просто, после рефакторирайте към SOLID, когато се появят нови изисквания.

---
*(Този документ е част от "The Ultimate C++ Mastery Framework".)*
