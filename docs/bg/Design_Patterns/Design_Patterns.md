# Шаблони за Дизайн (Design Patterns) в C++ - Пълно техническо ръководство

## 1. Въведение: Езикът на Архитектурата

Шаблоните за дизайн (Design Patterns) не са готов код, който можете да копирате и поставите. Те са **решения на повтарящи се архитектурни проблеми**. Те са общ език между инженерите. Когато кажете *"Тук използвам Observer"*, вашият колега веднага разбира структурата на класовете, зависимостите и потока на данните, без да е чел и ред код.

В C++ шаблоните имат специфичен привкус заради управлението на паметта (RAII), темплейтите (Compile-time polymorphism) и семантиката на преместване (Move semantics).

---

## 2. Създаващи Шаблони (Creational Patterns)

Тези шаблони абстрахират процеса на инстанциране. Те правят системата независима от това как нейните обекти се създават.

### 2.1. Singleton (Единствена Инстанция)
Гарантира, че един клас има само една инстанция и предоставя глобална точка за достъп.
**Употреба:** Логери, Конфигурационни мениджъри, Драйвери за хардуер.

**C++ Имплементация (Meyers Singleton):**
Това е "Златният стандарт" в модерния C++. Гарантирано Thread-safe инициализиране (от C++11 насам) и Lazy loading.

```cpp
class Database {
public:
    // Изтриваме методите за копиране, за да гарантираме уникалност
    Database(const Database&) = delete;
    void operator=(const Database&) = delete;

    static Database& get() {
        // Тази променлива се създава само веднъж, при първото извикване
        static Database instance; 
        return instance;
    }

    void query(const std::string& sql) { /* ... */ }

private:
    Database() { /* Скъпа инициализация, отваряне на порт... */ }
    ~Database() { /* Затваряне на връзката */ }
};
```

### 2.2. Factory Method (Фабричен Метод)
Дефинира интерфейс за създаване на обекти, но оставя на подкласовете да решат кой точно клас да инстанцират.
**Употреба:** Когато не знаете предварително какъв тип обекти ще ви трябват (напр. отваряне на документ – може да е PDF, Docx или TXT).

```cpp
class Document {
public:
    virtual void open() = 0;
    virtual ~Document() = default;
};

class PDFDocument : public Document { void open() override { /*...*/ } };

class Creator {
public:
    virtual std::unique_ptr<Document> createDoc() = 0;
    virtual ~Creator() = default;
};
```

### 2.3. Builder (Строител)
Разделя конструирането на сложен обект от неговото представяне.
**Употреба:** Създаване на сложни SQL заявки, HTML страници или конфигурации.

```cpp
// Fluent Interface
class HttpRequestBuilder {
    HttpRequest request;
public:
    HttpRequestBuilder& method(const std::string& m) {
        request.method = m;
        return *this;
    }
    HttpRequestBuilder& header(const std::string& key, const std::string& val) {
        request.headers[key] = val;
        return *this;
    }
    HttpRequest build() { return request; }
};

// Употреба:
auto req = HttpRequestBuilder().method("GET").header("Content-Type", "json").build();
```

---

## 3. Структурни Шаблони (Structural Patterns)

### 3.1. Adapter (Адаптер)
Позволява на класове с несъвместими интерфейси да работят заедно.
**Употреба:** Интегриране на стари (Legacy) библиотеки или 3rd-party код.

```cpp
// Стар интерфейс (несъвместим)
class LegacyPrinter {
public:
    void oldPrint(char* str) { /*...*/ }
};

// Новият интерфейс, който системата очаква
class IPrinter {
public:
    virtual void print(const std::string& s) = 0;
};

// Адаптерът
class PrinterAdapter : public IPrinter {
    LegacyPrinter legacy;
public:
    void print(const std::string& s) override {
        // Преобразуване на данни (Adaptation)
        legacy.oldPrint(const_cast<char*>(s.c_str()));
    }
};
```

### 3.2. PIMPL (Pointer to Implementation)
Уникален за C++ идиом (известен още като "Opaque Pointer" или "Cheshire Cat").
**Цел:** Скриване на детайлите на имплементацията от хедър файла, за да се намали времето за компилация и да се запази бинарната съвместимост (ABI).

**В Header (.h):**
```cpp
class Widget {
public:
    Widget();
    ~Widget(); // Деструкторът трябва да е тук
    void draw();
private:
    struct Impl; // Forward declaration
    std::unique_ptr<Impl> pImpl; // Указател към скритата имплементация
};
```

**В Source (.cpp):**
```cpp
struct Widget::Impl {
    // Всички тежки include-и (windows.h, gl.h) са тук
    void specializedDraw() { /*...*/ }
};

Widget::Widget() : pImpl(std::make_unique<Impl>()) {}
Widget::~Widget() = default; // Тук Impl вече е дефиниран
void Widget::draw() { pImpl->specializedDraw(); }
```

---

## 4. Поведенчески Шаблони (Behavioral Patterns)

### 4.1. Observer (Наблюдател)
Дефинира зависимост "един към много", така че когато един обект промени състоянието си, всички зависими се уведомяват.
**Употреба:** GUI системи (бутонът е натиснат -> уведоми бизнес логиката), Event системи.

**Модерна C++ имплементация:** Използвайте `std::function` вместо чисто наследяване.
```cpp
using EventCallback = std::function<void(int)>;

class Sensor {
    std::vector<EventCallback> observers;
public:
    void subscribe(EventCallback cb) { observers.push_back(cb); }
    void notify(int data) {
        for(auto& cb : observers) cb(data);
    }
};
```

### 4.2. Strategy (Стратегия)
Позволява смяна на алгоритъма по време на изпълнение.
**Употреба:** Сортиране, Компресия (Zip/Rar), Плащания (Card/PayPal).

**Compile-time Strategy (Policy-based design):**
В C++ често предпочитаме стратегията да се избира по време на компилация за по-висока скорост (без виртуални функции).

```cpp
template <typename SortPolicy>
class DataProcessor {
public:
    void process(std::vector<int>& data) {
        SortPolicy::sort(data); // Статичен полиморфизъм
    }
};
```

---

## 5. RAII (Resource Acquisition Is Initialization)

Макар и да не е в оригиналната книга "Gang of Four", RAII е **най-важният шаблон** в C++.
Идеята: Животът на ресурса (файл, памет, мутекс) е вързан за живота на обект в стека.
*   **Конструктор:** Заема ресурса.
*   **Деструктор:** Освобождава ресурса.

Това прави кода **Exception Safe**. Дори функцията да хвърли грешка, деструкторите на локалните обекти ще се извикат и ресурсите ще се освободят. `std::unique_ptr`, `std::lock_guard`, `std::fstream` са примери за RAII.

---

## 6. Професионално обобщение

1.  **Не прекалявайте (Over-engineering):** Не започвайте с Factory и Abstract Factory, ако просто `new` върши работа. Шаблоните добавят сложност. Използвайте ги само когато проблемът наистина го изисква.
2.  **CRTP (Curiously Recurring Template Pattern):** Специфичен за C++ шаблон за статичен полиморфизъм (`class Derived : public Base<Derived>`). Позволява добавяне на функционалност без цената на виртуални функции.
3.  **Dependency Injection:** Използвайте шаблони като Constructor Injection, за да направите кода си тестваем.

---
*(Този документ е част от "The Ultimate C++ Mastery Framework".)*