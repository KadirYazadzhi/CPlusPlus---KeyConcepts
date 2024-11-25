#include <iostream>

void printMessage() {
    std::cout << "Hello from a function!" << std::endl; 
    // Български: Функцията извежда съобщение
    // English: The function prints a message
}

int main() {
    void (*funcPtr)() = printMessage; // Български: Указателят funcPtr сочи към функцията printMessage
                                      // English: Pointer funcPtr points to the function printMessage

    funcPtr(); // Български: Извикваме функцията чрез указателя
               // English: Call the function via the pointer

    return 0;
}
