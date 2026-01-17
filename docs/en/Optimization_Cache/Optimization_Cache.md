# Optimization and Cache in C++

## 1. Introduction

High-performance C++ requires understanding how the CPU handles data.

---

## 2. Cache Locality

Keep data contiguous in memory to maximize cache hits.
**Vector is King:** Elements are adjacent.
**List is Slow:** Pointer chasing causes cache misses.

---

## 3. Data-Oriented Design

Organize data for processing efficiency (SoA - Structure of Arrays) instead of object-heavy hierarchies (AoS).

---

## 4. Summary

Measure before you optimize. Contiguous memory is usually the best optimization.
