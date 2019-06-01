#pragma once
#include"ConsoleInterface.h"
#include"Player.h"
#include <ctime>
#include <algorithm>
#include <cstdlib>
using namespace std;

class Bank
{
public:
	Bank();
	~Bank();
	void generate();
	static int Despoit[4];
	static int Business[4];
};

