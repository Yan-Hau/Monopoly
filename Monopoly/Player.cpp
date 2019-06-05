#include "pch.h"
#include "Player.h"


Player::Player()
{
	this->position = 0;   //目前座標
	this->money = 30000;  //現金
	this->despoit = 0;	  //存款
	this->debt = 0;		  //債務

	/* 股票數量 */
	this->stock[0] = 0;
	this->stock[1] = 0;
	this->stock[2] = 0;
	this->stock[3] = 0;

	/* 道具數量 */
	this->card[0]  = 0;
	this->card[1]  = 0;
	this->card[2]  = 0;
	this->card[3]  = 0;
	this->card[4]  = 0;
	
	
	
	this->oweTurn = 0;
	this->inGame = true; //是否出局
	this->stop = false;  //是否暫停一回合
	this->nextStep = 0;  //下一次移動
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
	info.card[4] = this->card[4];
	info.despoit  = this->despoit;
	info.estate   = this->estate;
	info.debt = this->debt;
	info.nextStep = this->nextStep;
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
	this->money = -1;
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
	this->inGame = false;
	this->stop = true;
	this->estate.clear();
}

void Player::interest()
{
	if (this->debt <= 0)
		this->oweTurn = 0;

	if (this->debt > 0)
		++this->oweTurn;


	this->debt = this->debt* (1 + 0.15 * this->oweTurn);
}