#include "stdafx.h"
#include <iostream>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");

	double  x0, v0, t, x_t_1, x_t_2;
	double a = (-9.8);

	cout << "Введите значения x0, v0, t:" << endl;

	cin >> x0 >> v0 >> t;

	x_t_1 = x0 + (v0 * t) + (a * t * t / 2);
	x_t_2 = x0 + (v0 * t) + (1.0 / 2 * a * t * t);

	cout << "x(t)1= " << x_t_1 << endl;
	cout << "x(t)2= " << x_t_2 << endl;
}