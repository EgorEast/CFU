#include "stdafx.h"
#include <iostream>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");

	double a;
	double b;
	double tmp;
	cout << "Введите числа a и b:" << endl;
	cin >> a;
	cin >> b;
	tmp = a;
	a = b;
	b = tmp;

	cout << "Значение a= " << a << endl;
	cout << "Значение b= " << b << endl << endl;


	double c;
	double d;
	cout << "Введите числа c и d:" << endl;
	cin >> c;
	cin >> d;
	c = c + d;
	d = c - d;
	c = c - d;
	cout << "Значение c= " << c << endl;
	cout << "Значение d= " << d << endl;
}