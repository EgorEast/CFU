#include <iostream>
#include <cstdlib>
#include<cmath>


using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	int answer = 1;

	while (answer == 1) {
		int variation = 0;
		int size, zero = 0, one = 0, two = 0, three = 0, four = 0, five = 0, six = 0, seven = 0, eight = 0, nine = 0;
		cout << "Введите число n (количество элементов): ";
		cin >> size;
		if (size<1 || size > pow(10, 5)) {
			cout << "Ошибка! Количество элементов должно быть больше 1 и меньше 10^5" << endl;
			continue;
		}
		cout << "Введите элементы (через пробел) от 0 до 9: ";
		int* number = new int[size];
		for (int i = 0; i < size; i++) {
			cin >> number[i];
			if (number[i] < 0 || number[i] > 9) {
				cout << "Ошибка! Число должно быть от 0 до 9" << endl << endl;
				variation = 1;
				break;
			}
		}
		if (variation == 1) continue;
		
		for (int i = 0; i < 10; i++) {
			if (number[i] == 0) zero++;
			if (number[i] == 1)	one++;
			if (number[i] == 2) two++;
			if (number[i] == 3)	three++;
			if (number[i] == 4) four++;
			if (number[i] == 5) five++;
			if (number[i] == 6) six++;
			if (number[i] == 7) seven++;
			if (number[i] == 8) eight++;
			if (number[i] == 9) nine++;
		}

		if (zero != 0) cout << "0: " << zero << endl;
		if (one != 0) cout << "1: " << one << endl;
		if (two != 0) cout << "2: " << two << endl;
		if (three != 0) cout << "3: " << three << endl;
		if (four != 0) cout << "4: " << four << endl;
		if (five!= 0) cout << "5: " << five << endl;
		if (six!= 0) cout << "6: " << six << endl;
		if (seven!= 0) cout << "7: " << seven << endl;
		if (eight!= 0) cout << "8: " << eight << endl;
		if (nine!= 0) cout << "9: " << nine << endl;

		cout << "Повторить еще раз? (1 - Да): ";
		cin >> answer;
	}
}