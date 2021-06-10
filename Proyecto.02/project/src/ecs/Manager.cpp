#include "Manager.h"
#include "Entity.h"
#include "../GameObjects/Button.h"
#include "../Game.h"

EntityManager::EntityManager(SDLGame *game) :
		game_(game) {
}

EntityManager::~EntityManager() {
	//entities.clear();
}

void EntityManager::update() {
	auto n = entities.size();
	for (auto i = 0u; i < n; i++)
	{
		if (entities[i]->isActive())
			entities[i]->update();
	}
	refresh();
}

void EntityManager::refresh() {
	for (auto it = entities.begin(); it != entities.end();) {
		if (!(*it).get()->isActive()) {
			it = entities.erase(it);
		}
		else
			it++;
	}	
}

void EntityManager::draw() {
	auto n = entities.size();
	for (auto i = 0u; i < n; i++)
	{
		if (entities[i]->isActive())
			entities[i]->draw();
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

void EntityManager::removeEntity(Entity* e)
{
	for (auto it = entities.begin(); it != entities.end();) {
		if ((*it).get() == e) {
			it = entities.erase(it);
		}
		else
			it++;
	}
}

