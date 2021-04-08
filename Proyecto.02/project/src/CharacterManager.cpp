#include "CharacterManager.h"
#include <fstream>

void CharacterManager::init()
{
	loadJson(Resources::jsons_[Resources::Heroes].filename, heroJson);
	loadJson(Resources::jsons_[Resources::Enemies].filename, enemyJson);
}

void CharacterManager::loadJson(string json, jute::jValue& j)
{
	ifstream in(json);

	if (in.is_open()) {
		// Guardamos todo lo que se puede leer del archivo en un string
		string str = "";
		string tmp;
		while (getline(in, tmp)) str += tmp;

		in.close();

		// El parser lo transforma de string a un Jvalue del que podremos sacar la informaci�n
		j = jute::parser::parse(str);
	}
	else
		;	// HACER EL THROW
}

Hero* CharacterManager::addHeroFromTemplate(rpgLogic::heroTemplate t)
{
	Hero* h = new Hero(game_, this);
	h->loadFromTemplate(heroJson, t);
	newCharacter(h);
	return h;
}

Hero* CharacterManager::addRandomHero()
{
	Hero* h = new Hero(game_, this);
	h->loadFromTemplate(heroJson, getRandomHero());
	newCharacter(h);
	return h;
}

Enemy* CharacterManager::addEnemyFromTemplate(rpgLogic::enemyTemplate t)
{
	Enemy* e = new Enemy(game_, this);
	e->loadFromTemplate(enemyJson, t);
	newCharacter(e);
	return e;
}

Enemy* CharacterManager::addRandomEnemy()
{
	Enemy* e = new Enemy(game_, this);
	e->loadFromTemplate(enemyJson, getRandomEnemy());
	newCharacter(e);
	return e;
}

void CharacterManager::newCharacter(Entity* e)
{
	std::unique_ptr<Entity> uPtr(e);
	entities.emplace_back(std::move(uPtr));
}
