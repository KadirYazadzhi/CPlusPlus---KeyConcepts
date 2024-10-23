# Основни концепции в C++ 🚀

Този документ обяснява основните концепции в C++, като предоставя кратки обяснения и примери за всяка тема. Целта е да се улесни разбирането и да се предостави полезен справочник.

---

## 1. 🛠 Референции (References)
Референцията е **алтернатива на указателя**. Тя създава псевдоним (alias) за вече съществуваща променлива, което означава, че референцията сочи директно към стойността на променливата.

### 🟢 Плюсове:
- Лесни за използване.
- Предотвратяват нулиране на указатели (null pointers).

### 🔴  Минуси:
- Не могат да бъдат пренасочвани след инициализация.

```cpp
int a = 5;
int& ref = a; // референция към 'a'
ref = 10;     // променя 'a' на 10
```

## 2. 🧭 Указатели (Pointers)
Указателите са **променливи, които съхраняват адреса на друга променлива**. Те са полезни при динамично разпределяне на памет и директна работа с паметта.

### 🟢 Плюсове:
- Предоставят директен достъп до паметта.
- Могат да бъдат пренасочвани.

### 🔴  Минуси:
- Могат да водят до грешки като **dangling pointers** или **memory leaks**.

```cpp
int a = 5;
int* ptr = &a; // указател към 'a'
*ptr = 10;     // променя 'a' на 10
```

## 3. 📊 Масиви (Arrays)
Масивът е **последователност от елементи с фиксиран размер**. Всички елементи в масива трябва да са от един и същи тип.

### 🟢 Плюсове:
- Прост и ефективен за съхранение на множество стойности.

### 🔴 Минуси:
- Размерът на масива трябва да бъде известен предварително.
- Липсва гъвкавост при добавяне на нови елементи.

### 🔹 Четене на елементи от масив:
За да прочетете елемент от масив, използвате индекса на елемента. Индексирането започва от 0.

```cpp
int arr[5] = {1, 2, 3, 4, 5}; // Инициализация на масив
int firstElement = arr[0]; // Четене на първия елемент (1)
int thirdElement = arr[2]; // Четене на третия елемент (3)
```

### 🔹 Извеждане на елементи от масив:
Можете да използвате цикъл за извеждане на всички елементи от масива.

```cpp
#include <iostream>
using namespace std;

int arr[5] = {1, 2, 3, 4, 5}; // Инициализация на масив

for (int i = 0; i < 5; i++) {
    cout << "Елемент " << i << ": " << arr[i] << endl; // Извежда всеки елемент
}
```

### 🔹 Модификация на елементи в масива:
Можете да промените стойностите на елементите по същия начин, по който ги четете.

```cpp
arr[0] = 10; // Променя първия елемент на 10
arr[2] = 20; // Променя третия елемент на 20
```

### 🔹 Размер на масива:
В C++ няма вграден начин да се разбере размерът на масива по време на изпълнение (runtime). Можете да го получите чрез sizeof, но това работи само в рамките на същия обхват (scope).

```cpp
int arrSize = sizeof(arr) / sizeof(arr[0]); // Определя броя на елементите
cout << "Размер на масива: " << arrSize << endl;
```

### 🔹 Операции с масиви:
- **Обхождане на масив:** Можете да използвате цикли за обхождане на елементите.
- **Търсене:** Можете да използвате цикъл за търсене на конкретен елемент.

```cpp
bool found = false;
int searchValue = 3;

for (int i = 0; i < 5; i++) {
    if (arr[i] == searchValue) {
        found = true;
        cout << "Намерено на индекс: " << i << endl;
        break;
    }
}

if (!found) {
    cout << "Елементът не е намерен." << endl;
}
```


## 4. 🔢 Двумерни масиви (2D Arrays)
Двумерните масиви **са масиви от масиви** и могат да се използват за съхраняване на матрици.

### 🟢 Плюсове:
- Удобни за работа с матрици и таблични данни.

