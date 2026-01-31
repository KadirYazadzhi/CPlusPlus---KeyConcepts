# JNI и Връзка с Java (Java Native Interface) - Пълно техническо ръководство

## 1. Въведение: Мостът между два свята

Java е език, работещ във Виртуална Машина (JVM), докато C++ работи директно върху хардуера. JNI (Java Native Interface) е стандартният механизъм, който позволява на Java код да вика C++ функции и обратно.

**Защо ни трябва?**
1.  **Legacy Code:** Имате 20-годишна C++ библиотека, която трябва да ползвате в Android приложение.
2.  **Performance:** Критични математически изчисления или обработка на изображения, където Java е твърде бавна.
3.  **Hardware Access:** Достъп до драйвери, USB устройства или специфични OS API-та, които Java няма.

---

## 2. Анатомия на JNI

JNI не е просто библиотека, а сложен протокол за маршалинг на данни.

### 2.1. От Java към C++ (`native` методи)
В Java декларираме метода като `native`:
```java
package com.example;

public class MathLib {
    // Зареждане на библиотеката (libnative.so или native.dll)
    static { System.loadLibrary("native"); }

    // Декларация без имплементация
    public native int add(int a, int b);
}
```

### 2.2. От C++ към Java (Header Generation)
Използваме `javac -h . MathLib.java`, за да генерираме C++ хедър:
```cpp
/* com_example_MathLib.h */
#include <jni.h>

JNIEXPORT jint JNICALL Java_com_example_MathLib_add
  (JNIEnv *env, jobject thisObj, jint a, jint b) {
    return a + b;
}
```
*   **`JNIEnv*`**: Най-важният указател. Той е интерфейсът към JVM. Чрез него създавате обекти, хвърляте изключения и достъпвате масиви.
*   **`jobject`**: Референция към `this` (Java обекта).

---

## 3. Обмен на Данни и Памет

Това е най-скъпата част. Данните трябва да преминат границата между Managed Heap (Java) и Native Heap (C++).

### 3.1. Примитивни типове
`int` -> `jint`, `boolean` -> `jboolean`. Те се копират директно и са бързи.

### 3.2. Стрингове (`jstring`)
Java стринговете са UTF-16 и не са null-terminated. C++ стринговете са обикновено UTF-8/ASCII.
Трябва да ги конвертирате:
```cpp
JNIEXPORT void JNICALL Java_Print(JNIEnv* env, jobject, jstring msg) {
    // Взимане на указател към UTF-8 буфер (алокация!)
    const char* str = env->GetStringUTFChars(msg, nullptr);
    
    printf("%s", str);
    
    // ЗАДЪЛЖИТЕЛНО освобождаване!
    env->ReleaseStringUTFChars(msg, str);
}
```
⚠️ **Critical Trap:** Ако забравите `ReleaseStringUTFChars`, ще имате Memory Leak в JVM хийпа.

### 3.3. Масиви
Не можете да достъпите Java масив директно като `int*`.
```cpp
JNIEXPORT jint JNICALL Java_Sum(JNIEnv* env, jobject, jintArray arr) {
    jint* elements = env->GetIntArrayElements(arr, nullptr);
    // ... сумиране ...
    // Освобождаване и копиране обратно на промените (ако има)
    env->ReleaseIntArrayElements(arr, elements, 0); 
}
```
**Оптимизация:** За големи данни използвайте `GetPrimitiveArrayCritical` (може да спре Garbage Collector-а временно за бърз достъп).

---

## 4. Изключения (Exceptions)

C++ изключенията (`std::exception`) **НЕ** се прехващат от Java. Ако C++ хвърли изключение и то стигне до JVM границата, процесът **крашва** (SIGABRT).

Трябва ръчно да хванете всичко в C++ и да го "преведете" на JNI:
```cpp
try {
    do_heavy_work();
} catch (const std::exception& e) {
    // Намираме Java Exception класа
    jclass exClass = env->FindClass("java/lang/RuntimeException");
    // Хвърляме го в JVM
    env->ThrowNew(exClass, e.what());
}
```

---

## 5. Управление на референции (Local vs Global)

Всички обекти, подадени на C++ (като `jobject`), са **Local References**. Те са валидни само докато трае текущата функция.
Ако искате да запазите Java обект за по-късно (напр. в глобална C++ променлива), трябва да го направите глобален:

```cpp
jobject globalCallback;

// В инициализацията
globalCallback = env->NewGlobalRef(localCallback);

// В деструктора (много важно!)
env->DeleteGlobalRef(globalCallback);
```
Липсата на `DeleteGlobalRef` е най-честата причина за Memory Leak в Android NDK приложения.

---

## 6. Performance Tips

1.  **RegisterNatives:** Вместо да разчитате на дълги имена като `Java_com_package_Class_method`, регистрирайте функциите динамично в `JNI_OnLoad`. Това е по-бързо и по-чисто.
2.  **Cross-boundary calls:** Всяко минаване Java <-> C++ е скъпо (overhead). Не правете JNI за функция, която събира две числа. Правете го за функции, които работят поне няколко милисекунди ("Chunky, not Chatty").
3.  **Direct ByteBuffers:** За видео/аудио използвайте `java.nio.ByteBuffer.allocateDirect()`. Това дава памет, достъпна и от Java, и от C++ без никакво копиране.

---

## 7. Професионално обобщение

*   **Избягвайте JNI**, ако е възможно. Сложността на дебъгване е 10x по-висока.
*   **Безопасност:** JNI кодът може да счупи цялата JVM (Segmentation Fault). Java безопасността не важи тук.
*   **Инструменти:** Използвайте SWIG или модерните Java решения като **Project Panama (Foreign Function & Memory API)**, които целят да заменят JNI с нещо по-модерно и безопасно.

---
*(Този документ е част от "The Ultimate C++ Mastery Framework".)*
