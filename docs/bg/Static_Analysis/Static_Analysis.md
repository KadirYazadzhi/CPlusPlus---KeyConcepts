# Статичен Анализ и Линтери в C++ (Static Analysis) - Пълно техническо ръководство

## 1. Въведение: Философията "Shift Left"

В традиционния "Waterfall" модел на разработка, тестването се случва най-накрая – точно преди релийз. Това е катастрофално скъпо. Ако откриете архитектурен бъг в деня преди пускането, поправката му може да струва 100 пъти по-скъпо, отколкото ако го бяхте открили докато пишете кода.

Модерният DevOps подход се нарича **"Shift Left"** – преместване на откриването на бъгове "наляво" по времевата линия (т.е. към момента на писане).
**Статичният анализ** е най-мощното оръжие в този арсенал. Той представлява автоматизиран "Code Reviewer", който никога не спи, знае наизуст 1000 страници от C++ стандарта и може да проследи променлива през 50 функции, за да открие потенциален `null pointer dereference`.

---

## 2. Clang-Tidy: Де факто стандартът

`Clang-Tidy` е част от LLVM проекта и е много повече от просто "линтер". Тъй като използва същия front-end като компилатора Clang, той има пълно разбиране за синтактичното дърво (AST) на вашия код.

### 2.1. Подробен преглед на проверките (Checks)

Clang-Tidy групира проверките си в модули. Ето най-важните от тях с примери:

#### A. `bugprone-*` (Ловци на бъгове)
Тези проверки намират код, който се компилира, но почти сигурно е грешен.

*   **`bugprone-sizeof-expression`**:
    ```cpp
    int* p = new int[10];
    // ГРЕШКА: sizeof(p) връща 8 (размер на pointer), а не 40 (размер на масива)!
    std::memset(p, 0, sizeof(p)); 
    ```

*   **`bugprone-use-after-move`**:
    ```cpp
    std::string s = "hello";
    std::vector<std::string> v;
    v.push_back(std::move(s));
    // ГРЕШКА: s вече е в "unspecified state", но ние го ползваме!
    std::cout << s << std::endl; 
    ```

#### B. `modernize-*` (Модернизация)
Помага ви да мигрирате стар C++98 код към C++11/14/17/20.

*   **`modernize-use-override`**: Добавя `override` на виртуалните функции (предпазва от правописни грешки).
*   **`modernize-use-nullptr`**: Заменя `NULL` и `0` с `nullptr`.
*   **`modernize-loop-convert`**:
    ```cpp
    // Преди
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) { ... }
    // След (Автоматичен Fix!)
    for (int val : v) { ... }
    ```

#### C. `performance-*` (Оптимизация)
Намира неефективен код, който забавя програмата.

*   **`performance-unnecessary-copy-initialization`**:
    ```cpp
    // Лошо: Копираме string без причина
    const std::string val = getLongString(); 
    // Добро: Ползваме референция
    const std::string& val = getLongString(); 
    ```

*   **`performance-move-const-arg`**: Предупреждава, ако се опитвате да `std::move` константен обект (което не прави нищо и води до копиране).

---

## 3. Cppcheck: Дълбокият анализ

Докато Clang-Tidy е отличен за стил и модернизация, **Cppcheck** е кралят на "Path Analysis" (Анализ на пътищата). Той не изисква кодът да се компилира перфектно, което го прави идеален за бързи проверки на legacy проекти.

### 3.1. Как работи Data Flow Analysis?
Cppcheck симулира изпълнението на програмата, проследявайки стойностите на променливите.

```cpp
void process(int* ptr, bool flag) {
    int x = 0;
    if (flag) {
        x = 5;
    }
    
    // ... 100 реда код ...
    
    if (x == 0) {
        // Cppcheck знае, че ако сме тук, flag е бил false.
        // Ако тук де-реферираме ptr, той ще провери дали ptr може да е null при flag == false.
        *ptr = 10;
    }
}
```

