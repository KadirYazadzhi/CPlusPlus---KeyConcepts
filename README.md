# C++ Key Concepts / Ключови Концепции в C++ 🚀

[![Language: English](https://img.shields.io/badge/Language-English-blue.svg)](./docs/en/README.md)
[![Language: Bulgarian](https://img.shields.io/badge/Език-Български-green.svg)](./docs/bg/README.md)
[![Deployment: GitHub Pages](https://img.shields.io/badge/Deployment-GitHub_Pages-orange.svg)](https://pages.github.com/)

Welcome to the **Ultimate C++ Reference Guide** – a comprehensive, bilingual educational resource covering 44 fundamental and advanced C++ topics. This repository is structured as a high-quality online book, providing deep dives into every aspect of modern software engineering with C++.

Добре дошли в **Пълния справочник по C++** – изчерпателен, двуезичен образователен ресурс, обхващащ 44 фундаментални и напреднали теми. Това хранилище е структурирано като висококачествена онлайн книга, предоставяща задълбочени обяснения за всеки аспект на модерното софтуерно инженерство.

---

## 🗺 Choose Your Language / Изберете език

### 🇺🇸 [English Version (Go to Docs)](./docs/en/README.md)
Detailed documentation, professional examples, and performance analysis in English.

### 🇧🇬 [Българска Версия (Към Документацията)](./docs/bg/README.md)
Пълна документация, практически примери и анализ на производителността на български език.

---

## 📂 Repository Structure / Структура на файловете

```text
.
├── docs/                   # Full documentation source
│   ├── bg/                 # Bulgarian version (44 topics)
│   │   ├── References/     # Detailed Topic Folders
│   │   ├── Pointers/
│   │   └── ...
│   ├── en/                 # English version (44 topics)
│   │   ├── References/
│   │   ├── Pointers/
│   │   └── ...
│   └── index.md            # Homepage for the Online Book
├── .github/workflows/      # Automated Deployment (GitHub Actions)
├── mkdocs.yml              # Configuration for the static site (Material Theme)
└── README.md               # You are here (Project Overview)
```

---

## 📚 What's Inside? / Какво се разглежда?

This guide covers 9 logical modules, taking you from a beginner to a senior-level engineer:
Това ръководство обхваща 9 логически модула, превеждайки ви от начинаещ до сениор инженер:

### 1. Fundamentals / Основи (1-17)
Basic syntax, memory basics, and core data structures (Arrays, Stacks, Queues, Maps, Recursion).
Базов синтаксис, основи на паметта и базови структури от данни.

### 2. OOP / Обектно-ориентирано програмиране (18-20)
Encapsulation, Inheritance, Polymorphism, and Operator Overloading.
Инкапсулация, Наследяване, Полиморфизъм и Предефиниране на оператори.

### 3. Memory & Modern C++ / Памет и модерен C++ (21-22)
Smart Pointers (RAII) and Move Semantics (R-value references).
Умни указатели (RAII) и Move семантика.

### 4. Advanced Features / Разширени възможности (23-26)
Templates, Exception Handling, Type Casting, and Lambda Expressions.
Шаблони, Изключения, Кастване и Ламбда изрази.

### 5. STL & Systems / Стандартна библиотека и Системи (27-29)
Algorithm library, File I/O, and Multithreading (Mutex, Async, Atomic).
Алгоритми на STL, Файлове и Многонишково програмиране.

### 6. Engineering / Инженерни практики (30-33)
Design Patterns, Unit Testing (GTest), Preprocessor, and Build Systems (CMake).
Шаблони за дизайн, Тестване на код, Препроцесор и CMake.

### 7. C++20 Innovations / C++20 Иновации (34-37)
Concepts, Modules, Ranges, and Coroutines.
Концепти, Модули, Ranges и Корутини.

### 8. Modern Tools / Модерни библиотеки (38-40)
Chrono, Filesystem, Optional/Variant/Any, Type Traits, and SFINAE.
Време, Файлова система, Метапрограмиране.

### 9. Low-Level / Ниско ниво и Архитектура (41-44)
Bit Manipulation, Cache Optimization, Serialization, and SOLID Principles.
Битови операции, Оптимизация на кеша, Сериализация и SOLID принципи.

---

## 🛠 How to Use / Как да използвате

### 🌐 View as an Online Book / Вижте като онлайн книга
The project is configured with **MkDocs Material**. To host it locally:
Проектът е конфигуриран с **MkDocs Material**. За локален преглед:

1.  **Install requirements / Инсталирайте:**
    ```bash
    pip install mkdocs-material
    ```
2.  **Run server / Стартирайте сървъра:**
    ```bash
    mkdocs serve
    ```
3.  Open / Отворете: `http://127.0.0.1:8000`

### 🤖 Automatic Hosting / Автоматичен хостинг
Every `git push` to `main` triggers a **GitHub Action** that builds and deploys the site to **GitHub Pages**. Ensure your repository settings allow **Read/Write** permissions for Actions.

Всеки `git push` към `main` задейства **GitHub Action**, който билдва и публикува сайта в **GitHub Pages**.

---

## 🤝 Contribution / Принос
Feel free to fork this repository and add more examples or translations!
Чувствайте се свободни да разклоните хранилището и да добавите нови примери или преводи!

*Created with ❤️ for the C++ Community.*