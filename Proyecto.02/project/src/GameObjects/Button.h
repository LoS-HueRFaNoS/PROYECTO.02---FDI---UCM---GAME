#pragma once
#include "SDL_Objects.h"
#include "../Templates/callbacks.h"
#include "../Structures/Item.h"
#include "../Components/Sprite.h"
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

	virtual void click() { 
		callbacks::toggleThemeFondo(); 
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
	};
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
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
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
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
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
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
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
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
	}
};
// ----------------------------------------------------

enum class accionMenu { start, lobby, how_to_play, options, quit, shop, stash, shop_lobby,
	stash_lobby, avanzarHeroes, avanzarItems, retrocederHeroes, retrocederItems, backToMenu,inventarioLobby
};

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
		case accionMenu::avanzarHeroes:
			callbacks::avanzarHeroes(app);
			break;
		case accionMenu::avanzarItems:
			callbacks::avanzarItems(app);
			break;
		case accionMenu::retrocederHeroes:
			callbacks::retrocederHeroes(app);
			break;
		case accionMenu::retrocederItems:
			callbacks::retrocederItems(app);
			break;
		case accionMenu::backToMenu:
			callbacks::backToMenu(app);
			break;
		case accionMenu::inventarioLobby:
			callbacks::inventarioLobby(app);
			break;
		default:
			break;
		}
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
		
	}
};
// ----------------------------------------------------



class ButtonBuyHero : public Button {
private:
	int heroeid;
	Interfaz* app;
public:
	ButtonBuyHero(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};

	~ButtonBuyHero() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, int her, Interfaz* app_) {
		heroeid = her;
		app = app_;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		callbacks::shoppingHero(app, heroeid);

	}
};

class ButtonShowHeroToParty : public Button {
private:
	int heroeid;
	Interfaz* app;
public:
	ButtonShowHeroToParty(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};

	~ButtonShowHeroToParty() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, int her, Interfaz* app_) {
		heroeid = her;
		app = app_;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		callbacks::showHeroToParty(app, heroeid);

	}
};

enum class accionHero {
	sendHeroToStash, sendHeroToParty
};
class ButtonHeroManagement : public Button {
private:
	int heroeid;
	accionHero accion;
	Interfaz* app;
public:
	ButtonHeroManagement(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};

	~ButtonHeroManagement() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen,accionHero accion_, int her, Interfaz* app_) {
		heroeid = her;
		app = app_;
		accion = accion_;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		switch (accion)
		{
		case accionHero::sendHeroToStash:
				callbacks::sendHeroToStash(app, heroeid);
				break;
		case accionHero::sendHeroToParty:
			callbacks::sendHeroToParty(app, heroeid);
			break;
		}
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
	}
};
// ----------------------------------------------------

class ButtonBuyItem : public Button {
private:
	int itemid;
	int itemType;
	Interfaz* app;
public:
	ButtonBuyItem(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};

	~ButtonBuyItem() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen,int itemId_, int itemType_, Interfaz* app_) {
		itemid = itemId_;
		itemType = itemType_;
		app = app_;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		callbacks::shopping(app, itemType, itemid);
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
	}
};
// ----------------------------------------------------

// ----------------------------------------------------
enum class accionItem {
	sellItem, showSellButton
};
class ButtonItemManagement : public Button {
private:
	int itemid;
	accionItem accion_item;
	Interfaz* app;
public:
	ButtonItemManagement(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};

	~ButtonItemManagement() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, accionItem accion_item_ , int itemId_, Interfaz* app_) {
		itemid = itemId_;
		accion_item = accion_item_;
		app = app_;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		switch (accion_item)
		{
		case accionItem::showSellButton:
			callbacks::showSellButton(app, itemid);
			break;
		case accionItem::sellItem:
			callbacks::sellStashItem(app,itemid);
			break;
		}
		
		
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
	}
};
// ----------------------------------------------------

class ButtonInfoTienda : public Button {
private:
	Interfaz* app;
	int id;
	bool isHero = false;
public:
	ButtonInfoTienda(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};

	~ButtonInfoTienda() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen,bool isHero_, int id_, Interfaz* app_) {
		app = app_;
		id = id_;
		isHero = isHero_;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		callbacks::infoTienda(app,isHero,id);
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
	}
};

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
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
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
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
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
		//addComponent<Sprite>(game_->getTextureMngr()->getTexture(Resources::Selected), 0, 0, true, true); // marco select
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
	virtual void turnON() { setActive(true); setHide(false); }
	virtual void turnOFF() { 
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
		setActive(false); setHide(true);
	}

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