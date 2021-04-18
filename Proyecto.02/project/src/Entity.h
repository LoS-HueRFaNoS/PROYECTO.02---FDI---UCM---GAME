#pragma once

#include <iostream>
#include <array>
#include "Component.h"
#include "Manager.h"
#include "SDLGame.h"

class EntityManager;

class Entity {
public:
	Entity(SDLGame *game, EntityManager* mngr);
	virtual ~Entity();

	EntityManager* getEntityMangr() {
		return mngr_;
	}

	SDLGame* getSDLGame() {
		return game_;
	}

	template<typename T, typename ... TArgs>
	T* addComponent(TArgs&& ...mArgs) {
		T *c(new T(std::forward<TArgs>(mArgs)...));
		std::unique_ptr<Component> uPtr(c);
		components_.push_back(std::move(uPtr));
		componentsArray_[c->getId()] = c;
		c->setEntity(this);
		c->setGame(game_);
		c->init();
		return c;
	}

	void deleteComponent(ecs::CmpIdType id) {
		for (auto it = components_.begin(); it != components_.end(); /**/)
		{
			if ((*it).get()->getId() == id) {
				it = components_.erase(it);
			}
			else it++;
		}		
		Component* c = componentsArray_[id];
		componentsArray_[id] = nullptr;
		delete c;
	}

	template<typename T>
	T* getComponent(ecs::CmpIdType id) {
		return static_cast<T*>(componentsArray_[id]);
	}

	bool hasComponent(ecs::CmpIdType id) {
		return componentsArray_[id] != nullptr;
	}

	void update() {
		if (!enabled) return;
		for (auto &c : components_) {
			c->update();
		}
	}

	void draw() {
		if (!enabled) return;
		for (auto &c : components_) {
			c->draw();
		}
	}

	void toggleEnabled() {
		enabled = !enabled;
	}

protected:
	SDLGame *game_;
	EntityManager* mngr_;

	bool enabled;

	std::vector<unique_ptr<Component>> components_;
	std::array<Component*,ecs::maxComponents> componentsArray_ = {};
};