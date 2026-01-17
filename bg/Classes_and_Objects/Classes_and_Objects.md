# Класове и Обекти (Classes and Objects) в C++

## 1. Въведение в ООП

Обектно-ориентираното програмиране (ООП) е парадигма, която организира софтуерния дизайн около **данни** (обекти) и **логика** (методи), вместо около функции и логика.

В C++ основните градивни блокове на ООП са **класовете**.

---

## 2. Класове и Обекти

### 2.1. Дефиниция на Клас
Класът е **шаблон** (blueprint) или потребителски дефиниран тип данни. Той описва какви данни съдържа обектът (член-променливи) и какви операции може да извършва (член-функции или методи).

```cpp
class Car {
    // Данни (Member variables)
    int speed;
    
public:
    // Методи (Member functions)
    void accelerate() {
        speed += 10;
    }
};
```

### 2.2. Обект
Обектът е **инстанция** на класа. Това е конкретната променлива, създадена по шаблона.

```cpp
int main() {
    Car myCar; // Създаване на обект (инстанция) от тип Car
    myCar.accelerate(); // Извикване на метод
    return 0;
}
```

---

## 3. Модификатори за достъп (Access Modifiers)

C++ предоставя три нива на достъп за контрол на видимостта (Encapsulation):

1.  **public:** Достъпно отвсякъде (извън класа).
2.  **private:** Достъпно само вътре в класа. (По подразбиране за `class`).
3.  **protected:** Достъпно вътре в класа и в класовете наследници (виж Наследяване).

**Добра практика (Encapsulation):** Дръжте данните `private`, а интерфейса (методите) `public`.

```cpp
class BankAccount {
private:
    double balance; // Скрито от външния свят

public:
    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }

    double getBalance() const; // Getter (Read-only)
        return balance;
    }
};
```

---

## 4. Конструктори и Деструктори

### 4.1. Конструктор (Constructor)
Специален метод, който се извиква автоматично при **създаване** на обекта. Има същото име като класа и няма връщан тип. Използва се за инициализация.

```cpp
class Person {
    std::string name;
    int age;

public:
    // Конструктор по подразбиране
    Person() {
        name = "Unknown";
        age = 0;
    }

    // Параметризиран конструктор
    Person(std::string n, int a) {
        name = n;
        age = a;
    }
    
    // Member Initializer List (По-ефективният начин!)
    // Person(std::string n, int a) : name(n), age(a) {}
};
```

### 4.2. Деструктор (Destructor)
Специален метод, който се извиква автоматично при **унищожаване** на обекта (излизане от обхват или `delete`). Името му започва с тилда `~`. Използва се за освобождаване на ресурси (памет, файлове).

```cpp
class FileHandler {
public:
    FileHandler() { std::cout << "File opened\n"; }
    ~FileHandler() { std::cout << "File closed\n"; } // Автоматично затваряне
};
```

---

## 5. `this` Пойнтер

Във всеки метод на класа съществува скрит указател `this`, който сочи към текущия обект.

```cpp
class Box {
    int width;
public:
    void setWidth(int width) {
        // Името на параметъра скрива член-променливата
        // Използваме this-> за да ги различим
        this->width = width;
    }
    
    Box& getSelf() {
        return *this; // Връща референция към текущия обект
    }
};
```

---

## 6. Static членове

### 6.1. Static променливи
Споделят се между **всички** обекти от този клас. Има само едно копие в паметта.

### 6.2. Static методи
Могат да се викат без създаден обект (`ClassName::method()`). Могат да достъпват само static променливи.

```cpp
class User {
public:
    static int userCount; // Декларация

    User() { userCount++; }
    static int getCount() { return userCount; }
};

// Инициализация извън класа (задължително!)
int User::userCount = 0;

int main() {
    User u1;
    User u2;
    std::cout << User::getCount(); // 2
}
```

---

## 7. Struct vs Class

В C++ единствената разлика между `struct` и `class` е достъпът по подразбиране:
*   **struct:** Всичко е `public` по подразбиране.
*   **class:** Всичко е `private` по подразбиране.

Обикновено `struct` се използва за прости контейнери на данни (POD - Plain Old Data), а `class` за обекти с логика и инварианти.

---

## 8. Разделяне на декларация и дефиниция

За големи проекти е задължително разделянето на кода:
*   **Header file (.h / .hpp):** Съдържа дефиницията на класа (интерфейса).
*   **Source file (.cpp):** Съдържа имплементацията на методите.

**MyClass.h**
```cpp
#ifndef MYCLASS_H
#define MYCLASS_H

class MyClass {
public:
    void doSomething();
};

#endif
```

**MyClass.cpp**
```cpp
#include "MyClass.h"
#include <iostream>

void MyClass::doSomething() {
    std::cout << "Doing something...\n";
}
```

---

## 9. Обобщение

*   Класовете са основата на C++.
*   Използвайте **Encapsulation** (private данни, public методи).
*   Винаги инициализирайте променливите в конструктора (препоръчително чрез Initializer List).
*   Деструкторите са критични за управление на ресурси (RAII).

```