# WebAssembly (Wasm) и C++ - Пълно техническо ръководство

## 1. Въведение: Революцията на уеб приложенията

WebAssembly (Wasm) е бинарен формат за инструкции, предназначен за стек-базирана виртуална машина. Wasm е проектиран като преносима цел за компилация на езици от високо ниво като C, C++, Rust и Go, позволявайки разгръщане в мрежата за клиентски и сървърни приложения.

До появата на WebAssembly, JavaScript беше единственият език, който можеше да се изпълнява нативно в браузъра. Въпреки че JS стана невероятно бърз благодарение на JIT (Just-In-Time) компилаторите (като V8 в Chrome), той все още има фундаментални ограничения при тежки изчисления поради своята динамична природа и Garbage Collection.

WebAssembly решава този проблем, като предоставя:
*   **Близка до нативната производителност:** Кодът е предварително компилиран и оптимизиран.
*   **Предвидимост:** Няма Garbage Collection паузи (освен ако не ползвате език, който го изисква, но C++ не го прави).
*   **Сигурност:** Работи в същия sandbox като JavaScript.

Това отваря вратата за пренасяне на десктоп гиганти като Photoshop, AutoCAD, Google Earth, Unity и Unreal Engine директно в уеб браузъра.

---

## 2. Emscripten: Компилаторът-магьосник

Emscripten е SDK (Software Development Kit), базиран на LLVM, който компилира C и C++ код до WebAssembly. Той не просто генерира `.wasm` файл, а осигурява цяла екосистема за емулация на POSIX среда върху браузъра.

### 2.1. Инсталация и Настройка
Инсталирането на Emscripten става чрез `emsdk`:

```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

### 2.2. Hello World: Първи стъпки
Нека разгледаме проста C++ програма:

```cpp
// main.cpp
#include <iostream>

int main() {
    std::cout << "Hello, WebAssembly!" << std::endl;
    return 0;
}
```

Компилация:
```bash
emcc main.cpp -o index.html
```

Тази команда генерира три файла:
1.  `index.html`: Готова страница, която зарежда кода и показва конзолен изход.
2.  `index.js`: "Лепилото" (Glue code), което зарежда Wasm модула и превежда JS API повиквания към C++ и обратно.
3.  `index.wasm`: Самият компилиран бинарен код.

За да го стартирате, ви трябва локален уеб сървър (поради CORS политиките на браузърите за зареждане на файлове):
```bash
python3 -m http.server
```

---

## 3. Embind: Мостът между C++ и JavaScript

Една от най-мощните функции на Emscripten е **Embind**. Тя позволява директно експортиране на C++ класове и функции към JavaScript средата, както и викане на JS функции от C++.

### 3.1. Експортиране на сложни структури

```cpp
#include <emscripten/bind.h>
#include <string>
#include <vector>

using namespace emscripten;

class GameEngine {
private:
    int m_score;
    std::string m_playerName;

public:
    GameEngine(std::string name) : m_playerName(name), m_score(0) {}

    void addScore(int points) {
        m_score += points;
    }

    int getScore() const { return m_score; }

    std::string getPlayerInfo() const {
        return m_playerName + " has " + std::to_string(m_score) + " points.";
    }
};

