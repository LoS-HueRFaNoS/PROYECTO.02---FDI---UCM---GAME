#pragma once

#include "../../ecs/Manager.h"

class InterfazManager : public EntityManager {
private:
	bool pause = false;
public:

	InterfazManager(SDLGame* game) : EntityManager(game) {}

	template<typename T, typename ... TArgs>
	T* addButton(TArgs&& ... mArgs)
	{
		T* b(new T(game_, this));
		std::unique_ptr<Entity> uPtr(b);
		entities.emplace_back(std::move(uPtr));
		b->init(std::forward<TArgs>(mArgs)...);
		return b;
	}

	void update() override {
		if (!pause) {
			EntityManager::update();
		}
	}

	void togglePause() { pause = !pause; };
	
	void setPause() {
		for (auto it = entities.begin(); it != entities.end(); it++) {
			(*it)->setPause();
		}
	}
	void setContinue() {
		for (auto it = entities.begin(); it != entities.end(); it++) {
			(*it)->setContinue();
		}
	}
};

