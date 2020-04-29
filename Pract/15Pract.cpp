#include <iostream>
#include <cmath>

using namespace std;
void sorting(int size, int signals[]) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (signals[i] < signals[j]) {
				swap(signals[i], signals[j]);
			}
		}
	}
}
void output(int size, int signals[]){
	for (int k = 1; k <= size; k++) {
		for (int i = 0; i < k; i++) {
			cout << signals[i];
		}
		cout << endl;
	}
}
int main()
{
	setlocale(LC_ALL, "RUSSIAN");

	int size;
	cout << "Число количество сигналов n (1 <= n <= 100 000)\nПоследовательность ai (-1 000 000 <= ai <= 1 000 000)\n";
	cout << "Введите число n: ";
	cin >> size;
	cout << "\nВведите сигналы:" << endl;

	int* signals = new int[size];
	for (int i = 0; i < size; i++) {
		cout << "Сигнал " << i + 1 << ": ";

		cin >> signals[i];
	}
	sorting(size, signals);
	output(size, signals);
}
