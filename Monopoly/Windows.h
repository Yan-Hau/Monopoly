#pragma once
#include "ConsoleInterface.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

namespace Windows
{
	bool startScreen();
	bool mapBrand();
	bool playerBrand();
	bool bankImage();
	bool stockImage();
	bool checkYesOrNo(SHORT, string);
	bool prompt(SHORT, string);
	int menu();
	bool gameInstructions();
	bool clearAll();

	/* �}�l�e���� */
	inline bool startScreen()
	{
		//Cmder::setColor(CLI_FONT_YELLOW | CLI_FONT_LIGHT);
		//Cmder::setCursor({ 0,0 });
		cout << setw(115) << "                             \x1B[37m`.                                                    \x1B[37m:                  \x1B[1;35m`                " << endl;
		cout << setw(115) << "                           \x1B[37m,.`` '`                                                \x1B[37m+:'             \x1B[35m.+#`                " << endl;
		cout << setw(115) << "                          \x1B[37m. ````.,@                                              \x1B[37m+: :`+       \x1B[35m`+;::'`#                " << endl;
		cout << setw(115) << "                        \x1B[37m```  ` `.:;.'                                           \x1B[37m+'., ,#     \x1B[35m+;::::;',                 " << endl;
		cout << setw(115) << "                       \x1B[37m````\x1B[1;31m��\x1B[37m:' ```,',.:.                                        \x1B[37m#;;;`::'  \x1B[35m;':::::::;`:;+               " << endl;
		cout << setw(115) << "                      \x1B[37m``` ;''` ```..,.`+                                      \x1B[37m#;;;;``',\x1B[35m#::::::;:;;',::`               " << endl;
		cout << setw(115) << "                    \x1B[37m.``.```  `..`'';``.```          \x1B[0;33m,@####@@#            \x1B[37m`;;;;;:::;;;:+\x1B[35m,,`;;;:::;`,    .              " << endl;
		cout << setw(115) << "                   \x1B[37m```\x1B[1;31m��\x1B[37m``': ```\x1B[1;31m��\x1B[37m.`';;;..`.           \x1B[0;33m,#`.......@           \x1B[37m;;;';::;:;;;;.\x1B[35m:::,:::::;`,``,``              " << endl;
		cout << setw(115) << "                  \x1B[37m`````;''` `..`;;::`,''`` ` .:\x1B[0;33m',,,@ .....,,,'@@@@@@+.  \x1B[37mm#;;\x1B[0;33m+@@##@#\x1B[37m;;;;\x1B[35m+`,,;:::::;..,,.`,.;            " << endl;
		cout << setw(115) << "                \x1B[37m``````;;;` \x1B[1;31m��\x1B[37m.`..`.:,`.;''```:\x1B[0;33m@:``````.......,,,..```..#@@@@@#`.....#;;+@#+#\x1B[35m:::::;'::`';':`@            " << endl;
		cout << setw(115) << "                  \x1B[37m```:;;,``.:\x1B[0;33m@@@@;\x1B[37m..;\x1B[1;31m��\x1B[37m:;;`.'\x1B[0;33m@`................,,,,,,:#````....#.,,#++@`  '@\x1B[35m;::;;;';`;;;;;;#            " << endl;
		cout << setw(115) << "                   \x1B[37m`++``  `\x1B[0;33m@;`,,,;#\x1B[37m`.::\x1B[0;33m@+@@`......``````.....,,,,:#: ........,##'+.@ .,.` ;@\x1B[35m;;;';.;;:;+#+.            " << endl;
		cout << setw(115) << "                    \x1B[37m```` \x1B[0;33m.@`,,,,..@...@...@.. ;; `..... `;;;;;;;;#;;;, .  ;; #;;;;;` #,,,,. +@\x1B[35m:;;'@#+;`               " << endl;
		cout << setw(115) << "                    \x1B[1;32m:   `\x1B[0;33m@:,.,,..`:+@,```.#````'`````.......,,,,,#+: .....,##,;:,,.@  #,,,,,.`@\x1B[36m+#@+#+'.`              " << endl;
		cout << setw(115) << "                 \x1B[1;32m'#  \x1B[0;33m@```+ ,,.,.```'``....#..,.`.################:::`....,#`.,;',@     #,:,,:,.@\x1B[36m;;;;:`;;:             " << endl;
		cout << setw(115) << "                \x1B[1;32m;:':+ \x1B[0;33m@`@.:,,,.``......,,.#..,,#`....,,,,,:::::::,#:#.,,:@`,...@     @::#,::::::@\x1B[36m:;;;:.,;             " << endl;
		cout << setw(115) << "             \x1B[1;32m:``::+::',\x1B[0;33m#.;,::.`.`.....,,.,:### #.,,,,,,,,,,,,,,,,,#::#:#@;.,,,@     @::::#::::::#\x1B[36m;;:;,`,@             " << endl;
		cout << setw(115) << "             \x1B[1;32m;,` :..;;:\x1B[0;33m#,;;;.:``.....,,,,,,.,,####################::::'@@@,.,,.,@###@;,,:#::::::#\x1B[36m'::,:.:`:            " << endl;
		cout << setw(115) << "             \x1B[1;32m,,  `,: '\x1B[0;33m@'.;:.,```...,,,,,,,:.#;@.,,,,.,,,:::::::::::#+`..``;#:::,;':,@,:,:,#:::::@\x1B[36m:;;;;,'#,            " << endl;
		cout << setw(115) << "              \x1B[1;32m:;`, +\x1B[0;33m#.`,; .;`.....,,,,,,,,,,#@@.,,,,,=======,:::::;#.,;;;#######,...,:::::#::::@\x1B[36m##@@':.+              " << endl;
		cout << setw(115) << "           \x1B[1;32m`+.`,,`'\x1B[0;33m@ ,,,,........,,,,,,,:,,,#@:,,,,,,,,,,,::::::::#' ,# ``,,,,,,:+++++##::@#'@@\x1B[36m      .;               " << endl;
		cout << setw(115) << "            \x1B[1;32m#'',:`;\x1B[0;33m@`,,,.``.....,,,,,,,#####@#`##+################;:,#:`:,, ,::,::#::::.###@#\x1B[0;32m,,,'@,                   " << endl;
		cout << setw(115) << "             \x1B[1;32m'''`;;\x1B[0;33m'`,,,.......,,,,,,,::,,.,#,,,,,,,,,,,,:::::::::::::#####,,:::::#:::::::,,#\x1B[0;32m+,::,,:+;                " << endl;
		cout << setw(115) << "               \x1B[1;32m#;';\x1B[0;33m@.,.......,,,,,,,,,,,:,,:#,,,,,,,,,,,,::::::::::::##::::#;:::::#``+:::::::'+\x1B[0;32m:::,,::,:#.            " << endl;
		cout << setw(115) << "               \x1B[1;32m';#+\x1B[0;33m@.,......,,,,,,,,,::::,,,#,,,,,,,,,,,::::::::::::.  #::::#::::;:####::::::;#\x1B[0;32m:::::,::,::,#,         " << endl;
		cout << setw(115) << "                \x1B[1;32m`` \x1B[0;33m#..,,,,,,,',,,,,,::::::,:#:,,,,,====::::====::::.:###::;#::::'#:::.#:::::::+\x1B[0;32m;::::::::::;`:#`       " << endl;
		cout << setw(115) << "                  \x1B[1;32m` \x1B[0;33m@..,,::;:.,,,,::::::::::#,:,,,,::.,::::::,:::::#;;::;;;#;:::;;:#:::#:::::::@\x1B[0;32m:::::::::::';`,:::    " << endl;
		cout << setw(115) << "                  \x1B[35m@;;\x1B[0;33m@,,:+#.,,,,,:::#:::::::#.:,,,:;;`:::::::.:;:::#;;;;;;#':;:;';;#:;:#:::::::@\x1B[0;32m::::;:::::,'::.',``   " << endl;
		cout << setw(115) << "               \x1B[35m @,';;:\x1B[0;33m@##@.,:,,,::,:#:::::::#.:::::====::::====::::#;;;;'#';;:;::#;;::;#;:::;;;@\x1B[0;32m;;;:::::;:';: ::,'`   " << endl;
		cout << setw(115) << "               \x1B[35m;;,;;::::\x1B[0;33m@.,,:,::::::#:;::::::#,:::::;:;;;;::::::::;;#@;'#::::;##:::;;;#'::;;;;;#\x1B[0;32m+:;;;::::;.,,  .`+    " << endl;
		cout << setw(115) << "               \x1B[35m#,``;::;:\x1B[0;33m@.:::::::::#'@@+;:;:;+@;;;;;;;;:;;;;;;;;;;'@;`@@ ;;;;:+;#:;;'#+;;;;;;;#  \x1B[0;32m:@:;::'..:`   ,.     " << endl;
		cout << setw(115) << "           \x1B[35m`  . , :`:;'\x1B[0;33m@ :::::+:::;@\x1B[37m:,,:\x1B[0;33m+@@@@+`:;'++++++++++++++;;.   \x1B[0;33m`@ :;;;;::;#;#,:;;;;;;;;@   \x1B[0;32m``#';::,`,:`:,,,    " << endl;
		cout << setw(115) << "          \x1B[35m.',,,;:`.;;#;\x1B[0;33m@`::::;++:;+'\x1B[37m:,,,::,;``+                        \x1B[0;33m`#;';;;;;@#+ ;;;;;;;;;':       \x1B[0;32m++:;;'::.'+@    " << endl;
		cout << setw(115) << "           \x1B[35m,.:,,`.,#;  \x1B[0;33m@.,::.;:,;;@\x1B[37m,:,,:::@,;`+                         \x1B[0;33m`@@@++#@:,@`;;;;;;;;;@          \x1B[0;32m;#:'``+       " << endl;
		cout << setw(115) << "            \x1B[35m,,,#` `   \x1B[1;34m;,\x1B[0;33m@.:+#::;;@\x1B[37m,:,,,::'+.:'                             \x1B[1;31m@:::::::\x1B[0;33m+;;;;;;;;@` `          \x1B[0;32m,#.+ `      " << endl;
		cout << setw(115) << "              \x1B[35m:     \x1B[1;34m':,::\x1B[0;33m@,.:;;;#\x1B[37m;:,,,:::# `                                \x1B[1;31m@::::::'\x1B[0;33m@#;';';@.               \x1B[0;32m,         " << endl;
		cout << setw(115) << "              \x1B[35m`    \x1B[1;34m#,::,:,,\x1B[0;33m@+'+@\x1B[37m,:,,:::,#                                    \x1B[1;31m@::::::,:'\x1B[0;33m@@@'                           " << endl;
		cout << setw(115) << "                \x1B[1;34m:::;;;:;:@. `   \x1B[37m#,#@;`'                                        \x1B[1;31m` +,,`. `,,`#                          " << endl;
		cout << setw(115) << "            \x1B[1;34m',:: ::.`,:@.       \x1B[37m+,  .`                                            \x1B[1;31m`+:,: `,`#;                         " << endl;
		cout << setw(115) << "             \x1B[1;34m@,`  ,,;;#,`                                                          \x1B[1;31m`:`,`:`'                           " << endl;
		cout << setw(115) << "              \x1B[1;34m+,```;;#;                                                             \x1B[1;31m,#++#`                            " << endl;
		return 1;
	}

