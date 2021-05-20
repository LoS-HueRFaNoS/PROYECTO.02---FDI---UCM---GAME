#include "RPGLogic.h"
#include "../Managers/SDLGame.h"
#include "../Managers/game/ChatManager.h"
#include <iostream>

namespace rpgLogic {

	int throwDice(int n, int dice, bool text)
	{
		int r = 0;
		std::string out1 = "Throwing: " + std::to_string(n);
		out1 += "d" + std::to_string(dice);
		std::string out2 = "";
		for (int i = 0; i < n; i++) {
			int t = SDLGame::instance()->getRandGen()->nextInt(1, dice + 1);
			out2 += std::to_string(t) + " ";
			r += t;
		}
		if (text && ChatManager::instance()) {
			ChatManager::instance()->addLine(out1, LineType::Info);
			ChatManager::instance()->addLine(out2, LineType::Info);
			std::cout << out1 << "\n";
			std::cout << out2 << "\n";
		}
		return r;
	}

	enemyTemplate getRandomEnemy()
	{
		return (enemyTemplate)SDLGame::instance()->getRandGen()->nextInt(0, int(eTem::_lastEnemyTemplateId_));
	}

	heroTemplate getRandomHero()
	{
		return (heroTemplate)SDLGame::instance()->getRandGen()->nextInt(0, int(heroTem::_lastHeroTemplateId_));
	}

	weaponId getRandomWeapon()
	{
		return (weaponId)SDLGame::instance()->getRandGen()->nextInt(0, int(wID::_lastWeaponId_));
	}

	armorId getRandomArmor()
	{
		return (armorId)SDLGame::instance()->getRandGen()->nextInt(0, int(aID::_lastArmorId_));
	}

}
