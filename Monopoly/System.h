#pragma once
#include "ConsoleInterface.h"
#include <functional>
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
using namespace std;

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
	vector<Estate> own;
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
	//bool start();
	//bool game();
	//bool startBrand();
	bool mapBrand();
	bool mapStatus();
	bool gameStatus();
	bool playerBrand();
	bool playerStatus();
	int dice();
	bool merchandise();
	bool readFile();

	/* ¹Cְ¸µe­±°ע©³ */
	inline bool mapBrand()
	{
		string option[] = { "¸פ¹L»ָ¦ז" , "×ׁ²¼¶R½ז" , "¨ֿ¥־¹D¨ד" , "₪g¦a¥X°ג" , "¥D¿ן³ז" , "µ²§פ¦^¦X" };
		system("COLOR 07");
		cout << "שÝשששששששששששששששששששששששששששששÞשששששששששששששששששששששששששששששÞשששששששששששששששששששששששששששששÞשששששששששששששששששששששששששששששÞשששששששששששששששששששששששששששששÞשששששששששששששששששששששששששששששÞשששששששששששששששששששששששששששששÞשששששששששששששששששששששששששששששß" << '\n';
		cout << "שר              שר              שר              שר              שר              שר              שר              שר              שר" << '\n';
		cout << "שר              שר              שר              שר              שר              שר              שר              שר              שר" << '\n';
		cout << "שר              שר              שר              שר              שר              שר              שר              שר              שר" << '\n';
		cout << "שר              שר              שר              שר              שר              שר              שר              שר              שר" << '\n';
		cout << "שאשששששששששששששששששששששששששששששבשששששששששששששששששששששששששששששהשששששששששששששששששששששששששששששהשששששששששששששששששששששששששששששהשששששששששששששששששששששששששששששהשששששששששששששששששששששששששששששהשששששששששששששששששששששששששששששבשששששששששששששששששששששששששששששג" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שאשששששששששששששששששששששששששששששג                                                                                         שאשששששששששששששששששששששששששששששג" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שאשששששששששששששששששששששששששששששג                                                                                         שאשששששששששששששששששששששששששששששג" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שאשששששששששששששששששששששששששששששג                                                                                         שאשששששששששששששששששששששששששששששג" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שאשששששששששששששששששששששששששששששג                                                                                         שאשששששששששששששששששששששששששששששג" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שאשששששששששששששששששששששששששששששג                                                                                         שאשששששששששששששששששששששששששששששג" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שר              שר                                                                                         שר              שר" << '\n';
		cout << "שאשששששששששששששששששששששששששששששבשששששששששששששששששששששששששששששÞשששששששששששששששששששששששששששששÞשששששששששששששששששששששששששששששÞשששששששששששששששששששששששששששששÞשששששששששששששששששששששששששששששÞשששששששששששששששששששששששששששששבשששששששששששששששששששששששששששששג" << '\n';
		cout << "שר              שר              שר              שר              שר              שר              שר              שר              שר" << '\n';
		cout << "שר              שר              שר              שר              שר              שר              שר              שר              שר" << '\n';
		cout << "שר              שר              שר              שר              שר              שר              שר              שר              שר" << '\n';
		cout << "שר              שר              שר              שר              שר              שר              שר              שר              שר" << '\n';
		cout << "שדשששששששששששששששששששששששששששששהשששששששששששששששששששששששששששששהשששששששששששששששששששששששששששששהשששששששששששששששששששששששששששששהשששששששששששששששששששששששששששששהשששששששששששששששששששששששששששששהשששששששששששששששששששששששששששששהשששששששששששששששששששששששששששששו" << '\n';
		for (short i = 0; i < 6; i++)
		{
			Cmder::setCursor(COORD{ 91, 9 + 2 * i });
			cout << option[i];
		}
		return 1;
	}

	/* ¦a¹ֿ×«¥ף×¬÷A */
	bool mapStatus()
	{
		enum Play { player1 = 0, player2, player3, player4};
		int buildingColor[28];
		memset(buildingColor, -1, 28 * sizeof(int));
		function<void(int i)> coutName[] = {
			[](int i) -> void {		//³]¬°×±®a1©³¦ג
				Cmder::setColor(CLI_BACK_BLUE | CLI_BACK_LIGHT);
				cout << gameData.building[i].name;
			},

			[](int i) -> void {       //³]¬°×±®a2©³¦ג
				Cmder::setColor(CLI_BACK_GREEN | CLI_BACK_LIGHT);
				cout << gameData.building[i].name;
			},

			[](int i) -> void {       //³]¬°×±®a3©³¦ג
				Cmder::setColor(CLI_BACK_YELLOW | CLI_BACK_LIGHT);
				cout << gameData.building[i].name;
			},

			[](int i) -> void {       //³]¬°×±®a3©³¦ג
				Cmder::setColor(CLI_BACK_RED | CLI_BACK_LIGHT);
				cout << gameData.building[i].name;
			},

			[](int i) -> void {       //µL₪H¾ײ¦³
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
	

		for (int player = player1; player < 4; player++)//ֵ×¨ת¦U×±®a¾ײ¦³«״¿v
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

	/* ¹Cְ¸×¬÷A */
	inline bool gameStatus()
	{
		Cmder::setCursor(COORD{ 20, 7 });
		cout << "·ם«e¦^¦X: " << 21 - gameData.remainingRound;
		Cmder::setCursor(COORD{ 40, 7 });
		cout << "½ü¨ל²ִ " << gameData.turn + 1 << " ¦ל×±®a";
		return 1;
	}

	/* ₪H×«×¬÷Aµe­±°ע©³ */
	inline bool playerBrand()
	{
		system("COLOR 07");
		for (SHORT i = 0; i < 5; i++)
		{
			Cmder::setCursor(COORD{ 121, 0 + 10 * i });
			cout << "שששששששששששששששששששששששששששששששששששששששששששששששששששששששש";
			if (i == 0)
				cout << "שß";
			else if (i == 4)
				cout << "שו";
			else
				cout << "שג";
		}

		for (SHORT i = 0; i < 4; i++)
		{
			for (SHORT j = 0; j < 9; j++)
			{
				Cmder::setCursor(COORD{ 149, 1 + 10 * i + j });
				cout << "שר";
			}
		}

		return 1;
	}

	/* ₪H×«×¬÷A */
	inline bool playerStatus()
	{
		function<void()> nameColor[] = {
			[]() -> void {		//³]¬°×±®a1©³¦ג
				Cmder::setColor(CLI_BACK_BLUE | CLI_BACK_LIGHT);
			},

			[]() -> void {       //³]¬°×±®a2©³¦ג
				Cmder::setColor(CLI_BACK_GREEN | CLI_BACK_LIGHT);
			},

			[]() -> void {       //³]¬°×±®a3©³¦ג
				Cmder::setColor(CLI_BACK_YELLOW | CLI_BACK_LIGHT);
			},

			[]() -> void {       //³]¬°×±®a3©³¦ג
				Cmder::setColor(CLI_BACK_RED | CLI_BACK_LIGHT);
			},
		};
		for (short i = 0; i < 4; i++)
		{
			Cmder::setCursor(COORD{ 123, 1 + 10 * i });
			nameColor[i]();
			cout << "×±®a" << i + 1;
			Cmder::setColor();
			Cmder::setCursor(COORD{ 123, 2 + 10 * i });
			cout << "¾ײ¦³×ק¿ת: " << gameData.player[i].money;
		}
		return 1;
	}

	/* ֲY»כ₪l */
	int dice()
	{
		function<void()> diceNum[] = {
			[]() -> void {	
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 24, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 25 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 27 }); cout << "      ¡´      ";
				Cmder::setCursor(COORD{ 24, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 29 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 30 }); cout << "              ";
			},

			[]() -> void {       
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 24, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 25 }); cout << "   ¡´         ";
				Cmder::setCursor(COORD{ 24, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 27 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 29 }); cout << "         ¡´   ";
				Cmder::setCursor(COORD{ 24, 30 }); cout << "              ";
			},

			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 24, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 25 }); cout << "   ¡´         ";
				Cmder::setCursor(COORD{ 24, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 27 }); cout << "      ¡´      ";
				Cmder::setCursor(COORD{ 24, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 29 }); cout << "         ¡´   ";
				Cmder::setCursor(COORD{ 24, 30 }); cout << "              ";
			},

			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 24, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 25 }); cout << "   ¡´    ¡´   ";
				Cmder::setCursor(COORD{ 24, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 27 }); cout << "              "; 
				Cmder::setCursor(COORD{ 24, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 29 }); cout << "   ¡´    ¡´   ";
				Cmder::setCursor(COORD{ 24, 30 }); cout << "              ";
			},

			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 24, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 25 }); cout << "   ¡´    ¡´   ";
				Cmder::setCursor(COORD{ 24, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 27 }); cout << "      ¡´      ";
				Cmder::setCursor(COORD{ 24, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 29 }); cout << "   ¡´    ¡´   ";
				Cmder::setCursor(COORD{ 24, 30 }); cout << "              ";
			},

			[]() -> void {       
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 24, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 25 }); cout << "   ¡´    ¡´   ";
				Cmder::setCursor(COORD{ 24, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 27 }); cout << "   ¡´    ¡´   ";
				Cmder::setCursor(COORD{ 24, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 24, 29 }); cout << "   ¡´    ¡´   ";
				Cmder::setCursor(COORD{ 24, 30 }); cout << "              ";
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

		return result;
	}

	/* ¶R½ז¦a²£ */
	bool merchandise()
	{
		int playerPlace = gameData.player[gameData.turn].position;/* ×±®a·ם«e¦aֲI */

		if (gameData.building[playerPlace].owner == -1)
		{
			gameData.building[playerPlace].owner = gameData.turn;//ֲא²¾¦a¥D
			gameData.player[gameData.turn].money -= gameData.building[playerPlace].initialPrice;//×±®a¥I¿ת

			Estate temp;//¬צ¿‎×±®a¦a²£
			temp.position = playerPlace;
			temp.level = 0;
			gameData.player[gameData.turn].own.push_back(temp);
		}
		else if (gameData.building[playerPlace].owner == gameData.turn)
		{
			if (gameData.building[playerPlace].level < 3)
			{
				gameData.building[playerPlace].level++;//«״¿v×«₪ֹ¯ֵ
				gameData.player[gameData.turn].money -= gameData.building[playerPlace].initialPrice;//×±®a¥I¿ת

				for (int ownNum = 0; ownNum < gameData.player[gameData.turn].own.size(); ownNum++)//×±®a¸׃¦a²£₪ֹ¯ֵ
				{
					if(gameData.player[gameData.turn].own[ownNum].position = playerPlace)
						gameData.player[gameData.turn].own[ownNum].level++;
				}
			}
		}
		else if (gameData.building[playerPlace].owner >= 0)
		{
			gameData.player[gameData.turn].money -= gameData.building[playerPlace].price[gameData.building[playerPlace].level];//×±®a¥I¹L¸פ¶O
			gameData.player[gameData.building[playerPlace].owner].money += gameData.building[playerPlace].price[gameData.building[playerPlace].level];
		}
		return 1;
	}

	/* ֵ×¨ת¬צ¿‎ */
	bool readFile()
	{
		string null;
		fstream file;
		int position = 0;
		file.open("basemap.txt", ios::in);
		file >> gameData.mapName >> gameData.remainingRound >> gameData.playerNum;//ֵ×¨ת¦a¹ֿ¦W÷Ù ³ׁ¾l¦^¦X¼ֶ ֱ`×±®a₪H¼ֶ
		for (int i = 0; i < 28; i++)//ֵ×¨ת¨C­׃¦a²£×«¥ף¸ך°T
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
		file >> null >> gameData.turn;//ֵ×¨ת½ü¨ל²ִ´X₪H
		for (int i = 0; i < 4; i++)//ֵ×¨ת×±®a ©ׂ¦b¦ל¸m ¾ײ¦³×ק¿ת ©ׂ¦³¦a²£¸עµ¥¯ֵ
		{
			string input, token;
			int c = 0, num, x;
			file >> num;
			getline(file, input);
			istringstream delim(input);//±N¥´¦n×÷×F¦ט©ס¨ל¦r¦ךdelim¸ּ,¥]§t×ֵ¥ױ
			//getline(delim, token, ' ') getline(delim[¨׃·½¦ל¸m],token[¦s₪J¦ל¸m],'¡@'[₪ְ³־×÷±ר¥ף])
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
cout << "שÝשששששששששששששששÞשששששששששששששששÞשששששששששששששששÞשששששששששששששששÞשששששששששששששששÞשששששששששששששששÞשששששששששששששששÞשששששששששששששששß" << '\n';
cout << "שר              שר              שר              שר              שר              שר              שר              שר              שר" << '\n';
cout << "שר              שר              שר              שר              שר              שר              שר              שר              שר" << '\n';
cout << "שר              שר              שר              שר              שר              שר              שר              שר              שר" << '\n';
cout << "שר              שר              שר              שר              שר              שר              שר              שר              שר" << '\n';
cout << "שאשששששששששששששששבשששששששששששששששהשששששששששששששששהשששששששששששששששהשששששששששששששששהשששששששששששששששהשששששששששששששששבשששששששששששששששג" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שאשששששששששששששששג                                                                                              שאשששששששששששששששג" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שאשששששששששששששששג                                                                                              שאשששששששששששששששג" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שאשששששששששששששששג                                                                                              שאשששששששששששששששג" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שאשששששששששששששששג                                                                                              שאשששששששששששששששג" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שאשששששששששששששששג                                                                                              שאשששששששששששששששג" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שר              שר                                                                                              שר              שר" << '\n';
cout << "שאשששששששששששששששבשששששששששששששששÞשששששששששששששששÞשששששששששששששששÞשששששששששששששששÞשששששששששששששששÞשששששששששששששששבשששששששששששששששג" << '\n';
cout << "שר              שר              שר              שר              שר              שר              שר              שר              שר" << '\n';
cout << "שר              שר              שר              שר              שר              שר              שר              שר              שר" << '\n';
cout << "שר              שר              שר              שר              שר              שר              שר              שר              שר" << '\n';
cout << "שר              שר              שר              שר              שר              שר              שר              שר              שר" << '\n';
cout << "שדשששששששששששששששהשששששששששששששששהשששששששששששששששהשששששששששששששששהשששששששששששששששהשששששששששששששששהשששששששששששששששהשששששששששששששששו" << '\n';
*/