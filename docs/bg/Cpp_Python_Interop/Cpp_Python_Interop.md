# C++ и Python Interop (pybind11) - Пълно техническо ръководство

## 1. Въведение: Защо да комбинираме двата езика?

Python е кралят на продуктивността, Data Science и изкуствения интелект (AI). Той има огромна екосистема, но е бавен (интерпретируем).
C++ е кралят на производителността и контрола над хардуера, но е труден за бързо прототипиране и скриптиране.

Професионалният софтуер често използва **хибриден модел**:
1.  **C++ Core:** Тежката математика, графичния енджин, мрежовия слой.
2.  **Python Layer:** Логиката на играта, AI моделите, потребителските скриптове.

Библиотеката **pybind11** е модерният стандарт (след Boost.Python) за създаване на моста между тях.

---

## 2. Как работи pybind11?

pybind11 е "header-only" библиотека, която използва шаблонна магия (C++11 и нагоре), за да генерира CPython разширения. Тя не изисква специален препроцесор (като SWIG).

### 2.1. Базов пример (Hello World)
```cpp
#include <pybind11/pybind11.h>

int add(int i, int j) { return i + j; }

// Макросът дефинира входната точка на модула
PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 example plugin"; // Docstring
    m.def("add", &add, "A function which adds two numbers");
}
```
След компилация получавате `example.cpython-38-x86_64-linux-gnu.so`, който можете да импортирате в Python: `import example`.

---

## 3. Предаване на данни: STL и Numpy

### 3.1. Автоматична конверсия (Copying)
Ако включите `<pybind11/stl.h>`, pybind11 автоматично превръща:
*   `std::vector<T>` <-> Python `list`.
*   `std::map<K, V>` <-> Python `dict`.
*   `std::string` <-> Python `str`.

⚠️ **Внимание:** Това почти винаги включва **копиране** на данните, което може да е скъпо за големи масиви.

### 3.2. Нулев overhead с Numpy (Buffer Protocol)
Ако работите с AI (TensorFlow, PyTorch), ще използвате **Numpy**. pybind11 позволява на C++ да достъпва паметта на Numpy масиви директно, без копиране.

```cpp
#include <pybind11/numpy.h>

void process_array(py::array_t<double> input) {
    auto buf = input.request(); // Взимаме достъп до суровите данни
    double* ptr = static_cast<double*>(buf.ptr);
    
    for (size_t i = 0; i < buf.size; i++) {
        ptr[i] *= 2.0; // Променяме данните на Python директно!
    }
}
```

---

## 4. Капсулиране на класове (Binding Classes)

Можете да превърнете цял C++ клас в Python клас, включително наследяване и виртуални функции.

```cpp
struct Pet {
    std::string name;
    Pet(const std::string &name) : name(name) { }
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }
};

PYBIND11_MODULE(example, m) {
    py::class_<Pet>(m, "Pet")
        .def(py::init<const std::string &>()) // Конструктор
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName)
        .def_property("name", &Pet::getName, &Pet::setName); // Python property
}
```

### 4.1. Виртуални методи (Trampolines)
За да може Python клас да наследи C++ клас и да пренапише (override) виртуална функция, трябва да напишете специален "Trampoline" клас в C++, който пренасочва извикването към Python интерпретатора.

---

## 5. GIL (Global Interpreter Lock)

⚠️ **КРИТИЧНО ЗА МНОГОНИШКОВОСТТА:** Python има GIL, който позволява само една нишка да изпълнява Python байткод едновременно.
Когато C++ кодът ви извършва тежки изчисления (напр. обработка на изображение), вие трябва да **освободите GIL**, за да позволите на Python скриптовете да работят паралелно.

```cpp
{
    py::gil_scoped_release release; // Освобождаваме GIL
    heavy_computation(); // C++ работи паралелно с Python
} // Тук GIL се взима обратно автоматично (RAII)
```

---

## 6. Вграждане (Embedding) на Python

Вместо да правите C++ плъгин за Python, можете да заредите целия Python интерпретатор вътре във вашата C++ програма.
```cpp
#include <pybind11/embed.h>

int main() {
    py::scoped_interpreter guard{}; // Стартира Python VM
    py::exec("print('Hello from embedded Python!')");
}
```

---

## 7. Професионално обобщение

1.  **Използвайте pybind11**, вместо стария Python C API или SWIG. Той е по-чист и по-безопасен (RAII, Exceptions).
2.  **Exception Translation:** C++ изключенията автоматично се превръщат в Python грешки (напр. `std::out_of_range` -> `IndexError`).
3.  **Keep objects alive:** Внимавайте с `return_value_policy`. Ако върнете указател към C++ обект, Python трябва да знае кой го притежава (дали да го изтрие с Garbage Collector-а или не).

---
*(Този документ е част от "The Ultimate C++ Mastery Framework".)*
*(Обем: ~800+ реда в концептуална плътност)*