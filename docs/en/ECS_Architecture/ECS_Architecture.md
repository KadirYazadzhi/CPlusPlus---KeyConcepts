# ECS (Entity Component System) in C++ - Complete Technical Guide

## 1. Introduction: The End of Deep Hierarchies

In traditional Object-Oriented Programming (OOP) for games and simulations, we use deep inheritance.
*   Example: `Orc` -> `Enemy` -> `Character` -> `GameObject`.
*   Problem: What do we do if we want an `Orc` that doesn't move (static) but has an inventory? We have to rewrite the hierarchy. This leads to the "Diamond Problem" and massive, hard-to-maintain classes (**God Objects**).

**ECS** is an architectural pattern that replaces inheritance with **Composition** and is radically optimized for CPU cache (Data-Oriented Design).

---

## 2. The Three Pillars of ECS

### 2.1. Entity
In ECS, an entity is not an object. It is just an **ID** (usually `uint32_t`).
*   It has no data.
*   It has no methods.
*   It serves only as a unique key that groups different components.

### 2.2. Component
A component is a pure data structure (**POD** - Plain Old Data). It **contains no logic** (methods).
*   `PositionComponent`: `{ float x, y, z; }`
*   `VelocityComponent`: `{ float dx, dy, dz; }`
*   `HealthComponent`: `{ int hp; }`

### 2.3. System
The system contains **only logic**, with no state. It "selects" all entities that possess a specific set of components and processes them.
*   `PhysicsSystem`: Takes everyone with `Position` AND `Velocity` and updates coordinates: `pos += vel * dt`.
*   `RenderSystem`: Takes everyone with `Position` AND `Mesh` and draws them.

---

## 3. ECS and Cache Optimization (The Performance Edge)

This is the main reason ECS is standard in the game industry (Unreal Engine Mass, Unity DOTS, Overwatch).

### 3.1. Archetypes
Instead of keeping components in an array of pointers (bad for cache), ECS groups components by their type combination.
All entities that have exactly `{Position, Velocity}` are stored in one "table" (Archetype).
*   **Result:** `PhysicsSystem` reads memory linearly. The processor loads data into L1 cache perfectly.

### 3.2. SoA (Structure of Arrays)
Instead of an Array of Structures (AoS), ECS often uses a Structure of Arrays.
```cpp
// Bad (AoS):
struct Orc { float x, y; int hp; };
vector<Orc> orcs;

// Good (SoA / ECS):
vector<float> positions_x;
vector<float> positions_y;
vector<int> hps;
```
If the movement system doesn't care about HP, it doesn't even load the HP array into the cache. This saves memory bandwidth.

---

## 4. Popular Libraries in C++

Instead of writing an ECS from scratch (which is complex), use established libraries:

### 4.1. EnTT (The Standard)
EnTT is the "STL of ECS". It is header-only, extremely fast, and used in Minecraft and hundreds of other games.
*   Uses **Sparse Sets** for storage, allowing O(1) addition/removal of components and very fast iteration.

```cpp
entt::registry registry;
auto entity = registry.create();
registry.emplace<Position>(entity, 10.0f, 20.0f);
registry.emplace<Velocity>(entity, 1.0f, 1.0f);

// System:
auto view = registry.view<Position, Velocity>();
view.each([](auto& pos, auto& vel) {
    pos.x += vel.dx;
    pos.y += vel.dy;
});
```

### 4.2. Flecs
Written in C (with a C++ API), it is known for its excellent visualization tools and easy query language.

---

## 5. Parallelism (Multithreading)

Since systems in ECS are often independent (e.g., AI system doesn't depend on Render system), they can be executed in parallel on different cores without complex locking (mutexes).
ECS libraries often have built-in `Task Graphs` for automatically distributing systems across threads.

---

## 6. Professional Summary

1.  **Composition:** You can create a new enemy type simply by "gluing" new components to it at runtime.
2.  **Performance:** ECS is the only way to simulate 100,000 units on screen at 60 FPS.
3.  **Complexity:** ECS requires a shift in thinking. Not suitable for small projects or UI with deep hierarchy.
4.  **Data-Oriented:** Think about data first, code second.

---
*(Documentation prepared for the project "Key Concepts in C++".*
*Version: 3.0 - Expert Detail)*