### 🔴 Минуси:
- Както и при едномерните масиви, размерът им трябва да е известен предварително.

### 🔹 Инициализация на двумерен масив:
Можете да инициализирате двумерен масив по следния начин:

```cpp
int matrix[3][3] = {
  {1, 2, 3},
  {4, 5, 6},
  {7, 8, 9}
};
```

### 🔹 Четене на елементи от двумерен масив:
За да прочетете елемент от двумерен масив, трябва да използвате два индекса: един за реда и един за колоната.

```cpp
int value = matrix[0][1]; // Чете стойността на елемента на ред 0 и колона 1 (2)
```

### 🔹 Извеждане на елементи от двумерен масив:
Можете да използвате вложени цикли, за да извеждате всички елементи от двумерен масив.

```cpp
#include <iostream>
using namespace std;

int matrix[3][3] = {
  {1, 2, 3},
  {4, 5, 6},
  {7, 8, 9}
};

for (int i = 0; i < 3; i++) {  // Обхожда редовете
    for (int j = 0; j < 3; j++) {  // Обхожда колоните
        cout << matrix[i][j] << " "; // Извежда всеки елемент
    }
    cout << endl; // Прехвърля на нов ред след всеки ред
}
```

### 🔹 Модификация на елементи в двумерен масив:
Можете да промените стойностите в двумерен масив по същия начин, както при едномерните масиви.

```cpp
matrix[1][1] = 10; // Променя елемента на ред 1 и колона 1 (5 -> 10)
```

### 🔹 Размер на двумерен масив:
Можете да получите общия брой елементи в двумерен масив, като използвате sizeof, но трябва да разделите общия размер на масива на размера на един ред и след това на един елемент.

```cpp
int numRows = sizeof(matrix) / sizeof(matrix[0]); // Брой редове
int numCols = sizeof(matrix[0]) / sizeof(matrix[0][0]); // Брой колони
cout << "Размер на масива: " << numRows << "x" << numCols << endl;
```

### 🔹 Операции с двумерен масив:
- **Обхождане на двумерен масив:** Използват се вложени цикли, за да се обходят всички елементи.
- **Търсене на стойност:** Можете да използвате вложени цикли за търсене на конкретна стойност в масива.

```cpp
int searchValue = 6;
bool found = false;

for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        if (matrix[i][j] == searchValue) {
            found = true;
            cout << "Стойността " << searchValue << " е намерена на позиция: (" << i << ", " << j << ")" << endl;
            break;
        }
    }
    if (found) break;
}

if (!found) {
    cout << "Стойността " << searchValue << " не е намерена." << endl;
}
```


## 5. 🔁 Функции (Functions)
Функциите са **блокове от код**, които могат да се извикват многократно. Те могат да приемат аргументи и да връщат резултати.

### 🟢 Плюсове:
- Разделят кода на по-малки, управляеми части.
- Подобряват четимостта на кода, ако са използвани правилно.

### 🔴 Минуси:
- Могат да бъдат по-неефективни от инлайн код поради извикване на функцията.

```cpp
int add(int a, int b) {
  return a + b;
}

int result = add(3, 4); // result = 7
```


## 6. 🗂 Стекове (Stacks)
Стекът е **LIFO (Last In, First Out)** структура от данни, която позволява добавяне и премахване на елементи само от върха.

### 🟢 Плюсове:
- Полезен за задачи като обратен обход или рекурсия.

### 🔴 Минуси:
- Достъп до елементи само от върха.

### 🔹 Инициализация на стек:
В C++ стековете могат да се използват чрез библиотеката `<stack>`.

```cpp
#include <stack>

std::stack<int> s;
s.push(1); // Добавя 1 в стека
s.push(2); // Добавя 2 в стека
s.pop();   // Премахва последния елемент (2)
```

### 🔹 Проверка дали стекът е празен:
Можете да използвате функцията `empty()` за да проверите дали стекът съдържа елементи.

