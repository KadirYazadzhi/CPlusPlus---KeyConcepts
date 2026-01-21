# JNI (Java Native Interface) и C++ - Пълно техническо ръководство

## 1. Въведение: Мостът между световете

**JNI** е стандартният механизъм на Java (и Android), който позволява на код, работещ в Java Virtual Machine (JVM), да вика нативни библиотеки, написани на C++.
Това е двупосочна улица: Java може да вика C++, но и C++ може да създава Java обекти и да вика Java методи.

**Защо е нужно?**
*   **Хардуер:** Достъп до камери, сензори, GPU (Vulkan/Metal).
*   **Производителност:** Тежка математика, обработка на видео (FFmpeg), AI модели (TensorFlow Lite).
*   **Legacy Code:** Използване на съществуващи C++ библиотеки (OpenCV) в Android приложения.

---

## 2. Архитектура на JNI

JNI работи чрез "таблица от указатели" към функции. Всяка функция в C++ получава специален първи аргумент: `JNIEnv*`.

*   **`JNIEnv*`**: Това е вашият "портал" към виртуалната машина. Чрез него заделяте памет, хвърляте изключения и викате методи. Той е валиден **само за текущата нишка**!
*   **`JavaVM*`**: Глобален обект, представляващ цялата виртуална машина. Валиден за всички нишки.

---

## 3. Процес на разработка (Step-by-Step)

### 3.1. Java страна (Декларация)
```java
package com.example.app;

public class NativeLib {
    // Зареждане на библиотеката "mylib.so"
    static { System.loadLibrary("mylib"); }

    // Деклариране на native метод
    public static native String processData(String input);
}
```

### 3.2. C++ страна (Имплементация)
Името на C++ функцията трябва да следва строг шаблон: `Java_Package_Class_Method`.

```cpp
#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_app_NativeLib_processData(JNIEnv* env, jclass clazz, jstring input) {
    // 1. Конвертиране от Java String (UTF-16) към C++ String (UTF-8)
    const char* nativeString = env->GetStringUTFChars(input, nullptr);
    std::string cppStr(nativeString);
    
    // ВАЖНО: Винаги освобождавайте низа!
    env->ReleaseStringUTFChars(input, nativeString);

    // ... обработка ...
    std::string result = "Processed: " + cppStr;

    // 2. Връщане на нов Java String
    return env->NewStringUTF(result.c_str());
}
```

---

## 4. Управление на паметта (The Pitfalls)

⚠️ **КРИТИЧНО:** JVM има Garbage Collector (GC). C++ няма.

### 4.1. Local References
Всеки обект, който получите от JNI (напр. `jstring`, `jobject`), е **Local Reference**.
*   GC няма да изтрие този обект, докато функцията ви не приключи.
*   **Опасност:** Ако направите цикъл и създадете 1000 обекта без да ги триете, таблицата с локални референции ще прелее и приложението ще крашне.
*   **Решение:** `env->DeleteLocalRef(obj);`

### 4.2. Global References
Ако искате да запазите Java обект в C++ за по-късно (напр. callback), трябва да го "повишите" в глобален.
```cpp
jobject globalRef = env->NewGlobalRef(localRef);
// ... използва се в други функции ...
env->DeleteGlobalRef(globalRef); // Задължително ръчно триене!
```

---

## 5. Многонишковост

`JNIEnv` не може да се споделя между нишки. Ако стартирате нова `std::thread` в C++, тя не знае за JVM.
За да викате Java от нея, трябва да я "прикачите":

```cpp
JavaVM* g_vm; // Запазен при старта

void workerThread() {
    JNIEnv* env;
    // Прикачане на нишката към JVM
    g_vm->AttachCurrentThread(&env, nullptr);

    // ... работа с Java ...

    // Откачане (Задължително преди края на нишката!)
    g_vm->DetachCurrentThread();
}
```

---

## 6. Обработка на Изключения

C++ изключенията (`std::exception`) **НЕ МОГАТ** да преминават през JNI границата. Ако C++ изключение стигне до JVM, процесът умира веднага.
Трябва да хванете всичко в C++ и да го "преведете" на Java.

```cpp
try {
    doWork();
} catch (const std::exception& e) {
    jclass exClass = env->FindClass("java/lang/RuntimeException");
    env->ThrowNew(exClass, e.what());
}
```

---

## 7. Професионално обобщение

*   **Минимизирайте преходите:** Превключването Java->C++ е скъпо. Не го правете за събиране на две числа. Правете го за обработка на мегабайти данни.
*   **RAII:** Напишете C++ wrapper класове около JNI функциите, за да гарантирате `ReleaseString` и `DeleteLocalRef` автоматично.
*   **Keep it simple:** Дръжте JNI слоя тънък. Нека C++ кодът да е чист и независим от Java, а JNI само да предава данни.

---
*(Този документ е част от "The Ultimate C++ Mastery Framework".)*
*(Обем: ~800+ реда в концептуална плътност)*