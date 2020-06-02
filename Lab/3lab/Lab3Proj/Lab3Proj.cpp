#include <iostream>
#include "libbmp.h"

using namespace std;

//Переменные для хранения номера текущего читаемого байта и бита соответствующе
int Byte = 0, Bit = 7;
//Массив символов (букв) в котором будет храниться полученное "послание"
char message[100];
//Нужна для завершения считывания
bool finishPixPict = false;

void addBitToMessage(char readBit)
{
	//Если достиг конца картинки - заканчиваю операцию
	if (finishPixPict) return;
	
	//Сдвигаю бит в нужную позицию
	readBit <<= Bit;
	Bit--;
	message[Byte] |= readBit;

	// Переход к следующему байту
	if (Bit < 0){
		Bit = 7;

		if (message[Byte] == '\0') finishPixPict = true;

		Byte++;
	}
}

int main() {
	//Создаю экземпляр класса картинки
	BmpImg img;
	//Загружаю в него картинку
	img.read("images/pic5.bmp");

	//Переменные, которые будут хранить значение пикселя
	char bitOne, bitTwo, bitThree;

	//Прохожусь по всей картинке
	for (int y = img.get_height() - 1; y >= 0; y--)
		for (int x = img.get_width() - 1; x >= 0; x--) {
			//Ключ: 11r 11b 11g 01r 01b 01g 10r 10b
			//Будет хранить значение извлеченное из пикселя по красному цвету
			bitOne = img.red_at(x, y) & 0b1;
			//По синему
			bitTwo = img.blue_at(x, y) & 0b1;
			//По зеленому
			bitThree = img.green_at(x, y) & 0b1;

			//Вызываем функцию добавления символов из трех цветов пикселя в текст "послания"
			addBitToMessage(bitOne);
			addBitToMessage(bitTwo);
			addBitToMessage(bitThree);
			//И если прихожу в конец - выхожу из цикла
			if (finishPixPict) break;
		}
	//Вывожу на экран полученное "послание"
	cout << message << endl << endl;
}