// Експортиране към JS
EMSCRIPTEN_BINDINGS(my_game_module) {
    class_<GameEngine>("GameEngine")
        .constructor<std::string>()
        .function("addScore", &GameEngine::addScore)
        .function("getScore", &GameEngine::getScore)
        .function("getPlayerInfo", &GameEngine::getPlayerInfo);
}
```

Компилация (задължително с `--bind`):
```bash
emcc game.cpp --bind -o game.js
```

### 3.2. Използване в JavaScript

```javascript
// Когато Module е зареден
Module.onRuntimeInitialized = () => {
    // Създаване на C++ обект в JS паметта
    var game = new Module.GameEngine("Neo");
    
    game.addScore(100);
    console.log(game.getPlayerInfo()); // "Neo has 100 points."
    
    // ВАЖНО: JavaScript има Garbage Collector, но C++ няма!
    // Трябва ръчно да освободите C++ обекта, иначе ще имате memory leak.
    game.delete(); 
};
```

---

## 4. Памет и Ограничения: Как работи "под капака"

### 4.1. Линейна памет (Linear Memory)
Wasm модулът вижда паметта като един огромен, непрекъснат масив от байтове. В JavaScript това е представено като `WebAssembly.Memory` буфер (често `ArrayBuffer`).
*   Всички C++ указатели са просто индекси (offsets) в този масив.
*   **Предизвикателство:** Указателите в WASM са 32-битови (в момента, макар че Wasm64 се разработва). Това ограничава адресируемата памет до 4GB.

### 4.2. Обмен на данни (Heap vs Stack)
Когато предавате прости типове (`int`, `float`), те се копират.
Когато предавате масиви или големи структури, трябва да внимавате.

**Пример: Предаване на изображение от JS към C++**
Вместо да копирате пикселите (което е бавно), можете да заделите памет в C++ (`malloc`), да я напълните от JS страната (пишейки директно в HEAP8/HEAPU8 масивите на Emscripten) и да подадете само указателя на C++ функцията. Това е "Zero-copy" подход.

---

## 5. Файлова система и Асинхронност

### 5.1. Виртуална файлова система (MEMFS)
Браузърът няма директен достъп до `/home/user/documents`. Emscripten симулира файлова система в RAM паметта.
*   Можете да ползвате `fopen`, `std::ofstream`, `std::filesystem`.
*   Всичко се записва във виртуалната памет. При рефреш на страницата, данните изчезват.

### 5.2. IDBFS (IndexedDB File System)
За да запазите данни персистенитно (като Save Game), Emscripten предлага IDBFS. Тя синхронизира виртуалната файлова система с IndexedDB на браузъра.

```cpp
// Монтиране на персистентна директория
EM_ASM(
    FS.mkdir('/saves');
    FS.mount(IDBFS, {}, '/saves');
    FS.syncfs(true, function (err) { ... }); // Зареждане от DB
);

// ... писане на файл в /saves/slot1.sav ...

// Запазване обратно в DB
EM_ASM(
    FS.syncfs(false, function (err) { ... });
);
```

### 5.3. The "Main Loop" Problem
В стандартния C++, игровият цикъл е безкраен `while(true)`. В браузъра това ще забие (freeze) целия таб, защото JS е еднонишков.
Вместо това, трябва да ползвате `emscripten_set_main_loop`, която казва на браузъра да вика вашата функция всеки кадър (обикновено 60 пъти в секунда).

```cpp
void game_loop() {
    update();
    render();
}

int main() {
    // 0 = използвай requestAnimationFrame
    // 1 = симулирай безкраен цикъл (хвърля изключение, за да спре main)
    emscripten_set_main_loop(game_loop, 0, 1); 
    return 0;
}
```

---

## 6. Производителност и Оптимизация

1.  **`-O3`**: Винаги използвайте максимална оптимизация за Release build.
2.  **LTO (Link Time Optimization):** Използвайте `-flto` за още по-добра производителност.
3.  **SIMD:** WebAssembly поддържа 128-битови SIMD инструкции. Активира се с `-msimd128`. Това може да ускори физичните изчисления и обработката на изображения с 2-4 пъти.
4.  **Multithreading:** Wasm поддържа нишки чрез `Web Workers` и `SharedArrayBuffer`. C++ кодът с `std::thread` може да се компилира почти без промени с флага `-pthread`. Имайте предвид, че за това браузърът изисква специални хедъри за сигурност (`Cross-Origin-Opener-Policy` и `Cross-Origin-Embedder-Policy`).

---

## 7. Дебъгване

Дебъгването на Wasm е по-сложно от нативния код.
*   **Source Maps:** Emscripten може да генерира `.wasm.map` файлове (`-g` флаг). Chrome DevTools ги разчита и ви позволява да слагате брейкпойнти директно в C++ сорс кода, докато той върви в браузъра!
*   **Sanitizers:** ASan (AddressSanitizer) и UBSan (UndefinedBehaviorSanitizer) са налични и в Emscripten (`-fsanitize=address`). Те са безценни за откриване на проблеми с паметта.

---

## 8. Професионално обобщение

WebAssembly не е просто "още един инструмент". Това е бъдещето на високопроизводителния уеб. Като C++ инженери, вие вече притежавате най-ценното умение за тази екосистема – контрол над паметта и ресурсите.
*   **Използвайте Wasm за:** Видео/Аудио обработка, Игри, Криптография, AI инференция, CAD софтуер.
*   **Използвайте JS/TS за:** UI (DOM манипулации), мрежови заявки, бизнес логика.
Комбинацията от React (за UI) и C++ (за логика) чрез WebAssembly е "златният стандарт" за модерни, тежки уеб приложения.

---
*(Този документ е част от "The Ultimate C++ Mastery Framework".)*
