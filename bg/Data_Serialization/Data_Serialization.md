# Сериализация на Данни (Data Serialization) в C++

## 1. Въведение

Сериализацията е процесът на преобразуване на обект в паметта в поредица от байтове, които могат да бъдат:
1.  Записани във файл.
2.  Изпратени по мрежата.
3.  Запазени в база данни.

Десериализацията е обратният процес.

В C++ няма вградена рефлексия (все още), така че сериализацията не е автоматична (както в C# или Java).

---

## 2. Бинарна Сериализация (POD)

За прости структури (Plain Old Data) можем просто да копираме паметта (`memcpy`).

```cpp
struct Player {
    int id;
    float x, y;
};

// Сериализация
Player p = {1, 10.5f, 20.0f};
std::ofstream out("save.dat", std::ios::binary);
out.write(reinterpret_cast<char*>(&p), sizeof(Player));

// Десериализация
Player p2;
std::ifstream in("save.dat", std::ios::binary);
in.read(reinterpret_cast<char*>(&p2), sizeof(Player));
```

⚠️ **Проблеми:**
*   **Endianness:** Big-endian vs Little-endian машини.
*   **Padding:** Компилаторите добавят празни байтове за подравняване.
*   **Pointers:** Ако структурата има `std::string` или `std::vector` (които съдържат указатели), горният код ще гръмне. Трябва да сериализираме данните, не указателите!

---

## 3. JSON Сериализация

JSON е най-популярният текстов формат. Тъй като не е вграден в STL, индустриалният стандарт е библиотеката **nlohmann/json**.

```cpp
// Пример с nlohmann/json (псевдокод, изисква инсталация)
/*
#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct User {
    std::string name;
    int age;
};

// Макрос за автоматично генериране на конверсия
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(User, name, age)

int main() {
    User u = {"Alice", 30};
    json j = u; // Автоматична конверсия
    
    std::cout << j.dump(4) << std::endl; // Pretty print
}
*/
```

---

## 4. Protobuf (Protocol Buffers)

За високопроизводителни системи (Google, gRPC) се използва **Protobuf**.
1.  Дефинирате структурата в `.proto` файл.
2.  Компилаторът `protoc` генерира C++ клас.
3.  Този клас има методи `SerializeToString()` и `ParseFromString()`.

Предимства: Много по-малък размер от JSON и много по-бърз.

---

## 5. Обобщение

*   За прости задачи и дебъгване: използвайте **JSON**.
*   За скорост и мрежови протоколи: използвайте **Protobuf** или **FlatBuffers**.
*   Внимавайте с указателите при ръчна бинарна сериализация.
