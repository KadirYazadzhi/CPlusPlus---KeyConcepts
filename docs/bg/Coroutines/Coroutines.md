# Корутини (Coroutines) в C++20 - Пълно техническо ръководство

## 1. Въведение: Функциите с Памет

Корутината е най-революционното допълнение в C++20. Това е функция, която може да бъде спряна (**Suspend**) и по-късно възобновена (**Resume**), запазвайки цялото си вътрешно състояние (локални променливи, текущ ред на изпълнение).

За разлика от нишките (Threads), корутините са **безстекови (stackless)**.
*   **Нишка:** Има запазен стек в ОС (1-2 MB). Тежка за превключване (Context Switch).
*   **Корутина:** Има малък блок памет в Heap-а (няколко десетки байта). Екстремно лека и бърза. Управлява се от компилатора, не от ядрото.

---

## 2. Ключовите думи на бъдещето

Една функция автоматично става корутина, ако съдържа поне една от следните ключови думи:

1.  **`co_await`**: Спира изпълнението на корутината, докато чаканото събитие не приключи. Връща контрола на извикващия (Caller).
2.  **`co_yield`**: Връща междинна стойност и спира корутината (Генератор).
3.  **`co_return`**: Финализира корутината, унищожава състоянието ѝ и връща краен резултат.

---

## 3. Анатомия на Корутината (Under the Hood)

⚠️ **ИНЖЕНЕРЕН ПОГЛЕД:** Когато компилаторът види корутина, той я "нарязва" на части и създава **Машина за състояния (State Machine)**.

Тя се състои от три основни компонента:

### 3.1. Promise Object
Това е "мозъкът" на корутината. Той се създава вътре в нея и служи за комуникация с външния свят.
*   Какво да прави при старт (`initial_suspend`)?
*   Какво да прави при край (`final_suspend`)?
*   Как да се справи с изключения (`unhandled_exception`)?
*   Как да върне стойност (`return_value` / `yield_value`)?

### 3.2. Coroutine Handle (`std::coroutine_handle`)
Това е "дистанционното управление" за корутината. То е лек указател (като `void*`), който позволява на външния код да:
*   Възобнови корутината (`resume()`).
*   Я унищожи (`destroy()`).
*   Провери дали е приключила (`done()`).

### 3.3. Coroutine State (Frame)
Скрит блок в динамичната памет (Heap), който съхранява:
*   Обекта Promise.
*   Аргументите на функцията (копирани или преместени).
*   Локалните променливи.
*   Точката на спиране (Instruction Pointer).

Този фрейм се заделя с `operator new` (освен ако компилаторът не приложи HALO - Heap Allocation Elision).

---

## 4. Имплементация на Генератор (Step-by-Step)

Ето как се пише най-простият генератор (преди C++23 да добави `std::generator`):

```cpp
#include <coroutine>
#include <iostream>

struct Generator {
    struct promise_type {
        int current_value;
        
        Generator get_return_object() { 
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)}; 
        }
        std::suspend_always initial_suspend() { return {}; } // Спира веднага при старт
        std::suspend_always final_suspend() noexcept { return {}; } // Спира преди унищожаване
        void return_void() {} // Край на функцията
        void unhandled_exception() { std::terminate(); }
        
        std::suspend_always yield_value(int value) { // При co_yield
            current_value = value;
            return {};
        }
    };

    std::coroutine_handle<promise_type> handle;
    
    Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Generator() { if (handle) handle.destroy(); } // RAII

    int next() {
        handle.resume(); // Възобновява до следващия co_yield
        return handle.promise().current_value;
    }
};

Generator counter() {
    for (int i = 0; i < 3; ++i) {
        co_yield i; // Спира и връща i
    }
}

int main() {
    auto gen = counter();
    std::cout << gen.next(); // 0
    std::cout << gen.next(); // 1
    std::cout << gen.next(); // 2
}
```

---

## 5. Асинхронен I/O и Awaitables

Най-мощната употреба на корутините е за превръщане на "Callback Hell" в линеен код.
За да може нещо да се `co_await`-ва, то трябва да бъде **Awaitable** (да има методи `await_ready`, `await_suspend`, `await_resume`).

```cpp
// Примерна логика (псевдокод с библиотека като Asio)
Task processNetwork() {
    try {
        auto socket = co_await connect("127.0.0.1", 8080);
        auto data = co_await socket.async_read();
        co_await socket.async_write("OK");
    } catch (const std::exception& e) {
        // Обработка на грешки точно като при синхронен код!
        std::cerr << e.what();
    }
}
```

---

## 6. Професионални капани

1.  **Dangling References:** Корутините копират аргументите си във фрейма, но ако подадете референция към временен обект, корутината може да увисне.
2.  **Забравен `co_return`:** Ако корутината приключи без `co_return` (пада от края), се вика `return_void`. Ако Promise обекта няма такъв метод, компилаторът дава грешка.
3.  **Heap Allocation:** Корутините винаги ползват Heap (освен при оптимизации). В много стегнати цикли това може да е проблем.

---

## 7. Професионално обобщение

*   Корутините не са нишки. Те се изпълняват в нишката, която ги вика (освен ако не ги прехвърлите с `co_await executor`).
*   Използвайте ги за **Генератори** (Lazy sequences) и **Асинхронни задачи**.
*   В C++23 използвайте `std::generator`, вместо да пишете свой собствен Promise type.

---
*(Документацията е подготвена за проекта "Ключови концепции в C++".*
*Версия: 3.0 - Експертна детайлност)*