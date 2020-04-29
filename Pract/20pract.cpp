#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    int* arr; // указатель для выделения памяти под массив
    int size; // размер массива

    // Ввод количества элементов массива
    do {
        cout << "Введите количество элементов массива: ";
        cin >> size;

        if (size <= 0) {
            // Размер масива должен быть положитлеьным
            cout << "Некорректный размер!" << endl;
        }
    } while (size <= 0);

    arr = new int[size]; // выделение памяти под массив

    // заполнение массива
    for (int i = 0; i < size; i++) {
        cout << i + 1 << " элемент = ";
        cin >> arr[i];
    }

    // Сортировка массива пузырьком
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // меняем элементы местами
                swap(arr[j],arr[j + 1]);
            }
        }
    }

    // Вывод отсортированного массива на экран
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr; // освобождение памяти;

    return 0;
}