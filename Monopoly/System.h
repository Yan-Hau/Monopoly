#pragma once
#include "ConsoleInterface.h"
#include "Windows.h"
#include "Player.h"
#include "Bank.h"
#include <windows.h>
#include <time.h>

#include <functional>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include <regex>
#include <fstream>
#include <sstream>

using namespace std;
using namespace Windows;

typedef struct {
	string name;
	int initialPrice, type, owner = -1, level = 0;
	int price[4];
	bool barrier = false;
}Building;

typedef struct {
	short position, level;
}Estate;

/*
typedef struct {
	short position;
	int money;
	vector<Estate> own;//�֦��a��
}Player;
*/
typedef struct {
	string mapName;
	short remainingRound, playerNum, turn;
	Building building[28];
}GameData;




namespace
{
	Player players[4];
	Bank bank;
	enum Play { player1 = 0, player2, player3, player4 };
	enum keyboardValue { Up = 72, Down = 80, Left = 75, Right = 77, Enter = 13, Esc = 27 };
	function<void()> nameColor[] = {
			[]() -> void {		//�]�����a1����
				Cmder::setColor(CLI_BACK_BLUE | CLI_BACK_LIGHT);
			},

			[]() -> void {       //�]�����a2����
				Cmder::setColor(CLI_BACK_GREEN | CLI_BACK_LIGHT);
			},

			[]() -> void {       //�]�����a3����
				Cmder::setColor(CLI_BACK_YELLOW | CLI_BACK_LIGHT);
			},

			[]() -> void {       //�]�����a3����
				Cmder::setColor(CLI_BACK_RED | CLI_BACK_LIGHT);
			},

			[]() -> void {       //�L�H�֦�
				Cmder::setColor();
			},
	};
}

namespace System
{

	GameData gameData;

	inline bool mapStatus();
	inline bool gameStatus();
	inline bool playerStatus();
	inline int dice();
	inline bool merchandise();
	inline bool readFile();
	inline bool saveFile();
	inline void goBank();
	inline void transStock();
	inline void useCard();
	inline int getWealth(Player&);
	inline int getNumber();
	inline bool do_chance(Player&);
	inline bool Barrior(Player&);
	inline void saleEstate();
	

	/* �a�Ϫ��󪬺A */
	inline bool mapStatus()
	{
		function<void(short x, short y, short order)> coutBuilding = [&](short x, short y, short order) ->
			void {
			Cmder::setColor();
			Cmder::setCursor(COORD{ x, y });
			cout << order;

			/* ��X�в� */
			Cmder::setCursor(COORD{ x, y + 1 });
			(gameData.building[order].owner != -1) ? nameColor[gameData.building[order].owner]() : nameColor[4]();
			cout << gameData.building[order].name;

			/* ��X�в����� */
			Cmder::setColor();
			Cmder::setCursor(COORD{ x, y + 2 });
			if (gameData.building[order].owner != -1)
				cout << "Level: " << gameData.building[order].level;

			/* ��X���a��m */
			Cmder::setCursor(COORD{ x, y + 3 });
			cout << "             ";
			Cmder::setCursor(COORD{ x, y + 3 });
			for (int player = player1, count = 0; player <= player4; player++)
			{
				if (players[player].getState().position == order)
				{
					if (count == 0)
						cout << "Player: ";
					nameColor[player]();
					cout << player + 1;
					count++;
				}
			}
		};

		/* ��X�a�ϸ�T */
		for (short i = 0; i < 7; i++)
		{
			coutBuilding(2, 1 + 5 * i, i);
			coutBuilding(2 + 15 * i, 36, i + 7);
			coutBuilding(107, 36 - 5 * i, i + 14);
			coutBuilding(107 - 15 * i, 1, i + 21);
		}
		return 1;
	}

	/* �C�����A */
	inline bool gameStatus()
	{
		Cmder::setColor();
		Cmder::setCursor(COORD{ 20, 7 });
		cout << "���e�^�X: " << 21 - gameData.remainingRound;
		Cmder::setCursor(COORD{ 40, 7 });
		cout << "���� ";
		nameColor[gameData.turn]();
		cout << "���a" << gameData.turn + 1;

		short colors[] = {
			CLI_BACK_BLACK | CLI_FONT_LIGHT | CLI_FONT_PURPLE ,
			CLI_BACK_BLACK | CLI_FONT_LIGHT | CLI_FONT_YELLOW ,
			CLI_BACK_BLACK | CLI_FONT_LIGHT | CLI_FONT_RED ,
			CLI_BACK_BLACK | CLI_FONT_LIGHT | CLI_FONT_BLUE ,
		};
		char names[] = { 'A' , 'B' , 'C' , 'D' };

		Cmder::setColor();
		for (int i = 0; i < 4; ++i)
		{
			Cmder::setColor(colors[i]);
			Cmder::setCursor(20, 30 + i);
			cout << names[i] << "��: " << Bank::Business[i] << "$ / ��";
		}
		return 1;
	}

