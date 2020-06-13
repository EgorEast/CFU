#include <iostream>
#include "Game.h"

using namespace std;
int main() {
	
	setlocale(LC_ALL, "Russian");
	char play = 'Y';
	while (play == 'Y') {
		char character = ' ';

		while (character != 'x' && character != '0') {
			cout << "Выбери кем будешь играть (x или 0): ";
			cin >> character;
		}

		//Создаю экземпляр структуры и передаю в него выбранный персонаж
		Game game = initGame(character);

		//Запускаю игру. Работает, пока обновление игры истинно
		while (updateGame(&game))
		{
			//Обновляю дисплей
			updateDisplay(game);
			//Если переходит ход к игроку, то игрок ходит
			if (game.isUserTurn) userTurn(&game);
			//Иначе ходит бот
			else botTurn(&game);
			//И снова обновляю дисплей
			updateDisplay(game);
		}

		//Условия победы
		if (game.status == USER_WIN) cout << "Ты победил :D" << endl;
		if (game.status == BOT_WIN) cout << "Бот победил :(" << endl;
		if (game.status == NOT_WIN) cout << "Ничья :|" << endl;

		//И цикл для завершения или продолжения игры
		while (play != 'N') {
			cout << "Хочешь повторить? (Y/N):";
			cin >> play;
			if (play != 'Y' && play != 'N'){ 
				cout << "Неверно введен символ" << endl; 
				continue;
			}
			if (play == 'Y' || play == 'N') break;
		}
	}
	return 0;
}