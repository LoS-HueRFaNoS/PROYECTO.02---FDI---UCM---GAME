#pragma once

#include "SDLGame.h"

class Entity;
class Game;
class ButtonMovimiento;
class ButtonCombate;
class ButtonHeroes;
class ButtonInfo;

class EntityManager {
public:
	EntityManager(SDLGame* game);
	virtual ~EntityManager();

	void update();
	void draw();
	Entity* addEntity();
	void addEntity(Entity* e);

	//template<typename T, typename ... TArgs>
	//T* addButtonEntity(TArgs&& ...mArgs);
	/*ButtonMovimiento* addButtonMovimientoEntity();
	ButtonCombate* addButtonCombateEntity();
	ButtonHeroes* addButtonHeroesEntity();
	ButtonInfo* addButtonInfoEntity();*/


protected:
	SDLGame* game_;
	std::vector<std::unique_ptr<Entity>> entities;
};
