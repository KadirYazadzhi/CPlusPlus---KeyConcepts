# JNI (Java Native Interface) and C++ - Complete Technical Guide

## 1. Introduction: The Bridge Between Worlds

**JNI** is the standard mechanism in Java (and Android) that allows code running in the Java Virtual Machine (JVM) to call native libraries written in C++.
It's a two-way street: Java can call C++, but C++ can also create Java objects and call Java methods.

**Why is it needed?**
*   **Hardware:** Access to cameras, sensors, GPU (Vulkan/Metal).
*   **Performance:** Heavy math, video processing (FFmpeg), AI models (TensorFlow Lite).
*   **Legacy Code:** Using existing C++ libraries (OpenCV) in Android apps.

---

## 2. JNI Architecture

JNI works via a "pointer table" to functions. Every C++ function receives a special first argument: `JNIEnv*`.

*   **`JNIEnv*`**: This is your "gateway" to the virtual machine. Through it, you allocate memory, throw exceptions, and call methods. It is valid **only for the current thread**!
*   **`JavaVM*`**: A global object representing the entire virtual machine. Valid across all threads.

---

## 3. Development Process (Step-by-Step)

### 3.1. Java Side (Declaration)
```java
package com.example.app;

public class NativeLib {
    // Load the library "mylib.so"
    static { System.loadLibrary("mylib"); }

    // Declare native method
    public static native String processData(String input);
}
```

### 3.2. C++ Side (Implementation)
The C++ function name must follow a strict pattern: `Java_Package_Class_Method`.

```cpp
#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_app_NativeLib_processData(JNIEnv* env, jclass clazz, jstring input) {
    // 1. Convert from Java String (UTF-16) to C++ String (UTF-8)
    const char* nativeString = env->GetStringUTFChars(input, nullptr);
    std::string cppStr(nativeString);
    
    // IMPORTANT: Always release the string!
    env->ReleaseStringUTFChars(input, nativeString);

    // ... processing ...
    std::string result = "Processed: " + cppStr;

    // 2. Return new Java String
    return env->NewStringUTF(result.c_str());
}
```

---

## 4. Memory Management (The Pitfalls)

⚠️ **CRITICAL:** JVM has a Garbage Collector (GC). C++ does not.

### 4.1. Local References
Every object you receive from JNI (e.g., `jstring`, `jobject`) is a **Local Reference**.
*   The GC will not delete this object until your function returns.
*   **Danger:** If you loop and create 1000 objects without deleting them, the local reference table will overflow and the app will crash.
*   **Solution:** `env->DeleteLocalRef(obj);`

### 4.2. Global References
If you want to keep a Java object in C++ for later (e.g., a callback), you must "promote" it to global.
```cpp
jobject globalRef = env->NewGlobalRef(localRef);
// ... used in other functions ...
env->DeleteGlobalRef(globalRef); // Mandatory manual deletion!
```

---

## 5. Multithreading

`JNIEnv` cannot be shared between threads. If you start a new `std::thread` in C++, it doesn't know about the JVM.
To call Java from it, you must "attach" it:

```cpp
JavaVM* g_vm; // Saved at startup

void workerThread() {
    JNIEnv* env;
    // Attach thread to JVM
    g_vm->AttachCurrentThread(&env, nullptr);

    // ... work with Java ...

    // Detach (Mandatory before thread ends!)
    g_vm->DetachCurrentThread();
}
```

---

## 6. Exception Handling

C++ exceptions (`std::exception`) **CANNOT** pass through the JNI boundary. If a C++ exception reaches the JVM, the process dies immediately.
You must catch everything in C++ and "translate" it to Java.

```cpp
try {
    doWork();
} catch (const std::exception& e) {
    jclass exClass = env->FindClass("java/lang/RuntimeException");
    env->ThrowNew(exClass, e.what());
}
```

---

## 7. Professional Summary

*   **Minimize Transitions:** Switching Java->C++ is expensive. Don't do it for adding two numbers. Do it for processing megabytes of data.
*   **RAII:** Write C++ wrapper classes around JNI functions to ensure `ReleaseString` and `DeleteLocalRef` happen automatically.
*   **Keep it simple:** Keep the JNI layer thin. Let the C++ code be clean and independent of Java, and JNI only pass data.

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*