
#include "stdafx.h"
#include <iostream>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");

	int one, two;
	double oneMore, twoMore;
	cout << "Введите числа A; B; C; D:" << endl;;
	cin >> one >> two >> oneMore >> twoMore;
	cout << "A+B= " << one + two << endl;
	cout << "A-B= " << one - two << endl;
	cout << "A*B= " << one * two << endl;
	cout << "A/B= " << one / two << endl << endl;

	cout << "C+D= " << oneMore + twoMore << endl;
	cout << "C-D= " << oneMore - twoMore << endl;
	cout << "C*D= " << oneMore * twoMore << endl;
	cout << "C/D= " << oneMore / twoMore << endl << endl;

	cout << "A+D= " << one + twoMore << endl;
	cout << "A-D= " << one - twoMore << endl;
	cout << "A*D= " << one * twoMore << endl;
	cout << "A/D= " << one / twoMore << endl << endl;

	cout << "B+C= " << two + oneMore << endl;
	cout << "B-C= " << two - oneMore << endl;
	cout << "B*C= " << two * oneMore << endl;
	cout << "B/C= " << two / oneMore << endl << endl;
}