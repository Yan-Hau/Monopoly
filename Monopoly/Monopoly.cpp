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
	Cmder::initialize(50, 170);
	/*
	if(strat)
	{
	mapBrand();
	statusBrand();
		while(remaing turn)
		{
			地圖跟狀態改變
			做選擇
			switch
			{
				銀行
				...
				...
				結束回合:
			}
			if(turn == 3)
			remaing turn --; 
		}
		顯示誰贏
	}
	*/
	readFile();
	mapBrand();
	playerBrand();
	Bank::Business[0] = rand() % 21 + 100 - 10;
	Bank::Business[1] = rand() % 21 + 100 - 10;
	Bank::Business[2] = rand() % 21 + 100 - 10;
	Bank::Business[3] = rand() % 21 + 100 - 10;
	
	while ( System::gameData.remainingRound )
	{
		enum keyboardValue { Up = 72, Down = 80, Left = 75, Right = 77, Enter = 13, Esc = 27 };

		/* 選項位置 */
		COORD optionPosition[] = { {94,7} , {94,9} , {94,11}, {94,13} , {94,15} , {94,17} };
		
		/* 選項名稱 */
		string option[] = { "進入銀行" , "股票買賣" , "使用道具" , "土地出售" , "主選單" , "結束回合" };
		auto select = [&](int set) -> void {
			Cmder::setCursor(optionPosition[set]);
			Cmder::setColor(CLI_FONT_CYAN);
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
				order < 4; order++,

				//Increment
				System::gameData.turn++
			)
		{
			Player& currentPlayer = players[order];
			if (!currentPlayer.stop) 
			{
				mapStatus();
				gameStatus();
				playerStatus();
				optionSet = 0;
				
				perform = 1;
				while (perform)//擲骰子
				{
					Cmder::setCursor(COORD{ 20, 9 });
					cout << "請按空白鍵(space)擲骰子~";
					keypress = _getch();
					if (keypress == 32)
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
						mapStatus();
						playerStatus();
						perform = 0;
					}
					else
					{
						Cmder::setCursor(COORD{ 20, 9 });
						cout << "                         ";
						Cmder::setCursor(COORD{ 20, 9 });
						cout << "阿是聽不懂人話齁!?";
						Sleep(700);
					}
				}

				perform = 1;
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
						if (optionSet == 0)        //路過銀行
						{
							goBank();
							
						}
						else if (optionSet == 1)   //股票買賣
						{
							transStock();
						}
						else if (optionSet == 2)   //使用道具
						{
							useCard();
						}
						else if (optionSet == 3)   //土地出售
						{
							saleEstate();
						}
						else if (optionSet == 4)   //主選單
						{

						}
						else if (optionSet == 5)   //結束回合
						{
							perform = 0;
						}

						mapBrand();
						mapStatus();
						gameStatus();
						playerStatus();
						break;

						/*
						case Left: //Key press Left
							break;

						case Right:  //Key press Right
							break;
						*/

					case Esc:    //Key press ESC
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
					bank.generate();
					select(0);
				}
			}
			else
			currentPlayer.stop = false;
		}
		
		System::gameData.turn = 0;//下次從第1位玩家開始
		System::gameData.remainingRound--;
		bank.generate();
	}

	Cmder::setCursor(COORD{ 0, 40 });

	return 0;
}