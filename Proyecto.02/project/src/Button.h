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
		// if(i_ != nulptr) i_->use();
	};
};

class ButtonLine : public Button
{
	// private: Item* i_;
public:
	ButtonLine(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};
	~ButtonLine() {};
	virtual void init(Vector2D pos, uint ancho, uint alto, string line, Resources::FontId font, const SDL_Color &color);

	virtual void click() {
		// if(i_ != nulptr) i_->use();
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
#pragma ButtonHeroes
#include "../TheElementalMaze.h"

#pragma endregion

// ----------------------------------------------------

enum class AtkType { normal, magic };

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

enum class DfndType { defend, escape };

class ButtonDefend : public Button {
private:
	DfndType defendType_;
public:
	ButtonDefend(SDLGame* game, EntityManager* mngr) : Button(game, mngr), defendType_(DfndType::defend) {};

	~ButtonDefend() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, DfndType attack) {
		defendType_ = attack;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		callbacks::defendType((int)defendType_);
	}
};

enum class target { target01, target02, target03, target04, target05 };

class ButtonTarget : public Button {
private:
	target target_;
public:
	ButtonTarget(SDLGame* game, EntityManager* mngr) : Button(game, mngr), target_(target::target01) {};

	~ButtonTarget() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, target attack) {
		target_ = attack;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		callbacks::addTarget((int)target_);
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
#include "../TheElementalMaze.h"

class Interfaz;
class Panel;

using namespace interfaz;

// activa / desactiva los botones de un panel concreto
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

// crear / destruye en tiempo de ejecución los botones de un panel concreto
class ButtonPanel : public Button {
protected:
	bool activated;
	idPanel pan_;
public:
	ButtonPanel(SDLGame* game, EntityManager* mngr) : Button(game, mngr), activated(true), pan_(Fight) {};

	~ButtonPanel() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, idPanel p, bool active) {
		activated = active;
		pan_ = p;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		callbacks::createPanel(activated, pan_);
		activated = !activated;
	}

	bool getActive() { return activated; };
	void setActive(bool set_) { activated = set_; };
};

enum class HeroNum { hero1, hero2, hero3, hero4 };

class ButtonHero : public ButtonPanel {
private:
	HeroNum heroType_;
public:
	ButtonHero(SDLGame* game, EntityManager* mngr) : ButtonPanel(game, mngr), heroType_(HeroNum::hero1) {};

	~ButtonHero() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, HeroNum hero, idPanel p, bool active) {
		heroType_ = hero;
		ButtonPanel::init(pos, ancho, alto, imagen, p, active);
	};

	virtual void click();
};
#pragma endregion

// ----------------------------------------------------

#pragma region ButtonCombateResources
#include "callbacks.h"
#include "ecs_interfaz.h"
#include "Interfaz.h"

enum class HbltType { hability1, hability2, hability3, hability4 };

class ButtonHability : public Button {
private:
	HbltType hability_;
	bool activated;
	idPanel pan_;
public:
	ButtonHability(SDLGame* game, EntityManager* mngr) : Button(game, mngr), hability_(HbltType::hability1) {};

	~ButtonHability() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, HbltType attack, idPanel panId, bool active, Panel* p_);

	virtual void click()
	{
		callbacks::createPanel(activated, pan_);
		activated = !activated;
		callbacks::set_hability((int)hability_);
	}
};

#pragma endregion

// ----------------------------------------------------