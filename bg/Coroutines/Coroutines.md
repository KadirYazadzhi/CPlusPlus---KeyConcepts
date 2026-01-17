# Корутини (Coroutines) в C++20

## 1. Въведение

Корутината е функция, която може да **спре изпълнението си** (suspend), да върне контрола на извикващия код, и по-късно да **възобнови изпълнението си** (resume) от точката, в която е спряла, запазвайки локалните си променливи.

В C++20 корутините са безстекови (Stackless), което ги прави изключително леки и ефективни (няма нужда от заделяне на мегабайти памет за стек на нишка).

Корутините се разпознават по наличието на една от трите ключови думи:
*   `co_await`: Спира изпълнението до завършване на задача.
*   `co_yield`: Връща стойност и спира (за генератори).
*   `co_return`: Завършва корутината.

---

## 2. Генератор (Пример)

Най-простият пример е генератор на числа. Вместо да изчислява всички числа и да ги пази във `vector`, той ги генерира "мързеливо" едно по едно.

⚠️ **Забележка:** C++20 предоставя само *механизма*. Самият клас `Generator` все още не е в стандарта (идва в C++23 като `std::generator`), затова трябва да напишем boilerplate код (обещание и манипулатор).

```cpp
#include <iostream>
#include <coroutine>

// Нашият Generator клас (Boilerplate)
struct Generator {
    struct promise_type {
        int current_value;
        
        Generator get_return_object() { 
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)}; 
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }

        std::suspend_always yield_value(int value) {
            current_value = value;
            return {};
        }
    };

    std::coroutine_handle<promise_type> handle;

    Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Generator() { if (handle) handle.destroy(); }

    bool next() {
        handle.resume();
        return !handle.done();
    }

    int value() const {
        return handle.promise().current_value;
    }
};

// Корутината
Generator sequence(int start, int end) {
    for (int i = start; i <= end; ++i) {
        co_yield i; // Спира тук и връща i
    }
}

int main() {
    auto gen = sequence(1, 5);
    
    while (gen.next()) {
        std::cout << gen.value() << " ";
    }
    // Изход: 1 2 3 4 5
}
```

---

## 3. co_await и Асинхронност

Основната сила на корутините е в асинхронното програмиране (мрежови заявки, четене на файлове). Корутините позволяват асинхронният код да изглежда като синхронен.

```cpp
// Псевдокод (защото изисква библиотека за networking)
Task downloadFile(std::string url) {
    // Вместо callback hell:
    auto connection = co_await connect(url);
    auto data = co_await connection.read();
    co_return data;
}
```

`co_await` казва: "Спри тази функция, освободи нишката да прави други неща, и когато `connect` завърши, върни ме тук."

---

## 4. Обобщение

*   Корутините са революция за C++, но имат стръмна крива на учене.
*   Използвайте ги за **Generators** (мързеливи поредици) и **Asynchronous I/O**.
*   В C++20 трябва да пишете много собствен код (Promises/Handles), но C++23 добавя `std::generator` за улеснение.
