#pragma once
#include "../../ecs/Component.h"
#include "../../Structures/Vector2D.h"
#include "../../GameObjects/Character.h"
#include <vector>

class Panel;
class InterfazManager;

class DadosP : public Component
{
private:
	const unsigned int SIZE = 25;

protected:
	Panel* pan_;
	InterfazManager* iM_;

	Vector2D pos_;
	Vector2D offset_;
	std::vector<Hero*>* heroes_;

public:
	DadosP(SDLGame* game, Panel* pan, InterfazManager* iM,
		Vector2D pos, Vector2D off, std::vector<Hero*>* her);
	~DadosP();
	virtual void init();
	virtual void update();
};