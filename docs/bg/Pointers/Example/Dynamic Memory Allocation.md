#include <iostream>

int main() {
    int *dynamicVar = new int(10); // Български: Заделяме динамично памет за цяло число и го инициализираме със стойност 10
                                   // English: Dynamically allocate memory for an integer and initialize it to 10

    std::cout << "Dynamic value: " << *dynamicVar << std::endl; // Български: Извеждаме стойността на динамичното число
                                                                // English: Output the value of the dynamically allocated integer

    delete dynamicVar; // Български: Освобождаваме паметта
                       // English: Free the allocated memory

    return 0;
}
