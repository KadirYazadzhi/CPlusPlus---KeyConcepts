# Шаблони за Дизайн (Design Patterns) в C++

## 1. Въведение

Шаблоните за дизайн (Design Patterns) са утвърдени решения на често срещани проблеми в софтуерното проектиране. Те не са готов код, а по-скоро **концепции** или **шаблони**, които можете да приложите към конкретен проблем.

В C++ те са особено важни за управлението на зависимости, памет и сложност.

Основните групи са:
1.  **Creational (Създаващи):** За създаване на обекти (Singleton, Factory).
2.  **Structural (Структурни):** За композиция на класове (Adapter, Decorator).
3.  **Behavioral (Поведенчески):** За комуникация между обекти (Observer, Strategy).

---

## 2. Singleton (Одинак)

Гарантира, че един клас има **само една инстанция** и предоставя глобална точка за достъп до нея.

**Приложение:** Логери, Конфигурационни мениджъри, Драйвери за хардуер.

```cpp
#include <iostream>

class Singleton {
private:
    // 1. Private конструктор (за да не може да се създава отвън)
    Singleton() { std::cout << "Singleton Created\n"; } 
    
    // Забраняваме копирането
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // 2. Static метод за достъп
    static Singleton& getInstance() {
        // C++11 гарантира, че това е thread-safe инициализация
        static Singleton instance; 
        return instance;
    }

    void doSomething() { std::cout << "Doing work...\n"; }
};

int main() {
    Singleton& s1 = Singleton::getInstance();
    s1.doSomething();
    
    // Singleton s2; // ГРЕШКА! Private конструктор.
}
```

---

## 3. Factory Method (Фабричен метод)

Дефинира интерфейс за създаване на обекти, но оставя подкласовете да решат кой точно клас да инстанцират. Полезно е, когато не знаем предварително какъв тип обект ще ни трябва.

```cpp
#include <memory>

// Интерфейс
class Product {
public:
    virtual void use() = 0;
    virtual ~Product() {}
};

class ConcreteProductA : public Product {
    void use() override { std::cout << "Using Product A\n"; }
};

class ConcreteProductB : public Product {
    void use() override { std::cout << "Using Product B\n"; }
};

// Фабрика
class Factory {
public:
    static std::unique_ptr<Product> createProduct(char type) {
        if (type == 'A') return std::make_unique<ConcreteProductA>();
        if (type == 'B') return std::make_unique<ConcreteProductB>();
        return nullptr;
    }
};

int main() {
    auto p = Factory::createProduct('A');
    if (p) p->use();
}
```

---

## 4. Observer (Наблюдател)

Дефинира зависимост "един към много". Когато един обект (Subject) промени състоянието си, всички зависими от него (Observers) биват уведомени автоматично.

**Приложение:** UI системи (бутонът е натиснат -> обнови екрана), Event Handling.

```cpp
#include <vector>
#include <algorithm>

class Observer {
public:
    virtual void update(int value) = 0;
};

class Subject {
    std::vector<Observer*> observers;
    int state;

public:
    void attach(Observer* o) { observers.push_back(o); } 
    
    void setState(int s) {
        state = s;
        notify();
    }

    void notify() {
        for (Observer* o : observers) {
            o->update(state);
        }
    }
};

class ConcreteObserver : public Observer {
    std::string name;
public:
    ConcreteObserver(std::string n) : name(n) {}
    void update(int value) override {
        std::cout << name << " notified. New state: " << value << "\n";
    }
};

int main() {
    Subject subject;
    ConcreteObserver obs1("Observer 1");
    ConcreteObserver obs2("Observer 2");

    subject.attach(&obs1);
    subject.attach(&obs2);

    subject.setState(10); // И двата наблюдателя ще бъдат уведомени
}
```

---

## 5. RAII (Resource Acquisition Is Initialization)

Това не е точно GoF (Gang of Four) шаблон, а специфичен за C++ идиом, но е най-важният от всички.

**Идея:** Ресурсът (памет, файл, мрежова връзка) се заема в конструктора и се освобождава в деструктора. Тъй като деструкторите се викат автоматично при излизане от обхват (дори при грешка/exception), ресурсът никога не изтича.

Пример: `std::lock_guard`, `std::unique_ptr`, `std::fstream`.

---

## 6. Обобщение

*   Шаблоните правят кода по-гъвкав и лесен за поддръжка.
*   Не прекалявайте с тях (Over-engineering). Използвайте ги само когато решават реален проблем.
*   **Singleton** трябва да се използва внимателно, защото е по същество глобална променлива.
*   **Factory** скрива сложността на създаването на обекти.
*   **Observer** разкача (decouples) логиката на данните от логиката на интерфейса.

```