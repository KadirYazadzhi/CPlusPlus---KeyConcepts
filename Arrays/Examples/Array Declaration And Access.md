#include <iostream>
using namespace std;

int main() {
    // 📚 Деклариране и инициализация на масив
    int arr[5] = {1, 2, 3, 4, 5}; // Масив с 5 елемента

    // 🖨️ Обхождане на масива и печат на стойностите му
    for (int i = 0; i < 5; i++) {
        cout << "Element at index " << i << " is: " << arr[i] << endl;
        // Елемент на индекс i е: стойност
    }

    return 0;
}
