#include "pch.h"
#include "System.h"
#include "ConsoleInterface.h"
#include <iostream>
using namespace std;
using namespace System;

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

	while (System::gameData.remainingRound)
	{
		COORD optionPosition[] = { {91,9} , {91,11} , {91,13} , {91,15} , {91,17} , {91,19} };
		string option[] = { "路過銀行" , "股票買賣" , "使用道具" , "土地出售" , "主選單" , "結束回合" };
		auto select = [&](int set) -> void {
			Cmder::setCursor(optionPosition[set]);
			Cmder::setColor(CLI_FONT_CYAN);
			cout << option[set];
			Cmder::setCursor(optionPosition[set]);
		};

		for (int order = System::gameData.turn/* 當前玩家 */, keypress/* 按鍵代號 */, optionSet/* 目前選項 */, perform; order < 4; order++, System::gameData.turn++)
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
					System::gameData.player[order].position = (System::gameData.player[order].position + dice()) % 28;
					merchandise();
					mapStatus();
					playerStatus();
					perform = 0;
					Cmder::setCursor(COORD{ 20, 9 });
					cout << "                         ";
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
				case 72:	//Key press Up
					optionSet = (optionSet + 5) % 6;
					break;

				case 80:	//Key press Down
					optionSet = (++optionSet % 6);
					break;

				case 13:	//Key press Enter
					if (optionSet == 0)        //路過銀行
					{

					}
					else if (optionSet == 1)   //股票買賣
					{

					}
					else if (optionSet == 2)   //使用道具
					{

					}
					else if (optionSet == 3)   //土地出售
					{

					}
					else if (optionSet == 4)   //主選單
					{

					}
					else if (optionSet == 5)   //結束回合
					{
						perform = 0;
					}
					break;

				/*case 75:	//Key press Left
					break;

				case 77:	//Key press Right
					break;

				case 27:    //Key press ESC
					break;*/

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
		}
		System::gameData.turn = 0;//下次從第1位玩家開始
		System::gameData.remainingRound--;
		
	}
	Cmder::setCursor(COORD{ 0, 40 });
	return 0;
}