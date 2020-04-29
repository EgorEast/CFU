#include <iostream>
#include <cmath>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	long long s, l1, r1, l2, r2, x1, x2, answer = 1, w = 0;

	while (answer == 1) {
		do {
			cout << "Введите числа: s, l1, r1, l2, r2 через пробел\n";
			cout << "l1 должно быть меньше или равно r1, l2 должно быть меньше или равно r2\n";
			cout << "Также l1, r1, l2, r2 должны находиться в диапазоне от -10^15 до 10^15\n";

			cin >> s >> l1 >> r1 >> l2 >> r2;

			if (l1 > r1 || l2 > r2) cout << "Ошибка! Число l1 не может быть больше r1 или l2 не может быть больше r2\n \n";
			if (abs(s || l1 || r1 || l2 || r2) > pow(10, 15)) cout << "Ошибка! Все введенные числа должны находиться в диапазоне от от -10^15 до 10^15\n \n";
		} while ((l1 > r1 || l2 > r2) || (abs(s || l1 || r1 || l2 || r2) > pow(10, 15)));

		if (s < l1 + l2 || s > r1 + r2) cout << "-1\n";

		else {
			for (long long i = l1; i <= r1 && w == 0; i++) {
				for (long long j = r2; j >= l2; j--) {
					if (s == i + j) {
						x1 = i;
						x2 = j;
						w = 1;
						break;
					}
				}
			}
			cout << "x1 = " << x1 << " x2 = " << x2 << endl;
		}
		cout << "Вы хотите повторить? (1- Да)";
		cin >> answer;
	}
}
