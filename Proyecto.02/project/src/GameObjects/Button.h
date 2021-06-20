#pragma once
#include "SDL_Objects.h"
#include "../Templates/callbacks.h"
#include "../Structures/Item.h"
#include "../Components/Sprite.h"
#include <cassert>

// ----------------------------------------------------

class Button : public SDL_Object
{
protected:
	Resources::TextureId id_;
public:
	Button(SDLGame* game, EntityManager* mngr) :
		SDL_Object(game, mngr)
	{};
	virtual ~Button() {};
	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen);
	virtual void init(SDL_Rect dest, Resources::TextureId imagen);

	virtual void click() = 0;
	virtual void pointerEntered() {};
	virtual void pointerExited() {};

	void toggleImage(Resources::TextureId imagen);
	Resources::TextureId getImageID() { return id_; };
};

// ----------------------------------------------------

class ButtonVolumen : public Button // <3
{
private:
	uint min_;
	uint max_;
	uint barMin_;
	uint barMax_;
	SDL_Object* obj_;
	int delta_;
public:
	ButtonVolumen(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};
	virtual ~ButtonVolumen() {};

	virtual void init(SDL_Rect dest, Resources::TextureId imagen, int delta, SDL_Object* obj, uint barMin, uint barMax) {
		min_ = 0;
		max_ = 100;
		barMin_ = barMin;
		barMax_ = barMax;
		obj_ = obj;
		delta_ = delta;
		Button::init(dest, imagen);
	};

	virtual void click() {
		// feedback sonoro
		game_->getAudioMngr()->playChannel(Resources::AudioId::Boton2, 0, 0); ///Boton1
		/*
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();

		Transform* tr = GETCMP2(obj_, Transform);

		int aux = tr->getPos().getX();
		int change = aux + delta_;

		if (change < max_ && change > min_) {
			tr->setPosX(change);
			int value = (tr->getPos().getX() - min_) / (max_ - min_) * 100;
			game_->getAudioMngr()->setMusicVolume(value);
		}
		*/
	};
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
		if (id_ == src::Change) 
			toggleImage(src::Change2);
		else 
			toggleImage(src::Change);
		callbacks::toggleThemeFondo(); 		
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
	};

	
};

// ----------------------------------------------------

