#pragma once

#include "../Managers/SDLGame.h"

class Entity;
class Game;

class EntityManager {
public:
	EntityManager(SDLGame* game);
	virtual ~EntityManager();

	virtual void update();
	void refresh();
	virtual void draw();
	Entity* addEntity();
	void addEntity(Entity* e);
	void removeEntity(Entity* e);

	const std::vector<std::unique_ptr<Entity>>& entities_() { return entities; };

protected:
	SDLGame* game_;
	std::vector<std::unique_ptr<Entity>> entities;
};
