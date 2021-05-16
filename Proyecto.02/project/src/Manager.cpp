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
	auto n = entities.size();
	for (auto i = 0u; i < n; i++)
	{
		if (entities[i]->isActive())
			entities[i]->update();
	}
		
	/*for (auto& e : entities)
		e->update();*/
	/*for (auto it = entities.begin(); it != entities.end();it++) {
		(*it)->update();
	}*/
	refresh(); // sólo si todos los managers lo necesitan
}

void EntityManager::refresh() {
	// elimina todas las entidades dehabilitados
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

