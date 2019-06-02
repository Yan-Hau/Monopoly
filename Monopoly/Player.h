#pragma once
#include <map>
#include <string>
#include <functional>
#include "Bank.h"

using namespace std;

typedef struct _State {
	short position;
	int money;
	int stock[4];
	int despoit;
	map<int, int> estate;
} State;

class Player
{
public:
	short position;
	int money;
	int stock[4];
	int despoit;
	int wealth;
	int card[4] = { 0 };
	map<int, int> estate;
	bool stop;

public:
	Player();
	~Player();
	State getState();
	int cash(int delta = 0);
	int bank(int delta = 0);
	short nextPosition(int delta);
	void setPosition(short);
	void setMoney(unsigned int);
	void setEstate(int, int, bool isBuy = true);
};

