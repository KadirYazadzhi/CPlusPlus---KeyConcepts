#include <iostream>

int main() {
    int x = 100;                    // Български: Декларираме променлива x със стойност 100
                                    // English: Declare variable x with value 100
    int *ptr = &x;                  // Български: Указател ptr сочи към x
                                    // English: Pointer ptr points to x
    int **doublePtr = &ptr;         // Български: doublePtr сочи към ptr
                                    // English: doublePtr points to ptr

    std::cout << "Value of x: " << **doublePtr << std::endl; 
    // Български: Извеждаме стойността на x чрез указател към указател
    // English: Output the value of x via pointer-to-pointer

    return 0;
}
