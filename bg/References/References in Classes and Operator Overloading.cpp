#include <iostream>

// Клас с претоварен оператор, използващ референция.
// A class with an overloaded operator using a reference.
class Counter {
private:
    int count;

public:
    Counter(int initial) : count(initial) {}

    // Претоварваме оператора += за увеличаване на стойността / Overloading the += operator
    Counter &operator+=(const Counter &other) {
        this->count += other.count;
        return *this; // Връщаме текущия обект / Returning the current object
    }

    // Функция за показване на стойността / Function to display the value
    void show() const {
        std::cout << "Count: " << count << std::endl;
    }
};

int main() {
    Counter c1(10);
    Counter c2(20);

    c1 += c2; // Увеличаваме стойността на 'c1' с тази на 'c2' / Increasing 'c1' by 'c2'

    c1.show(); // Изход: 30 / Output: 30

    return 0;
}
