#include <iostream>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	int a;
	int b = 2;
	int c = 0;
	cout << "Введите число: ";
	cin >> a;
	while (b*b <= a && c !=1) { // числа меньше 4 (не включительно) - простые.
		//cout << b * b << endl;
		if (a % b == 0) { // a % b - a делю на b и если есть остаток, то это выражение принимает значение остатка.
			c = 1;
		}
		b++;
	}
	if (c == 1) {
		cout << "Составное число" << endl;
	}
	else cout << "Простое  число" << endl;
}