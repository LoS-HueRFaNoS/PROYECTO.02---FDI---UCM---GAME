#pragma once
#include "../../ecs/Manager.h"

class ElementManager : public EntityManager
{
public:
	ElementManager(SDLGame* game) : EntityManager(game) {};
	virtual ~ElementManager() {};

	// polimorphic line adder, using move semantics
	template<typename T, typename ... TArgs>
	T* addElement(TArgs&& ... mArgs)
	{
		T* b(new T(game_, this));
		std::unique_ptr<T> uPtr(b);
		entities.emplace_back(std::move(uPtr));
		b->init(std::forward<TArgs>(mArgs)...);
		return b;
	}
};