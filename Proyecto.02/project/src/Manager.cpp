#include "Manager.h"
#include "Entity.h"

EntityManager::EntityManager(SDLGame *game) :
		game_(game) {
}

EntityManager::~EntityManager() {
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
