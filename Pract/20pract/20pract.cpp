#include <iostream>

using namespace std;

void sorting(int pArr[], int size);
int fillingOutArr(int pArr[], int size);
void printArr(int pArr[], int size);

int main()
{
    setlocale(LC_ALL, "Russian");
    int size, aswer = 1;
    int* pArr;

    do {
        do {
            cout << "Введите размер массива: ";
            cin >> size;

            if (size <= 0) {
                cout << "Некорректный размер!" << endl << endl;
            }
        } while (size <= 0);

        pArr = new int(size);

        sorting(pArr, size);


        cout << "Хотите поыторить (1-Да)? ";
        cin >> aswer;

    } while (aswer == 1);
    
    delete[] pArr;

    return 0;
}

void sorting(int pArr[], int size) {

    fillingOutArr(pArr, size);

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (pArr[i] > pArr[j]) swap(pArr[i], pArr[j]);
        }
    }

    printArr(pArr, size);
}

int fillingOutArr(int pArr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "Элемент " << i + 1 << ": ";
        cin >> pArr[i];
    }
    for (int i = 0; i < size; i++) {
        return pArr[i];
    }
}

void printArr(int pArr[], int size) {
    cout << "Отсортированный массив: ";
    for (int i = 0; i < size; i++) {
        //cout << "Элемент " << i << " = " << pArr[i] << endl;
        cout << pArr[i] << " ";
    }
}