#pragma once
#include "SDL_Objects.h"
#include "../Templates/callbacks.h"
#include "../Structures/Item.h"
#include <cassert>

// ----------------------------------------------------

class Button : public SDL_Object
{
public:
	Button(SDLGame* game, EntityManager* mngr) :
		SDL_Object(game, mngr)
	{};
	virtual ~Button() {};
	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen);
	virtual void init(SDL_Rect dest, Resources::TextureId imagen);

	virtual void click() = 0;
};

// ----------------------------------------------------

class ButtonSettings : public Button
{
public:
	ButtonSettings(SDLGame* game, EntityManager* mngr) :
		Button(game, mngr)
	{};
	virtual ~ButtonSettings() {};
	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen) {
		Button::init(pos, ancho, alto, imagen);
	};
	virtual void init(SDL_Rect dest, Resources::TextureId imagen) {
		Button::init(dest, imagen);
	};

	virtual void click() { callbacks::toggleThemeFondo(); };
};

// ----------------------------------------------------

class ButtonSlott : public Button
{
private:
	Item* i_;
public:
	ButtonSlott(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};
	~ButtonSlott() {};
	virtual void init(SDL_Rect dest, Item* item);
	virtual void init(Vector2D pos, uint ancho, uint alto, Item* item);

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
		game_->getAudioMngr()->playChannel(Resources::AudioId::Boton1, 0, 0);
		callbacks::movCommand((int)movementType_);
	}
};

// ----------------------------------------------------


// ----------------------------------------------------

enum class CmbtType { attack, magic, defend, escape };

class ButtonCombate : public Button {
private:
	CmbtType combatType_;
public:
	ButtonCombate(SDLGame* game, EntityManager* mngr) : Button(game, mngr), combatType_(CmbtType::attack) {};

	~ButtonCombate() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, CmbtType combate) {
		combatType_ = combate;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		callbacks::combatType((int)combatType_);
	}
};

enum class target { target01, target02, target03, target04, target05 };

class ButtonTarget : public Button {
private:
	target target_;
public:
	ButtonTarget(SDLGame* game, EntityManager* mngr) : Button(game, mngr), target_(target::target01) {};

	~ButtonTarget() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, target objetive) {
		target_ = objetive;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		callbacks::addTarget((int)target_);
	}
};
// ----------------------------------------------------

enum class accionMenu { start, lobby, how_to_play, options, quit, shop, stash, shop_lobby, stash_lobby};

class ButtonMenu : public Button {
private:
	accionMenu tipo;
	Interfaz* app;
public:
	ButtonMenu(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};

	~ButtonMenu() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, accionMenu type, Interfaz* app_) {
		tipo = type;
		app = app_;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		switch (tipo)
		{
		case accionMenu::start:
			callbacks::startExp(app);
			break;
		case accionMenu::lobby:
			callbacks::startLobby(app);
			break;
		case accionMenu::how_to_play:
			callbacks::howToPlay(app);
			break;
		case accionMenu::options:
			callbacks::options(app);
			break;
		case accionMenu::quit:
			callbacks::quit(app);
			break;
		case accionMenu::shop:
			callbacks::shop(app);
			break;
		case accionMenu::stash:
			callbacks::stash(app);
			break;
		case accionMenu::stash_lobby:
			callbacks::stash_lobby(app);
			break;
		case accionMenu::shop_lobby:
			callbacks::shop_lobby(app);
			break;
		default:
			break;
		}
		
	}
};
// ----------------------------------------------------



class ButtonHeroEquipar : public Button {
private:
	int heroeid;
	Interfaz* app;
public:
	ButtonHeroEquipar(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};

	~ButtonHeroEquipar() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, int her, Interfaz* app_) {
		heroeid = her;
		app = app_;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		callbacks::equiparHeroe(app, heroeid);

	}
};
// ----------------------------------------------------

class ButtonCompra : public Button {
private:
	int itemid;
	int itemType;
	Interfaz* app;
public:
	ButtonCompra(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};

	~ButtonCompra() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen,int itemId_, int itemType_, Interfaz* app_) {
		itemid = itemId_;
		itemType = itemType_;
		app = app_;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		callbacks::shopping(app, itemType, itemid);

	}
};
// ----------------------------------------------------


enum class accionOption {volumen, velocidad  };


class ButtonOption : public Button {
private:
	accionOption tipo;
	Interfaz* app;
	int value;
public:
	ButtonOption(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};

	~ButtonOption() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, accionOption type, Interfaz* app_) {
		tipo = type;
		app = app_;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		switch (tipo)
		{
		case accionOption::volumen:

			break;
		case accionOption::velocidad:

			break;
		default:
			break;
		}

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
		game_->getAudioMngr()->haltMusic();
		game_->getAudioMngr()->setChannelVolume(30, 0);
		//game_->getAudioMngr()->haltChannel(0);

		callbacks::potionType((int)potionType_);
	}
};

// ----------------------------------------------------

#pragma region ButtonPanelResources
#include "../Templates/callbacks.h"
#include "../ecs/ecs_interfaz.h"
#include "../Components/Sprite.h"
#include "../Managers/TheElementalMaze.h"

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

// crear / destruye en tiempo de ejecuci�n los botones de un panel concreto
class ButtonPanel : public Button {
protected:
	bool activated;
	idPanel pan_;

	void setActive(bool set);
	void setHide(bool set);

public:
	ButtonPanel(SDLGame* game, EntityManager* mngr) : Button(game, mngr), activated(true), pan_(Fight) {};

	~ButtonPanel() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, idPanel p, bool active) {
		setActive(active);
		pan_ = p;
		Button::init(pos, ancho, alto, imagen);
		addComponent<Sprite>(game_->getTextureMngr()->getTexture(Resources::Selected), 0, 0, true, true); // marco select
	};

	virtual void click()
	{
		game_->getAudioMngr()->playMusic(Resources::Exploracion, -1);
		game_->getAudioMngr()->setMusicVolume(50);

		callbacks::createPanel(activated, pan_);
		if (!activated) turnON();
		else turnOFF();
	}

	virtual bool getActive() { return activated; };
	virtual void turnON() { setActive(true), setHide(false); }
	virtual void turnOFF() { setActive(false), setHide(true); }

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

	HeroNum getNumHero() { return heroType_; };

};
#pragma endregion

// ----------------------------------------------------

#pragma region ButtonCombateResources
#include "../Templates/callbacks.h"
#include "../Components/Interfaz.h"

class ButtonHability : public Button {
private:
	uint hability_;

public:
	ButtonHability(SDLGame* game, EntityManager* mngr) : Button(game, mngr), hability_(0) {};

	~ButtonHability() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, uint attack);

	virtual void click();
	
};

#pragma endregion

// ----------------------------------------------------