### 3.2. Inconclusive Checks
Cppcheck има режим `--inconclusive`, при който съобщава за проблеми, дори да не е 100% сигурен. Това дава повече фалшиви позитиви, но хваща изключително трудни бъгове в мултинишкови сценарии.

---

## 4. Интеграция в CI/CD (GitHub Actions)

Статичният анализ е безполезен, ако разчитате програмистите да го пускат ръчно. Той трябва да е "Gatekeeper" във вашия CI пайплайн.

Примерна конфигурация за GitHub Actions:

```yaml
name: Static Analysis
on: [push, pull_request]

jobs:
  clang-tidy:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v3
    
    - name: Install LLVM
      run: sudo apt-get install clang-tidy-14
      
    - name: Run Clang-Tidy
      run: |
        cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
        run-clang-tidy -p build -header-filter=src/.*
```
Флагът `CMAKE_EXPORT_COMPILE_COMMANDS=ON` генерира файл `compile_commands.json`, който казва на Clang-Tidy точно как се компилира всеки файл (какви `#define` и `-I` пътища се ползват). Без този файл анализът е неточен.

---

## 5. Потискане на Предупреждения (Suppression)

В реалния свят понякога имаме "фалшиви позитиви" или код, който съзнателно нарушава правилата (напр. low-level optimization).

### 5.1. NOLINT коментари
В Clang-Tidy:
```cpp
// Игнорираме всички проверки на този ред
int* p = (int*)malloc(100); // NOLINT

// Игнорираме само конкретна проверка (Препоръчително!)
int* p = (int*)malloc(100); // NOLINT(cppcoreguidelines-no-malloc)
```

В Cppcheck:
```cpp
// cppcheck-suppress memleak
int* p = new int[10];
```

**Best Practice:** Винаги добавяйте коментар ЗАЩО потискате предупреждението.
`// NOLINT(bugprone-narrowing-conversions) - Хардуерът изисква 8-битов регистър`

---

## 6. Enterprise Инструменти: PVS-Studio и SonarQube

Когато става въпрос за милиони редове код, безплатните инструменти могат да се задъхат или да липсва отчетност.

*   **PVS-Studio:** Платен инструмент, известен с намирането на "Copy-Paste Errors". Например:
    ```cpp
    if (a.x == b.x && a.y == a.y) { ... } // Трябваше да е b.y!
    ```
    Човешкото око пропуска това. PVS-Studio го хваща.

*   **SonarQube:** Това е мениджърски дашборд. Той визуализира "Техническия дълг" в дни/часове.
    *   "Quality Gate": Можете да настроите правило "Ако новият код има по-малко от 80% покритие или повече от 5 Critical Issues, не позволявай Merge".

---

## 7. Компилаторът като Анализатор

Преди да инсталирате каквото и да е, пуснете компилатора си на макс.
*   **GCC/Clang:** `-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2`.
*   **MSVC:** `/W4 /permissive-`.

Опцията `-Werror` е критична за дисциплината на екипа. Тя превръща Warning-а в Error. Никой не може да каже "Ще го оправя по-късно", защото кодът просто не се компилира.

---

## 8. Професионално обобщение

1.  **Не всичко наведнъж:** Ако пуснете `clang-tidy` на 10-годишен проект, ще получите 50,000 грешки. Екипът ще се демотивира.
    *   **Стратегия:** Включете проверките само за **новите файлове** или само за редовете, променени в текущия Pull Request (т.нар. Differential Analysis).
2.  **Formatter vs Linter:** Не бъркайте `clang-format` (който оправя само интервалите и скобите) с `clang-tidy` (който оправя логиката). Трябват ви и двете.
3.  **Custom Checks:** За много големи проекти можете да напишете свои собствени Clang-Tidy проверки (напр. "Всички класове, наследяващи `IWidget`, трябва да имат метод `Draw()`").

---
*(Този документ е част от "The Ultimate C++ Mastery Framework".)*