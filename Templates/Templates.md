# Шаблони (Templates) в C++

## 1. Въведение

Шаблоните са основата на **Generic Programming** (Обобщено програмиране) в C++. Те позволяват да напишем код (функция или клас) веднъж и той да работи с **всякакъв тип данни**.

Всички контейнери от STL (`vector`, `map`, `set`) са реализирани чрез шаблони.

---

## 2. Шаблони на Функции (Function Templates)

Вместо да пишем отделни функции `add(int, int)` и `add(double, double)`, пишем един шаблон.

```cpp
#include <iostream>

// T е заместител (placeholder) за типа
template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(5, 10) << std::endl;       // T става int
    std::cout << add(5.5, 2.3) << std::endl;    // T става double
    
    // std::cout << add(5, 2.5); // ГРЕШКА! T не може да е int и double едновременно.
    std::cout << add<double>(5, 2.5); // Изрично указване: T е double
}
```

### Няколко шаблонни параметъра
```cpp
template <typename T1, typename T2>
void printTypes(T1 a, T2 b) {
    std::cout << a << " " << b << "\n";
}
// printTypes(1, "Hello");
```

---

## 3. Шаблони на Класове (Class Templates)

Използват се за създаване на гъвкави структури от данни.

```cpp
template <typename T>
class Box {
private:
    T value;
public:
    Box(T val) : value(val) {}
    
    T getValue() { return value; }
    void setValue(T val) { value = val; }
};

int main() {
    Box<int> intBox(10);
    Box<std::string> strBox("Hello");
    
    std::cout << intBox.getValue();
}
```

---

## 4. Шаблонна Специализация (Template Specialization)

Понякога общият код работи за повечето типове, но не за всички. Например, сравняването на `char*` (C-strings) не работи с `==`. Можем да напишем специална версия за конкретен тип.

```cpp
// Общ шаблон
template <typename T>
bool isEqual(T a, T b) {
    return a == b;
}

// Пълна специализация за char*
template <>
bool isEqual<const char*>(const char* a, const char* b) {
    return strcmp(a, b) == 0;
}
```

---

## 5. Non-type Template Parameters

Шаблоните могат да приемат не само типове, но и стойности (обикновено цели числа), които са известни по време на компилация.

```cpp
// N е константа, известна при компилация
template <typename T, int N>
class StaticArray {
    T arr[N]; // Размерът е фиксиран
public:
    int getSize() { return N; }
};

int main() {
    StaticArray<int, 5> arr1; // Масив с размер 5
    StaticArray<int, 10> arr2; // Масив с размер 10
    
    // arr1 = arr2; // ГРЕШКА! Това са различни типове.
}
```
Това е принципът, на който работи `std::array`.

---

## 6. Вариадични Шаблони (Variadic Templates) - C++11

Позволяват на шаблона да приема произволен брой аргументи.

```cpp
// Базов случай за рекурсията (край на списъка)
void print() {
    std::cout << "\n";
}

// Рекурсивен шаблон
template <typename T, typename... Args>
void print(T first, Args... args) {
    std::cout << first << " ";
    print(args...); // Рекурсивно извикване за останалите
}

// print(1, "Hello", 3.14); -> "1 Hello 3.14"
```

---

## 7. Обобщение

*   Шаблоните пренасят логиката от Run-time към **Compile-time**.
*   Водят до генериране на отделен код за всеки използван тип (Code Bloat).
*   Грешките при шаблоните често са дълги и трудни за четене.
*   Незаменим инструмент за писане на библиотеки.

```
