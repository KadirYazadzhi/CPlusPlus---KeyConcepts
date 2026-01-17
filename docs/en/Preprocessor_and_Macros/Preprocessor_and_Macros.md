# Preprocessor and Macros in C++

## 1. Introduction

Runs before compilation. Commands start with `#`.

---

## 2. Macros

```cpp
#define PI 3.14
#define MAX(a,b) ((a)>(b)?(a):(b))
```

Avoid macros! Use `const` and `templates`.

---

## 3. Include Guards

```cpp
#ifndef HEADER_H
#define HEADER_H
// ...
#endif
```

Or `#pragma once`.

---

## 4. Summary

Use for build config (`#ifdef`), not for logic.
