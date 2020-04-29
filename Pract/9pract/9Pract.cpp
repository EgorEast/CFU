#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random> // для random_device и mt19937


using namespace std;

int main(){
	setlocale(LC_ALL, "Russian");
	double number, answer = 1;

	cout << "Правила игры: \nЗагаданно случайное число. Это число не может быть меньше 0 и не больше 100. \nУ вас есть 5 попыток, чтобы угатдать это число. \n \n";
	while (answer == 1) {
		random_device rd;
		mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 
		uniform_int_distribution<> random(0, 101);

		double randomNumber = random(mersenne);

		cout << randomNumber;
		for (int i = 1; i < 7; i++){
			cout << "Введите число: ";
			cin >> number;

			if (i < 5){

				if (number == randomNumber){
					cout << "Поздравляю! Вы победили\n";
					break;
				}

				else if (number < randomNumber){
					cout << "\nЗагаданное число больше. ";
				}
				else{
					cout << "\nЗагаданное число меньше. ";
				}
				cout << "У вас осталось " << 5 - i << " попыток.\n";
			}
			else{
				cout << "\nВы проиграли. Было загадано число: " << randomNumber << endl;
				break;
			}
		}
		cout << "Хотите сыграть еще? (1 - Да): ";
		cin >> answer;
	}
}
