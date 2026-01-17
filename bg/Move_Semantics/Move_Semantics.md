# Семантика на Преместването (Move Semantics) в C++

## 1. Въведение

До C++11, копирането на обекти беше единственият начин за прехвърляне на данни. Това обаче е бавно за големи обекти (като `std::vector` или `std::string`), защото изисква заделяне на нова памет и копиране на всеки байт.

**Move Semantics** позволява ресурсите на един обект (памет, файлови дескриптори) да бъдат **преместени** в друг обект, вместо копирани. Това е ключова оптимизация за производителност.

---

## 2. L-values и R-values

За да разберем Move Semantics, трябва да разберем категориите стойности:

*   **L-value (Left Value):** Обект, който има име и адрес в паметта. Може да стои отляво на присвояването.
    ```cpp
    int x = 10; // x е l-value
    ```
*   **R-value (Right Value):** Временен обект, който няма име и скоро ще бъде унищожен. Обикновено стои отдясно.
    ```cpp
    int x = 10 + 20; // (10+20) е r-value (временен резултат 30)
    func("Hello");   // "Hello" е r-value
    ```

Move Semantics ни позволява да "откраднем" ресурсите от R-values, защото знаем, че те са временни и никой друг няма да ги ползва.

---

## 3. R-value Reference (`&&`)

За да разпознаем, че даден аргумент е R-value, използваме двоен амперсанд `&&`.

```cpp
void process(int& x)  { std::cout << "L-value (Copy)\n"; }
void process(int&& x) { std::cout << "R-value (Move)\n"; }

int main() {
    int a = 5;
    process(a); // Вика L-value версията
    process(10); // Вика R-value версията
}
```

---

## 4. Move Constructor и Move Assignment

Ако пишем собствен клас, който управлява динамична памет, трябва да имплементираме тези специални методи.

### Пример: Клас String

```cpp
class MyString {
    char* data;
    int size;

public:
    // 1. Стандартен конструктор
    MyString(const char* str) {
        size = strlen(str);
        data = new char[size + 1];
        strcpy(data, str);
    }

    // 2. Copy Constructor (Дълбоко копиране - Бавно)
    MyString(const MyString& other) {
        std::cout << "Copying...\n";
        size = other.size;
        data = new char[size + 1];
        strcpy(data, other.data);
    }

    // 3. Move Constructor (Преместване - Бързо!)
    // Приема R-value референция (other е временен обект)
    MyString(MyString&& other) noexcept {
        std::cout << "Moving...\n";
        
        // 1. Крадем ресурсите (просто копираме указателя)
        data = other.data;
        size = other.size;

        // 2. Оставяме другия обект в валидно, но "празно" състояние
        // За да не изтрие паметта в деструктора си!
        other.data = nullptr;
        other.size = 0;
    }

    // Деструктор
    ~MyString() {
        delete[] data; // nullptr е безопасно за delete
    }
};
```

---

## 5. `std::move`

Понякога имаме L-value (именуван обект), който искаме да третираме като R-value, защото знаем, че няма да го ползваме повече. Функцията `std::move` прави точно това – **каства** (преобразува) L-value към R-value референция.

```cpp
int main() {
    std::string s1 = "Hello World";
    std::string s2 = s1; // Copy: s1 си стои, s2 е копие. 

    // Move: s3 взима паметта на s1. s1 остава празен.
    std::string s3 = std::move(s1); 
    
    // std::cout << s1; // Внимавайте! s1 е в неопределено състояние (обикновено празен).
}
```

**Приложение:** При размяна (swap), сортиране, връщане на тежки обекти от функции и добавяне във `vector`.

```cpp
std::vector<std::string> vec;
std::string hugeString(1000000, 'a');

// Вместо копиране на 1MB, местим указателя:
vec.push_back(std::move(hugeString)); 
```

---

## 6. Правилото на Петте (Rule of Five)

В модерния C++, ако дефинирате ръчно един от следните методи, трябва да дефинирате всичките 5, за да управлявате правилно ресурсите:

1.  Деструктор
2.  Copy Constructor
3.  Copy Assignment Operator
4.  Move Constructor
5.  Move Assignment Operator

Или да използвате `= default;` и `= delete;`.

---

## 7. Обобщение

*   **Move Semantics** превръща скъпите копирания в евтини премествания на указатели.
*   Използва се автоматично за временни обекти (R-values).
*   Може да се форсира за именувани обекти чрез `std::move`.
*   Задължително е за типове като `std::unique_ptr`, които не могат да се копират.

```
