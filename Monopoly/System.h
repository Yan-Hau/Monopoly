#pragma once
#include "ConsoleInterface.h"
#include "Windows.h"
#include <functional>
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
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

typedef struct {
	short position;
	int money;
	vector<Estate> own;//�֦��a��
}Player;

typedef struct{
	string mapName;
	short remainingRound, playerNum, turn;
	Building building[28];
	Player player[4];
}GameData;

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

	/* �a�Ϫ��󪬺A */
	bool mapStatus()
	{
		function<void(short x, short y, short order)> coutBuilding = [&](short x, short y, short order) -> void {       
			Cmder::setColor();
			Cmder::setCursor(COORD{ x, y });
			cout << order;

			Cmder::setCursor(COORD{ x, y + 1 });
			(gameData.building[order].owner != -1) ? nameColor[gameData.building[order].owner]() : nameColor[4]();
			cout << gameData.building[order].name;

			Cmder::setColor();
			Cmder::setCursor(COORD{ x, y + 2 });
			if (gameData.building[order].owner != -1)
				cout << "Level: " << gameData.building[order].level;

			Cmder::setCursor(COORD{ x, y + 3 });
			cout << "             ";
			Cmder::setCursor(COORD{ x, y + 3 });
			for (int player = player1, count = 0; player <= player4; player++)
			{
				if (gameData.player[player].position == order)
				{
					if(count == 0)
						cout << "Player: ";
					nameColor[player]();
					cout << player + 1;
					count++;
				}
			}
		};
	
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
		return 1;
	}

	/* �H�����A */
	inline bool playerStatus()
	{
		for (short i = player1; i <= player4; i++)
		{
			Cmder::setCursor(COORD{ 123, 1 + 10 * i });
			nameColor[i]();
			cout << "���a" << i + 1;
			Cmder::setColor();
			Cmder::setCursor(COORD{ 123, 2 + 10 * i });
			cout << "�֦�����: " << gameData.player[i].money;
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
			Sleep(50);
		}
		diceNum[result - 1]();

		return 2;
	}

	/* �R��a�� */
	bool merchandise()
	{
		mapStatus();
		int playerPlace = gameData.player[gameData.turn].position;/* ���a��e�a�I */

		if (gameData.building[playerPlace].owner == -1 && gameData.building[playerPlace].type == 1)//�Ӧa�I�S�D�H�B�i�H�ʶR
		{
			if (checkYesOrNo(40, "�O�_�n��" + to_string(gameData.building[playerPlace].initialPrice) + "�ʶR�g�a?"))
			{
				gameData.building[playerPlace].owner = gameData.turn;//�ಾ�a�D
				gameData.player[gameData.turn].money -= gameData.building[playerPlace].initialPrice;//���a�I��

				Estate temp;//�������a�a��
				temp.position = playerPlace;
				temp.level = 0;
				gameData.player[gameData.turn].own.push_back(temp);
			}
		}
		else if (gameData.building[playerPlace].owner == gameData.turn )//���a���a�I���D�H
		{
			if (gameData.building[playerPlace].level < 3)
			{
				if (checkYesOrNo(40, "�O�_�n��" + to_string(gameData.building[playerPlace].initialPrice) + "�ɯūؿv?"))
				{
					gameData.building[playerPlace].level++;//�ؿv���ɯ�
					gameData.player[gameData.turn].money -= gameData.building[playerPlace].initialPrice;//���a�I��

					for (int ownNum = 0; ownNum < gameData.player[gameData.turn].own.size(); ownNum++)//���a�Ӧa���ɯ�
					{
						if (gameData.player[gameData.turn].own[ownNum].position == playerPlace)
							gameData.player[gameData.turn].own[ownNum].level++;
					}
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
			gameData.player[gameData.turn].money -= gameData.building[playerPlace].price[gameData.building[playerPlace].level];//���a�I�L���O
			gameData.player[gameData.building[playerPlace].owner].money += gameData.building[playerPlace].price[gameData.building[playerPlace].level];
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
			istringstream delim(input);//�N���n���F����r��delim��,�]�t�ť�
			//getline(delim, token, ' ') getline(delim[�ӷ���m],token[�s�J��m],'�@'[���Ϊ�����])
			while (delim >> x)
			{
				if (c == 0)
					gameData.player[num].position = x;
				else if (c == 1)
					gameData.player[num].money = x;
				else
				{
					Estate temp;
					temp.position = x;
					gameData.building[temp.position].owner = num;
					delim >> x;
					temp.level = x;
					gameData.building[temp.position].level = temp.level;
					gameData.player[num].own.push_back(temp);
				}
				c++;
			}
		}

		return 1;
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