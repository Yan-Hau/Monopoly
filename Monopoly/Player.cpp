#include "pch.h"
#include "Player.h"


Player::Player()
{
	this->position = 0;
	this->money = 30000;
	this->stock[0] = 0;
	this->stock[1] = 0;
	this->stock[2] = 0;
	this->stock[3] = 0;
}


Player::~Player()
{
}

/* ���o���A */
State Player::getState()
{
	State info;
	info.position = this->position;
	info.money	  = this->money;
	info.stock[0] = this->stock[0];
	info.stock[1] = this->stock[1];
	info.stock[2] = this->stock[2];
	info.stock[3] = this->stock[3];
	info.despoit  = this->despoit;
	info.estate   = this->estate;
	return info;
}

/* �{���ܤ� */
int Player::cash(int delta)
{
	this->money += delta;
	return this->money;
}

/* �s���ܤ� */
int Player::bank(int delta)
{
	this->despoit += delta;
	return this->despoit;
}

/* �y���ܤ� */
short Player::nextPosition(int delta)
{
	this->position += delta;
	this->position %= 28;
	return this->position;
}

/* �R��в� */
void Player::setEstate(int estate, int level, bool isBuy)
{
	// �ʶR
	if (isBuy == true)
	{
		this->estate[estate] = level;
	}

	// �c��
	else
	{
		this->estate.erase(estate);
	}
}

/* �]�m�y�� */
void Player::setPosition(short pos)
{
	this->position = pos;
}

/* �����]�m */
void Player::setMoney(unsigned int money)
{
	this->money = money;
}

