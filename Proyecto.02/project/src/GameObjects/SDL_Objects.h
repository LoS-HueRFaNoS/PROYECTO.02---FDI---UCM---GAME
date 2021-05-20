#pragma once
#include "../ecs/Entity.h"
#include "../Templates/Resources.h"
#include "../Utilities/SDL_macros.h"
#include <cassert>

typedef unsigned int uint;

class SDL_Object : public Entity
{
public:
	SDL_Object(SDLGame* game, EntityManager* mngr) : Entity(game, mngr) {};
	virtual ~SDL_Object() {};

	virtual void init(SDL_Rect dest, Resources::TextureId imagen) {
		initComponents(POS(dest), dest.w, dest.h, imagen);
	};

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

class Fondo : public SDL_Object
{
private:
	src::TextureId image;
public:
	Fondo(SDLGame* game, EntityManager* mngr) : SDL_Object(game, mngr) {};
	~Fondo() {};
	void init(Vector2D pos, uint ancho, uint alto);
	void changeTheme();
};

class Line : public SDL_Object
{
private:
	Texture* tex_;
public:
	Line(SDLGame* game, EntityManager* mngr) : tex_(nullptr), SDL_Object(game, mngr) {};
	~Line() {
		delete tex_;
		tex_ = nullptr;
	};
	virtual void init(SDL_Rect size, string line, const SDL_Color& color);
	virtual void init(Vector2D pos, uint ancho, uint alto, string line, Resources::FontId font, const SDL_Color& color);
};
