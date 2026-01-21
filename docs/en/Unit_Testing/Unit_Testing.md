# Unit Testing in C++ - Complete Technical Guide

## 1. Introduction: Software Quality as a Discipline

Unit Testing is not just about checking if the code works. It is an engineering practice for ensuring the correctness of the smallest isolated parts of software (functions, methods, classes). In professional C++ development, code without automated tests is considered "incomplete" or even "technical debt".

Tests are your "safety net". They give you the confidence to refactor and optimize code without fear of breaking something that worked 5 years ago.

---

## 2. Anatomy of a Unit Test (The AAA Pattern)

Every professional test should follow the three-stage structure:
1.  **Arrange:** Initialize objects, set input data, and prepare the environment.
2.  **Act:** Invoke the functionality we are testing.
3.  **Assert:** Compare the actual result with the expected one.

---

## 3. Tooling: Google Test (GTest)

Google Test is the industry standard for C++.

### 3.1. Assertion Macros
*   **ASSERT_EQ(val1, val2):** Fatal error. If the check fails, the test stops immediately.
*   **EXPECT_EQ(val1, val2):** Non-fatal error. The test continues so we can see other potential issues.
*   **EXPECT_THROW(code, ExceptionType):** Checks if the code throws the correct exception.

### 3.2. Test Fixtures
If many tests use the same initial configuration (e.g., opening a connection to a test database), we use a `Test Fixture` (inheriting from `testing::Test`).

```cpp
class DatabaseTest : public testing::Test {
protected:
    void SetUp() override { db.connect(); } // Before each test
    void TearDown() override { db.disconnect(); } // After each test
    Database db;
};

TEST_F(DatabaseTest, InsertWorks) { // TEST_F instead of TEST
    db.insert("user", "data");
    EXPECT_TRUE(db.hasUser("user"));
}
```

### 3.3. Parameterized Tests
Allow you to execute the same test logic with thousands of different inputs.
```cpp
class MathTest : public testing::TestWithParam<int> {};

TEST_P(MathTest, IsEven) {
    int n = GetParam();
    EXPECT_EQ(n % 2, 0);
}

INSTANTIATE_TEST_SUITE_P(EvenNumbers, MathTest, testing::Values(2, 4, 6, 8, 100));
```

---

## 4. Isolation and Substitution: Google Mock (GMock)

In real systems, classes depend on external resources (network, file system). A unit test must be **isolated**.
**Google Mock** allows us to create "fake" objects that mimic the behavior of real ones.

```cpp
class MockBank : public IBank {
public:
    MOCK_METHOD(bool, withdraw, (int amount), (override));
};

TEST(ATM, WithdrawFailsOnNoMoney) {
    MockBank bank;
    // Expectations: "withdraw" will be called once with argument 100 and must return false.
    EXPECT_CALL(bank, withdraw(100)).Times(1).WillOnce(testing::Return(false));
    
    ATM atm(&bank);
    bool result = atm.requestMoney(100);
    EXPECT_FALSE(result);
}
```

---

## 5. Methodology: TDD (Test-Driven Development)

TDD changes the order of work:
1.  **Red:** Write a test that fails (because the function doesn't exist yet).
2.  **Green:** Write the minimal code just to make the test pass.
3.  **Refactor:** Clean up and optimize the code while tests continue to be green.

---

## 6. Integration with CMake

To make testing part of the build process, add it to `CMakeLists.txt`:

```cmake
enable_testing()
add_executable(my_tests tests.cpp)
target_link_libraries(my_tests GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(my_tests)
```
Now you can run all tests with the `ctest` command.

---

## 7. Professional Summary

1.  **Code Coverage:** Do not blindly aim for 100% coverage. Test critical business logic and edge cases.
2.  **No logic in tests:** Test code should be dumb (linear). If you have `if` or `for` in a test, you probably need a test for the test.
3.  **Speed:** Unit tests must be instant. Slow tests are run rarely and lose their value.

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*