#include <iostream>

// Демонстрация на работа с референции към динамично разпределена памет.
// Demonstrating references to dynamically allocated memory.

int main() {
    // Създаваме динамична променлива / Creating a dynamic variable
    int *dynamicVar = new int(50);

    // Създаваме референция към динамичната променлива / Creating a reference to the dynamic variable
    int &ref = *dynamicVar;

    // Променяме стойността чрез референцията / Modifying the value through the reference
    ref = 100;

    std::cout << "Dynamic variable: " << *dynamicVar << std::endl; // Изход: 100 / Output: 100
    std::cout << "Reference: " << ref << std::endl;               // Изход: 100 / Output: 100

    // Освобождаваме паметта / Releasing the memory
    delete dynamicVar;

    return 0;
}
