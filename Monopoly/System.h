#pragma once
#include "ConsoleInterface.h"
#include "Windows.h"
#include "Player.h"
#include "Bank.h"
#include <functional>
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <time.h>
using namespace std;
using namespace Windows;

typedef struct {
	string name;
	int initialPrice, type, owner = -1, level = 0;
	int price[4];
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


Player players[4];
Bank bank;

namespace
{
	enum Play { player1 = 0, player2, player3, player4 };

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

	bool mapStatus();
	bool gameStatus();
	bool playerStatus();
	int dice();
	bool merchandise();
	bool readFile();
	int getWealth(Player&);

	/* �a�Ϫ��󪬺A */
	bool mapStatus()
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
		cout << "��e�^�X: " << 21 - gameData.remainingRound;
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
	int dice()
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

		return 2;
	}

	/* �R��a�� */
	bool merchandise()
	{
		mapStatus();
		int playerPlace = players[gameData.turn].getState().position;/* ���a��e�a�I */

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

	/* Ū������ */
	bool readFile()
	{
		string null;
		fstream file;
		file.open("basemap.txt", ios::in);

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
			int price = gameData.building[house.first].initialPrice * house.second;
			total += price;
		}
		player.wealth = total;
		return total;
	};
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