#pragma once
#include "Entity.h"
#include "Resources.h"
#include "Manager.h"
#include <cassert>
class Game;
typedef unsigned int uint;
class Cursor : public Entity
{
public:
	Cursor(SDLGame* game, EntityManager* mngr) : Entity(game, mngr) {};
	void init(SDLGame* game, Game* g, Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen);
};

