#pragma once
#include "Entity.h"
#include "Resources.h"
#include "callbacks.h"
#include <cassert>

typedef unsigned int uint;

enum class AtkType { normal, magic, defend, escape };
enum class Inf { inventory, potionHealth, potionMana, chat, config };

//class InterfazManager;
class Button : public Entity
{
protected:

	void initComponents(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen);

public:
	Button(SDLGame* game, EntityManager* mngr) :
		Entity(game, mngr)
	{};
	~Button() {};
	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen) {
		initComponents(pos, ancho, alto, imagen);
	};

	virtual void click() = 0;
};

// ----------------------------------------------------

enum class MovType { rotR, rotL, forward, touch };

class ButtonMovimiento : public Button {
private:
	MovType movementType_;
public:
	ButtonMovimiento(SDLGame* game, EntityManager* mngr) : Button(game, mngr), movementType_(MovType::touch){};

	~ButtonMovimiento() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, MovType movement) {
		movementType_ = movement;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click() 
	{
		callbacks::movCommand((int)movementType_);
	}
};

// ----------------------------------------------------

enum class HeroNum { hero1, hero2, hero3, hero4 };

class ButtonHero : public Button {
private:
	HeroNum heroType_;
public:
	ButtonHero(SDLGame* game, EntityManager* mngr) : Button(game, mngr), heroType_(HeroNum::hero1) {};

	~ButtonHero() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, HeroNum hero) {
		heroType_ = hero;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		callbacks::heroType((int)heroType_);
	}
};

// ----------------------------------------------------

enum class accionMenu { start, how_to_play, options, quit};

class ButtonMenu : public Button {
private:
	
public:
	ButtonMenu(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};

	~ButtonMenu() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen) {
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		//callbacks::((int)heroType_);
	}
};
// ----------------------------------------------------



// ----------------------------------------------------



// ----------------------------------------------------