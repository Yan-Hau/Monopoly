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
private:
	short position;
	int money;
	int stock[4];
	int despoit;
	map<int, int> estate;

public:
	Player();
	~Player();
	State getState();
	int wealth;
	int cash(int delta = 0);
	int bank(int delta = 0);
	short nextPosition(int delta);
	void setPosition(short);
	void setMoney(unsigned int);
	void setEstate(int, int, bool isBuy = true);
	void goBank();
	void transStock();

};

