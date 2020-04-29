#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random> // для random_device и mt19937


using namespace std;

void random(int cicle[]) {
	random_device rd;
	mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 
	for (int i = 0; i <= 19; i++) {
		uniform_int_distribution<> random(-100, 101);

		cicle[i] = random(mersenne);
		cout << cicle[i] << " ";
	}
}

void sorting(int cicle[]) {

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (cicle[i] < cicle[j]) {
				swap(cicle[i], cicle[j]);
			}
		}
	}

}

int main() {
	setlocale(LC_ALL, "Russian");
	double answer = 1;

	while (answer == 1) {
		int cicle[20];

		random(cicle);
		cout << endl;

		sorting(cicle);
		cout << "min = " << cicle[0] << endl;
		cout << "max = " << cicle[19] << endl;

		cout << "Повторить еще раз? (1 - Да): ";
		cin >> answer;
	}
}