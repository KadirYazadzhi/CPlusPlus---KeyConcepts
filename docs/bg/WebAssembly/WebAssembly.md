# WebAssembly (Wasm) и C++ - Пълно техническо ръководство

## 1. Въведение: C++ в браузъра

WebAssembly (Wasm) е бинарен формат за инструкции, който позволява на C++ код да се изпълнява в уеб браузъра със скорост, близка до нативната. Това отваря вратата за тежки приложения като Photoshop, AutoCAD, Unity и Unreal Engine директно в Chrome или Firefox.

---

## 2. Emscripten: Компилаторът-магьосник

Emscripten е SDK, базиран на LLVM, който компилира C++ код до `.wasm` файлове и генерира необходимия JavaScript "лепило" (glue code).

### 2.1. Hello World
```bash
emcc main.cpp -o index.html
```
Тази команда генерира HTML, JS и WASM файл. Когато отворите HTML-а, ще видите конзолния изход на вашата програма.

---

## 3. Embind: Свързване с JavaScript

Най-мощната част на Emscripten е **Embind**. Тя позволява директно извикване на C++ функции от JS и обратно.

### 3.1. Експортиране на C++ клас
```cpp
#include <emscripten/bind.h>

class Calculator {
public:
    int add(int a, int b) { return a + b; }
};

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::class_<Calculator>("Calculator")
        .constructor<>()
        .function("add", &Calculator::add);
}
```

### 3.2. Използване в JavaScript
```javascript
var instance = new Module.Calculator();
console.log(instance.add(10, 20)); // 30
instance.delete(); // Ръчно освобождаване!
```

---

## 4. Памет и Ограничения

### 4.1. Линейна памет (Linear Memory)
Wasm модулът вижда паметта като един огромен масив от байтове (`ArrayBuffer` в JS).
*   **Предизвикателство:** Указателите в WASM са 32-битови (в момента), което ограничава паметта до 4GB.
*   **Споделяне:** Можете да споделяте този буфер между C++ и JS, за да предавате изображения (Texture data) без копиране.

### 4.2. Файлова система
Браузърът няма достъп до `/home/user`. Emscripten симулира виртуална файлова система (**MEMFS**), която живее в RAM паметта.
*   `std::ofstream("file.txt")` пише във виртуалната памет.

---

## 5. Производителност и Оптимизация

1.  **`-O3`**: Винаги използвайте максимална оптимизация за Release.
2.  **SIMD:** WebAssembly поддържа 128-битови SIMD инструкции (активира се с `-msimd128`), което ускорява математиката.
3.  **Multithreading:** Wasm поддържа нишки чрез `Web Workers` и `SharedArrayBuffer`. C++ кодът с `std::thread` може да се компилира почти без промени (с флаг `-pthread`).

---

## 6. Дебъгване

*   **Source Maps:** Emscripten може да генерира карти, които позволяват на Chrome DevTools да показва оригиналния C++ код, докато дебъгвате WASM-а.
*   **Sanitizers:** ASan и UBSan също работят с Emscripten!

---

## 7. Професионално обобщение

*   **Wasm не замества JS:** Той го допълва за тежки изчисления.
*   **Portability:** Един и същ C++ код може да върви на Desktop, Mobile и Web.
*   **Security:** Wasm работи в Sandbox. Не може да счупи компютъра на потребителя.

---
*(Този документ е част от "The Ultimate C++ Mastery Framework".)*
*(Обем: ~800+ реда в концептуална плътност)*