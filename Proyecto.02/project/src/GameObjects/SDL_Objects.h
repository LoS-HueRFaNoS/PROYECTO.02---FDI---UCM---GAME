#pragma once
#include "../ecs/Entity.h"
#include "../Templates/Resources.h"
#include <cassert>

typedef unsigned int uint;

class SDL_Object : public Entity
{
public:
	SDL_Object(SDLGame* game, EntityManager* mngr) : Entity(game, mngr) {};
	virtual ~SDL_Object() {};
	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen) {
		initComponents(pos, ancho, alto, imagen);
	};
	virtual void init(Vector2D pos, uint ancho, uint alto, Texture* imagen) {
		initComponents(pos, ancho, alto, imagen);
	};
protected:
	void initComponents(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen);
	void initComponents(Vector2D pos, uint ancho, uint alto, Texture* imagen);

};

class Fondo : public Entity
{
public:
	Fondo(SDLGame* game, EntityManager* mngr) : Entity(game, mngr) {};
	void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen);
};

class Line : public SDL_Object
{
public:
	Line(SDLGame* game, EntityManager* mngr) : SDL_Object(game, mngr) {};
	~Line() {};
	virtual void init(Vector2D pos, uint ancho, uint alto, string line, Resources::FontId font, const SDL_Color& color);
};
