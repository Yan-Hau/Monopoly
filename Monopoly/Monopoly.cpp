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

	while (gameData.remainingRound)
	{
		COORD optionPosition[] = { {91,9} , {91,11} , {91,13} , {91,15} , {91,17} };
		string option[] = { "路過銀行" , "股票買賣" , "使用道具" , "土地出售" , "主選單" };
		auto select = [&](int set) -> void {
			Cmder::setCursor(optionPosition[set]);
			Cmder::setColor(CLI_FONT_CYAN);
			cout << option[set];
			Cmder::setCursor(optionPosition[set]);
		};

		select(0);
		for (int order = gameData.turn, keypress, optionSet = 0; order < 4; order++)
		{
			mapStatus();
			gameStatus();
			playerStatus();
			while (true)
			{
				keypress = _getch();

				switch (keypress)
				{
				case 72:	//Key press Up
					optionSet = (optionSet + 2) % 5;
					break;

				case 80:	//Key press Down
					optionSet = (++optionSet % 5);
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
				for (int i = 0; i < 5; ++i)
				{
					Cmder::setColor();
					Cmder::setCursor(optionPosition[i]);
					cout << option[i];
				}
				select(optionSet);
			}
		}
		gameData.turn = 0;//下次從第1位玩家開始
		gameData.remainingRound--;
		
	}
	Cmder::setCursor(COORD{ 0, 40 });
	return 0;
}