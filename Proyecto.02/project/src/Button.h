#pragma once
#include "Entity.h"
#include "Resources.h"
#include "callbacks.h"
#include <cassert>

typedef unsigned int uint;

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

class ButtonSlott : public Button
{
	// private: Item* i_;
public:
	ButtonSlott(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};
	~ButtonSlott() {};
	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen) {
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click() {
		// i_->use();
	};
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

enum class AtkType { normal, magic, defend, escape };

class ButtonAttack : public Button {
private:
	AtkType attackType_;
public:
	ButtonAttack(SDLGame* game, EntityManager* mngr) : Button(game, mngr), attackType_(AtkType::normal) {};

	~ButtonAttack() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, AtkType attack) {
		attackType_ = attack;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		callbacks::attackType((int)attackType_);
	}
};

// ----------------------------------------------------

enum class PtnType { health, mana, resurrection };

class ButtonPotion : public Button {
private:
	PtnType potionType_;
public:
	ButtonPotion(SDLGame* game, EntityManager* mngr) : Button(game, mngr), potionType_(PtnType::health) {};

	~ButtonPotion() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, PtnType potion) {
		potionType_ = potion;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		callbacks::potionType((int)potionType_);
	}
};

// ----------------------------------------------------

#pragma region ButtonPanelResources
#include "callbacks.h"
#include "ecs_interfaz.h"
class Panel;

using namespace interfaz;

class ButtonPanelCte : public Button {
private:
	Panel* pan_;
public:
	ButtonPanelCte(SDLGame* game, EntityManager* mngr) : Button(game, mngr), pan_(nullptr) {};

	~ButtonPanelCte() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, Panel* p) {
		pan_ = p;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click();
};

#pragma endregion

// ----------------------------------------------------