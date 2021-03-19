#pragma once
#include "Entity.h"
#include "Resources.h"
typedef unsigned int uint;

class Button : public Entity
{
public:
	Button(SDLGame* g, EntityManager* mngr, Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen);
	virtual ~Button() {};
};