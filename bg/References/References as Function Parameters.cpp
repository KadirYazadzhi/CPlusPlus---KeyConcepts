#include <iostream>

// Функцията използва референция, за да промени оригиналната стойност.
// The function uses a reference to modify the original value.
void doubleValue(int &num) {
    num *= 2; // Удвояваме стойността / Doubling the value
}

int main() {
    int value = 15;

    std::cout << "Before: " << value << std::endl; // Изход: 15 / Output: 15

    // Предаваме променливата по референция / Passing the variable by reference
    doubleValue(value);

    std::cout << "After: " << value << std::endl; // Изход: 30 / Output: 30

    return 0;
}
