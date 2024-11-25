#include <iostream>
using namespace std;

int main() {
    // 🏗️ Деклариране и инициализация на двумерен масив
    int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};

    // 📋 Печат на елементите на масива
    for (int i = 0; i < 2; i++) { // Итерация по редовете
        for (int j = 0; j < 3; j++) { // Итерация по колоните
            cout << "Element at [" << i << "][" << j << "] is: " << matrix[i][j] << " ";
            // Елемент на [i][j] е: стойност
        }
        cout << endl; // Нов ред за всеки ред от матрицата
    }

    return 0;
}