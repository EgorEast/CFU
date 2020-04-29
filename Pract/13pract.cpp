#include <iostream>
#include <cmath>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");

	long long n, i = 0, answer = 1, k = 1;
	while (answer == 1) {
		cout << "Введите целое число от 0 до 10^15: ";
		cin >> n;
		if (n < 0 || n > pow(10, 15)) { //pow- степень, 10- число, 15- степень
			cout << "Вы ввели недопустимое число. Повторите попытку.\n \n";
			answer = 1;
		}

		else {
			while (k <= n) {
				k = k * 2;
				i++;
			}
			cout << "\nОтвет: " << i << endl;
		}
		cout << "Вы хотите повторить? (1-Да) ";
		cin >> answer;
	}
}