	/* �C���e���� */
	inline bool mapBrand()
	{
		Cmder::setCursor(0, 0);
		string option[] = { "�i�J�Ȧ�" , "�Ѳ��R��" , "�ϥιD��" , "�g�a�X��" , "�D���" , "�����^�X" };
		system("COLOR 07");
		cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������" << '\n';
		cout << "��              ��              ��              ��              ��              ��              ��              ��              ��" << '\n';
		cout << "��              ��              ��              ��              ��              ��              ��              ��              ��" << '\n';
		cout << "��              ��              ��              ��              ��              ��              ��              ��              ��" << '\n';
		cout << "��              ��              ��              ��              ��              ��              ��              ��              ��" << '\n';
		cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��������������������������������                                                                                         ��������������������������������" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��������������������������������                                                                                         ��������������������������������" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��������������������������������                                                                                         ��������������������������������" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��������������������������������                                                                                         ��������������������������������" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��������������������������������                                                                                         ��������������������������������" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��              ��                                                                                         ��              ��" << '\n';
		cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������" << '\n';
		cout << "��              ��              ��              ��              ��              ��              ��              ��              ��" << '\n';
		cout << "��              ��              ��              ��              ��              ��              ��              ��              ��" << '\n';
		cout << "��              ��              ��              ��              ��              ��              ��              ��              ��" << '\n';
		cout << "��              ��              ��              ��              ��              ��              ��              ��              ��" << '\n';
		cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������" << '\n';
		
		//�L�X�ﶵ
		for (short i = 0; i < 6; i++)
		{
			Cmder::setCursor(COORD{ 94, 7 + 2 * i });
			cout << option[i];
		}

		//�L�X�ﶵ���
		for (short i = 0; i < 16; i++)
		{
			Cmder::setCursor(COORD{ 90, 5 + i });
			if (i == 0)
			{
				cout << "��";
				continue;
			}
			else if (i == 15)
			{
				cout << "������������������������������";
				continue;
			}
			cout << "��";
		}
		return 1;
	}