	/* �H�����A */
	inline bool playerStatus()
	{
		for (short i = player1; i <= player4; i++)
		{
			for (short j = 1; j <= 9; ++j)
			{
				Cmder::setColor();
				Cmder::setCursor(COORD{ 123, j + 10 * i });
				printf("%25c", ' ');
			}
			Cmder::setCursor(COORD{ 123, 1 + 10 * i });
			nameColor[i]();
			cout << "���a" << setw(2) << i + 1;
			Cmder::setColor();

			Cmder::setCursor(COORD{ 123, 2 + 10 * i });
			cout << "�֦�����: " << setw(2) << players[i].getState().money << " $";

			Cmder::setCursor(COORD{ 123, 3 + 10 * i });
			cout << "�֦��s��: " << players[i].getState().despoit << " $";

			Cmder::setCursor(COORD{ 123, 4 + 10 * i });
			cout << "�֦��Ѳ�A: " << players[i].getState().stock[0] << "��";

			Cmder::setCursor(COORD{ 123, 5 + 10 * i });
			cout << "�֦��Ѳ�B: " << players[i].getState().stock[1] << "��";

			Cmder::setCursor(COORD{ 123, 6 + 10 * i });
			cout << "�֦��Ѳ�C: " << players[i].getState().stock[2] << "��";

			Cmder::setCursor(COORD{ 123, 7 + 10 * i });
			cout << "�֦��Ѳ�D: " << players[i].getState().stock[3] << "��";



			Cmder::setCursor(COORD{ 123, 9 + 10 * i });
			cout << "�`����: " << getWealth(players[i]) << " $";
		}
		return 1;
	}

