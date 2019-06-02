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

