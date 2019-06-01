#include "pch.h"
#include "Bank.h"
int Bank::Despoit[4] = { 0,0,0,0 };
int Bank::Business[4] = { 
	rand() % 21 + 100 - 10, 
	rand() % 21 + 100 - 10,
	rand() % 21 + 100 - 10,
	rand() % 21 + 100 - 10 
};

Bank::Bank() {};
Bank::~Bank() {};

/* ªÑ²¼º¦´T¡B¶^°± */
void Bank::generate()
{
	srand(time(0));
	for (int i = 0; i < 4; ++i)
	{
		int current = Bank::Business[i];
		int delta = (rand() % 2) ? rand() % 11 - 5 : rand() % 21 - 10;
		Bank::Business[i] += delta;
		
		if (Bank::Business[i] < 70)
		{
			Bank::Business[i] = 70;
			continue;
		}

		if (Bank::Business[i] > 200)
		{
			Bank::Business[i] = 200;
			continue;
		}
	}
}