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
	vector<Estate> own;//¾Ö¦³¦a²£
}Player;

typedef struct{
	string mapName;
	short remainingRound, playerNum, turn;
	Building building[28];
	Player player[4];
}GameData;

namespace System
{
	GameData gameData;
	
	bool mapStatus();
	bool gameStatus();
	bool playerStatus();
	int dice();
	bool merchandise();
	bool readFile();

	/* ¦a¹Ïª«¥óª¬ºA */
	bool mapStatus()
	{
		enum Play { player1 = 0, player2, player3, player4};
		int buildingColor[28];
		memset(buildingColor, -1, 28 * sizeof(int));
		function<void(int i)> coutName[] = {
			[](int i) -> void {		//³]¬°ª±®a1©³¦â
				Cmder::setColor(CLI_BACK_BLUE | CLI_BACK_LIGHT);
				cout << gameData.building[i].name;
			},

			[](int i) -> void {       //³]¬°ª±®a2©³¦â
				Cmder::setColor(CLI_BACK_GREEN | CLI_BACK_LIGHT);
				cout << gameData.building[i].name;
			},

			[](int i) -> void {       //³]¬°ª±®a3©³¦â
				Cmder::setColor(CLI_BACK_YELLOW | CLI_BACK_LIGHT);
				cout << gameData.building[i].name;
			},

			[](int i) -> void {       //³]¬°ª±®a3©³¦â
				Cmder::setColor(CLI_BACK_RED | CLI_BACK_LIGHT);
				cout << gameData.building[i].name;
			},

			[](int i) -> void {       //µL¤H¾Ö¦³
				Cmder::setColor();
				cout << gameData.building[i].name;
			},
		};

		function<void(short x, short y, short order)> coutBuilding = [&](short x, short y, short order) -> void {       
			Cmder::setColor();
			Cmder::setCursor(COORD{ x, y });
			cout << order;

			Cmder::setCursor(COORD{ x, y + 1 });
			(buildingColor[order] != -1) ? coutName[buildingColor[order]](order) : coutName[4](order);

			Cmder::setColor();
			Cmder::setCursor(COORD{ x, y + 2 });
			if (gameData.building[order].owner != -1)
				cout << "Level: " << gameData.building[order].level;

			Cmder::setCursor(COORD{ x, y + 3 });
			cout << "             ";
			Cmder::setCursor(COORD{ x, y + 3 });
			for (int i = 0, count = 0; i < 4; i++)
			{
				if (gameData.player[i].position == order)
				{
					if(count == 0)
						cout << "Player: ";
					cout << i + 1;
					count++;
				}
			}
		};
	

		for (int player = player1; player < 4; player++)//Åª¨ú¦Uª±®a¾Ö¦³«Ø¿v
		{
			for (int ownNum = 0; ownNum < gameData.player[player].own.size(); ownNum++)
			{
				buildingColor[gameData.player[player].own[ownNum].position] = player;
			}
		}

		for (short i = 0; i < 7; i++)
		{
			coutBuilding(2, 1 + 5 * i, i);
			coutBuilding(2 + 15 * i, 36, i + 7);
			coutBuilding(107, 36 - 5 * i, i + 14);
			coutBuilding(107 - 15 * i, 1, i + 21);
		}
		return 1;
	}

	/* ¹CÀ¸ª¬ºA */
	inline bool gameStatus()
	{
		Cmder::setCursor(COORD{ 20, 7 });
		cout << "·í«e¦^¦X: " << 21 - gameData.remainingRound;
		Cmder::setCursor(COORD{ 40, 7 });
		cout << "½ü¨ì²Ä " << gameData.turn + 1 << " ¦ìª±®a";
		return 1;
	}

	/* ¤Hª«ª¬ºA */
	inline bool playerStatus()
	{
		function<void()> nameColor[] = {
			[]() -> void {		//³]¬°ª±®a1©³¦â
				Cmder::setColor(CLI_BACK_BLUE | CLI_BACK_LIGHT);
			},

			[]() -> void {       //³]¬°ª±®a2©³¦â
				Cmder::setColor(CLI_BACK_GREEN | CLI_BACK_LIGHT);
			},

			[]() -> void {       //³]¬°ª±®a3©³¦â
				Cmder::setColor(CLI_BACK_YELLOW | CLI_BACK_LIGHT);
			},

			[]() -> void {       //³]¬°ª±®a3©³¦â
				Cmder::setColor(CLI_BACK_RED | CLI_BACK_LIGHT);
			},
		};
		for (short i = 0; i < 4; i++)
		{
			Cmder::setCursor(COORD{ 123, 1 + 10 * i });
			nameColor[i]();
			cout << "ª±®a" << i + 1;
			Cmder::setColor();
			Cmder::setCursor(COORD{ 123, 2 + 10 * i });
			cout << "¾Ö¦³ª÷¿ú: " << gameData.player[i].money;
		}
		return 1;
	}

