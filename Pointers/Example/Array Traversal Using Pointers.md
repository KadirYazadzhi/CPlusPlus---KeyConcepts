#include <iostream>

int main() {
    int arr[] = {1, 2, 3, 4, 5};   // Български: Декларираме масив от цели числа
                                   // English: Declare an array of integers
    int *ptr = arr;               // Български: Указателят сочи към първия елемент на масива
                                   // English: Pointer points to the first element of the array

    for (int i = 0; i < 5; i++) {
        std::cout << "Value at index " << i << ": " << *(ptr + i) << std::endl; 
        // Български: Извеждаме стойността на елемента на текущия индекс
        // English: Output the value of the element at the current index
    }

    return 0;
}