class ButtonSlott : public Button // <2
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
		game_->getAudioMngr()->setChannelVolume(15,-1);
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
	stash_lobby, avanzarHeroes, avanzarItems, retrocederHeroes, retrocederItems, backToMenu, inventarioLobby, closeMessage, inventario_to_lobby,resume,
	backToMaze,
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
	virtual void init(SDL_Rect dest, Resources::TextureId imagen, accionMenu type, Interfaz* app_ = nullptr) {
		tipo = type;
		app = app_;
		Button::init(dest, imagen);
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
		case accionMenu::closeMessage:
			callbacks::closeMessage();
			break;
		case accionMenu::inventario_to_lobby:
			callbacks::inventarioToLobby(app);
			break;
		case accionMenu::resume:
			callbacks::resumeGame(app);
			break; 
		case accionMenu::backToMaze:
			callbacks::backToMaze(app);
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
	virtual void init(SDL_Rect dest, Resources::TextureId imagen, int her, Interfaz* app_) {
		heroeid = her;
		app = app_;
		Button::init(dest, imagen);
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
	virtual void init(SDL_Rect dest, Resources::TextureId imagen, int her, Interfaz* app_) {
		heroeid = her;
		app = app_;
		Button::init(dest, imagen);
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
	virtual void init(SDL_Rect dest, Resources::TextureId imagen,accionHero accion_, int her, Interfaz* app_) {
		heroeid = her;
		app = app_;
		accion = accion_;
		Button::init(dest, imagen);
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
	virtual void init(SDL_Rect dest, Resources::TextureId imagen,int itemId_, int itemType_, Interfaz* app_) {
		itemid = itemId_;
		itemType = itemType_;
		app = app_;
		Button::init(dest, imagen);
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
	sellItem, showSellButton, showSendToStash, sendToStash, showSendToInventory, sendToInventory, showEquipButton
};
class ButtonItemManagement : public Button {
private:
	int itemid;
	accionItem accion_item;
	bool isWeapon;
	Interfaz* app;
public:
	ButtonItemManagement(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};

	~ButtonItemManagement() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, accionItem accion_item_ ,bool isWeapon_, int itemId_, Interfaz* app_) {
		itemid = itemId_;
		accion_item = accion_item_;
		isWeapon = isWeapon_;
		app = app_;
		Button::init(pos, ancho, alto, imagen);
	};
	virtual void init(SDL_Rect dest, Resources::TextureId imagen, accionItem accion_item_ ,bool isWeapon_, int itemId_, Interfaz* app_) {
		itemid = itemId_;
		accion_item = accion_item_;
		isWeapon = isWeapon_;
		app = app_;
		Button::init(dest, imagen);
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
		case accionItem::showSendToStash:
			callbacks::showSendToStash(app, itemid);
			callbacks::showEquipButton(app,isWeapon, itemid);
			break;
		case accionItem::sendToStash:
			callbacks::sendToStash(app, itemid);
			break;
		case accionItem::showSendToInventory:
			callbacks::showSellButton(app, itemid);
			break;
		case accionItem::sendToInventory:
			callbacks::sendToInventory(app, itemid);
			break;
		case accionItem::showEquipButton:
			callbacks::showEquipButton(app,isWeapon, itemid);
			break;
		}
		
		
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
	}
};
// ----------------------------------------------------

class ButtonInfoTienda : public Button { // <3
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
	virtual void init(SDL_Rect dest, Resources::TextureId imagen,bool isHero_, int id_, Interfaz* app_) {
		app = app_;
		id = id_;
		isHero = isHero_;
		Button::init(dest, imagen);
	};

	virtual void click()
	{
		callbacks::infoTienda(app,isHero,id);
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
	}
	virtual void pointerEntered();
	virtual void pointerExited();
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


#include "../Components/Contador.h"
class ButtonPotion : public Button { // <2
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
	idPanel pan_; // Panel que va a ser activado o desactivado

	void setActive(bool set);
	void setHide(bool set);

public:
	ButtonPanel(SDLGame* game, EntityManager* mngr) : Button(game, mngr), activated(true), pan_() {};

	~ButtonPanel() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, idPanel p, bool active) {
		setActive(active);
		pan_ = p; // asigna el panel
		Button::init(pos, ancho, alto, imagen);
		//addComponent<Sprite>(game_->getTextureMngr()->getTexture(Resources::Selected), 0, 0, true, true); // marco select
	};

	virtual void click()
	{
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
	Interfaz* app;
public:
	ButtonHability(SDLGame* game, EntityManager* mngr) : Button(game, mngr), hability_(0) {};

	~ButtonHability() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, uint attack);

	virtual void click();
	virtual void pointerEntered();
	virtual void pointerExited();
	
};

class ButtonWeaponAttack : public Button {
private:
	uint attack_;
	Interfaz* app;
public:
	ButtonWeaponAttack(SDLGame* game, EntityManager* mngr) : Button(game, mngr), attack_(0) {};

	~ButtonWeaponAttack() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, int attack);

	virtual void click();
	virtual void pointerEntered();
	virtual void pointerExited();
};

#pragma endregion

// ----------------------------------------------------

// ----------------------------------------------------

// ----------------------------------------------------
enum class accionHeroEquipment {showUnequip,Unequip, showEquip, Equip};
class ButtonHeroEquipment : public Button { // <3
private:
	bool isWeapon = false;
	int heroid;
	int itemid;
	Interfaz* app;
	accionHeroEquipment accion;
public:
	ButtonHeroEquipment(SDLGame* game, EntityManager* mngr) : Button(game, mngr) {};

	~ButtonHeroEquipment() {};

	virtual void init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, accionHeroEquipment accion_, bool isWeapon_,int itemId_,int heroId_, Interfaz* app_) {
		isWeapon = isWeapon_;
		heroid = heroId_;
		itemid = itemId_;

		app = app_;
		accion = accion_;
		Button::init(pos, ancho, alto, imagen);
	};

	virtual void click()
	{
		switch (accion)
		{
		case accionHeroEquipment::showUnequip:
			callbacks::showUnequipButton(app, isWeapon, heroid);
			break;
		case accionHeroEquipment::Unequip:
			callbacks::unequip(app, isWeapon, heroid);
			break;
		case accionHeroEquipment::Equip:
			callbacks::equip(app, isWeapon, itemid, heroid);
			break;

		case accionHeroEquipment::showEquip:
			callbacks::showEquipButton(app, isWeapon, itemid);
			break;
		}
	
		
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
	}
	virtual void pointerEntered();
	virtual void pointerExited();
};
// ----------------------------------------------------