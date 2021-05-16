#include "RPGLogic.h"
#include "../Managers/SDLGame.h"
#include <iostream>

namespace rpgLogic {

	int throwDice(int n, int dice, bool text)
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

	enemyTemplate getRandomEnemy()
	{
		return (enemyTemplate)SDLGame::instance()->getRandGen()->nextInt(0, _LastEnemyTemplateId_);
	}

	heroTemplate getRandomHero()
	{
		return (heroTemplate)SDLGame::instance()->getRandGen()->nextInt(0,_LastheroTemplateId_);
	}

	weaponId getRandomWeapon()
	{
		return (weaponId)SDLGame::instance()->getRandGen()->nextInt(0, _LastWeaponId_);
	}

	armorId getRandomArmor()
	{
		return (armorId)SDLGame::instance()->getRandGen()->nextInt(0, _LastArmorId_);
	}

}