/* �s���� */
void Player::goBank()
{
	enum keyboardValue { Up = 72, Down = 80, Left = 75, Right = 77, Enter = 13, Esc = 27 };
	COORD optionPosition[] = { {20,9}, {20,11}, {20,13} };
	string option[] = {
		"�ڭn�s��", "�ڭn����", "���}�Ȧ�"
	};

	/* �l��� */
	auto print = [&]() -> void {
		for(int i = 0 ; i < 3 ; ++i)
		{
			Cmder::setCursor(optionPosition[i]);
			Cmder::setColor(CLI_FONT_WHITE);
			cout << option[i];
			Cmder::setCursor(optionPosition[i]);
		}
	};

	/* �l����� */
	auto select = [&](int set) -> void {
		Cmder::setCursor(optionPosition[set]);
		Cmder::setColor(CLI_FONT_RED);
		cout << option[set];
		Cmder::setCursor(optionPosition[set]);
	};
	int keypress , optionSet = 0;

	function<int()> eventTrigger[] = {
		[&]() -> int
		{
			int value;
			COORD _pos = Cmder::getCursor();
			Cmder::setCursor(20,15);
			Cmder::setColor();
			cout << "�п�J���B : ";
			cin >> value;
			if (value >= 0 && this->money >= value)
			{
				this->bank(value);
				this->cash(-value);
			}
			else
			{
				Cmder::setCursor(20, 16);
				cout << "�z�S������h�{��, �άO���B��J�t��";
				_getch();
			}
			Cmder::setCursor(20, 15);
			printf("%50c", ' ');
			Cmder::setCursor(20, 16);
			printf("%50c", ' ');
			Cmder::setCursor(_pos);
			return 1;
		},

		[&]() -> int
		{
			int value;
			COORD _pos = Cmder::getCursor();
			Cmder::setCursor(20,15);
			Cmder::setColor();
			cout << "�п�J���B : ";
			cin >> value;
			if (value >= 0 && this->despoit >= value)
			{
				this->bank(-value);
				this->cash(value);
			}
			else
			{
				Cmder::setCursor(20, 16);
				cout << "�z�S������h�s��, �άO���B��J�t��";
				_getch();
			}
			cin.get();
			Cmder::setCursor(20, 15);
			printf("%50c", ' ');
			Cmder::setCursor(20, 16);
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
	while(loop)
	{ 
		keypress = _getch();
		switch (keypress)
		{
		case Up:
			optionSet = (optionSet + 2) % 3;
			break;

		case Down:
			optionSet = (++optionSet) % 3;
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

/* �R��Ѳ�*/
void Player::transStock()
{
	enum keyboardValue { Up = 72, Down = 80, Left = 75, Right = 77, Enter = 13, Esc = 27 };
	COORD optionPosition[] = { {20,9}, {20,11}, {20,13} , {20,15} , {30,9}, {30,11}, {30,13} , {30,15} , {30,17} };
	string option[] = {
		"�R�iA��", "�R�iB��", "�R�iC��" , "�R�iD��",
		"��XA��", "��XB��", "��XC��" , "��XD��",
		"���}�����",
	};

	/* �l��� */
	auto print = [&]() -> void {
		for (int i = 0; i < 9; ++i)
		{
			Cmder::setCursor(optionPosition[i]);
			Cmder::setColor(CLI_FONT_WHITE);
			cout << option[i];
			Cmder::setCursor(optionPosition[i]);
		}
	};

	/* �l����� */
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
			int amount;
			COORD _pos = Cmder::getCursor();
			Cmder::setCursor(20,19);
			Cmder::setColor();
			cout << "�п�J�ʶR�Ѽ�: ";
			cin >> amount;
			if (amount >= 0 && this->despoit  >= amount * Bank::Business[stockNum])
			{
				this->bank(-amount * Bank::Business[stockNum]);
				this->stock[stockNum] += amount;
			}
			else
			{
				Cmder::setCursor(20, 20);
				cout << "�z�S������h�s��, �άO�Ѽƿ�J�t��";
				_getch();
			}
			Cmder::setCursor(20, 19);
			printf("%50c", ' ');
			Cmder::setCursor(20, 20);
			printf("%50c", ' ');
			Cmder::setCursor(_pos);
			return 1;
		},

		[&](int stockNum) -> int
		{
			int amount;
			COORD _pos = Cmder::getCursor();
			Cmder::setCursor(20,19);
			Cmder::setColor();
			cout << "�п�J��X�Ѽ�: ";
			cin >> amount;
			if (amount >= 0 && this->stock[stockNum] >= amount)
			{
				this->bank(amount * Bank::Business[stockNum]);
				this->stock[stockNum] -= amount;
			}
			else
			{
				Cmder::setCursor(20, 20);
				cout << "�z�S������h�Ѳ�, �άO�Ѽƿ�J�t��";
				_getch();
			}
			Cmder::setCursor(20, 19);
			printf("%50c", ' ');
			Cmder::setCursor(20, 20);
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
			if(4 <= optionSet && optionSet <= 7)
				optionSet = (optionSet - 4) % 9;
			break;
		case Right:
			if (0 <= optionSet && optionSet <= 3)
				optionSet = (optionSet + 4) % 9;
			break;

		case Enter:
			loop = eventTrigger[optionSet/4](optionSet%4);
			break;
		}
		print();
		select(optionSet);
	}
	
	return;
}

/* �ϥιD�� */
void Player::useCard()
{
	enum keyboardValue { Up = 72, Down = 80, Left = 75, Right = 77, Enter = 13, Esc = 27 };
	COORD optionPosition[] = { {81,9}, {81,11}, {81,13}, {81, 15}, {81, 17} };
	string option[] = {
		"�{���d", "���٥d", "�ЫΥd", "�K�O�d", "���ϥ�"
	};

	/* �l��� */
	auto print = [&]() -> void {
		for (int i = 0; i < 5; ++i)
		{
			Cmder::setCursor(optionPosition[i]);
			Cmder::setColor(CLI_FONT_WHITE);
			cout << option[i];
			Cmder::setCursor(optionPosition[i]);
		}
	};

	/* �l����� */
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
			optionSet = (optionSet + 2) % 5;
			break;

		case Down:
			optionSet = (++optionSet) % 5;
			break;

		case Enter:
			if (optionSet == 4)		 //���ϥ�
				break;

			else if (this->card[optionSet] > 0)
			{
				this->card[optionSet] -= 1;

				switch (optionSet)
				{
				case 0:				//�{���d
					break;

				case 1:				//���٥d
					break;

				case 2:				//�ЫΥd
					break;

				case 3:				//�K�O�d
					break;
				}
			}
			else {
				Cmder::setCursor(20, 16);
				cout << "�z�S���o���D��";
			}
		}
		print();
		select(optionSet);
	}
}
