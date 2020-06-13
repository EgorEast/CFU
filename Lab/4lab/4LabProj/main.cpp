#include <iostream>
#include "Game.h"

using namespace std;
int main() {
	
	setlocale(LC_ALL, "Russian");
	char play = 'Y';
	while (play == 'Y') {
		char character = ' ';

		while (character != 'x' && character != '0') {
			cout << "������ ��� ������ ������ (x ��� 0): ";
			cin >> character;
		}

		//������ ��������� ��������� � ������� � ���� ��������� ��������
		Game game = initGame(character);

		//�������� ����. ��������, ���� ���������� ���� �������
		while (updateGame(&game))
		{
			//�������� �������
			updateDisplay(game);
			//���� ��������� ��� � ������, �� ����� �����
			if (game.isUserTurn) userTurn(&game);
			//����� ����� ���
			else botTurn(&game);
			//� ����� �������� �������
			updateDisplay(game);
		}

		//������� ������
		if (game.status == USER_WIN) cout << "�� ������� :D" << endl;
		if (game.status == BOT_WIN) cout << "��� ������� :(" << endl;
		if (game.status == NOT_WIN) cout << "����� :|" << endl;

		//� ���� ��� ���������� ��� ����������� ����
		while (play != 'N') {
			cout << "������ ���������? (Y/N):";
			cin >> play;
			if (play != 'Y' && play != 'N'){ 
				cout << "������� ������ ������" << endl; 
				continue;
			}
			if (play == 'Y' || play == 'N') break;
		}
	}
	return 0;
}