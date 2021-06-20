#pragma once

#include "../../ecs/Manager.h"
#include "../../GameObjects/SDL_Objects.h"

class TextBlockManager : public EntityManager 
{
private:
	friend class TextBlockResources;
	bool pause = false;

public:

	TextBlockManager(SDLGame* game) : EntityManager(game) {}

	// polimorphic line adder, using move semantics
	template<typename ... TArgs>
	Line* addLine(TArgs&& ... mArgs)
	{
		Line* b(new Line(game_, this));
		std::unique_ptr<Entity> uPtr(b);
		entities.emplace_back(std::move(uPtr));
		b->init(std::forward<TArgs>(mArgs)...);
		return b;
	}

	void togglePause() { pause = !pause; };
	bool isPaused() { return pause; };

};
using tb_Mngr = TextBlockManager;
