#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");

	double a, b, x;
	char z;
	cout << "Калькулятор:" << endl;

	cin >> a >> z >> b;

	switch (z) {
	case '+':
		x = a + b;
		break;
	case '-':
		x = a - b;
		break;
	case '*':
		x = a * b;
		break;
	case '/':
		if (b == 0)
		{
			cout << "На ноль делить нельзя" << endl;
			return 0;
		}
		x = a / b;
		break;
	default:
		cout << "Ошибка. Возможны операции: + ; - ; * ; / ." << endl;
		return 0;
	}
		

	cout << "Ответ: " << x << endl;
}