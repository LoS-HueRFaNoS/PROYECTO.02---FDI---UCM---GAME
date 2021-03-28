#include "RPGLogic.h"
#include "SDLGame.h"
#include <iostream>

int rpgLogic::throwDice(int n, int dice, bool text)
{
	int r = 0;
	if (text) cout << "Throwing: " << n << "d" << dice << endl;
	for (int i = 0; i < n; i++) {
		int t = SDLGame::instance()->getRandGen()->nextInt(1, dice + 1);
		if (text) cout << t << " ";
		r += t;
	}
	if (text) cout << "\n";
	return r;
}
