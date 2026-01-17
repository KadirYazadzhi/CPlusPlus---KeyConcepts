#include <iostream>

int main() {
    int x = 42;           // Български: Декларираме променлива x със стойност 42
                          // English: Declare variable x with value 42
    int *ptr = &x;        // Български: Съхраняваме адреса на x в указателя ptr
                          // English: Store the address of x in pointer ptr

    std::cout << "Address of x: " << ptr << std::endl;     // Български: Извеждаме адреса на x
                                                          // English: Output the address of x
    std::cout << "Value of x: " << *ptr << std::endl;     // Български: Извеждаме стойността на x чрез указателя
                                                          // English: Output the value of x via the pointer
    return 0;
}
