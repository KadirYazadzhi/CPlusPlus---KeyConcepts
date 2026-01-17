# Тестване на Код (Unit Testing) в C++

## 1. Въведение

Unit Testing (Модулно тестване) е процесът на тестване на най-малките изолирани части от кода (функции, класове) поотделно.

Целта е да се гарантира, че всеки компонент работи коректно, преди да бъде сглобен в по-голяма система.

### Защо да пишем тестове?
1.  **Качество:** Откривате бъгове рано.
2.  **Рефакториране:** Можете да променяте кода спокойно, знаейки, че тестовете ще хванат, ако счупите нещо.
3.  **Документация:** Тестовете показват как *трябва* да се използва кодът.

---

## 2. Фреймворци за тестване

В C++ няма вграден механизъм за тестване. Най-популярните библиотеки са:
*   **Google Test (GTest):** Индустриален стандарт. Мощен и богат на функции.
*   **Catch2:** Модерен, header-only, използва лесен синтаксис.
*   **Doctest:** Изключително бърз и лек.

Тук ще разгледаме примери в стил **Google Test**, тъй като е най-разпространен.

---

## 3. Структура на един тест

Един тест обикновено следва шаблона **AAA**:
1.  **Arrange:** Подготовка на данните и обектите.
2.  **Act:** Извикване на функцията, която тестваме.
3.  **Assert:** Проверка дали резултатът е очакваният.

```cpp
#include <gtest/gtest.h>

// Функция за тестване
int add(int a, int b) {
    return a + b;
}

// Тест случай (Test Case)
TEST(MathTests, AdditionWorks) {
    // Arrange
    int x = 5;
    int y = 10;

    // Act
    int result = add(x, y);

    // Assert
    EXPECT_EQ(result, 15);
}
```

---

## 4. Assertions (Твърдения)

GTest предоставя макроси за проверки.

*   `ASSERT_EQ(val1, val2)`: Проверява за равенство. Ако не успее, **прекратява** теста веднага.
*   `EXPECT_EQ(val1, val2)`: Проверява за равенство. Ако не успее, записва грешка, но **продължава** теста. (Препоръчително)
*   `EXPECT_TRUE(condition)` / `EXPECT_FALSE(condition)`
*   `EXPECT_GT(a, b)` (Greater Than), `EXPECT_LT` (Less Than)

```cpp
TEST(VectorTests, SizeCheck) {
    std::vector<int> v;
    EXPECT_TRUE(v.empty());
    
    v.push_back(1);
    EXPECT_EQ(v.size(), 1);
}
```

---

## 5. Test Fixtures (Подготовка на среда)

Ако няколко теста използват едни и същи данни (напр. отваряне на база данни или създаване на сложен обект), използваме **Fixtures**.

Това е клас, наследяващ `::testing::Test`, който има методи `SetUp()` и `TearDown()`.

```cpp
class DatabaseTest : public ::testing::Test {
protected:
    Database* db;

    void SetUp() override {
        // Вика се ПРЕДИ всеки тест
        db = new Database();
        db->connect();
    }

    void TearDown() override {
        // Вика се СЛЕД всеки тест
        db->disconnect();
        delete db;
    }
};

// Използваме TEST_F вместо TEST
TEST_F(DatabaseTest, InsertUser) {
    // db е достъпен тук и е инициализиран
    bool success = db->insert("User1");
    EXPECT_TRUE(success);
}
```

---

## 6. Тестване на Изключения

Можем да проверим дали кодът хвърля (или не хвърля) изключение.

```cpp
void riskyFunction(int x) {
    if (x < 0) throw std::invalid_argument("Negative!");
}

TEST(ExceptionTest, ThrowsOnNegative) {
    EXPECT_THROW(riskyFunction(-1), std::invalid_argument);
}

TEST(ExceptionTest, NoThrowOnPositive) {
    EXPECT_NO_THROW(riskyFunction(10));
}
```

---

## 7. TDD (Test Driven Development)

Това е методология, при която:
1.  Пишете теста **преди** да напишете кода.
2.  Пускате теста -> той се проваля (Red).
3.  Пишете минималния код, за да мине теста (Green).
4.  Подобрявате кода (Refactor).

---

## 8. Обобщение

*   Тестовете са вашата "застраховка" срещу регресии (счупване на работещ код).
*   Добрият тест е бърз, изолиран и независим от другите тестове.
*   Инвестицията във време за писане на тестове се изплаща многократно при поддръжката.
