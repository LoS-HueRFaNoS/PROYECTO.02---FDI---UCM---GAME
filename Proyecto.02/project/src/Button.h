#pragma once
#include "Entity.h"
#include "Resources.h"
#include "callbacks.h"
//#include <SDL.h>
#include <cassert>
typedef unsigned int uint;

class Game;
using CallBackOnClick = void(Game* app);

class Button : public Entity
{
private:
	CallBackOnClick* cb = nullptr;
public:
	Button(SDLGame* game, Game* g, EntityManager* mngr, Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen);
	virtual ~Button() {};
	void click(Game* i)
	{
		assert(cb != nullptr);
		cb(i);
		int n = 0;
	};
	//void setCB(void c) { cb = static_cast<CallBackOnClick2*>(c); };
	//void setCB(void callback(Interfaz* app)) { cb = callback; };
	void setCB(CallBackOnClick* callback) { cb = callback; };
};