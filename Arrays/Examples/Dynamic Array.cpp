#include <iostream>
using namespace std;

int main() {
    int size;

    // 🧵 Въвеждане на размера на масива
    cout << "Enter the size of the array: ";
    cin >> size;

    // 🛠️ Създаване на динамичен масив
    int* arr = new int[size];

    // 🔄 Попълване на масива със стойности
    for (int i = 0; i < size; i++) {
        arr[i] = i * 2; // Пример: всяка стойност е i * 2
    }

    // 🖨️ Показване на стойностите
    for (int i = 0; i < size; i++) {
        cout << "Value at index " << i << " is: " << arr[i] << endl;
        // Стойност на индекс i е: стойност
    }

    // 🗑️ Освобождаване на динамичната памет
    delete[] arr;

    return 0;
}
