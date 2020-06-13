#include <iostream>
#include <ctime>
#include "Game.h"

using namespace std;

Game initGame(char userChar) {
	Game game;
	//������� ������� ���� �������� ��� ���������
	for (char i = 0; i < 3; i++)
		for (char j = 0; j < 3; j++)
			game.bord[i][j] = ' ';
	//��������� ������� ���������� ��� ���
	srand(time(0));
	if (rand() % 2 + 1 == 1) game.isUserTurn = true;
	else game.isUserTurn = false;
	//������������� ������ ��� ������ (������� ���������� userChar)
	game.userChar = userChar;
	//������������� ������ ��� ����
	if (game.userChar == 'x') game.botChar = '0';
	else game.botChar = 'x';
	//������ ����, ��� ��� ������
	game.status = PLAY;
	//���������� ����������� ���������
	return game;
}

void updateDisplay(const Game game) {
	//������ ����� � ������� ��������� �������
	system("cls");
	//���������� ���������� �������� ����
	cout << "\ta \tb \tc" ;
	for (int i = 0; i <= 2; i++) {
		cout << endl << i+1 << "\t";
		for (int j = 0; j <= 2; j++) {
			cout << game.bord[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void botTurn(Game* game) {
	//���������� ��� ����������� ������� ������ �������� � �����
	short empCharPos = 0,
		//���������� ��������, ������������� ������� � �����
		plSuppChar = 0,
		//���������� ������ ����� � �����
		blank�har = 0;
	//������� �� ����� ����
	for (short i = 0; i < 3; i++)
		for (short j = 0; j < 3; j++)
			//���� �������� ����� ������ ����� �������
			if (game->bord[i][j] != ' ')
				//����� ����������� ���������� ���� ��������
				empCharPos++;
	//���� ����� �������� = 0, ������ ���� ������, ����� ��� ����� � ��������� ����� � ����������� ���
	if (empCharPos == 0) {
		game->bord[1][1] = game->botChar;
		return;
	}
	//������� ������� ��������
	empCharPos = 0;
	//������ ����� ������� �� �����, �� ������ �� ���������
	for (short i = 0; i < 3; i++) {
		//���� �� �����-���� �� ������ ���� ��������� �������� ������ ������
		if (game->bord[i][i] == game->userChar)
			//����� ����������� ���������� �������� ������ � ���� ���������
			plSuppChar++;
		//� ������ ������ ������ � ���� ���������. ���� �� ���� ������ ������
		if (game->bord[i][i] == ' ') {
			//����� ���������, ��� � ���� ����� ���� ������ ������
			blank�har++;
			//��������� ��������� ���� ������
			empCharPos = i;
		}
	}
	//���� � ���� ��������� ������������ ��� ������� ������ � ���� ������ ������
	if ((plSuppChar == 2) && (blank�har == 1)) {
		//����� ������ � ��� ������ ������ ������ ����
		game->bord[empCharPos][empCharPos] = game->botChar;
		return;
	}

	//��� ����� �������� ������� ��������
	plSuppChar = 0;
	blank�har = 0;

	//��������� �� ������ ���������. ��-�� ������
	for (short i = 0; i < 3; i++) {
		if (game->bord[i][2 - i] == game->userChar)
			plSuppChar++;

		if (game->bord[i][2 - i] == ' ') {
			blank�har++;
			empCharPos = i;
		}
	}
	if ((plSuppChar == 2) && (blank�har == 1)) {
		game->bord[empCharPos][2 - empCharPos] = game->botChar;
		return;
	}

	//�������� ��� ��������, ������� � �������
	for (short i = 0; i < 3; i++) {
		//�� ������ ������� ������� ��������
		plSuppChar = 0;
		blank�har = 0;
		//������� �� �������
		for (short j = 0; j < 3; j++) {
			//����� ������� ������ ������ ���������� ����� ���� ������, ����� ������������ �����
			empCharPos = j;
			//���� ������� �� ������ ������
			if (game->bord[i][j] == game->userChar) {
				//�� �������� � �������
				plSuppChar++;
				//� ���� ���������� �������� ������ � ����� ����� 2
				if (plSuppChar == 2) {
					//����� � ������� j ������� ��� ����������, ��� ���� ���� �������
					j = plSuppChar;

					//� ������, ���� �� �� ������� �� ����� �������
					while (j >= 0) {
						//���� ������ ������
						if (game->bord[i][j] == ' ') {
							//���� ����� - ����� ���������
							game->bord[i][j] = game->botChar;
							return;
						}
						//���� �� �� �����, �� ���� � ���������� ��������
						j--;
					}
				}
				//��������� �������� 
				j = empCharPos;
			}
			//������ ������� �� �����
			if (game->bord[j][i] == game->userChar) {
				blank�har++;
				if (blank�har == 2) {
					j = blank�har;

					while (j >= 0) {
						if (game->bord[j][i] == ' ') {
							game->bord[j][i] = game->botChar;
							return;
						}

						j--;
					}
				}
				j = empCharPos;
			}
		}
	}

	//������ ������� ��������� �������
	do {
		//����������� ����� ����������
		plSuppChar = rand() % 3;
		blank�har = rand() % 3;
		//� ������ � ������ ������
		if (game->bord[plSuppChar][blank�har] == ' ') {
			game->bord[plSuppChar][blank�har] = game->botChar;
			return;
		}

	} while (true);
}

void userTurn(Game* game) {
	//���������� ��� ��������
	char symbol;
	//���������� ��� ����
	short numeral;
	//���������� ��� �������� ������������ �����
	bool correctly = false;

	std::cout << "���� ���. ����� ���������� ����� ������ (�����, �����): ";
	while (!correctly) {
		std::cin >> symbol >> numeral;
		//�������� �� �����
		switch (symbol) {
		case 'a': symbol = 0;
			break;
		case 'b': symbol = 1;
			break;
		case 'c': symbol = 2;
			break;
		default:
			std::cout << "����������� ������� �����!" << endl;
			break;
		}
		//�������� �� �����
		switch (numeral) {
			//�������� �� �� �������, ��� ��� ������ �������� ��������� � ����
		case 1: numeral--;
			break;
		case 2: numeral--;
			break;
		case 3: numeral--;
			break;
		default:
			std::cout << "����������� ������� �����!" << endl;
			break;
		}
		//���� ������� � ������ ����� ����, ����� ������ �� �����
		if (game->bord[numeral][symbol] == ' ') correctly = true;
		//���� �������, �� �������� ����� ����
		else cout << "������ ���� ���������!" << endl;

	}
	//������ ������
	game->bord[numeral][symbol] = game->userChar;
}

bool updateGame(Game* game) {
	//�������� ������ ������ ������ ��� ���� �� ������� � ��������
	for (short i = 0; i < 3; i++)
	{
		//�������� �������
		if (game->bord[0][i] == 'x' || game->bord[0][i] == '0')
		{
			//���� ���� ������� �������� ����������� ���������
			if ((game->bord[1][i] == game->bord[0][i]) && (game->bord[2][i] == game->bord[0][i]))
			{
				//���� ��� ������� ����������� ������
				if (game->bord[0][i] == game->userChar)
					//������� �����
					game->status = USER_WIN;
				else
					//�����: ������� ���
					game->status = BOT_WIN;
				//���������� ����
				return false;
			}
		}

		
		//������� �� ��������
		if (game->bord[i][0] == 'x' || game->bord[i][0] == '0')
		{
			//��-�� ������
			if ((game->bord[i][1] == game->bord[i][0]) && (game->bord[i][2] == game->bord[i][0]))
			{
				if (game->bord[i][0] == game->userChar)
					game->status = USER_WIN;
				else
					game->status = BOT_WIN;
				return false;
			}
		}
	}

	//������� �� ����� ���������
	if (game->bord[2][0] == 'x' || game->bord[2][0] == '0')
	{
		if ((game->bord[1][1] == game->bord[0][2]) && (game->bord[1][1] == game->bord[2][0]))
		{
			if (game->bord[1][1] == game->userChar)
				game->status = USER_WIN;
			else
				game->status = BOT_WIN;
			return false;
		}
	}

	//������� �� ������
	if (game->bord[0][0] == 'x' || game->bord[0][0] == '0')
	{
		if ((game->bord[1][1] == game->bord[0][0]) && (game->bord[2][2] == game->bord[0][0]))
		{
			if (game->bord[2][2] == game->userChar)
				game->status = USER_WIN;
			else
				game->status = BOT_WIN;
			return false;
		}
	}

	//�������� �� �����
	bool deadHeat = false;
	for (short i = 0; i < 3; i++)
		for (short j = 0; j < 3; j++)
			//���� ���� ���� ���� ������ ������, ����� ��� ������
			if (game->bord[i][j] == ' ') deadHeat = false;
	//���� �� ���� �����
	if (deadHeat){
		//����� �����
		game->status = NOT_WIN;
		//���������� ����
		return false;
	}

	//������� ��� ����
	game->isUserTurn = !game->isUserTurn;
	//��������� ����
	return true;
}