```cpp
if (s.empty()) {
    cout << "Стекът е празен!" << endl;
} else {
    cout << "Стекът съдържа елементи." << endl;
}
```

### 🔹 Достъп до най-горния елемент:
За да достъпите последно добавения елемент (върха на стека), използвайте функцията `top()`.

```cpp
int topElement = s.top();  // Връща върховия елемент (1 в този случай)
cout << "Върховият елемент е: " << topElement << endl;
```

### 🔹 Размер на стека:
Можете да получите броя на елементите в стека с помощта на `size()`.

```cpp
cout << "Размерът на стека е: " << s.size() << endl;
```

### 🔹 Извеждане на всички елементи от стека:
Тъй като стекът следва принципа **LIFO**, елементите трябва да се извеждат, като последователно се премахват от върха на стека.

```cpp
#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    // Извеждане на елементите, докато стекът не се изпразни
    while (!s.empty()) {
        cout << "Върхов елемент: " << s.top() << endl;
        s.pop(); // Премахва върховия елемент
    }

    return 0;
}
```

## 7.📬 Опашки (Queues)
Опашката е **FIFO (First In, First Out)** структура, която позволява добавяне на елементи от единия край и премахване от другия.

### 🟢 Плюсове:
- Полезна за моделиране на поредни процеси, като задачи или заявки.

### 🔴 Минуси:
- Ограничен достъп – можеш да премахваш само от началото и да добавяш само в края.

### 🔹 Инициализация на опашка:
В C++ опашките могат да се използват чрез библиотеката `<queue>`.

```cpp
#include <queue>

std::queue<int> q;
q.push(1); // Добавя 1 в опашката
q.push(2); // Добавя 2 в опашката
q.pop();   // Премахва първия елемент (1)
```

### 🔹 Проверка дали опашката е празна:

Можете да използвате функцията `empty()` за да проверите дали опашката съдържа елементи.

```cpp
if (q.empty()) {
    cout << "Опашката е празна!" << endl;
} else {
    cout << "Опашката съдържа елементи." << endl;
}
```

### 🔹 Достъп до първия и последния елемент:

Функцията `front()` се използва за достъп до първия елемент, а `back()` за достъп до последния елемент в опашката.

```cpp
int firstElement = q.front();  // Връща първия елемент (1)
int lastElement = q.back();    // Връща последния елемент (2)

cout << "Първи елемент: " << firstElement << endl;
cout << "Последен елемент: " << lastElement << endl;
```

### 🔹 Размер на опашката:

Можете да получите броя на елементите в опашката с помощта на `size()`.

```cpp
cout << "Размерът на опашката е: " << q.size() << endl;
```

### 🔹 Извеждане на всички елементи от опашката:

За да извеждате елементите на опашката, трябва да ги премахвате последователно с `pop()`, докато опашката не се изпразни.

```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);

    // Извеждане на елементите, докато опашката не се изпразни
    while (!q.empty()) {
        cout << "Първи елемент: " << q.front() << endl;
        q.pop(); // Премахва първия елемент
    }

    return 0;
```

### 🔹 Пример за работа с опашка:

Ето един обобщен пример, който показва добавяне, извеждане, премахване и проверка на опашка:

```cpp
#include <iostream>
#include <queue>
using namespace std;

int main() {
    // Създаване на опашка
    queue<int> q;

    // Добавяне на елементи
    q.push(10);
    q.push(20);
    q.push(30);

    // Достъп до първия и последния елемент
    cout << "Първи елемент: " << q.front() << endl; // 10
    cout << "Последен елемент: " << q.back() << endl; // 30

    // Премахване на елементи
    q.pop(); // Премахва 10
    cout << "Нов първи елемент: " << q.front() << endl; // 20

    // Проверка дали опашката е празна
    if (!q.empty()) {
        cout << "Опашката не е празна." << endl;
    } else {
        cout << "Опашката е празна." << endl;
    }

    // Размер на опашката
    cout << "Размерът на опашката е: " << q.size() << endl; // 2

    // Извеждане на всички елементи
    cout << "Извеждане на елементите от опашката:" << endl;
    while (!q.empty()) {
        cout << q.front() << " "; // Първи елемент в опашката
        q.pop(); // Премахва елемента
    }
    cout << endl;

    return 0;
}
```


