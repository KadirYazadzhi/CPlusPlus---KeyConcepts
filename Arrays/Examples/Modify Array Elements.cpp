#include <iostream>
using namespace std;

int main() {
    // 🛠️ Деклариране на масив
    int arr[3] = {10, 20, 30};

    // 🔄 Промяна на стойностите чрез умножение по 2
    for (int i = 0; i < 3; i++) {
        arr[i] *= 2; // Умножаваме всеки елемент по 2
    }

    // 🖨️ Показване на новите стойности
    for (int i = 0; i < 3; i++) {
        cout << "Updated value at index " << i << " is: " << arr[i] << endl;
        // Обновена стойност на индекс i е: стойност
    }

    return 0;
}
