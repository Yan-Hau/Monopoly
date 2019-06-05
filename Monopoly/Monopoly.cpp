#include "pch.h"
#include "System.h"
#include "Windows.h"
#include "ConsoleInterface.h"
#include <iostream>

using namespace std;
using namespace System;
using namespace Windows;

int main()
{
	srand(time(0));
	Cmder::initialize(51, 170);
	enum keyboardValue { Up = 72, Down = 80, Left = 75, Right = 77, Enter = 13, Esc = 27 , Space = 32 };

	startScreen();
	int optionSet = 0, keypress = 0;
	while (keypress != Enter)//開始畫面選擇
	{
		/* 選項位置 */
		COORD optionPosition[] = { {120,26} , {120,28} , {120,30} , {132,26} , {132,28} , {132,30} };

		/* 選項名稱 */
		string option[] = { "開始遊戲" , "復原遊戲" , "結束遊戲" , "2人遊戲" , "3人遊戲" , "4人遊戲" };
		auto select = [&](int set) -> void {
			Cmder::setCursor(optionPosition[set]);
			Cmder::setColor(CLI_FONT_YELLOW | CLI_FONT_LIGHT);
			cout << option[set];
			Cmder::setCursor(optionPosition[set]);
		};

		/* Reset other unselected option color */
		for (int i = 0; i < 3; ++i)
		{
			Cmder::setColor();
			Cmder::setCursor(optionPosition[i]);
			cout << option[i];
		}
		select(optionSet);

		keypress = _getch();
		switch (keypress)
		{
		case Up:	//Key press Up 
			optionSet = (optionSet + 2) % 3;
			break;

		case Down:	//Key press Down
			optionSet = (++optionSet % 3);
			break;

		case Enter:	//Key press Enter
			switch (optionSet)
			{
			case 0://開始遊戲
				readFile("basedata_.txt");
				keypress = 0, optionSet = 3;
				while (keypress != Enter)
				{
					for (int i = 0; i < 3; ++i)
					{
						Cmder::setColor();
						Cmder::setCursor(optionPosition[i + 3]);
						cout << option[i + 3];
					}
					select(optionSet);

					keypress = _getch();
					switch (keypress)
					{
					case Up:	//Key press Up 
						optionSet = (optionSet - 1) % 3 + 3;
						break;

					case Down:	//Key press Down
						optionSet = (++optionSet % 3) + 3;
						break;

					case Enter:	//Key press Enter
						switch (optionSet)
						{
						case 3:
							gameData.playerNum = 2;
							break;
						case 4:
							gameData.playerNum = 3;
							break;
						case 5:
							gameData.playerNum = 4;
							break;
						default:
							break;
						}
						break;
					}
				}
				break;
			case 1://復原遊戲
				readFile("basemap.txt");
				break;
			case 2://結束遊戲
				return 1;
				break;
			default:
				break;
			}
			keypress = Enter;
		}
	}

	clearAll();
	mapBrand();
	playerBrand(gameData.playerNum);
	short outerPlayer = 0;
	Bank::Business[0] = rand() % 21 + 100 - 10;
	Bank::Business[1] = rand() % 21 + 100 - 10;
	Bank::Business[2] = rand() % 21 + 100 - 10;
	Bank::Business[3] = rand() % 21 + 100 - 10;

	while (System::gameData.remainingRound && outerPlayer < gameData.playerNum)
	{
		Cmder::setCursor(COORD{ 45, 148 });
		//cout << 1;
		/* 選項位置 */
		COORD optionPosition[] = { {94,7} , {94,9} , {94,11}, {94,13} , {94,15} , {94,17} };

		/* 選項名稱 */
		string option[] = { "進入銀行" , "股票買賣" , "使用道具" , "土地出售" , "主選單" , "結束回合" };
		auto select = [&](int set) -> void {
			Cmder::setCursor(optionPosition[set]);
			Cmder::setColor(CLI_FONT_PURPLE | CLI_FONT_LIGHT);
			cout << option[set];
			Cmder::setCursor(optionPosition[set]);
		};

		for (
			//Initial
			int order = System::gameData.turn/* 當前玩家 */,
			keypress/* 按鍵代號 */,
			optionSet/* 目前選項 */,
			perform;

			//condition
			order < gameData.playerNum; order++,

			//Increment
			System::gameData.turn++
			)
		{
			Player& currentPlayer = players[order];
			if (!currentPlayer.stop || !currentPlayer.isEnd())
			{
				perform = 1, keypress = 0, optionSet = 0;
				System::mapStatus();
				System::gameStatus();
				System::playerStatus();

				/* 計算是否破產 */
				if (getWealth(currentPlayer) < 0 )
				{
					/* 清除房契 */
					for (auto& house : currentPlayer.estate)
						gameData.building[house.first].owner = -1;

					/* 結算玩家 */
					currentPlayer.out();
					
					/* 提示破產*/
					Cmder::setCursor(20, 9);
					cout << (Cmder::FONT_RED | Cmder::FONT_LIGHT) << "您已經破產";
					_getch();

					/* 出局數+1 */
					++outerPlayer;

					/* 重新繪製 */
					System::mapStatus();
					System::gameStatus();
					System::playerStatus();
					continue;
				}

				while (keypress != Space)//擲骰子
				{
					if (outerPlayer >= gameData.playerNum-1)
						break;
					Cmder::setCursor(COORD{ 20, 9 });
					cout << "請按空白鍵(space)擲骰子~";
					keypress = _getch();
					if (keypress == Space)
					{
						Cmder::setCursor(COORD{ 20, 9 });
						cout << "                         ";
						players[order].nextPosition(dice());
						merchandise();
						Barrier(currentPlayer);
						if (do_chance(currentPlayer))
						{
							merchandise();
							Barrier(currentPlayer);
						}
						System::mapStatus();
						System::playerStatus();
					}
					else
					{
						Cmder::setCursor(COORD{ 20, 9 });
						cout << "                         ";
						Cmder::setCursor(COORD{ 20, 9 });
						cout << "阿是聽不懂人話齁!?";
						Sleep(500);
					}
				}

				while (perform)//其他動作
				{
					/* Reset other unselected option color */
					for (int i = 0; i < 6; ++i)
					{
						Cmder::setColor();
						Cmder::setCursor(optionPosition[i]);
						cout << option[i];
					}
					select(optionSet);

					keypress = _getch();
					switch (keypress)
					{
					case Up:	//Key press Up 
						optionSet = (optionSet + 5) % 6;
						break;

					case Down:	//Key press Down
						optionSet = (++optionSet % 6);
						break;

					case Enter:	//Key press Enter
						switch (optionSet)
						{
						case 0:   //路過銀行
							goBank();
							break;
						case 1:   //股票買賣
							transStock();
							break;
						case 2:   //使用道具
							useCard();
							break;
						case 3:   //土地出售
							saleEstate();
							break;
						case 4:   //主選單
							switch (menu())
							{
							case 0://儲存檔案
								gameData.turn++;
								saveFile();
								gameData.turn--;
								break;
							case 1://遊戲說明
								gameInstructions();
								break;
							case 2://結束遊戲
								return 1;
								break;
							case 3://離開選單
								break;
							default:
								break;
							}
							break;
						case 5:   //結束回合
							perform = 0;
							break;
						}

						mapBrand();
						System::mapStatus();
						System::gameStatus();
						System::playerStatus();
						break;


					case Esc:    //Key press ESC
						switch (menu())
						{
						case 0://儲存檔案
							gameData.turn++;
							saveFile();
							gameData.turn--;
							break;
						case 1://遊戲說明
							gameInstructions();
							break;
						case 2://結束遊戲
							return 1;
							break;
						case 3://離開選單
							break;
						default:
							break;
						}
						break;

					default:
						break;
					}

					/* Reset other unselected option color */
					for (int i = 0; i < 6; ++i)
					{
						Cmder::setColor();
						Cmder::setCursor(optionPosition[i]);
						cout << option[i];
					}
					select(0);
				}
				currentPlayer.interest();
			}

			else
				currentPlayer.stop = false;
		}

		System::gameData.turn = 0;//下次從第1位玩家開始
		System::gameData.remainingRound--;
		bank.generate();
	}

	int max = 0;
	bool* winners = new bool[gameData.playerNum];
	for (int i = 0; i < gameData.playerNum; ++i)
	{
		if (getWealth(players[i]) > getWealth(players[max]))
			max = i;
	}

	for (int i = 0; i < gameData.playerNum; ++i)
	{
		if (getWealth(players[i]) == getWealth(players[max]))
			winners[i] = true;
	}
	for(int i = 0 , j = 0 ;i < gameData.playerNum; ++i)
	{
		if (winners[i] == true)
		{
			Cmder::setCursor(20, 9 + j);
			cout << Cmder::FONT_PURPLE << "Winner is Player " << i + 1;
			++j;
		}
	}
	_getch();
	return 0;
}