	/* �H�����A�e���� */
	inline bool playerBrand()
	{
		system("COLOR 07");
		for (SHORT i = 0; i < 5; i++)
		{
			Cmder::setCursor(COORD{ 121, 0 + 10 * i });
			cout << "��������������������������������������������������������";
			if (i == 0)
				cout << "��"; 
			else if (i == 4)
				cout << "��";
			else
				cout << "��";
		}

		for (SHORT i = 0; i < 4; i++)
		{
			for (SHORT j = 0; j < 9; j++)
			{
				Cmder::setCursor(COORD{ 149, 1 + 10 * i + j });
				cout << "��";
			}
		}

		return 1;
	}
	
	/* �Ȧ�Ϥ� */
	inline bool bankImage()
	{
		Cmder::setColor(CLI_FONT_GREEN | CLI_FONT_LIGHT);
		Cmder::setCursor({ 20,15 });
		cout << "          ''''''''''''''''''''''''''''''''''''''''''''" ;Cmder::setCursor({ 20,16 });
		cout << "       '''''                                       '''''" ;Cmder::setCursor({ 20,17 });
		cout << "    '''''                                             '''''" ;Cmder::setCursor({ 20,18 });
		cout << "'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''" ;Cmder::setCursor({ 20,19 });
		cout << "'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''" ;Cmder::setCursor({ 20,20 });
		cout << "      '''      '''             '''              '''      '''" ;Cmder::setCursor({ 20,21 });
		cout << "      '''      '''          '''''''''           '''      '''" ;Cmder::setCursor({ 20,22 });
		cout << "      '''      '''        '''''''' ''';         '''      '''" ;Cmder::setCursor({ 20,23 });
		cout << "      '''      '''       '''   '''  ''''        '''      '''" ;Cmder::setCursor({ 20,24 });
		cout << "      '''      '''       '''  .'''   ''         '''      '''" ;Cmder::setCursor({ 20,25 });
		cout << "      '''      '''         '''''''              '''      '''" ;Cmder::setCursor({ 20,26 });
		cout << "      '''      '''            ''''''            '''      '''" ;Cmder::setCursor({ 20,27 });
		cout << "      '''      '''             ''''''           '''      '''" ;Cmder::setCursor({ 20,28 });
		cout << "      '''      '''        ''   '''   '''        '''      '''" ;Cmder::setCursor({ 20,29 });
		cout << "      '''      '''       ''''  '''   '''        '''      '''" ;Cmder::setCursor({ 20,30 });
		cout << "      '''      '''         '''''''''''`         '''      '''" ;Cmder::setCursor({ 20,31 });
		cout << "      '''      '''          ''''''''''          '''      '''" ;Cmder::setCursor({ 20,32 });
		cout << "      '''      '''             '''              '''      '''" ;Cmder::setCursor({ 20,33 });
		cout << ":''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''`" ;Cmder::setCursor({ 20,34 });
		cout << "''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''";
		return 1;
	}
	
