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
	this->card[4]  = 0;
	this->wealth = 0;
	this->despoit = 0;
	this->debt = 0;
	this->inGame = true;
	this->stop = false;
	this->nextStep = 0;
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

/* �Ű��ܤ� */
int Player::owe(int delta)
{
	this->debt += delta;
	return this->debt;
}


/* �y���ܤ� */
short Player::nextPosition(int delta)
{
	this->position += delta;
	if (this->position / 28 > 0)
		this->money += 2000;
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
}

void Player::interest()
{
	this->debt *= 1.05;
}