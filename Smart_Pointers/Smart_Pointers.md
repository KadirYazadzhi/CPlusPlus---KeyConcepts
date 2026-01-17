# Интелигентни Указатели (Smart Pointers) в C++

## 1. Проблемът с "суровите" указатели (Raw Pointers)

В традиционния C++, управлението на динамична памет (`new` / `delete`) е изцяло отговорност на програмиста. Това води до чести грешки:
*   **Memory Leaks:** Забравяне на `delete`.
*   **Dangling Pointers:** Използване на памет, която вече е освободена.
*   **Double Free:** Опит за двукратно освобождаване на една и съща памет.
*   **Exception Safety:** Ако функция хвърли изключение преди `delete`, паметта изтича.

Smart Pointers (въведени в C++11 в заглавния файл `<memory>`) решават тези проблеми чрез идиомата **RAII (Resource Acquisition Is Initialization)**. Те са обекти, които се държат като указатели, но автоматично освобождават паметта, когато излязат от обхват.

---

## 2. std::unique_ptr

Това е най-често използваният умен указател. Той представлява **ексклузивна собственост**. Един обект може да бъде притежаван само от един `unique_ptr`.

### Характеристики:
*   **Не може да се копира:** Опитът за копиране (`p2 = p1`) води до грешка при компилация.
*   **Може да се мести (Move):** Собствеността може да се прехвърли.
*   **Лек:** Няма overhead (същия размер като суров указател).

```cpp
#include <iostream>
#include <memory>

class Resource {
public:
    Resource() { std::cout << "Resource Acquired\n"; } // Corrected: \n to 

    ~Resource() { std::cout << "Resource Destroyed\n"; } // Corrected: \n to 

    void sayHi() { std::cout << "Hi!\n"; } // Corrected: \n to 

};

int main() {
    // Създаване (Препоръчително с make_unique от C++14)
    std::unique_ptr<Resource> ptr1 = std::make_unique<Resource>();
    
    ptr1->sayHi();

    // std::unique_ptr<Resource> ptr2 = ptr1; // ГРЕШКА! Няма копиране.

    // Прехвърляне на собствеността
    std::unique_ptr<Resource> ptr2 = std::move(ptr1);

    if (!ptr1) std::cout << "ptr1 is now empty (nullptr)\n"; // Corrected: \n to 

    ptr2->sayHi();

    return 0; // ptr2 излиза от обхват -> деструкторът се вика автоматично.
}
```

---

## 3. std::shared_ptr

Представлява **споделена собственост**. Няколко `shared_ptr` могат да сочат към един и същи ресурс. Ресурсът се освобождава едва когато **последният** указател към него бъде унищожен.

### Как работи?
Използва **Reference Counting** (Броене на референции). Всеки път, когато се създаде копие, броячът се увеличава. Когато указател се унищожи, броячът намалява. Когато стане 0 -> `delete`.

```cpp
int main() {
    // make_shared е по-ефективно (една алокация за обекта + контролния блок)
    std::shared_ptr<Resource> p1 = std::make_shared<Resource>();

    {
        std::shared_ptr<Resource> p2 = p1; // Copy constructor
        std::cout << "Count: " << p1.use_count() << std::endl; // 2
    } // p2 умира тук, count става 1

    std::cout << "Count: " << p1.use_count() << std::endl; // 1
} // p1 умира, count става 0 -> Ресурсът се трие.
```

### Недостатък:
Има overhead (памет за контролния блок и атомарни операции за брояча).

---

## 4. std::weak_ptr

`weak_ptr` е специален указател, който наблюдава `shared_ptr`, **без да притежава** ресурса и без да увеличава брояча на референциите.

### Защо ни е?
За решаване на проблема с **Циклични референции (Circular Dependencies)**. Ако Обект А има `shared_ptr` към Б, и Б има `shared_ptr` към А, броячът никога няма да стане 0 и паметта ще изтече.

```cpp
class B; // Forward declaration

class A {
public:
    std::shared_ptr<B> b_ptr;
    ~A() { std::cout << "~A\n"; } // Corrected: \n to 

};

class B {
public:
    // Ако тук беше shared_ptr<A>, щеше да има memory leak!
    std::weak_ptr<A> a_ptr; 
    ~B() { std::cout << "~B\n"; } // Corrected: \n to 

};

int main() {
    auto a = std::make_shared<A>();
    auto b = std::make_shared<B>();
    
    a->b_ptr = b;
    b->a_ptr = a; // Weak pointer не пречи на изтриването
}
```

За да използваме обекта, към който сочи `weak_ptr`, трябва да го заключим (`lock()`), което връща временно `shared_ptr` (ако обектът все още съществува).

```cpp
if (auto tempShared = b->a_ptr.lock()) {
    // Използвай tempShared безопасно
} else {
    // Обектът вече е изтрит
}
```

---

## 5. Кога какво да използвам?

1.  **`std::unique_ptr`**: По подразбиране. Винаги започвайте с него. Най-бърз и безопасен.
2.  **`std::shared_ptr`**: Само ако наистина ви трябва споделена собственост (напр. в графи, многонишкови опашки).
3.  **`std::weak_ptr`**: За разкъсване на цикли или за кеширане.
4.  **Raw Pointer (`T*`)**: Само за "наблюдение" (non-owning), когато сте сигурни, че обектът съществува, или при работа със стари C API-та.

---

## 6. Обобщение

Умните указатели са най-добрата практика в модерния C++. Те премахват нуждата от ръчно извикване на `delete` и правят кода по-устойчив на грешки.
Винаги използвайте `std::make_unique` и `std::make_shared` вместо `new`.

```