	/* �Ѳ��Ϥ� */
	inline bool stockImage()
	{
		Cmder::setColor(CLI_FONT_RED | CLI_FONT_LIGHT);
		Cmder::setCursor({ 40,17 });
		cout << "                          //////// "; Cmder::setCursor({ 20,18 });
		cout << "                                               ////// "; Cmder::setCursor({ 20,19 });
		cout << "                                              /// (/. "; Cmder::setCursor({ 20,20 });
		cout << "                                          ...(//  "; Cmder::setCursor({ 20,21 });
		cout << "                                       //////// "; Cmder::setCursor({ 20,22 });
		cout << "                                     ///    ..  ."; Cmder::setCursor({ 20,23 });
		cout << "          �o�j�]              //**,*((,    (====)"; Cmder::setCursor({ 20,24 });
		cout << "                             (////((/      (====),"; Cmder::setCursor({ 20,25 });
		cout << "                           ///.     ..     (====)."; Cmder::setCursor({ 20,26 });
		cout << "                       ///(((     (====)   (====)"; Cmder::setCursor({ 20,27 });
		cout << "                   .(((((((/      (====)   (====)"; Cmder::setCursor({ 20,28 });
		cout << "                   ((       . .   (====)   (====)"; Cmder::setCursor({ 20,29 });
		cout << "                  //.    (====)   (====)   (====)"; Cmder::setCursor({ 20,30 });
		cout << "            ////***,     (====)   (====)   (====)"; Cmder::setCursor({ 20,31 });
		cout << "***/////**////***(====),,(====)   (====)   (====)"; Cmder::setCursor({ 20,32 });
		cout << "......*(///*(%#(////((/(//*/(********,,./***,,"; Cmder::setCursor({ 20,33 });
		cout << "               .,/(//,,#*///*/#((*//*#/**(/(/*,.";
		return 1;
	}
	
