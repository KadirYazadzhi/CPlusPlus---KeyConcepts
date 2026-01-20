# Unordered Maps in C++ - Complete Technical Guide

## 1. Introduction: The Speed Revolution

`std::unordered_map` (introduced in C++11) changed the way C++ programmers work with large datasets. While the traditional `std::map` relies on ordering and logarithmic speed, `std::unordered_map` relies on **extreme speed** (constant time O(1)).
It is implemented via a **Hash Table**, making it the ideal choice for caching systems, dictionaries, database indexes, and any scenario where lookup is the most frequent operation.

---

## 2. How Does a Hash Table Work? (Under the Hood)

### 2.1. Hashing and Buckets
The magic of O(1) happens through math, not traversal.
1.  **Input:** Takes the key (e.g., username "Admin").
2.  **Hash Function:** Applies a `std::hash` function that converts the string into a large integer (e.g., `1489201849`).
3.  **Mapping:** This number is divided modulo the number of internal "buckets".
    *   `Bucket_Index = Hash_Value % Bucket_Count`
4.  **Storage:** The value is stored directly in that bucket.

### 2.2. Collisions
What happens if two different keys (e.g., "User1" and "User2") land in the same bucket?
C++ uses the **Separate Chaining** method:
*   Each "bucket" is actually a pointer to a linked list.
*   When a collision occurs, the new element is added to this list.
*   Upon search, the algorithm finds the bucket (instantly) and then linearly searches the short list inside.

---

## 3. Performance: O(1) vs O(N)

*   **Best/Average Case:** **O(1)**.
    *   This is achieved when the hash function is good and distributes elements evenly. Buckets are short (0 or 1 element).
*   **Worst Case:** **O(N)**.
    *   This happens if the hash function is poor and all 1 million elements land in **a single bucket**. Then the map turns into a slow `std::list`.

---

## 4. Memory Management: Load Factor and Rehashing

Unlike a vector, `unordered_map` has two growth parameters:
1.  **Max Load Factor:** The ratio `size / bucket_count`. Default is **1.0**. This means C++ allows on average 1 element per bucket.
2.  **Rehashing:** When you add an element and exceed the Load Factor:
    *   Allocates a new array with more buckets (usually double).
    *   **All** elements are rehashed and moved to the new buckets.
    *   This is an expensive **O(N)** operation.

**Pro Tip:**
```cpp
std::unordered_map<int, string> m;
m.reserve(1000000); // Allocates enough buckets in advance.
// This avoids multiple Rehashes while filling.
```

---

## 5. Key Requirements (Custom Types)

To use your own class as a key in `unordered_map`, you must teach C++ how to do two things:
1.  **Compare for equality** (`operator==`), to distinguish collisions.
2.  **Hash** (specialization of `std::hash`).

```cpp
struct Point { int x, y; };

// 1. Equality
bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

// 2. Hashing (Injecting into std namespace)
namespace std {
    template <>
    struct hash<Point> {
        size_t operator()(const Point& p) const {
            // Combining hashes (XOR)
            return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
        }
    };
}

std::unordered_map<Point, string> map; // Now works!
```

---

## 6. Security: Hash DoS Attacks

If you use `std::unordered_map` in a public web server and read JSON data into it, you are vulnerable.
A malicious hacker can generate thousands of keys that yield the same hash ("Hash Collision Attack"). This will turn your hash table into a list (O(N)), load the CPU to 100%, and crash the server (Denial of Service).
**Solution:** Use more complex, cryptographically secure hash functions (e.g., SipHash) or libraries like `abseil::flat_hash_map`.

---

## 7. Comparative Analysis: Map vs Unordered Map

| Feature | `std::map` | `std::unordered_map` |
| :--- | :--- | :--- |
| **Structure** | Red-Black Tree | Hash Table |
| **Speed (Lookup)** | O(log N) - Guaranteed | O(1) - Average |
| **Order** | Sorted (a-z) | Random (Chaotic) |
| **Memory** | High (Node overhead) | Higher (Buckets + Nodes) |
| **Iterator Invalidation** | Never (on insert) | Possible (on Rehash) |

---

## 8. Professional Summary

1.  **Default choice:** Use `unordered_map` for speed (Lookups), unless you need sorting.
2.  **Reserve:** Always use `reserve()` if you know the number of elements.
3.  **Memory:** Keep in mind that the hash table wastes a lot of memory on empty buckets.
4.  **Enum Keys:** If your key is an `enum`, prefer using a regular array or `std::vector` (Direct Mapping); it is O(1) without hashing.