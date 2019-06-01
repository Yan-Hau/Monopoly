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

/* 取得狀態 */
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

/* 現金變化 */
int Player::cash(int delta)
{
	this->money += delta;
	return this->money;
}

/* 存款變化 */
int Player::bank(int delta)
{
	this->despoit += delta;
	return this->despoit;
}

/* 座標變化 */
short Player::nextPosition(int delta)
{
	this->position += delta;
	this->position %= 28;
	return this->position;
}

/* 買賣房產 */
void Player::setEstate(int estate, int level, bool isBuy)
{
	// 購買
	if (isBuy == true)
	{
		this->estate[estate] = level;
	}

	// 販賣
	else
	{
		this->estate.erase(estate);
	}
}

/* 設置座標 */
void Player::setPosition(short pos)
{
	this->position = pos;
}

/* 金錢設置 */
void Player::setMoney(unsigned int money)
{
	this->money = money;
}

/* 存提款 */
void Player::goBank()
{
	enum keyboardValue { Up = 72, Down = 80, Left = 75, Right = 77, Enter = 13, Esc = 27 };
	COORD optionPosition[] = { {81,9}, {81,11}, {81,13} };
	string option[] = {
		"我要存款", "我要提款", "離開銀行"
	};

	/* 子選單 */
	auto print = [&]() -> void {
		for(int i = 0 ; i < 3 ; ++i)
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
	int keypress , optionSet = 0;

	function<int()> eventTrigger[] = {
		[&]() -> int
		{
			int value;
			COORD _pos = Cmder::getCursor();
			Cmder::setCursor(20,15);
			Cmder::setColor();
			cout << "請輸入金額 : ";
			cin >> value;
			if (value >= 0 && this->money >= value)
			{
				this->bank(value);
				this->cash(-value);
			}
			else
			{
				Cmder::setCursor(20, 16);
				cout << "您沒有那麼多現金, 或是金額輸入負數";
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
			cout << "請輸入金額 : ";
			cin >> value;
			if (value >= 0 && this->despoit >= value)
			{
				this->bank(-value);
				this->cash(value);
			}
			else
			{
				Cmder::setCursor(20, 16);
				cout << "您沒有那麼多存款, 或是金額輸入負數";
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

/* 買賣股票*/
void Player::transStock()
{

}
