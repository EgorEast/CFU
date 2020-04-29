#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	double a, b, c, x1, x2, D;

	cout << "Введите значения a, b, c:" << endl;
	cin >> a >> b >> c;

	// ax^2+bx-c=0;

	if (a == 0 && b == 0)
	{
		cout << "x = Бесконечное множество" << endl;
		return 0;
	}
	else if (a == 0)
	{
		cout << "x = " << -c / b << endl;
	}

	else if (b == 0)
	{		
		if ((-c / a) < 0) cout << "Решений нет";
		else cout << "x = " << x1 = sqrt(-c / a) << endl;
	}

	else
	{
		D = b * b - 4 * a * c;

		if (D < 0)
		{
			cout << "Решений нет." << endl;
		}

		if (D > 0)
		{
			double KD = sqrt(D);

			x1 = (-b + KD) / (2 * a);
			x2 = (-b - KD) / (2 * a);

			cout << "x1 = " << x1 << endl;
			cout << "x2 = " << x2 << endl;
		}
		if (D = 0)
		{
			double KD = sqrt(D);
			
			x1 = (-b) / (2 * a);

			cout << "x = " << x1 << endl;
			
	}
}