## 8. 🛡 Сетове (Sets)
Сетът е **контейнер**, който съхранява **уникални елементи**, като не допуска дублиране. Това го прави подходящ за задачи, където уникалността на елементите е важна, като съхраняване на множества от данни без повторения.

### 🟢 Плюсове:
- **Гарантира уникалност** – не позволява дублиране на елементи.
- **Бързо търсене** – осигурява ефективно търсене, добавяне и премахване на елементи.

### 🔴 Минуси:
- Може да бъде по-бавен при **добавяне на много елементи**, тъй като трябва да проверява дали елементът вече съществува.
- Не поддържа индексиран достъп до елементите.

### 🔹 Инициализация на сет:
Сетовете могат да се използват в C++ чрез библиотеката `<set>`. Те автоматично подреждат елементите в нарастващ ред.

```cpp
#include <set>

std::set<int> mySet;
mySet.insert(1);
mySet.insert(2);
mySet.insert(1); // 1 вече съществува, така че няма да бъде добавен отново
```

### 🔹 Проверка дали даден елемент съществува в сета:

Можете да използвате функцията `find()` за да проверите дали даден елемент съществува в сета.

```cpp
if (mySet.find(2) != mySet.end()) {
    cout << "Елементът 2 съществува в сета." << endl;
} else {
    cout << "Елементът 2 не е намерен." << endl;
}
```

### 🔹 Проверка на размера на сета:

Функцията `size()` връща броя на уникалните елементи в сета.

```cpp
cout << "Размерът на сета е: " << mySet.size() << endl;
```

### 🔹 Премахване на елемент от сет:

За да премахнете елемент от сета, използвайте функцията `erase()`.

```cpp
mySet.erase(2); // Премахва елемента 2 от сета
```

### 🔹 Извеждане на всички елементи в сета:

Можете да използвате итератори, за да обхождате елементите на сета и да ги изведете.

```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> mySet = {3, 1, 4, 1, 5};

    // Извеждане на елементите
    for (auto it = mySet.begin(); it != mySet.end(); ++it) {
        cout << *it << " ";  // Елементите ще бъдат подредени
    }
    cout << endl;

    return 0;
}
```

### 🔹 Премахване на всички елементи от сет:

Функцията `clear()` изтрива всички елементи от сета.

```cpp
mySet.clear(); // Изчиства всички елементи от сета
```

### 🔹 Пример за работа със сетове:

Ето един обобщен пример, който показва добавяне, премахване, проверка и извеждане на елементи от сет:

```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    // Създаване на сет
    set<int> mySet;

    // Добавяне на елементи
    mySet.insert(10);
    mySet.insert(20);
    mySet.insert(30);
    mySet.insert(10); // Дубликатът няма да бъде добавен

    // Проверка дали даден елемент съществува
    if (mySet.find(20) != mySet.end()) {
        cout << "Елементът 20 съществува в сета." << endl;
    } else {
        cout << "Елементът 20 не е намерен." << endl;
    }

    // Премахване на елемент
    mySet.erase(20); // Премахва елемента 20

    // Проверка на размера на сета
    cout << "Размерът на сета е: " << mySet.size() << endl; // 2

    // Извеждане на елементите
    cout << "Елементи в сета: ";
    for (auto it = mySet.begin(); it != mySet.end(); ++it) {
        cout << *it << " "; // 10 30 (подредени)
    }
    cout << endl;

    return 0;
}
```


