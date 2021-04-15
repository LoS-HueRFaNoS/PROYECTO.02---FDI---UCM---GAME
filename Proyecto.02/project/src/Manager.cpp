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

void EntityManager::addEntity(Entity* e) {
	std::unique_ptr<Entity> uPtr(e);
	entities.emplace_back(std::move(uPtr));
}

void EntityManager::removeEntiy(Entity* e)
{
	for (auto it = entities.begin(); it != entities.end();) {
		if ((*it).get() == e) {
			it = entities.erase(it);
		}
		else
			it++;
	}
}

