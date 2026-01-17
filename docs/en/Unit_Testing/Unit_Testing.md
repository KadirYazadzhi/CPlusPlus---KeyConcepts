# Unit Testing in C++ - The Ultimate Guide

## 1. Introduction: Why Test?
Unit Testing is the process of verifying the smallest components of code (functions, classes) in isolation. Professional C++ code is unthinkable without automated tests, which ensure that today's changes do not break yesterday's working functionality.

---

## 2. Google Test (GTest) - The Industrial Standard
Although many libraries exist (Catch2, doctest), Google Test is the most widely used.

### 2.1. Basic Syntax
Tests are written using macros:
*   `EXPECT_EQ(val1, val2)`: Continues even if the check fails.
*   `ASSERT_EQ(val1, val2)`: Stops the test immediately if the check fails.

```cpp
#include <gtest/gtest.h>

int sum(int a, int b) { return a + b; }

TEST(MathTests, AdditionWorks) {
    EXPECT_EQ(sum(2, 2), 4);
    EXPECT_NE(sum(2, 2), 5);
}
```

---

## 3. Test Fixtures
When you need the same setup (e.g., a database or a complex object) for multiple tests, use classes inheriting from `::testing::Test`.

---

## 4. TDD (Test-Driven Development)
A philosophy where you write the test first, it fails (because the code is not there), then you write the code to pass the test, and finally, you refactor.

---

## 5. Mocking
The **googlemock** library allows you to simulate the behavior of complex dependencies (e.g., network services) to test your class's logic in complete isolation.

---

## 6. Benefits
1.  **Bug Reduction:** Bugs are caught at the time of writing.
2.  **Documentation:** Tests serve as examples of how to use the code.
3.  **Design:** Code that is difficult to test is usually poorly designed.

---
*(This document is part of the "C++ Key Concepts" course)*