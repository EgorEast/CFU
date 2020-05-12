#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double a, b, xStart, xEnd, dx;
    double x, F, fMin, fMax;

    /*cout << "Введите a:";
    cin >> a;
    cout << endl << "Введите b:";
    cin >> b;
    cout << endl << "Введите xStart:";
    cin >> xStart;
    cout << endl << "Введите xEnd:";
    cin >> xEnd;
    cout << endl << "Введите dx:";
    cin >> dx;*/


    a = 0.7, b = 1.2, xStart = 0.5, xEnd = 1.5, dx = 0.05;

    for (x = xStart; x <= (xEnd + dx / 2); x += dx){
        if (x <= a) F = x - 2 * (pow(cos(x),2));
        else if (x > a && x < b) F = log(x) * sin(x);
        else if (x >= b) F = 1.3 + sin(x);
        
        if (x == xStart){ fMin = F; fMax = F; }

        if (F < fMin) fMin = F;
        if (F > fMax) fMax = F;
        if (abs(F) < 0.0000001) { F = 0; }
        
        cout << "F(" << x << ") = " << F << endl;
    }
    cout << endl << "Fmin = " << fMin;
    cout << endl << "Fmax = " << fMax;
}