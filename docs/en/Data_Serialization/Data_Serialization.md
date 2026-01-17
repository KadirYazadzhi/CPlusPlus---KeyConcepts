# Data Serialization in C++

## 1. Introduction

Transforming an object into a byte sequence for storage or network transmission.

---

## 2. Formats

*   **Binary:** Fastest, smallest, but complex (endianness, padding).
*   **JSON:** Human-readable. Popular library: **nlohmann/json**.
*   **Protobuf:** High performance, schema-based.

---

## 3. Summary

Essential for saving state and distributed systems. C++ has no native reflection, so manual work or libraries are needed.