	/* �T�w�O�_��� */
	bool checkYesOrNo(SHORT position, string sentence)
	{
		enum keyboardValue { Up = 72, Down = 80, Left = 75, Right = 77, Enter = 13, Esc = 27 };
		string option[] = { "�O" , "�_" };
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

		for (SHORT i = 0; i < 14; i++)//�~�����
		{
			Cmder::setCursor(COORD{ 20, 10 + i });
			if (i == 0)
			{
				cout << "��";
				for (SHORT j = 0; j < 60; j++)
				{
					cout << "��";
				}
				cout << "�� ";
			}
			else if (i == 13)
			{
				cout << "��";
				for (SHORT j = 0; j < 60; j++)
				{
					cout << "��";
				}
				cout << "�� ";
			}
			else
			{
				cout << "��";
				for (SHORT j = 0; j < 60; j++)
				{
					cout << " ";
				}
				cout << "�� ";
			}
		}

		for (SHORT i = 0; i < 3; i++)//�������
		{
			for (SHORT k = 0; k < 2; k++)
			{
				Cmder::setCursor(COORD{ 35 + k * 19 , 19 + i });
				if (i == 0)
				{
					cout << "��";
					for (SHORT j = 0; j < 11; j++)
					{
						cout << "��";
					}
					cout << "�� ";
				}
				else if (i == 2)
				{
					cout << "��";
					for (SHORT j = 0; j < 11; j++)
					{
						cout << "��";
					}
					cout << "�� ";
				}
				else
				{
					cout << "��";
					for (SHORT j = 0; j < 11; j++)
					{
						cout << " ";
					}
					cout << "�� ";
				}
			}
		}

		Cmder::setCursor(COORD{ position, 14 });
		cout << sentence;

		while (1)//�����
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
			case Left:	//Key press Left
				optionSet = (optionSet + 1) % 2;
				break;

			case Right:	//Key press Right
				optionSet = (++optionSet % 2);
				break;

			case Enter:	//Key press Enter
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

	/* ���� */
	bool prompt(SHORT position, string sentence)
	{
		string option[] = { "�O" };
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

		for (SHORT i = 0; i < 14; i++)//�~�����
		{
			Cmder::setCursor(COORD{ 20, 10 + i });
			if (i == 0)
			{
				cout << "��";
				for (SHORT j = 0; j < 60; j++)
				{
					cout << "��";
				}
				cout << "�� ";
			}
			else if (i == 13)
			{
				cout << "��";
				for (SHORT j = 0; j < 60; j++)
				{
					cout << "��";
				}
				cout << "�� ";
			}
			else
			{
				cout << "��";
				for (SHORT j = 0; j < 60; j++)
				{
					cout << " ";
				}
				cout << "�� ";
			}
		}

		Cmder::setCursor(COORD{ position, 14 });
		cout << sentence;

		for (SHORT i = 0; i < 3; i++)//�������
		{
			Cmder::setCursor(COORD{ 43, 19 + i });
			if (i == 0)
			{
				cout << "��";
				for (SHORT j = 0; j < 11; j++)
				{
					cout << "��";
				}
				cout << "�� ";
			}
			else if (i == 2)
			{
				cout << "��";
				for (SHORT j = 0; j < 11; j++)
				{
					cout << "��";
				}
				cout << "�� ";
			}
			else
			{
				cout << "��";
				for (SHORT j = 0; j < 11; j++)
				{
					cout << " ";
				}
				cout << "�� ";
			}
		}

		while (1)//�����
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
	
	/* �D��� */
	int menu()
	{
		enum keyboardValue { Up = 72, Down = 80, Left = 75, Right = 77, Enter = 13, Esc = 27 };
		string option[] = { "�x�s�C��" , "�C������", "���}�C��" , "���}���" };
		COORD optionPosition[] = { {58, 14} , {58, 17} , {58, 20} ,{58, 23} };
		int keypress = 0, optionSet = 0;
		auto select = [=](int set) -> void {
			Cmder::setCursor(optionPosition[set]);
			Cmder::setColor(CLI_BACK_YELLOW);
			cout << option[set];
			Cmder::setCursor(optionPosition[set]);
		};

		Cmder::setColor(CLI_BACK_YELLOW | CLI_BACK_LIGHT);

		for (SHORT i = 0; i < 20; i++)//�~�����
		{
			Cmder::setCursor(COORD{ 50, 10 + i });
			if (i == 0)
			{
				cout << "��";
				for (SHORT j = 0; j < 21; j++)
				{
					cout << "��";
				}
				cout << "�� ";
			}
			else if (i == 19)
			{
				cout << "��";
				for (SHORT j = 0; j < 21; j++)
				{
					cout << "��";
				}
				cout << "�� ";
			}
			else
			{
				cout << "��";
				for (SHORT j = 0; j < 21; j++)
				{
					cout << " ";
				}
				cout << "�� ";
			}
		}

		while (1)//�����
		{
			/* Reset other unselected option color */
			for (int i = 0; i < 4; ++i)
			{
				Cmder::setColor(CLI_BACK_YELLOW | CLI_BACK_LIGHT);
				Cmder::setCursor(optionPosition[i]);
				cout << option[i];
			}
			select(optionSet);

			keypress = _getch();
			switch (keypress)
			{
			case Up:	//Key press Up
				optionSet = (optionSet + 3) % 4;
				break;

			case Down:	//Key press Down
				optionSet = (++optionSet % 4);
				break;

			case Enter:	//Key press Enter
				if (optionSet == 0)
				{
					return 0;
				}
				else if (optionSet == 1)
				{
					return 1;
				}
				else if (optionSet == 2)
				{
					return 2;
				}
				else if (optionSet == 3)
				{
					return 3;
				}
				break;
			default:
				break;
			}
			
		}
		
		return 3;
	}

	/* �C������ */
	bool gameInstructions()
	{
		enum keyboardValue { Up = 72, Down = 80, Left = 75, Right = 77, Enter = 13, Esc = 27 };
		fstream ruler;
		ruler.open("ruler.txt", ios::in);
		vector<string> instructions;
		string sentence;
		int topPos = 0, keypress;

		while (getline(ruler, sentence))
		{
			instructions.push_back(sentence);
		}

		Cmder::setColor();
		Cmder::setCursor(COORD{ 90, 5 });
		cout << "��";
		Cmder::setCursor(20, 6);
		cout << left << setw(85) << " ";
		while (1)//�����
		{
			/* Reset other unselected option color */
			for (short i = 0; i < 26; i++)
			{
				Cmder::setCursor(20, 7 + i);
				cout << left << setw(85) << instructions[i + topPos];
			}
			
			keypress = _getch();
			switch (keypress)
			{
			case Up:	//Key press Up
				if(topPos > 0)
					topPos--;
				break;

			case Down:	//Key press Down
				if (topPos < (instructions.size() - 26))
					topPos++;
				break;

			case Esc:	//Key press Esc
				return 1;
				break;
			default:
				break;
			}

		}

		return 1;
	}

	/* �M������ */
	inline bool clearAll()
	{
		for (short i = 0; i < 50; i++)
		{
			Cmder::setCursor(COORD{ i, 0 });
			cout << setw(160) << " ";
		}
		return 1;
	}
}