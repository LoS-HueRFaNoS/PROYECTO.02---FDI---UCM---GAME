#pragma once

#include "Component.h"
#include "checkML.h"

class Game;
using CallBackOnClick = void(Game* app);

class Button : public Component
{
private:
	CallBackOnClick* cbOnClick = nullptr;
public:
	Button() : Component(ecs::Button) {};
	virtual ~Button() {};
protected:

};