	/* �Y��l */
	inline int dice()
	{
		function<void()> diceNum[] = {
			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "      ��      ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 30 }); cout << "              ";
			},

			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "   ��         ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "         ��   ";
				Cmder::setCursor(COORD{ 85, 30 }); cout << "              ";
			},

			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "   ��         ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "      ��      ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "         ��   ";
				Cmder::setCursor(COORD{ 85, 30 }); cout << "              ";
			},

			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "   ��    ��   ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "   ��    ��   ";
				Cmder::setCursor(COORD{ 85, 30 }); cout << "              ";
			},

			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "   ��    ��   ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "      ��      ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "   ��    ��   ";
				Cmder::setCursor(COORD{ 85, 30 }); cout << "              ";
			},

			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "   ��    ��   ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "   ��    ��   ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "   ��    ��   ";
				Cmder::setCursor(COORD{ 85, 30 }); cout << "              ";
			},
		};
		srand(time(NULL));
		int result = rand() % 6 + 1;

		for (int i = 0; i < 30; i++)
		{
			diceNum[i % 6]();
			Sleep(20);
		}
		diceNum[result - 1]();

		return result;
	}

	/* �R��a�� */
	inline bool merchandise()
	{
		mapStatus();
		int playerPlace = players[gameData.turn].getState().position;/* ���a���e�a�I */

		if (gameData.building[playerPlace].owner == -1 && gameData.building[playerPlace].type == 1)//�Ӧa�I�S�D�H�B�i�H�ʶR
		{
			if (checkYesOrNo(40, "�O�_�n��" + to_string(gameData.building[playerPlace].initialPrice) + "�ʶR�g�a?"))
			{
				gameData.building[playerPlace].owner = gameData.turn;//�ಾ�a�D
				players[gameData.turn].cash(-
					gameData.building[playerPlace].initialPrice);//���a�I��

				/*
				Estate temp;
				temp.position = playerPlace;
				temp.level = 0;
				*/
				players[gameData.turn].setEstate(playerPlace, 0);
			}
		}
		else if (gameData.building[playerPlace].owner == gameData.turn)//���a���a�I���D�H
		{
			if (gameData.building[playerPlace].level < 3)
			{
				if (checkYesOrNo(40, "�O�_�n��" + to_string(gameData.building[playerPlace].initialPrice) + "�ɯūؿv?"))
				{
					gameData.building[playerPlace].level++;//�ؿv���ɯ�
					players[gameData.turn].cash(-gameData.building[playerPlace].initialPrice);//���a�I��
					/*
					for (int ownNum = 0; ownNum < gameData.player[gameData.turn].own.size(); ownNum++)//���a�Ӧa���ɯ�
					{
						if (gameData.player[gameData.turn].own[ownNum].position == playerPlace)
							gameData.player[gameData.turn].own[ownNum].level++;
					}
					*/
					int currentLevel = players[gameData.turn].getState().estate[playerPlace];
					players[gameData.turn].setEstate(playerPlace, currentLevel + 1);
				}
			}
			else
			{
				prompt(43, "�Ӥg�a�A�w�g�ɺ�!");
			}
		}
		else if (gameData.building[playerPlace].owner >= 0)//�Ӧa�I����L�D�H
		{
			prompt(43, "�A�Q���F" + to_string(gameData.building[playerPlace].price[gameData.building[playerPlace].level]) + "��");
			int passValue = gameData.building[playerPlace].price[gameData.building[playerPlace].level];
			players[gameData.turn].cash(-passValue);//���a�I�L���O
			players[gameData.building[playerPlace].owner].cash(passValue);
		}
		return 1;
	}

	/* �s���� */
	inline void goBank()
	{
		COORD optionPosition[] = { {20,9}, {20,11}, {20,13} };
		string option[] = {
			"�ڭn�s��", "�ڭn����", "���}�Ȧ�"
		};

		/* �l��� */
		auto print = [&]() -> void {
			for (int i = 0; i < 3; ++i)
			{
				Cmder::setCursor(optionPosition[i]);
				Cmder::setColor(CLI_FONT_WHITE);
				cout << option[i];
				Cmder::setCursor(optionPosition[i]);
			}
		};

		/* �l����� */
		auto select = [&](int set) -> void {
			Cmder::setCursor(optionPosition[set]);
			Cmder::setColor(CLI_FONT_RED);
			cout << option[set];
			Cmder::setCursor(optionPosition[set]);
		};
		int keypress, optionSet = 0;

		function<int()> eventTrigger[] = {
			[&]() -> int
			{
				int value = 0;
				COORD _pos = Cmder::getCursor();
				Cmder::setCursor(40,9);
				Cmder::setColor();
				cout << "�п�J���B : ";
				value = getNumber();
				if (value > 0 && players[gameData.turn].money >= value)
				{
					players[gameData.turn].bank(value);
					players[gameData.turn].cash(-value);
					playerStatus();
				}
				else
				{
					Cmder::setCursor(40, 10);
					cout << "�z�S������h�{��, �άO���B��J���s�B�t�ơB�D�Ʀr";
					_getch();
				}
				Cmder::setCursor(40, 9);
				printf("%50c", ' ');
				Cmder::setCursor(40, 10);
				printf("%50c", ' ');
				Cmder::setCursor(_pos);
				return 1;
			},

			[&]() -> int
			{
				int value = 0;
				COORD _pos = Cmder::getCursor();
				Cmder::setCursor(40, 9);
				Cmder::setColor();
				cout << "�п�J���B : ";
				value = getNumber();
				if (value > 0 && players[gameData.turn].despoit >= value)
				{
					players[gameData.turn].bank(-value);
					players[gameData.turn].cash(value);
					playerStatus();
				}
				else
				{
					Cmder::setCursor(40, 10);
					cout << "�z�S������h�s��, �άO���B��J���s�B�t�ơB�D�Ʀr";
					_getch();
				}
				//cin.get();
				Cmder::setCursor(40, 9);
				printf("%50c", ' ');
				Cmder::setCursor(40, 10);
				printf("%50c", ' ');
				Cmder::setCursor(_pos);
				return 1;
			},

			[]() -> int {
				return 0;
			}
		};
		print();
		select(0);
		bool loop = true;
		while (loop)
		{
			bankImage();
			select(optionSet);
			keypress = _getch();
			switch (keypress)
			{
			case Up:
				optionSet = (optionSet + 2) % 3;
				break;

			case Down:
				optionSet = (++optionSet) % 3;
				break;

			case Enter:
				loop = eventTrigger[optionSet]();
				break;
			}
			print();
			select(optionSet);
		}
		return;
	}

	/* �R��Ѳ�*/
	inline void transStock()
	{
		COORD optionPosition[] = { {20,9}, {20,11}, {20,13} , {20,15} , {30,9}, {30,11}, {30,13} , {30,15} , {30,17} };
		string option[] = {
			"�R�iA��", "�R�iB��", "�R�iC��" , "�R�iD��",
			"��XA��", "��XB��", "��XC��" , "��XD��",
			"���}�����",
		};

		/* �l��� */
		auto print = [&]() -> void {
			for (int i = 0; i < 9; ++i)
			{
				Cmder::setCursor(optionPosition[i]);
				Cmder::setColor(CLI_FONT_WHITE);
				cout << option[i];
				Cmder::setCursor(optionPosition[i]);
			}
		};

		/* �l����� */
		auto select = [&](int set) -> void {
			Cmder::setCursor(optionPosition[set]);
			Cmder::setColor(CLI_FONT_RED);
			cout << option[set];
			Cmder::setCursor(optionPosition[set]);
		};
		int keypress, optionSet = 0;

		function<int(int)> eventTrigger[] = {
			[&](int stockNum) -> int
			{
				int amount = -1;
				COORD _pos = Cmder::getCursor();
				Cmder::setCursor(20,19);
				Cmder::setColor();
				cout << "�п�J�ʶR�Ѽ�: ";
				amount = getNumber();

				if (amount > 0 && players[gameData.turn].despoit >= amount * Bank::Business[stockNum])
				{
					players[gameData.turn].bank(-amount * Bank::Business[stockNum]);
					players[gameData.turn].stock[stockNum] += amount;
					playerStatus();
				}
				else
				{
					Cmder::setCursor(20, 20);
					cout << "�z�S������h�s��, �άO�Ѽƿ�J���s�B�t�ơB�D�Ʀr";
					_getch();
				}
				Cmder::setCursor(20, 19);
				printf("%50c", ' ');
				Cmder::setCursor(20, 20);
				printf("%50c", ' ');
				Cmder::setCursor(_pos);
				return 1;
			},

			[&](int stockNum) -> int
			{
				int amount = -1;
				COORD _pos = Cmder::getCursor();
				Cmder::setCursor(20,19);
				Cmder::setColor();
				cout << "�п�J��X�Ѽ�: ";
				amount = getNumber();

				if (amount > 0 && players[gameData.turn].stock[stockNum] >= amount)
				{
					players[gameData.turn].bank(amount * Bank::Business[stockNum]);
					players[gameData.turn].stock[stockNum] -= amount;
					playerStatus();
				}
				else
				{
					Cmder::setCursor(20, 20);
					cout << "�z�S������h�Ѳ�, �άO�Ѽƿ�J���s�B�t�ơB�D�Ʀr";
					_getch();
				}
				Cmder::setCursor(20, 19);
				printf("%50c", ' ');
				Cmder::setCursor(20, 20);
				printf("%50c", ' ');
				Cmder::setCursor(_pos);
				return 1;
			},

			[](int x = 0) -> int {
				return 0;
			}
		};
		print();
		select(0);

		bool loop = true;
		while (loop)
		{
			stockImage();
			select(optionSet);
			keypress = _getch();
			switch (keypress)
			{
			case Up:
				optionSet = (optionSet + 8) % 9;
				break;

			case Down:
				optionSet = (++optionSet) % 9;
				break;

			case Left:
				if (4 <= optionSet && optionSet <= 7)
					optionSet = (optionSet - 4) % 9;
				break;
			case Right:
				if (0 <= optionSet && optionSet <= 3)
					optionSet = (optionSet + 4) % 9;
				break;

			case Enter:
				loop = eventTrigger[optionSet / 4](optionSet % 4);
				break;
			}
			print();
			select(optionSet);
		}

		return;
	}

	/* �ϥιD�� */
	inline void useCard()
	{
		Player& current = players[gameData.turn];
		enum keyboardValue { Up = 72, Down = 80, Left = 75, Right = 77, Enter = 13, Esc = 27 };
		COORD optionPosition[] = { {81,9}, {81,11}, {81,13}, {81, 15}, {81, 17} };
		string option[] = {
			"�{���d", "���٥d", "�ЫΥd", "�K�O�d", "���ϥ�"
		};

		/* �l��� */
		auto print = [&]() -> void {
			for (int i = 0; i < 5; ++i)
			{
				Cmder::setCursor(optionPosition[i]);
				Cmder::setColor(CLI_FONT_WHITE);
				cout << option[i];
				if (i != 4)
					cout << setw(2) << current.getState().card[i];

				Cmder::setCursor(optionPosition[i]);
			}
		};

		/* �l����� */
		auto select = [&](int set) -> void {
			Cmder::setCursor(optionPosition[set]);
			Cmder::setColor(CLI_FONT_RED);
			cout << option[set];
			Cmder::setCursor(optionPosition[set]);
		};
		int keypress, optionSet = 0;

		print();
		select(0);
		bool loop = true;
		while (loop)
		{
			keypress = _getch();
			switch (keypress)
			{
			case Up:
				optionSet = (optionSet + 4) % 5;
				break;

			case Down:
				optionSet = (++optionSet) % 5;
				break;

			case Enter:
				if (optionSet == 4)		 //���ϥ�
					loop = false;

				else if (players[gameData.turn].card[optionSet] > 0)
				{
					int playerPlace = players[gameData.turn].getState().position; // ���a���e�a�I
					int passValue = gameData.building[playerPlace].price[gameData.building[playerPlace].level]; //�L���O���B

					switch (optionSet)
					{
					case 0:				//�{���d
						for (int i = 0; i < 4; i++)
						{
							if (i != gameData.turn)
							{
								players[gameData.turn].cash(players[i].getState().money);
								players[i].setMoney(0);
							}
						}
						prompt(43, "�w�j�A�Ҧ����a�{��");
						players[gameData.turn].card[optionSet] -= 1;
						break;

					case 1:				//���٥d
						gameData.building[playerPlace].barrier = true;
						prompt(30, "�j��Ҧ��H�g�L���ٳB�ɡA�𮧤@�^�X");
						players[gameData.turn].card[optionSet] -= 1;
						break;

					case 2:				//�ЫΥd
						for (int place = 0; place < 28; place++)
						{
							if (gameData.building[place].owner == gameData.turn && gameData.building[place].level < 3)
							{
								gameData.building[place].level++;//�ؿv���ɯ�
								int currentLevel = players[gameData.turn].getState().estate[place];
								players[gameData.turn].setEstate(place, currentLevel + 1);
							}
						}
						prompt(43, "�w�K�O�ɯũҦ��Ы�");
						players[gameData.turn].card[optionSet] -= 1;
						break;

					case 3:				//�K�O�d
						if (gameData.building[playerPlace].owner == -1 || gameData.building[playerPlace].type == 1 || gameData.building[playerPlace].owner == gameData.turn)
							prompt(43, "�����ϥΧK�O�d");
						else
						{
							players[gameData.turn].cash(gameData.building[playerPlace].price[gameData.building[playerPlace].level]); //���e���a
							players[gameData.building[players[gameData.turn].getState().position].owner].cash(-passValue); //�a�D
							prompt(43, "�a�D�w�h�^�L���O");
							players[gameData.turn].card[optionSet] -= 1;
						}
						break;
					}
				}
				else {
					Cmder::setCursor(20, 16);
					cout << "�z�S���o���D��";
				}
				Sleep(500);
				loop = false;
			}
			print();
			select(optionSet);
		}
	}

	/* Ū������ */
	inline bool readFile()
	{
		string null;
		fstream file;
		file.open(fileName, ios::in);

		file >> gameData.mapName >> gameData.remainingRound >> gameData.playerNum;//Ū���a�ϦW�� �Ѿl�^�X�� �`���a�H��
		for (int i = 0, position; i < 28; i++)//Ū���C�Ӧa�������T
		{
			file >> position;
			file >> gameData.building[position].name >> gameData.building[position].type;
			if (gameData.building[position].type == 1)
			{
				file >> gameData.building[position].initialPrice;
				for (int j = 0; j < 4; j++)
				{
					file >> gameData.building[position].price[j];
				}
			}
		}
		file >> null >> gameData.turn;//Ū������ĴX�H
		for (short i = player1; i <= player4; i++)//Ū�����a �Ҧb��m �֦����� �Ҧ��a���򵥯�
		{
			string input, token;

			int c = 0, num, x;
			file >> num;
			getline(file, input);
			stringstream delim(input);//�N���n���F����r��delim��,�]�t�ť�
			//getline(delim, token, ' ') getline(delim[�ӷ���m],token[�s�J��m],'�@'[���Ϊ�����])
			while (delim >> x)
			{
				if (c == 0)
					players[num].setPosition(x);
				else if (c == 1)
					players[num].setMoney(x);
				else
				{
					Estate temp;
					temp.position = x;
					gameData.building[temp.position].owner = num;
					delim >> x;
					temp.level = x;
					gameData.building[temp.position].level = temp.level;
					players[num].setEstate(temp.position, temp.level);
				}
				c++;
			}
		}

		return 1;
	}

	/* ��X�в� */
	inline void saleEstate()
	{
		
		typedef struct _house {
			int location;
			double price;
		}House;
		Player& current = players[gameData.turn];
		vector<House> myEstate;

		/* �إߩв��M�� */
		for (auto& house : current.getState().estate)
		{
			myEstate.push_back(House{ 
				house.first, 
				gameData.building[house.first].initialPrice *(0.3 * (house.second + 1))
			});
		}
		
		COORD optionPosition[] = { {20,9}, {20,11} };
		string option[] = { "��X�в�" , "���}�򤶦�" };
		/* �l��� */
		auto print = [&]() -> void {
			for (int i = 0; i < 2; ++i)
			{
				Cmder::setCursor(optionPosition[i]);
				Cmder::setColor(CLI_FONT_WHITE);
				cout << option[i];
				Cmder::setCursor(optionPosition[i]);
			}
		};

		/* �l����� */
		auto select = [&](int set) -> void {
			Cmder::setCursor(optionPosition[set]);
			Cmder::setColor(CLI_FONT_RED);
			cout << option[set];
			Cmder::setCursor(optionPosition[set]);
		};
		
		int keypress, optionSet = 0 , houseIndex = 0, houseLocation = 0;

		function<int(int,int)> eventTrigger[] = {
			/* ��X�Фl */
			[&](int house, int index) -> int {
				current.setEstate(house, 0 , false);
				current.bank((int)myEstate[index].price);
				auto iter = find_if(begin(myEstate), end(myEstate), [&](House& iter) {
					return iter.location == house;
				});
				if( iter != end(myEstate))
					myEstate.erase( iter );
				return 1;
			},

			[](int unless0,int unless1) -> int {
				return 0;
			}
		};
		print();
		select(0);
		int loop = true;

		if( !myEstate.empty() )
			houseLocation = myEstate[houseIndex].location;

		while (loop)
		{
			Cmder::setCursor(30, 9);
			printf("%30c", ' ');
			Cmder::setCursor(30, 9);
			if (!myEstate.empty()) // ���Фl�~��X�в���T
			{
				cout << Cmder::FONT_WHITE 
					<< "<- " << Cmder::FONT_YELLOW <<gameData.building[houseLocation].name <<": " << (int)myEstate[houseIndex].price  << " $"
					<< Cmder::FONT_WHITE << " ->";
			}

			else
			{
				cout << Cmder::FONT_PURPLE << "�z���e�L�в�";
			}
			Cmder::setCursor(20, 9);
			keypress = _getch();
			switch (keypress)
			{
				case Up:
				case Down:
					optionSet = (++optionSet) % 2;
					break;

				case Right:
					if (!myEstate.empty() )
					{
						houseIndex = (++houseIndex) % myEstate.size();
						houseLocation = myEstate[houseIndex].location;
					}
					break;

				case Left:
					if (!myEstate.empty() )
					{
						houseIndex = (houseIndex + myEstate.size() - 1) % myEstate.size();
						houseLocation = myEstate[houseIndex].location;
					}
					break;

				case Enter:
					if (optionSet == 0 && !myEstate.empty() && myEstate.size() > 0)
					{
						/* ��X�в� */
						auto iter = find_if(begin(myEstate), end(myEstate), [&](House& iter) {
							return iter.location == houseLocation;
						});
						if (iter != end(myEstate))
						{
							current.setEstate(houseLocation, 0, false);
							current.bank((int)myEstate[houseIndex].price);
							myEstate.erase(iter);
							gameData.building[houseLocation].owner = -1;
						}

						/* ��s�в��M�� */
						houseIndex = 0;
						if (!myEstate.empty())
							houseLocation = myEstate[houseIndex].location;
						playerStatus();
						mapStatus();
						loop = true;
					}

					if(optionSet == 1)
					{
						loop = false;
					}
					break;
			}
			
			print();
			select(optionSet);
			
		}
	}

	/* �x�s���� */
	inline bool saveFile()
	{
		fstream file;
		file.open("basemap1.txt", ios::out);
		file << gameData.mapName << " " << gameData.remainingRound << " " << gameData.playerNum << endl;
		for (int i = 0; i < 28; i++)
		{
			file << setfill('0') << setw(2) << i << " " << gameData.building[i].name << " " << gameData.building[i].type;
			if (gameData.building[i].type == 1)
			{
				file << " " << gameData.building[i].initialPrice;
				for (int j = 0; j < 4; j++)
				{
					file << " " << gameData.building[i].price[j];
				}
			}
			file << endl;
		}
		file << "playerstate" << " " << gameData.turn << endl;
		for (int i = 0; i < gameData.playerNum; i++)
		{
			file << i << " " << setfill('0') << setw(2) << players[i].position << " " << players[i].money;
			for (auto iter = players[i].estate.begin(); iter != players[i].estate.end(); iter++)
				file << " " << setfill('0') << setw(2) << iter->first << " " << setw(2) << iter->second;
			file << endl;
		}
		return 1;
	}
	
	/* �p�⨭�� */
	inline int getWealth(Player& player) {

		/* �{�� */
		int total = player.getState().money;

		/* ���� */
		for (int i = 0; i < 4; ++i)
			total += (Bank::Business[i] * player.getState().stock[i]);
		
		/* �s�� */
		total += player.getState().despoit;

		/* ���ʲ��`�� */
		for (auto& house : player.getState().estate)
		{
			int price = gameData.building[house.first].initialPrice *(0.3 * (house.second+1) );
			total += price;
		}
		player.wealth = total;
		return total;
	};

	/* ���|�R�B */
	inline bool do_chance(Player& player) {

		int playerPlace = player.getState().position;
		if (playerPlace == 6 || playerPlace == 16)
		{
			srand(time(NULL));
			int result = rand() % 60 + 1;

			switch (result)
			{
				/* �𮧤@�^�X */
			case 1:
				prompt(30, "�߲֡A�A�A�𮧤@�^");
				player.stop = true;
				break;

			case 2:
				prompt(30, "�X���ѰO�a�����A�����A�𮧤@�^");
				player.stop = true;
				break;

			case 3:
				prompt(30, "�z�G���A�𮧤@�^");
				player.stop = true;
				break;

			case 4:
				prompt(30, "�C�Ѽ��]�ɭP�x���ƹL���A�𮧤@�^");
				player.stop = true;
				break;

			case 5:
				prompt(30, "�V�O���@�w���\�A���@�w�ΪA�A�𮧤@�^");
				player.stop = true;
				break;

			case 6:
				prompt(30, "�ݤȸ`�s���A�𮧤@�^");
				player.stop = true;
				break;

			case 7:
				prompt(30, "�Q�wŪ�A���ˡA�𮧤@�^");
				player.stop = true;
				break;

			case 8:
				prompt(30, "�R�n�ήɤT�����ɡA���|�A�𮧤@�^");
				player.stop = true;
				break;

				/* �ǰe */
			case 9:
				prompt(30, "�ɪŧᦱ�A�H���ǰe");
				player.setPosition(rand() % 28);
				break;

			case 10:
				prompt(30, "���W�ɪŪ��A�H���ǰe");
				player.setPosition(rand() % 28);
				break;

			case 11:
				prompt(30, "�j�a�_�A�H���ǰe");
				player.setPosition(rand() % 28);
				break;

			case 12:
				prompt(30, "�A�o�@�ɲn�A�@���A�o�@���n�A�^�u�ǤH�J�١v");
				player.setPosition(12);
				break;

			case 13:
				prompt(30, "��R�A����ʤ��A�e���u��a���v");
				player.setPosition(11);
				break;

			case 14:
				prompt(30, "�䤣��Ū�ѰʤO�A�u��F�j�ӡv��z���");
				player.setPosition(18);
				break;

			case 15:
				prompt(30, "�|�I�}�l���u�A�t�t�e���u��`�\�U�v");
				player.setPosition(23);
				break;

			case 16:
				prompt(30, "���סA�{�R�e���u�z�u�ǰ|�v");
				player.setPosition(9);
				break;

			case 17:
				prompt(30, "�u���V�n�v�x�{�����A�e�����a��U�ͺA�_�|");
				player.setPosition(14);
				break;

			case 18:
				prompt(30, "�U�ư_�Y���A�^��u�_�I�v");
				player.setPosition(0);
				break;

			case 19:
				prompt(30, "�Q�������A�e���u����|�v�@�@");
				player.setPosition(20);
				break;

			case 20:
				prompt(30, "���Ѵ����ҡA��u�Ϯ��]�v�{�ɩ��}");
				player.setPosition(25);
				break;

				/* �D��d */
			case 21:
				prompt(30, "�ǵs��w�Ǳ¡u�{���d�v�A�i�j�A�Ҧ����a�{��");
				player.card[0]++;
				break;

			case 22:
				prompt(30, "��o�u���٥d�v�@�i");
				player.card[1]++;
				break;

			case 23:
				prompt(30, "��o�u���٥d�v�@�i");
				player.card[1]++;
				break;

			case 24:
				prompt(30, "��o�u���٥d�v�@�i");
				player.card[1]++;
				break;

			case 25:
				prompt(30, "��o�u�ЫΥd�v�@�i�A�i�K�O�ɯũҦ��Ы�");
				player.card[2]++;
				break;

			case 26:
				prompt(30, "��o�u�ЫΥd�v�@�i�A�i�K�O�ɯũҦ��Ы�");
				player.card[2]++;
				break;

			case 27:
				prompt(30, "��o�u�K�O�d�v�@�i�A�i��K�L���O");
				player.card[3]++;
				break;

			case 28:
				prompt(30, "��o�u�K�O�d�v�@�i�A�i��K�L���O");
				player.card[3]++;
				break;

				/* �y���ܤ� */
			case 29:
				prompt(30, "�ڷQ���_�믫�A���p�ߧ⥦�����F�A�˰h�@��");
				player.nextPosition(-1);
				break;

			case 30:
				prompt(30, "�S�@�ѹL�h�F�A���ڭw�󻷤F�A�˰h�@��");
				player.nextPosition(-1);
				break;

			case 31:
				prompt(30, "�����o�j�]�A�M���Ӥ@�_�˰h�@��");
				player.nextPosition(-1);
				break;

			case 32:
				prompt(30, "�ਤ����R�A�_��A�˰h�@��");
				player.nextPosition(-1);
				break;

			case 33:
				prompt(30, "���ѬO�P����A���ѬO�P���@�A���Q����A�˰h���");
				player.nextPosition(-2);
				break;

			case 34:
				prompt(30, "�b�Ǯճ��Ӹ�~�ݷϤ��A�Q�϶��A�˰h���");
				player.nextPosition(-2);
				break;

			case 35:
				prompt(30, "�_�ɰ{��y�A�˰h���");
				player.nextPosition(-2);
				break;

			case 36:
				prompt(30, "�J�����N�ǰ|�f�l�A�`�ۡA�˰h�T��");
				player.nextPosition(-3);
				break;

			case 37:
				prompt(30, "�o�참��ñ�W�A�p���ýġA�e�i�@��");
				player.nextPosition(1);
				break;

			case 38:
				prompt(30, "���ѬO�P�����A���ѬO�P�����A�C�A�e�i���");
				player.nextPosition(2);
				break;

			case 39:
				prompt(30, "�M�k����ѡA�믫�ʭ��e�i�T��");
				player.nextPosition(3);
				break;

			case 40:
				prompt(30, "�����o�j�]�A���i�����A�e�i�T��");
				player.nextPosition(3);
				break;

			case 41:
				prompt(30, "�U�B�ѷƭˡA�H�i�v�y�A�e�i����");
				player.nextPosition(5);
				break;

			case 42:
				prompt(30, "��A�����800���ءA�e�i�K��");
				player.nextPosition(8);
				break;

				/* �]���ܤ� */

			case 43:
				prompt(30, "��I�d�šA3000��");
				player.bank(-3000);
				break;

			case 44:
				prompt(30, "�Ƿ|��ꤣ�p�Ƿ|��L�A���Į��S�G��10000��");
				player.cash(-10000);
				break;

			case 45:
				prompt(30, "�{�M�ۤv�ण�O�]���D�A�Y�@�H���ؤ���A��O1000��");
				player.cash(-1000);
				break;

			case 46:
				prompt(30, "�l�P�A����R�ּ֡A�t�۷|����500��");
				player.cash(-500);
				break;

			case 47:
				prompt(30, "�T�_�W���A�����ĶO1000��");
				player.cash(-1000);
				break;

			case 48:
				prompt(30, "���L�x���A�S���W�I�W�A�٦���W�t�@��600��");
				player.cash(-600);
				break;

			case 49:
				prompt(30, "�@�ӤH�ݹq�v�A���F�A��100���R�åͯ�");
				player.cash(-100);
				break;

			case 50:
				prompt(30, "����l�Q�~��A�����200��");
				player.cash(-200);
				break;

			case 51:
				prompt(30, "�M�T�_�E�P�I���A��o�z��1000��");
				player.cash(1000);
				break;

			case 52:
				prompt(30, "�B�����N�A���D��300��");
				player.cash(300);
				break;

			case 53:
				prompt(30, "�ߤW����ı���l�尭�A�浹�ժ��]�A�o3000��");
				player.cash(3000);
				break;

			case 54:
				prompt(30, "��ݨ���{���A�o��300��");
				player.cash(300);
				break;

			case 55:
				prompt(30, "�s�~�R�����֡A����500��");
				player.cash(500);
				break;

			case 56:
				prompt(30, "���\���u�A�o�~��500��");
				player.cash(500);
				break;

			case 57:
				prompt(30, "��x�A�o5000��");
				player.cash(5000);
				break;

			case 58:
				prompt(30, "���W�����A���Ǫ�1000��");
				player.cash(1000);
				break;

			case 59:
				prompt(30, "�ͬ��p�T���A�o������100��");
				player.cash(100);
				break;

			case 60:
				prompt(30, "�}��W�n���A�ߨ�100��");
				player.cash(100);
				break;

			default:
				break;
			}

			return true;
		}
		return false;
	};

	/* �P�_���� */
	inline bool Barrier(Player& player)
	{
		int playerPlace = players[gameData.turn].getState().position; // ���a���e�a�I

		if (gameData.building[playerPlace].barrier == true)
		{
			player.stop = true;
			prompt(30, "�g�L���ٳB�A�𮧤@�^�X");
			return true;
		}

		return false;
	}

	inline int getNumber()
	{
		string str;
		cin >> str;

		stringstream ss(str);
		regex numeric("[0-9]+");
		if (regex_match(str, numeric))
		{
			int temp;
			ss >> temp;
			return temp;
		}

		else
		{
			return -1;
		}
	}
}



