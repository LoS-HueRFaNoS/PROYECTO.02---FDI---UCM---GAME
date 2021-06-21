#pragma once

#include <SDL.h>

#include "ecs.h"
#include "../Managers/SDLGame.h"
const enum Look { Norte, Este, Sur, Oeste };
class Entity;
class SDLGame;


class Component {
protected:
	Entity* entity_;
	SDLGame* game_;
	ecs::CmpId id_;
	bool active;
public:
	Component(ecs::CmpId id);
	Component(ecs::CmpId id, SDLGame* g);
	virtual ~Component();

	void setEntity(Entity* entity) {
		entity_ = entity;
	}

	void setGame(SDLGame* game) {
		game_ = game;
	}

	void setId(ecs::CmpId id) {
		id_ = id;
	}

	ecs::CmpId getId() const {
		return id_;
	}

	virtual void init() {
	}
	virtual void update() {
	}
	virtual void draw() {
	}

	// deshabilitar / delete
	void disable() { active = false; }
	bool isActive() const { return active; };

};

