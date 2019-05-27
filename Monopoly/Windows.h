#pragma once
#include "ConsoleInterface.h"
#include <iostream>
#include <string>
using namespace std;

namespace Windows
{
	bool mapBrand();
	bool playerBrand();
	bool checkYesOrNo(SHORT, string);
	bool prompt(SHORT, string);

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

	/* ½T©w¬O§_¿ן¾Ü */
	bool checkYesOrNo(SHORT position, string sentence)
	{
		string option[] = { "¬O" , "§_" };
		COORD optionPosition[] = { {41, 20} , {60, 20} };
		int keypress = 0, optionSet = 0;
		auto select = [=](int set) -> void {
			Cmder::setCursor(optionPosition[set]);
			Cmder::setColor(CLI_BACK_CYAN);
			cout << option[set];
			Cmder::setCursor(optionPosition[set]);
		};
		auto color = []() -> void {
			Cmder::setColor();
			for (SHORT i = 0; i < 14; i++)
			{
				Cmder::setCursor(COORD{ 20, 10 + i });
				for (SHORT j = 0; j < 63; j++)
				{
					cout << " ";
				}
			}
		};
		Cmder::setColor(CLI_BACK_CYAN | CLI_BACK_LIGHT);

		for (SHORT i = 0; i < 14; i++)//¥~³עֳה®״
		{
			Cmder::setCursor(COORD{ 20, 10 + i });
			if (i == 0)
			{
				cout << "שÝ";
				for (SHORT j = 0; j < 60; j++)
				{
					cout << "שש";
				}
				cout << "שß ";
			}
			else if (i == 13)
			{
				cout << "שד";
				for (SHORT j = 0; j < 60; j++)
				{
					cout << "שש";
				}
				cout << "שו ";
			}
			else
			{
				cout << "שר";
				for (SHORT j = 0; j < 60; j++)
				{
					cout << " ";
				}
				cout << "שר ";
			}
		}

		for (SHORT i = 0; i < 3; i++)//₪÷³¡ֳה®״
		{
			for (SHORT k = 0; k < 2; k++)
			{
				Cmder::setCursor(COORD{ 35 + k * 19 , 19 + i });
				if (i == 0)
				{
					cout << "שÝ";
					for (SHORT j = 0; j < 11; j++)
					{
						cout << "שש";
					}
					cout << "שß ";
				}
				else if (i == 2)
				{
					cout << "שד";
					for (SHORT j = 0; j < 11; j++)
					{
						cout << "שש";
					}
					cout << "שו ";
				}
				else
				{
					cout << "שר";
					for (SHORT j = 0; j < 11; j++)
					{
						cout << " ";
					}
					cout << "שר ";
				}
			}
		}

		Cmder::setCursor(COORD{ position, 14 });
		cout << sentence;

		while (1)//°µ¿ן¾Ü
		{
			/* Reset other unselected option color */
			for (int i = 0; i < 2; ++i)
			{
				Cmder::setColor(CLI_BACK_CYAN | CLI_BACK_LIGHT);
				Cmder::setCursor(optionPosition[i]);
				cout << option[i];
			}
			select(optionSet);

			keypress = _getch();
			switch (keypress)
			{
			case 75:	//Key press Up
				optionSet = (optionSet + 1) % 2;
				break;

			case 77:	//Key press Down
				optionSet = (++optionSet % 2);
				break;

			case 13:	//Key press Enter
				if (optionSet == 0)
				{
					color();
					return 1;
				}
				else
				{
					color();
					return 0;
				}
				break;
			default:
				break;
			}

		}

		return 0;
	}

	/* ´£¥Ü */
	bool prompt(SHORT position, string sentence)
	{
		string option[] = { "¬O" };
		COORD optionPosition[] = { {49, 20} };
		int keypress = 0;
		auto select = [=](int set) -> void {
			Cmder::setCursor(optionPosition[set]);
			Cmder::setColor(CLI_BACK_CYAN);
			cout << option[set];
			Cmder::setCursor(optionPosition[set]);
		};
		auto color = []() -> void {
			Cmder::setColor();
			for (SHORT i = 0; i < 14; i++)
			{
				Cmder::setCursor(COORD{ 20, 10 + i });
				for (SHORT j = 0; j < 63; j++)
				{
					cout << " ";
				}
			}
		};
		Cmder::setColor(CLI_BACK_CYAN | CLI_BACK_LIGHT);

		for (SHORT i = 0; i < 14; i++)//¥~³עֳה®״
		{
			Cmder::setCursor(COORD{ 20, 10 + i });
			if (i == 0)
			{
				cout << "שÝ";
				for (SHORT j = 0; j < 60; j++)
				{
					cout << "שש";
				}
				cout << "שß ";
			}
			else if (i == 13)
			{
				cout << "שד";
				for (SHORT j = 0; j < 60; j++)
				{
					cout << "שש";
				}
				cout << "שו ";
			}
			else
			{
				cout << "שר";
				for (SHORT j = 0; j < 60; j++)
				{
					cout << " ";
				}
				cout << "שר ";
			}
		}

		Cmder::setCursor(COORD{ position, 14 });
		cout << sentence;

		for (SHORT i = 0; i < 3; i++)//₪÷³¡ֳה®״
		{
			Cmder::setCursor(COORD{ 43, 19 + i });
			if (i == 0)
			{
				cout << "שÝ";
				for (SHORT j = 0; j < 11; j++)
				{
					cout << "שש";
				}
				cout << "שß ";
			}
			else if (i == 2)
			{
				cout << "שד";
				for (SHORT j = 0; j < 11; j++)
				{
					cout << "שש";
				}
				cout << "שו ";
			}
			else
			{
				cout << "שר";
				for (SHORT j = 0; j < 11; j++)
				{
					cout << " ";
				}
				cout << "שר ";
			}
		}

		while (1)//°µ¿ן¾Ü
		{
			select(0);

			keypress = _getch();
			if (keypress == 13)
			{
				color();
				return 1;
			}
		}

		return 0;
	}
}