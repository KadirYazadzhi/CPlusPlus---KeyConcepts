# Преобразуване на Типове (Type Casting) в C++

## 1. Въведение

В C++ има два начина за преобразуване на един тип данни в друг:
1.  **C-style cast:** `(int)3.14` или `int(3.14)`.
2.  **C++ cast:** `static_cast`, `dynamic_cast`, `const_cast`, `reinterpret_cast`.

C-style кастовете са мощни, но опасни и трудни за намиране в кода. **Винаги предпочитайте C++ кастовете**, защото те са по-специфични и безопасни.

---

## 2. static_cast

Най-често използваният каст. Извършва преобразувания, които са известни и безопасни по време на компилация.

*   Преобразуване между аритметични типове (double към int).
*   Преобразуване на указател към базов клас в указател към наследник (Downcasting), но **без проверка** (опасно!).
*   Извикване на експлицитни конструктори.

```cpp
double pi = 3.14159;
int num = static_cast<int>(pi); // 3

// Безопасно: Наследник -> Базов (Implicit)
Derived* d = new Derived();
Base* b = static_cast<Base*>(d); 

// Опасно: Базов -> Наследник (Без проверка!)
Derived* d2 = static_cast<Derived*>(b); 
```

---

## 3. dynamic_cast

Използва се само при **полиморфни класове** (такива с поне една виртуална функция). Извършва проверка по време на изпълнение (RTTI - Run-Time Type Information).

Ако кастът е неуспешен:
*   За указатели: връща `nullptr`.
*   За референции: хвърля `std::bad_cast`.

Това е единственият безопасен начин за **Downcasting** (от Базов към Наследник).

```cpp
class Base { virtual void foo() {} };
class Derived : public Base {};
class Another : public Base {};

Base* ptr = new Derived();

// Успешно
Derived* d = dynamic_cast<Derived*>(ptr);
if (d) { /* ptr наистина сочи към Derived */ }

// Неуспешно (връща nullptr)
Another* a = dynamic_cast<Another*>(ptr);
if (!a) { std::cout << "Cast failed\n"; }
```

⚠️ Има цена за производителността заради RTTI проверката.

---

## 4. const_cast

Използва се единствено за **премахване на const** (или volatile) квалификатора.

⚠️ **Внимание:** Ако промените обект, който е бил оригинално дефиниран като `const`, това е **Undefined Behavior**. Използва се главно при работа със стари API-та, които не приемат const, но не променят данните.

```cpp
void print(char* str) { std::cout << str; }

const char* msg = "Hello";
// print(msg); // ГРЕШКА: const char* не става на char*

print(const_cast<char*>(msg)); // ОК, стига print да не променя msg!
```

---

## 5. reinterpret_cast

Най-мощният и най-опасният каст. Казва на компилатора: "Третирай тези битове в паметта като друг тип". Не променя битовете, само интерпретацията им.

*   `int*` към `double*`
*   `int` към `pointer`

Използва се в системното програмиране, работа с хардуер и сериализация.

```cpp
struct Packet { int header; int body; };

char buffer[1024];
// Превръщаме буфера директно в структура
Packet* p = reinterpret_cast<Packet*>(buffer);

// Превръщаме pointer в число
long address = reinterpret_cast<long>(p);
```

---

## 6. Обобщение

| Cast | Проверка | Безопасност | Употреба |
| :--- | :--- | :--- | :--- |
| `static_cast` | Compile-time | Средна | Основни типове, Upcasting |
| `dynamic_cast` | Run-time | Висока | Полиморфен Downcasting |
| `const_cast` | Compile-time | Ниска | Махане на const |
| `reinterpret_cast` | Compile-time | Никаква | Битови реинтерпретации |

Винаги започвайте със `static_cast`. Ако ви трябва полиморфизъм, ползвайте `dynamic_cast`. Другите два са за много специфични случаи.

```