#include <iostream>


using namespace std;

int main()
{
	double a, b;
	setlocale(LC_ALL, "Russian");
	cout << "Введите число для нахождения факториала ";
	cin >> a;
	if (a < 0) b = 0;
	else if (a == 0) b = 1;
	else {
		b = 1;
		for (int i = 1; i <= a; i++) {
			b *= i;
		}	 
	}
	cout << "Факториал для числа " << a << " = " << b << endl;
}