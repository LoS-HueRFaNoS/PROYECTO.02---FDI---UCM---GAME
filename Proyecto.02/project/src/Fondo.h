#pragma once
#include "Entity.h"
#include "Resources.h"
#include <cassert>

class Interfaz;
typedef unsigned int uint;
class Fondo : public Entity
{
public:
	Fondo(SDLGame* game, EntityManager* mngr) : Entity(game, mngr) {};
	void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen);
};