/*gameBrand*/
/*
cout << "����������������������������������������������������������������������������������������������������������������������������������" << '\n';
cout << "��              ��              ��              ��              ��              ��              ��              ��              ��" << '\n';
cout << "��              ��              ��              ��              ��              ��              ��              ��              ��" << '\n';
cout << "��              ��              ��              ��              ��              ��              ��              ��              ��" << '\n';
cout << "��              ��              ��              ��              ��              ��              ��              ��              ��" << '\n';
cout << "����������������������������������������������������������������������������������������������������������������������������������" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "������������������                                                                                              ������������������" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "������������������                                                                                              ������������������" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "������������������                                                                                              ������������������" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "������������������                                                                                              ������������������" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "������������������                                                                                              ������������������" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "��              ��                                                                                              ��              ��" << '\n';
cout << "����������������������������������������������������������������������������������������������������������������������������������" << '\n';
cout << "��              ��              ��              ��              ��              ��              ��              ��              ��" << '\n';
cout << "��              ��              ��              ��              ��              ��              ��              ��              ��" << '\n';
cout << "��              ��              ��              ��              ��              ��              ��              ��              ��" << '\n';
cout << "��              ��              ��              ��              ��              ��              ��              ��              ��" << '\n';
cout << "����������������������������������������������������������������������������������������������������������������������������������" << '\n';
*/