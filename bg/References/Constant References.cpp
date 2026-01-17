#include <iostream>

// Функцията използва константна референция за безопасно четене на стойността.
// The function uses a constant reference for safe reading of the value.
void printValue(const int &num) {
    // Не можем да променяме 'num' / We cannot modify 'num'
    std::cout << "Value: " << num << std::endl;
}

int main() {
    int value = 42;

    // Извикваме функцията с константна референция / Calling the function with a constant reference
    printValue(value);

    return 0;
}
