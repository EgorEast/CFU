#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	double optionOneTwo, S, replay = 1;
	while (replay == 1) {
		cout << "Выберите вариант расчета площади треугольника:" << endl;
		cout << "1- Через длины сторон\n" << "2- Через координаты вершин" << endl;
		cout << "Ввод: ";
		cin >> optionOneTwo;

		if (optionOneTwo == 1) {
			double a, b, c, p;
			cout << "Введите длины сторон:" << endl;
			cout << "a= ";
			cin >> a;
			cout << endl << "b= ";
			cin >> b;
			cout << endl << "c= ";
			cin >> c;
			p = (a + b + c) / 2.0;

			S = sqrt(p * (p - a) * (p - b) * (p - c));
		}

		else if (optionOneTwo == 2) {
			double x1, x2, x3, y1, y2, y3;
			cout << "Введите координаты через пробел:" << endl;
			cout << "Точка:\t" << "x " << "y" << endl;
			cout << "A\t";
			cin >> x1 >> y1;
			cout << endl << "B\t";
			cin >> x2 >> y2;
			cout << endl << "C\t";
			cin >> x3 >> y3;
			S = abs(((x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3)) / 2.0);
		}

		else {
			cout << "Неверный ввод! Можно ввести тоько 1 или 2.";
		}
		cout << "Ответ: S= " << S << endl;
		cout << "Хотите повторить? Если да- введите '1' ";
		cin >> replay;
	}
}