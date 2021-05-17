#pragma once

#include "../../ecs/Manager.h"
#include "../../GameObjects/Button.h"

class InterfazManager : public EntityManager {

public:

	InterfazManager(SDLGame* game) : EntityManager(game) {}

	virtual ~InterfazManager() {};

	template<typename T, typename ... TArgs>
	T* addButton(TArgs&& ... mArgs)
	{
		T* b(new T(game_, this));
		std::unique_ptr<Entity> uPtr(b);
		entities.emplace_back(std::move(uPtr));
		b->init(std::forward<TArgs>(mArgs)...);
		return b;
	}
};
