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
			[]() -> void {		//設為玩家1底色
				Cmder::setColor(CLI_BACK_BLUE | CLI_BACK_LIGHT);
			},

			[]() -> void {       //設為玩家2底色
				Cmder::setColor(CLI_BACK_GREEN | CLI_BACK_LIGHT);
			},

			[]() -> void {       //設為玩家3底色
				Cmder::setColor(CLI_BACK_YELLOW | CLI_BACK_LIGHT);
			},

			[]() -> void {       //設為玩家3底色
				Cmder::setColor(CLI_BACK_RED | CLI_BACK_LIGHT);
			},

			[]() -> void {       //無人擁有
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
	inline  int dice();
	inline bool merchandise();
	inline bool readFile(string);
	inline bool saveFile();
	inline void goBank();
	inline void transStock();
	inline void useCard();
	inline  int getWealth(Player&);
	inline  int getNumber();
	inline bool do_chance(Player&);
	inline bool Barrior(Player&);
	inline void saleEstate();

	/* 地圖物件狀態 */
	inline bool mapStatus()
	{
		function<void(short x, short y, short order)> coutBuilding = [&](short x, short y, short order) ->
			void {
			Cmder::setColor();
			Cmder::setCursor(COORD{ x, y });
			cout << order;

			/* 輸出房產 */
			Cmder::setCursor(COORD{ x, y + 1 });
			(gameData.building[order].owner != -1) ? nameColor[gameData.building[order].owner]() : nameColor[4]();
			cout << gameData.building[order].name;

			/* 輸出房產等級 */
			Cmder::setColor();
			Cmder::setCursor(COORD{ x, y + 2 });
			if (gameData.building[order].owner != -1)
				cout << "Level: " << gameData.building[order].level;

			/* 輸出玩家位置 */
			Cmder::setCursor(COORD{ x, y + 3 });
			cout << "             ";
			Cmder::setCursor(COORD{ x, y + 3 });
			for (int player = player1, count = 0; player <= player4; player++)
			{
				if (players[player].getState().position == order && !players[player].isEnd() && getWealth(players[player]) >= 0 )
				{
					if (count == 0)
						cout << "Player: ";
					nameColor[player]();
					cout << player + 1;
					count++;
				}
			}
		};

		/* 輸出地圖資訊 */
		for (short i = 0; i < 7; i++)
		{
			coutBuilding(2, 1 + 5 * i, i);
			coutBuilding(2 + 15 * i, 36, i + 7);
			coutBuilding(107, 36 - 5 * i, i + 14);
			coutBuilding(107 - 15 * i, 1, i + 21);
		}
		return 1;
	}

	/* 遊戲狀態 */
	inline bool gameStatus()
	{
		Cmder::setColor();
		Cmder::setCursor(COORD{ 20, 7 });
		cout << "當前回合: " << 21 - gameData.remainingRound;
		Cmder::setCursor(COORD{ 40, 7 });
		cout << "輪到 ";
		nameColor[gameData.turn]();
		cout << "玩家" << gameData.turn + 1;

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
			Cmder::setCursor(75, 6 + i);
			cout << names[i] << "股: " << Bank::Business[i] << "$ / 股";
		}
		return 1;
	}

	/* 人物狀態 */
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
			cout << "玩家" << setw(2) << i + 1;
			Cmder::setColor();

			Cmder::setCursor(COORD{ 123, 2 + 10 * i });
			cout << "擁有金錢: " << setw(2) << players[i].getState().money << " $";

			Cmder::setCursor(COORD{ 123, 3 + 10 * i });
			cout << "擁有存款: " << players[i].getState().despoit << " $";

			Cmder::setCursor(COORD{ 123, 4 + 10 * i });
			cout << "擁有股票A: " << players[i].getState().stock[0] << " 股";
																		 
			Cmder::setCursor(COORD{ 123, 5 + 10 * i });					 
			cout << "擁有股票B: " << players[i].getState().stock[1] << " 股";
																		 
			Cmder::setCursor(COORD{ 123, 6 + 10 * i });					 
			cout << "擁有股票C: " << players[i].getState().stock[2] << " 股";
																		 
			Cmder::setCursor(COORD{ 123, 7 + 10 * i });					 
			cout << "擁有股票D: " << players[i].getState().stock[3] << " 股";

			Cmder::setCursor(COORD{ 123, 8 + 10 * i });
			cout << "總債務: " << players[i].getState().debt << " $";

			Cmder::setCursor(COORD{ 123, 9 + 10 * i });
			cout << "總身價: " << getWealth(players[i]) << " $";
		}
		return 1;
	}

	/* 擲骰子 */
	inline int dice()
	{
		function<void()> diceNum[] = {
			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "      ●      ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 30 }); cout << "              ";
			},

			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "   ●         ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "         ●   ";
				Cmder::setCursor(COORD{ 85, 30 }); cout << "              ";
			},

			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "   ●         ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "      ●      ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "         ●   ";
				Cmder::setCursor(COORD{ 85, 30 }); cout << "              ";
			},

			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "   ●    ●   ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "   ●    ●   ";
				Cmder::setCursor(COORD{ 85, 30 }); cout << "              ";
			},

			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "   ●    ●   ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "      ●      ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "   ●    ●   ";
				Cmder::setCursor(COORD{ 85, 30 }); cout << "              ";
			},

			[]() -> void {
				Cmder::setColor(CLI_BACK_WHITE | CLI_BACK_LIGHT | CLI_FONT_RED | CLI_FONT_LIGHT);
				Cmder::setCursor(COORD{ 85, 24 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 25 }); cout << "   ●    ●   ";
				Cmder::setCursor(COORD{ 85, 26 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 27 }); cout << "   ●    ●   ";
				Cmder::setCursor(COORD{ 85, 28 }); cout << "              ";
				Cmder::setCursor(COORD{ 85, 29 }); cout << "   ●    ●   ";
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

	/* 買賣地產 */
	inline bool merchandise()
	{
		mapStatus();
		int playerPlace = players[gameData.turn].getState().position;/* 玩家當前地點 */

		if (gameData.building[playerPlace].owner == -1 && gameData.building[playerPlace].type == 1)//該地點沒主人且可以購買
		{
			if (checkYesOrNo(40, "是否要花" + to_string(gameData.building[playerPlace].initialPrice) + "購買土地?"))
			{
				gameData.building[playerPlace].owner = gameData.turn;//轉移地主
				players[gameData.turn].cash(-gameData.building[playerPlace].initialPrice);//玩家付錢

				
				players[gameData.turn].setEstate(playerPlace, 0);
			}
		}
		else if (gameData.building[playerPlace].owner == gameData.turn)//玩家為地點的主人
		{
			if (gameData.building[playerPlace].level < 3)
			{
				if (checkYesOrNo(40, "是否要花" + to_string(gameData.building[playerPlace].initialPrice) + "升級建築?"))
				{
					gameData.building[playerPlace].level++;//建築物升級
					players[gameData.turn].cash(-gameData.building[playerPlace].initialPrice);//玩家付錢
					int currentLevel = players[gameData.turn].getState().estate[playerPlace];
					players[gameData.turn].setEstate(playerPlace, currentLevel + 1);
				}
			}
			else
			{
				prompt(43, "該土地你已經升滿!");
			}
		}
		else if (gameData.building[playerPlace].owner >= 0)//該地點有其他主人
		{
			prompt(43, "你被扣了" + to_string(gameData.building[playerPlace].price[gameData.building[playerPlace].level]) + "元");
			int passValue = gameData.building[playerPlace].price[gameData.building[playerPlace].level];
			if(players[gameData.turn].money >= passValue)
				players[gameData.turn].cash(-passValue);//玩家付過路費(現金)

			else if (players[gameData.turn].despoit >= passValue)
				players[gameData.turn].bank(-passValue);//玩家付過路費(存款)

			else
				players[gameData.turn].owe(passValue);//玩家付過路費(借款)

			players[gameData.building[playerPlace].owner].cash(passValue);
		}
		return 1;
	}

	/* 存提款 */
	inline void goBank()
	{
		COORD optionPosition[] = { {20,9}, {20,11}, {20,13},{30,9} };
		string option[] = {
			"我要借款", "我要存款", "我要還款", "離開銀行"
		};

		/* 子選單 */
		auto print = [&]() -> void {
			for (int i = 0; i < 4; ++i)
			{
				Cmder::setCursor(optionPosition[i]);
				Cmder::setColor(CLI_FONT_WHITE);
				cout << option[i];
				Cmder::setCursor(optionPosition[i]);
			}
		};

		/* 子選單選擇 */
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
				/* 欠款 */
				int value = 0;
				COORD _pos = Cmder::getCursor();
				Cmder::setCursor(40,9);
				Cmder::setColor();
				cout << "請輸入金額 : ";
				value = getNumber();
				if (value > 0)
				{
					players[gameData.turn].owe(value);
					playerStatus();
				}
				else
				{
					Cmder::setCursor(40, 10);
					cout << "金額輸入為零、負數、非數字";
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
				/* 存款 */
				int value = 0;
				COORD _pos = Cmder::getCursor();
				Cmder::setCursor(40, 9);
				Cmder::setColor();
				cout << "請輸入金額 : ";
				value = getNumber();
				if (value > 0 && players[gameData.turn].money >= value)
				{
					players[gameData.turn].bank(value);
					players[gameData.turn].cash(-value);
					playerStatus();
				}
				else
				{
					Cmder::setCursor(40, 9);
					cout << "您沒有那麼多現金, 或是金額輸入為零、負數、非數字";
					_getch();
				}
				Cmder::setCursor(40, 9);
				printf("%50c", ' ');
				Cmder::setCursor(40, 9);
				printf("%50c", ' ');
				Cmder::setCursor(_pos);
				return 1;
			},

			[&]() -> int
			{
				/* 還款 */
				int value = 0;
				COORD _pos = Cmder::getCursor();
				Cmder::setCursor(40,9);
				Cmder::setColor();
				cout << "請輸入金額 : ";
				value = getNumber();
				if (value > 0 && players[gameData.turn].despoit >= value)
				{
					players[gameData.turn].owe(-value);
					playerStatus();
				}
				else
				{
					Cmder::setCursor(40, 9);
					cout << "您沒有那麼多存款, 或是金額輸入為零、負數、非數字";
					_getch();
				}
				Cmder::setCursor(40, 9);
				printf("%50c", ' ');
				Cmder::setCursor(40, 9);
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

			case Left:
			case Right:
				optionSet = (optionSet == 3) ? 0 : 3;
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

	/* 買賣股票*/
	inline void transStock()
	{
		COORD optionPosition[] = { {20,9}, {20,11}, {20,13} , {20,15} , {30,9}, {30,11}, {30,13} , {30,15} , {30,17} };
		string option[] = {
			"買進A股", "買進B股", "買進C股" , "買進D股",
			"賣出A股", "賣出B股", "賣出C股" , "賣出D股",
			"離開交易所",
		};

		/* 子選單 */
		auto print = [&]() -> void {
			for (int i = 0; i < 9; ++i)
			{
				Cmder::setCursor(optionPosition[i]);
				Cmder::setColor(CLI_FONT_WHITE);
				cout << option[i];
				Cmder::setCursor(optionPosition[i]);
			}
		};

		/* 子選單選擇 */
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
				Cmder::setCursor(40, 9);
				Cmder::setColor();
				cout << "請輸入購買股數: ";
				amount = getNumber();

				if (amount > 0 && players[gameData.turn].despoit >= amount * Bank::Business[stockNum])
				{
					players[gameData.turn].bank(-amount * Bank::Business[stockNum]);
					players[gameData.turn].stock[stockNum] += amount;
					playerStatus();
				}
				else
				{
					Cmder::setCursor(40, 10);
					cout << "您沒有那麼多存款, 或是股數輸入為零、負數、非數字";
					_getch();
				}
				Cmder::setCursor(40, 9);
				printf("%50c", ' ');
				Cmder::setCursor(40, 10);
				printf("%50c", ' ');
				Cmder::setCursor(_pos);
				return 1;
			},

			[&](int stockNum) -> int
			{
				int amount = -1;
				COORD _pos = Cmder::getCursor();
				Cmder::setCursor(40, 9);
				Cmder::setColor();
				cout << "請輸入賣出股數: ";
				amount = getNumber();

				if (amount > 0 && players[gameData.turn].stock[stockNum] >= amount)
				{
					players[gameData.turn].bank(amount * Bank::Business[stockNum]);
					players[gameData.turn].stock[stockNum] -= amount;
					playerStatus();
				}
				else
				{
					Cmder::setCursor(40, 10);
					cout << "您沒有那麼多股票, 或是股數輸入為零、負數、非數字";
					_getch();
				}
				Cmder::setCursor(40, 9);
				printf("%50c", ' ');
				Cmder::setCursor(40, 10);
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

	/* 使用道具 */
	inline void useCard()
	{
		Player& current = players[gameData.turn];
		enum keyboardValue { Up = 72, Down = 80, Left = 75, Right = 77, Enter = 13, Esc = 27 };
		COORD optionPosition[] = { {81,11}, {81,13}, {81,15}, {81, 17}, {81, 19} };
		string option[] = {
			"現金卡", "路障卡", "房屋卡", "免費卡", "不使用"
		};

		/* 子選單 */
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

		/* 子選單選擇 */
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
				if (optionSet == 4)		 //不使用
					loop = false;

				else if (players[gameData.turn].card[optionSet] > 0)
				{
					int playerPlace = players[gameData.turn].getState().position; // 玩家當前地點
					int passValue = gameData.building[playerPlace].price[gameData.building[playerPlace].level]; //過路費金額

					switch (optionSet)
					{
					case 0:				//現金卡
						for (int i = 0; i < 4; i++)
						{
							if (i != gameData.turn)
							{
								players[gameData.turn].cash(players[i].getState().money);
								players[i].setMoney(0);
							}
						}
						prompt(43, "已搜括所有玩家現金");
						players[gameData.turn].card[optionSet] -= 1;
						break;

					case 1:				//路障卡
						gameData.building[playerPlace].barrier = true;
						prompt(30, "強制所有人經過路障處時，休息一回合");
						players[gameData.turn].card[optionSet] -= 1;
						break;

					case 2:				//房屋卡
						for (int place = 0; place < 28; place++)
						{
							if (gameData.building[place].owner == gameData.turn && gameData.building[place].level < 3)
							{
								gameData.building[place].level++;//建築物升級
								int currentLevel = players[gameData.turn].getState().estate[place];
								players[gameData.turn].setEstate(place, currentLevel + 1);
							}
						}
						prompt(43, "已免費升級所有房屋");
						players[gameData.turn].card[optionSet] -= 1;
						break;

					case 3:				//免費卡
						if (gameData.building[playerPlace].owner == -1 || gameData.building[playerPlace].type == 1 || gameData.building[playerPlace].owner == gameData.turn)
							prompt(43, "不須使用免費卡");
						else
						{
							players[gameData.turn].cash(gameData.building[playerPlace].price[gameData.building[playerPlace].level]); //當前玩家
							players[gameData.building[players[gameData.turn].getState().position].owner].cash(-passValue); //地主
							prompt(43, "地主已退回過路費");
							players[gameData.turn].card[optionSet] -= 1;
						}
						break;
					}
				}

				else {
					Cmder::setCursor(20, 16);
					cout << "您沒有這項道具";
					Sleep(200);
				}
				
				loop = false;
			}
			print();
			select(optionSet);
		}
	}

	/* 讀取紀錄 */
	inline bool readFile(string filename)
	{
		string null;
		fstream file;
		file.open(filename, ios::in);

		file >> gameData.mapName >> gameData.remainingRound >> gameData.playerNum;//讀取地圖名稱 剩餘回合數 總玩家人數
		for (int i = 0, position; i < 28; i++)//讀取每個地產物件資訊
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
		file >> null >> gameData.turn;//讀取輪到第幾人
		for (short i = player1; i <= player4; i++)//讀取玩家 所在位置 擁有金錢 所有地產跟等級
		{
			string input, token;

			int c = 0, num, x;
			file >> num;
			getline(file, input);
			stringstream delim(input);//將打好的東西放到字串delim裡,包含空白
			//getline(delim, token, ' ') getline(delim[來源位置],token[存入位置],'　'[分割的條件])
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

	/* 儲存紀錄 */
	inline bool saveFile()
	{
		fstream file;
		file.open("basemap.txt", ios::out);
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
	
	/* 賣出房產 */
	inline void saleEstate()
	{
		
		typedef struct _house {
			int location;
			double price;
		}House;
		Player& current = players[gameData.turn];
		vector<House> myEstate;

		/* 建立房產清單 */
		for (auto& house : current.getState().estate)
		{
			myEstate.push_back(House{ 
				house.first, 
				gameData.building[house.first].initialPrice *(0.3 * (house.second + 1))
			});
		}
		
		COORD optionPosition[] = { {20,9}, {20,11} };
		string option[] = { "賣出房產" , "離開仲介行" };
		/* 子選單 */
		auto print = [&]() -> void {
			for (int i = 0; i < 2; ++i)
			{
				Cmder::setCursor(optionPosition[i]);
				Cmder::setColor(CLI_FONT_WHITE);
				cout << option[i];
				Cmder::setCursor(optionPosition[i]);
			}
		};

		/* 子選單選擇 */
		auto select = [&](int set) -> void {
			Cmder::setCursor(optionPosition[set]);
			Cmder::setColor(CLI_FONT_RED);
			cout << option[set];
			Cmder::setCursor(optionPosition[set]);
		};
		
		int keypress, optionSet = 0 , houseIndex = 0, houseLocation = 0;

		function<int(int,int)> eventTrigger[] = {
			/* 賣出房子 */
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
			if (!myEstate.empty()) // 有房子才輸出房產資訊
			{
				cout << Cmder::FONT_WHITE 
					<< "<- " << Cmder::FONT_YELLOW <<gameData.building[houseLocation].name <<": " << (int)myEstate[houseIndex].price  << " $"
					<< Cmder::FONT_WHITE << " ->";
			}

			else
			{
				cout << Cmder::FONT_PURPLE << "您當前無房產";
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
						/* 賣出房產 */
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

						/* 刷新房產清單 */
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

	/* 計算身價 */
	inline int getWealth(Player& player) {

		/* 現金 */
		int total = player.getState().money;

		/* 持股 */
		for (int i = 0; i < 4; ++i)
			total += (Bank::Business[i] * player.getState().stock[i]);
		
		/* 存款 */
		total += player.getState().despoit;

		/* 不動產總值 */
		for (auto& house : player.getState().estate)
		{
			int price = gameData.building[house.first].initialPrice *(0.3 * (house.second+1) );
			total += price;
		}
		player.wealth = total;
		return total;
	};

	/* 機會命運 */
	inline bool do_chance(Player& player) {

		int playerPlace = player.getState().position;
		if (playerPlace == 6 || playerPlace == 16)
		{
			srand(time(NULL));
			int result = rand() % 60 + 1;

			switch (result)
			{
				/* 休息一回合 */
			case 1:
				prompt(30, "心累，，，休息一回");
				player.stop = true;
				break;

			case 2:
				prompt(30, "出門忘記帶水壺，中暑，休息一回");
				player.stop = true;
				break;

			case 3:
				prompt(30, "腸胃炎，休息一回");
				player.stop = true;
				break;

			case 4:
				prompt(30, "每天熬夜導致肝指數過高，休息一回");
				player.stop = true;
				break;

			case 5:
				prompt(30, "努力不一定成功，放棄一定舒服，休息一回");
				player.stop = true;
				break;

			case 6:
				prompt(30, "端午節連假，休息一回");
				player.stop = true;
				break;

			case 7:
				prompt(30, "被已讀，受傷，休息一回");
				player.stop = true;
				break;

			case 8:
				prompt(30, "愛要及時三不五時，約會，休息一回");
				player.stop = true;
				break;

				/* 傳送 */
			case 9:
				prompt(30, "時空扭曲，隨機傳送");
				player.setPosition(rand() % 28);
				break;

			case 10:
				prompt(30, "撞上時空門，隨機傳送");
				player.setPosition(rand() % 28);
				break;

			case 11:
				prompt(30, "大地震，隨機傳送");
				player.setPosition(rand() % 28);
				break;

			case 12:
				prompt(30, "耍廢一時爽，一直耍廢一直爽，回「學人宿舍」");
				player.setPosition(12);
				break;

			case 13:
				prompt(30, "算命，五行缺水，前往「游泳池」");
				player.setPosition(11);
				break;

			case 14:
				prompt(30, "找不到讀書動力，「行政大樓」辦理休學");
				player.setPosition(18);
				break;

			case 15:
				prompt(30, "四點開始打工，速速前往「湖畔餐廳」");
				player.setPosition(23);
				break;

			case 16:
				prompt(30, "暑修，認命前往「理工學院」");
				player.setPosition(9);
				break;

			case 17:
				prompt(30, "「環頸雉」瀕臨滅絕，前往當地協助生態復育");
				player.setPosition(14);
				break;

			case 18:
				prompt(30, "萬事起頭難，回到「起點」");
				player.setPosition(0);
				break;

			case 19:
				prompt(30, "嚮往圓明園，前往「原民院」瞧瞧");
				player.setPosition(20);
				break;

			case 20:
				prompt(30, "明天期末考，到「圖書館」臨時抱佛腳");
				player.setPosition(25);
				break;

				/* 道具卡 */
			case 21:
				prompt(30, "怪盜基德傳授「現金卡」，可搜括所有玩家現金");
				player.card[0]++;
				break;

			case 22:
				prompt(30, "獲得「路障卡」一張");
				player.card[1]++;
				break;

			case 23:
				prompt(30, "獲得「路障卡」一張");
				player.card[1]++;
				break;

			case 24:
				prompt(30, "獲得「路障卡」一張");
				player.card[1]++;
				break;

			case 25:
				prompt(30, "獲得「房屋卡」一張，可免費升級所有房屋");
				player.card[2]++;
				break;

			case 26:
				prompt(30, "獲得「房屋卡」一張，可免費升級所有房屋");
				player.card[2]++;
				break;

			case 27:
				prompt(30, "獲得「免費卡」一張，可抵免過路費");
				player.card[3]++;
				break;

			case 28:
				prompt(30, "獲得「免費卡」一張，可抵免過路費");
				player.card[3]++;
				break;

				/* 座標變化 */
			case 29:
				prompt(30, "我想打起精神，不小心把它打死了，倒退一格");
				player.nextPosition(-1);
				break;

			case 30:
				prompt(30, "又一天過去了，離歐趴更遠了，倒退一格");
				player.nextPosition(-1);
				break;

			case 31:
				prompt(30, "高雄發大財，和智商一起倒退一格");
				player.nextPosition(-1);
				break;

			case 32:
				prompt(30, "轉角撞到愛，震驚，倒退一格");
				player.nextPosition(-1);
				break;

			case 33:
				prompt(30, "今天是星期日，明天是星期一，不想面對，倒退兩格");
				player.nextPosition(-2);
				break;

			case 34:
				prompt(30, "在學校頂樓跨年看煙火，被煙嗆到，倒退兩格");
				player.nextPosition(-2);
				break;

			case 35:
				prompt(30, "起床閃到腰，倒退兩格");
				player.nextPosition(-2);
				break;

			case 36:
				prompt(30, "遇見藝術學院妹子，害羞，倒退三格");
				player.nextPosition(-3);
				break;

			case 37:
				prompt(30, "得到偶像簽名，小鹿亂衝，前進一格");
				player.nextPosition(1);
				break;

			case 38:
				prompt(30, "今天是星期五，明天是星期六，耶，前進兩格");
				player.nextPosition(2);
				break;

			case 39:
				prompt(30, "和女神聊天，精神百倍前進三格");
				player.nextPosition(3);
				break;

			case 40:
				prompt(30, "高雄發大財，錢進高雄，前進三格");
				player.nextPosition(3);
				break;

			case 41:
				prompt(30, "下雨天滑倒，隨波逐流，前進五格");
				player.nextPosition(5);
				break;

			case 42:
				prompt(30, "體適能測驗800公尺，前進八格");
				player.nextPosition(8);
				break;

				/* 財務變化 */

			case 43:
				prompt(30, "支付卡債，3000元");
				player.bank(-3000);
				break;

			case 44:
				prompt(30, "學會投資不如學會投胎，金融海嘯慘賠10000元");
				player.cash(-10000);
				break;

			case 45:
				prompt(30, "認清自己醜不是因為胖，吃一人豪華火鍋，花費1000元");
				player.cash(-1000);
				break;

			case 46:
				prompt(30, "追星，花錢買快樂，演唱會門票500元");
				player.cash(-500);
				break;

			case 47:
				prompt(30, "三寶上路，賠醫藥費1000元");
				player.cash(-1000);
				break;

			case 48:
				prompt(30, "錯過鬧鐘，沒趕上點名，還收到超速罰單600元");
				player.cash(-600);
				break;

			case 49:
				prompt(30, "一個人看電影，哭了，花100元買衛生紙");
				player.cash(-100);
				break;

			case 50:
				prompt(30, "照鏡子被嚇到，收驚花200元");
				player.cash(-200);
				break;

			case 51:
				prompt(30, "和三寶激烈碰撞，獲得理賠1000元");
				player.cash(1000);
				break;

			case 52:
				prompt(30, "拾金不昧，失主給300元");
				player.cash(300);
				break;

			case 53:
				prompt(30, "晚上不睡覺抓到吸血鬼，賣給博物館，得3000元");
				player.cash(3000);
				break;

			case 54:
				prompt(30, "填問卷抽現金，得到300元");
				player.cash(300);
				break;

			case 55:
				prompt(30, "新年買刮刮樂，中獎500元");
				player.cash(500);
				break;

			case 56:
				prompt(30, "學餐打工，得薪水500元");
				player.cash(500);
				break;

			case 57:
				prompt(30, "賣肝，得5000元");
				player.cash(5000);
				break;

			case 58:
				prompt(30, "當上卷哥，獎學金1000元");
				player.cash(1000);
				break;

			case 59:
				prompt(30, "生活小確幸，發票中獎100元");
				player.cash(100);
				break;

			case 60:
				prompt(30, "逛街超爽的，撿到100元");
				player.cash(100);
				break;

			default:
				break;
			}

			return true;
		}
		return false;
	};

	/* 判斷路障 */
	inline bool Barrier(Player& player)
	{
		int playerPlace = players[gameData.turn].getState().position; // 玩家當前地點

		if (gameData.building[playerPlace].barrier == true)
		{
			player.stop = true;
			prompt(30, "經過路障處，休息一回合");
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
cout << "╔═══════╦═══════╦═══════╦═══════╦═══════╦═══════╦═══════╦═══════╗" << '\n';
cout << "║              ║              ║              ║              ║              ║              ║              ║              ║" << '\n';
cout << "║              ║              ║              ║              ║              ║              ║              ║              ║" << '\n';
cout << "║              ║              ║              ║              ║              ║              ║              ║              ║" << '\n';
cout << "║              ║              ║              ║              ║              ║              ║              ║              ║" << '\n';
cout << "╠═══════╬═══════╩═══════╩═══════╩═══════╩═══════╩═══════╬═══════╣" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "╠═══════╣                                                                                              ╠═══════╣" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "╠═══════╣                                                                                              ╠═══════╣" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "╠═══════╣                                                                                              ╠═══════╣" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "╠═══════╣                                                                                              ╠═══════╣" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "╠═══════╣                                                                                              ╠═══════╣" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "║              ║                                                                                              ║              ║" << '\n';
cout << "╠═══════╬═══════╦═══════╦═══════╦═══════╦═══════╦═══════╬═══════╣" << '\n';
cout << "║              ║              ║              ║              ║              ║              ║              ║              ║" << '\n';
cout << "║              ║              ║              ║              ║              ║              ║              ║              ║" << '\n';
cout << "║              ║              ║              ║              ║              ║              ║              ║              ║" << '\n';
cout << "║              ║              ║              ║              ║              ║              ║              ║              ║" << '\n';
cout << "╚═══════╩═══════╩═══════╩═══════╩═══════╩═══════╩═══════╩═══════╝" << '\n';
*/