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
	this->card[0]  = 0;
	this->card[1]  = 0;
	this->card[2]  = 0;
	this->card[3]  = 0;
	this->wealth = 0;
	this->despoit = 0;
	this->debt = 0;
	this->inGame = true;
	this->stop = false;
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
	info.card[0] = this->card[0];
	info.card[1] = this->card[1];
	info.card[2] = this->card[2];
	info.card[3] = this->card[3];
	info.despoit  = this->despoit;
	info.estate   = this->estate;
	info.debt = this->debt;
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

/* 債務變化 */
int Player::owe(int delta)
{
	this->debt += delta;
	return this->debt;
}


/* 座標變化 */
short Player::nextPosition(int delta)
{
	this->position += delta;
	if (this->position / 28 > 0)
		this->money += 2000;
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

void Player::out()
{
	this->position = 0;
	this->money = 0;
	this->stock[0] = 0;
	this->stock[1] = 0;
	this->stock[2] = 0;
	this->stock[3] = 0;
	this->card[0] = 0;
	this->card[1] = 0;
	this->card[2] = 0;
	this->card[3] = 0;
	this->wealth = 0;
	this->despoit = 0;
	this->debt = 0;
	this->inGame = 0;
	this->stop = 0;
}

void Player::interest()
{
	this->debt *= 1.05;
}