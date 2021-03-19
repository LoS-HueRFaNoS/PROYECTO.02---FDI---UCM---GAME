#include "RPGLogic.h"
#include "SDLGame.h"


int rpgLogic::throwDice(int n, int dice)
{
	int r = 0;
	for (int i = 0; i < n; i++)
		r += SDLGame::instance()->getRandGen()->nextInt(1, dice + 1);
	return r;
}
