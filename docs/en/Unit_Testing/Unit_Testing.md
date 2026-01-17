# Unit Testing in C++

## 1. Introduction

Testing small parts of code in isolation.
Frameworks: **Google Test (GTest)**, Catch2.

---

## 2. Structure

**AAA:** Arrange, Act, Assert.

```cpp
TEST(Math, Add) {
    EXPECT_EQ(add(2, 2), 4);
}
```

---

## 3. Summary

Ensures code quality and prevents regressions.
