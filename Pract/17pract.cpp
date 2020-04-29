#include <iostream>

using namespace std;

double BMI(double weight, double height);

void printBMI(double BMI);

int main() {
    //setlocale(LC_ALL, "Russian");
    double weight, height;
    cout << "Enter the weight: ";
    cin >> weight;
    cout << "Enter the height: ";
    cin >> height;
    cout << "Result: ";
    printBMI(BMI(weight, height / 100));
}

double BMI(double weight, double height) {
    return weight / (height * height);
}

void printBMI(double BMI) {
    if (BMI < 18.5) cout << "Underweight";
    else if (BMI >= 18.5 && BMI < 25.0) cout << "Normal weight";
    else if (BMI >= 25.0 && BMI < 30.0) cout << "Overweight";
    else cout << "Obesity";
}