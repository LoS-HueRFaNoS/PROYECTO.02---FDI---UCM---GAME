#include "Manager.h"
#include "Entity.h"
#include "Button.h"
#include "Game.h"

EntityManager::EntityManager(SDLGame *game) :
		game_(game) {
}

EntityManager::~EntityManager() {
	entities.clear();
}

void EntityManager::update() {
	for (auto &e : entities) {
		e->update();
	}
}

void EntityManager::draw() {
	for (auto &e : entities) {
		e->draw();
	}
}

Entity* EntityManager::addEntity() {
	Entity* e = new Entity(game_,this);
	std::unique_ptr<Entity> uPtr( e );
	entities.emplace_back(std::move(uPtr));
	return e;
}

/*
template<typename T, typename ... TArgs>
T* EntityManager::addButtonEntity(TArgs&& ...mArgs) {
	T* e(new T(std::forward<TArgs>(mArgs)...));
	std::unique_ptr<Button> uPtr(e);
	entities.emplace_back(std::move(uPtr));
	return e;
}
*/

//ButtonMovimiento* EntityManager::addButtonMovimientoEntity() {
//	ButtonMovimiento* e = new ButtonMovimiento(game_, this);
//	std::unique_ptr<Entity> uPtr(e);
//	entities.emplace_back(std::move(uPtr));
//	return e;
//}
//
//ButtonCombate* EntityManager::addButtonCombateEntity() {
//	ButtonCombate* e = new ButtonCombate(game_, this);
//	std::unique_ptr<Entity> uPtr(e);
//	entities.emplace_back(std::move(uPtr));
//	return e;
//}
//
//ButtonHeroes* EntityManager::addButtonHeroesEntity() {
//	ButtonHeroes* e = new ButtonHeroes(game_, this);
//	std::unique_ptr<Entity> uPtr(e);
//	entities.emplace_back(std::move(uPtr));
//	return e;
//}
//
//ButtonInfo* EntityManager::addButtonInfoEntity() {
//	ButtonInfo* e = new ButtonInfo(game_, this);
//	std::unique_ptr<Entity> uPtr(e);
//	entities.emplace_back(std::move(uPtr));
//	return e;
//}