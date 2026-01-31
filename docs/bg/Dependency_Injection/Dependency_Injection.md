# Dependency Injection (DI) в C++ - Пълно техническо ръководство

## 1. Въведение: Защо кодът става "Спагети"?

Една от най-големите грешки в архитектурата е "Твърдото свързване" (Tight Coupling).
Представете си клас `Database`, който се свързва с MySQL.
Представете си клас `App`, който прави `new Database()` в конструктора си.

Сега `App` е женен за `Database`.
1.  **Не можете да тествате:** За да тествате `App`, трябва да имате работещ MySQL сървър.
2.  **Не можете да променяте:** Ако искате да минете на PostgreSQL, трябва да пренапишете `App`.

**Dependency Injection (DI)** решава това. Идеята е проста: **Не създавайте зависимостите си вътре. Поискайте някой да ви ги даде отвън.**

---

## 2. Inversion of Control (IoC) и SOLID

DI е реализация на принципа **D (Dependency Inversion)** от SOLID:
> "Модулите от високо ниво не трябва да зависят от модули от ниско ниво. И двата трябва да зависят от абстракции."

### Пример за Рефакториране

**Лош код (Tightly Coupled):**
```cpp
class Lamp {
public:
    void turnOn() { cout << "Light!"; }
};

class Button {
    Lamp lamp; // Твърда зависимост
public:
    void press() { lamp.turnOn(); }
};
```

**Добър код (Loosely Coupled):**
```cpp
// 1. Абстракция
class IDevice {
public:
    virtual void turnOn() = 0;
    virtual ~IDevice() = default;
};

class Lamp : public IDevice {
public:
    void turnOn() override { cout << "Light!"; }
};

class Motor : public IDevice {
public:
    void turnOn() override { cout << "Vroom!"; }
};

// 2. Инжектиране
class Button {
    IDevice& device; // Работи с ВСЯКО устройство
public:
    Button(IDevice& d) : device(d) {} // Constructor Injection
    void press() { device.turnOn(); }
};
```
Сега `Button` може да включва лампи, мотори, или дори `MockDevice` за тестове.

---

## 3. Видове Инжектиране

1.  **Constructor Injection (Препоръчително):**
    *   Зависимостите се подават в конструктора.
    *   Гарантира, че обектът е напълно инициализиран и валиден.
    *   Използвайте `const &` или `std::shared_ptr`.

2.  **Setter Injection:**
    *   `setDevice(IDevice* d)`.
    *   Полезно за опционални зависимости или кръгови зависимости (A иска B, B иска A).

3.  **Interface Injection:**
    *   Обектът имплементира интерфейс `IInjectable`, който има метод `inject`. Рядко се ползва в C++.

---

## 4. Mocking Frameworks: Силата на DI

Най-голямата полза от DI е тестването. За целта използваме Mock обекти.
В C++ най-популярният инструмент е **Google Mock (GMock)**.

```cpp
#include <gmock/gmock.h>

// Създаваме "фалшив" клас
class MockDevice : public IDevice {
public:
    // Макросът генерира целия нужен код за метода turnOn
    MOCK_METHOD(void, turnOn, (), (override));
};

TEST(ButtonTest, PressTurnsOnDevice) {
    MockDevice mock;
    
    // Очакваме, че методът turnOn ще бъде извикан точно 1 път
    EXPECT_CALL(mock, turnOn()).Times(1);
    
    Button btn(mock); // Инжектираме фалшивия обект
    btn.press();
}
```
Без DI, този тест би бил невъзможен.

---

## 5. DI Containers (Frameworks)

В малък проект ("Pure DI"), вие свързвате всичко в `main()`:
```cpp
int main() {
    auto lamp = std::make_shared<Lamp>();
    auto btn = std::make_shared<Button>(*lamp);
    btn->press();
}
```

В голям проект с 500 класа, този "Composition Root" става огромен. Тук идват DI Framework-ците като **Boost.DI** или **Google Fruit**. Те автоматизират свързването.

### Пример с Boost.DI
```cpp
#include <boost/di.hpp>
namespace di = boost::di;

int main() {
    // Описваме правилата: Когато някой иска IDevice, дай му Lamp.
    auto injector = di::make_injector(
        di::bind<IDevice>.to<Lamp>()
    );

    // Магия: injector-ът вижда, че Button иска IDevice,
    // създава Lamp, и после създава Button с нея.
    auto btn = injector.create<Button>();
    btn.press();
}
```

---

## 6. Composition Root

Това е архитектурният принцип, който казва:
**"Цялата конфигурация и свързване на обекти трябва да се случва на едно единствено място – в началото на програмата (`main`)."**

Останалата част от приложението не трябва да знае за `injector` или да вика `new`. Тя просто работи с подадените и интерфейси.

---

## 7. Service Locator (Анти-патерн)

Много хора бъркат DI със Service Locator.
```cpp
// Service Locator (Лошо!)
void Button::press() {
    auto device = Locator::Get<IDevice>(); // Скрита зависимост!
    device->turnOn();
}
```
Защо е лошо?
*   API-то лъже: Конструкторът на `Button` е празен, изглежда, че няма зависимости.
*   Глобално състояние: Локаторът е глобален Singleton, което прави тестовете трудни (състоянието "изтича" между тестовете).

---

## 8. Професионално обобщение

1.  **Тестваемост:** Това е главната причина за DI. Ако не можете да напишете Unit Test с Mock обект, архитектурата ви е грешна.
2.  **Lifetime Management:** Контейнерите (като Boost.DI) могат да управляват живота на обектите (Singleton vs Unique).
3.  **Performance:** C++ DI библиотеките използват шаблони (Templates) и правят всичко по време на компилация. **Няма Runtime Overhead!** Това е огромна разлика спрямо Java/C# контейнерите, които ползват Reflection и са бавни.

---
*(Този документ е част от "The Ultimate C++ Mastery Framework".)*