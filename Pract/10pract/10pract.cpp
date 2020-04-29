#include <iostream>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	double a, b, c, d;
	cout << "Введите число ";
	cin >> a;
	cout << "Введите степень ";
	cin >> b;
	if (b > 0) {
		d = 1;
		for (int i = 1; i <= b; i++) {
			d = d * a;
		}
		c = d;
	}
	else if (b == 0 && a != 0) c = 1;
	else if (b < 0 && a != 0) {
		d = 1;
		b = abs(b);
		for (int i = 1; i <= b; i++) {
			d = d * a;
		}
		c = 1 / d;
	}
	else if (a == 0 && b <= 0) {
		cout << "Результат неопредалён";
	}

	cout << "Ответ: " << c;
}