## 9. 📈 Вектори (Vectors)
Векторите са **динамични масиви** в C++, които могат автоматично да променят своя размер при добавяне или премахване на елементи. Те предоставят лесен и ефективен начин за работа с данни, чийто брой не е предварително известен.

### 🟢 Плюсове:
- **Гъвкав размер** – векторите автоматично се разширяват, когато се добавят нови елементи.
- **Бърз достъп по индекс** – достъпът до елементите по индекс е бърз и директен, както при обикновените масиви.
- **Богата функционалност** – векторите предоставят много удобни функции за работа с елементите.

### 🔴 Минуси:
- При добавяне на нови елементи **в средата или началото** може да има нужда от преместване на елементите, което може да забави изпълнението.
- Може да се наложи **преоразмеряване**, което води до копиране на елементите в нова памет, което отнема време.

### 🔹 Инициализация на вектор:

```cpp
#include <vector>

std::vector<int> v = {1, 2, 3};
v.push_back(4); // Добавя елемент в края
```

### 🔹 Добавяне на елементи:

Функцията push_back() добавя нов елемент в края на вектора.

```cpp
v.push_back(5); // Добавя 5 в края на вектора
```

### 🔹 Достъп до елемент по индекс:

Можете да получите достъп до елементи във вектора с помощта на индекс.

```cpp
int element = v[2]; // Връща елемента на индекс 2 (третият елемент)
```

### 🔹 Премахване на елементи:

Функцията `pop_back()` премахва последния елемент от вектора.

```cpp

v.pop_back(); // Премахва последния елемент
```

### 🔹 Проверка на размера:

Функцията `size()` връща текущия брой елементи във вектора.

```cpp
std::cout << "Размерът на вектора е: " << v.size() << std::endl;
```

### 🔹 Извеждане на всички елементи във вектор:

Можете да обхождате и извеждате всички елементи с помощта на цикъл.

```cpp
for (int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
}
std::cout << std::endl;
```

### 🔹 Итератори:

Можете да използвате итератори за обхождане на елементите на вектора.

```cpp
for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << " ";
}
std::cout << std::endl
```

### 🔹 Премахване на елементи по индекс:

Можете да използвате функцията `erase()`, за да премахнете елемент на даден индекс.

```cpp
v.erase(v.begin() + 1); // Премахва елемента на индекс 1
```

### 🔹 Изчистване на всички елементи:

Функцията `clear()` премахва всички елементи във вектора.

```cpp
v.clear(); // Изчиства всички елементи
```

### 🔹 Пример за работа с вектор:

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Създаване на вектор
    vector<int> v = {1, 2, 3};

    // Добавяне на елемент
    v.push_back(4);

    // Премахване на елемент
    v.pop_back();

    // Извеждане на елементите
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;

    // Проверка на размера
    cout << "Размерът на вектора е: " << v.size() << endl;

    return 0;
}
```

## 10.⏳ Опашки с приоритет (Priority Queues)
Опашката с приоритет подрежда елементите **според техния приоритет** – елементите с най-висок приоритет се премахват първи.

### 🟢 Плюсове:
- Полезни за задачи като планиране, където някои задачи имат приоритет над други.

### 🔴 Минуси:
- По-бавни от обикновените опашки поради подреждането.

```cpp
#include <queue>

std::priority_queue<int> pq;
pq.push(10);
pq.push(20);
pq.pop(); // Премахва най-големия елемент (20)
```


## 11.🌀 Рекурсия (Recursion)
Рекурсията е метод, при който функцията извиква сама себе си. Полезна е за задачи, които могат да бъдат разделени на по-малки подобни подзадачи.

### 🟢 Плюсове:
- Лесен начин за изразяване на проблеми като обхождане на дървета или търсене.

### 🔴 Минуси:
- Може да доведе до изчерпване на стека (stack overflow), ако не се управлява правилно.

```cpp
int factorial(int n) {
  if (n == 0) return 1;
  return n * factorial(n - 1);
}

int result = factorial(5); // result = 120
```
