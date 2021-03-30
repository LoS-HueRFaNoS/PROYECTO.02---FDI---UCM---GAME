#pragma once

#include "Manager.h"
#include "Character.h"
#include "jute.h"

class CharacterManager : public EntityManager {
public:
	CharacterManager(SDLGame* game) :EntityManager(game) {
		init();
	}



	Hero* addHeroFromTemplate(rpgLogic::heroTemplate t);
	Hero* addRandomHero();

	Enemy* addEnemyFromTemplate(rpgLogic::enemyTemplate t);
	Enemy* addRandomEnemy();

private:
	void newCharacter(Entity* e);

	void init();

	void loadJson(string json, jute::jValue& j);

	jute::jValue enemyJson;
	jute::jValue heroJson;
};