#include <iostream>

// Референциите като псевдоними позволяват лесен достъп до оригиналната променлива.
// References as aliases allow easy access to the original variable.

int main() {
    int a = 10; // Оригиналната променлива / Original variable
    int &ref = a; // Референция към 'a' / Reference to 'a'

    // Промяна на стойността чрез референцията / Changing the value through the reference
    ref = 20;

    std::cout << "Original variable (a): " << a << std::endl; // Изход: 20 / Output: 20
    std::cout << "Reference (ref): " << ref << std::endl;     // Изход: 20 / Output: 20

    return 0;
}
