#include <iostream>
using namespace std;

// 🧮 Функция за изчисляване на сумата на масив
int calculateSum(int arr[], int size) {
    int sum = 0;

    for (int i = 0; i < size; i++) {
        sum += arr[i]; // Добавяне на текущия елемент към сумата
    }

    return sum; // Връщане на сумата
}

int main() {
    int arr[4] = {5, 10, 15, 20}; // Деклариране на масив
    int size = 4; // Размер на масива

    // 📊 Призоваване на функцията и печат на резултата
    cout << "Sum of the array is: " << calculateSum(arr, size) << endl;
    // Сумата на масива е: стойност

    return 0;
}