	/* ÂY»ë¤l */
	int dice()
	{
		function<void()> diceNum[] = {
			[]() -> void {	
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "      ¡´      ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 30 }); cout << "              ";
			},

			[]() -> void {       
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "   ¡´         ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "         ¡´   ";
				Cmder::setCursor(COORD{ 85, 30 }); cout << "              ";
			},

			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "   ¡´         ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "      ¡´      ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "         ¡´   ";
				Cmder::setCursor(COORD{ 85, 30 }); cout << "              ";
			},

			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "   ¡´    ¡´   ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "   ¡´    ¡´   ";
				Cmder::setCursor(COORD{ 85, 30 }); cout << "              ";
			},

			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "   ¡´    ¡´   ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "      ¡´      ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "   ¡´    ¡´   ";
				Cmder::setCursor(COORD{ 85, 30 }); cout << "              ";
			},

			[]() -> void {       
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "   ¡´    ¡´   ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "   ¡´    ¡´   ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "   ¡´    ¡´   ";
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

	/* ¶R½æ¦a²£ */
	bool merchandise()
	{
		mapStatus();
		int playerPlace = gameData.player[gameData.turn].position;/* ª±®a·í«e¦aÂI */

		if (gameData.building[playerPlace].owner == -1 && gameData.building[playerPlace].type == 1)//¸Ó¦aÂI¨S¥D¤H¥B¥i¥HÁÊ¶R
		{
			if (checkYesOrNo(40, "¬O§_­nªá" + to_string(gameData.building[playerPlace].initialPrice) + "ÁÊ¶R¤g¦a?"))
			{
				gameData.building[playerPlace].owner = gameData.turn;//Âà²¾¦a¥D
				gameData.player[gameData.turn].money -= gameData.building[playerPlace].initialPrice;//ª±®a¥I¿ú

				Estate temp;//¬ö¿ýª±®a¦a²£
				temp.position = playerPlace;
				temp.level = 0;
				gameData.player[gameData.turn].own.push_back(temp);
			}
		}
		else if (gameData.building[playerPlace].owner == gameData.turn )//ª±®a¬°¦aÂIªº¥D¤H
		{
			if (gameData.building[playerPlace].level < 3)
			{
				if (checkYesOrNo(40, "¬O§_­nªá" + to_string(gameData.building[playerPlace].initialPrice) + "¤É¯Å«Ø¿v?"))
				{
					gameData.building[playerPlace].level++;//«Ø¿vª«¤É¯Å
					gameData.player[gameData.turn].money -= gameData.building[playerPlace].initialPrice;//ª±®a¥I¿ú

					for (int ownNum = 0; ownNum < gameData.player[gameData.turn].own.size(); ownNum++)//ª±®a¸Ó¦a²£¤É¯Å
					{
						if (gameData.player[gameData.turn].own[ownNum].position == playerPlace)
							gameData.player[gameData.turn].own[ownNum].level++;
					}
				}
			}
			else
			{
				prompt(43, "¸Ó¤g¦a§A¤w¸g¤Éº¡!");
			}
		}
		else if (gameData.building[playerPlace].owner >= 0)//¸Ó¦aÂI¦³¨ä¥L¥D¤H
		{
			prompt(43, "§A³Q¦©¤F" + to_string(gameData.building[playerPlace].price[gameData.building[playerPlace].level]) + "¤¸");
			gameData.player[gameData.turn].money -= gameData.building[playerPlace].price[gameData.building[playerPlace].level];//ª±®a¥I¹L¸ô¶O
			gameData.player[gameData.building[playerPlace].owner].money += gameData.building[playerPlace].price[gameData.building[playerPlace].level];
		}
		return 1;
	}

	/* Åª¨ú¬ö¿ý */
	bool readFile()
	{
		string null;
		fstream file;
		int position = 0;
		file.open("basemap.txt", ios::in);
		file >> gameData.mapName >> gameData.remainingRound >> gameData.playerNum;//Åª¨ú¦a¹Ï¦WºÙ ³Ñ¾l¦^¦X¼Æ Á`ª±®a¤H¼Æ
		for (int i = 0; i < 28; i++)//Åª¨ú¨C­Ó¦a²£ª«¥ó¸ê°T
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
		file >> null >> gameData.turn;//Åª¨ú½ü¨ì²Ä´X¤H
		for (int i = 0; i < 4; i++)//Åª¨úª±®a ©Ò¦b¦ì¸m ¾Ö¦³ª÷¿ú ©Ò¦³¦a²£¸òµ¥¯Å
		{
			string input, token;
			int c = 0, num, x;
			file >> num;
			getline(file, input);
			istringstream delim(input);//±N¥´¦nªºªF¦è©ñ¨ì¦r¦êdelim¸Ì,¥]§tªÅ¥Õ
			//getline(delim, token, ' ') getline(delim[¨Ó·½¦ì¸m],token[¦s¤J¦ì¸m],'¡@'[¤À³Îªº±ø¥ó])
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
cout << "ùÝùùùùùùùùùùùùùùùÞùùùùùùùùùùùùùùùÞùùùùùùùùùùùùùùùÞùùùùùùùùùùùùùùùÞùùùùùùùùùùùùùùùÞùùùùùùùùùùùùùùùÞùùùùùùùùùùùùùùùÞùùùùùùùùùùùùùùùß" << '\n';
cout << "ùø              ùø              ùø              ùø              ùø              ùø              ùø              ùø              ùø" << '\n';
cout << "ùø              ùø              ùø              ùø              ùø              ùø              ùø              ùø              ùø" << '\n';
cout << "ùø              ùø              ùø              ùø              ùø              ùø              ùø              ùø              ùø" << '\n';
cout << "ùø              ùø              ùø              ùø              ùø              ùø              ùø              ùø              ùø" << '\n';
cout << "ùàùùùùùùùùùùùùùùùáùùùùùùùùùùùùùùùäùùùùùùùùùùùùùùùäùùùùùùùùùùùùùùùäùùùùùùùùùùùùùùùäùùùùùùùùùùùùùùùäùùùùùùùùùùùùùùùáùùùùùùùùùùùùùùùâ" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùàùùùùùùùùùùùùùùùâ                                                                                              ùàùùùùùùùùùùùùùùùâ" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùàùùùùùùùùùùùùùùùâ                                                                                              ùàùùùùùùùùùùùùùùùâ" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùàùùùùùùùùùùùùùùùâ                                                                                              ùàùùùùùùùùùùùùùùùâ" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùàùùùùùùùùùùùùùùùâ                                                                                              ùàùùùùùùùùùùùùùùùâ" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùàùùùùùùùùùùùùùùùâ                                                                                              ùàùùùùùùùùùùùùùùùâ" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùø              ùø                                                                                              ùø              ùø" << '\n';
cout << "ùàùùùùùùùùùùùùùùùáùùùùùùùùùùùùùùùÞùùùùùùùùùùùùùùùÞùùùùùùùùùùùùùùùÞùùùùùùùùùùùùùùùÞùùùùùùùùùùùùùùùÞùùùùùùùùùùùùùùùáùùùùùùùùùùùùùùùâ" << '\n';
cout << "ùø              ùø              ùø              ùø              ùø              ùø              ùø              ùø              ùø" << '\n';
cout << "ùø              ùø              ùø              ùø              ùø              ùø              ùø              ùø              ùø" << '\n';
cout << "ùø              ùø              ùø              ùø              ùø              ùø              ùø              ùø              ùø" << '\n';
cout << "ùø              ùø              ùø              ùø              ùø              ùø              ùø              ùø              ùø" << '\n';
cout << "ùãùùùùùùùùùùùùùùùäùùùùùùùùùùùùùùùäùùùùùùùùùùùùùùùäùùùùùùùùùùùùùùùäùùùùùùùùùùùùùùùäùùùùùùùùùùùùùùùäùùùùùùùùùùùùùùùäùùùùùùùùùùùùùùùå" << '\n';
*/