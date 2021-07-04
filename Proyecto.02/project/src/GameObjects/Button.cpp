#include "Button.h"
#include "../Managers/SDLGame.h"
#include "../Components/Interfaz.h"
#include "../Components/Transform.h"
#include "../Components/Image.h"
#include "../Components/Sprite.h"
#include "../Components/ButtonCtrl.h"
#include "../Utilities/textures_box.h"
#include "../Utilities/SDL_macros.h"

#include "../Managers/game/LobbyManager.h";

using namespace textures_box;

// todo el juego se une mediante GameMngr(entity_)

// ----------------------------------------------------

#pragma region ButtonPanelResources

void ButtonPanelCte::click()
{
	pan_->toggleEnable();
	if (!pan_->getEnable()) {
		Sprite* s_ = GETCMP2(this, Sprite);
		s_->setHide(true);
		s_->reset();
	}
}

#include "../Components/Interfaz.h"
void ButtonHero::click()
{
	Interfaz* i_ = TheElementalMaze::instance()->getComponent<Interfaz>(ecs::Interfaz);
	i_->checkActiveHeroButton(heroType_);
	callbacks::createDDPan(activated, (uint)heroType_); //<3
	if (!activated) 
		turnON();
	else 
		turnOFF();
}

#pragma endregion

//----------------------------------------------------------------------------

#pragma region ButtonCombateResources
#include "../Managers/TheElementalMaze.h"
#include "../Managers/game/CombatManager.h"
#include "../ecs/ecs.h"
#include "../ecs/ecs_interfaz.h"
void ButtonHability::init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, uint attack) //¡
{
	app = TheElementalMaze::instance()->getComponent<Interfaz>(ecs::Interfaz);
	hability_ = attack;

	her = static_cast<Hero*>(GETCMP2(TheElementalMaze::instance(), CombatManager)->getCurrentCharacter());
	hab = her->getHabilities()[(int)hability_];
	affordable = her->getCharacterSheet()->manaPoints() >= hab->getMana();
	
	if (!affordable) imagen = (Resources::TextureId)((int)imagen + 38);
	Button::init(pos, ancho, alto, imagen);
}

void ButtonHability::click() // <3
{
	callbacks::createFichaDescPan(false, hab, affordable);

	if (affordable) callbacks::set_hability((int)hability_);
	else game_->getAudioMngr()->playChannel(Resources::Error, 0, 0);
};

void ButtonHability::pointerEntered() {
	callbacks::createFichaDescPan(true, hab, affordable);
};

void ButtonHability::pointerExited() {
	callbacks::createFichaDescPan(false, hab, affordable);
};

#pragma endregion

//----------------------------------------------------------------------------

void ButtonPanel::setActive(bool set)
{
	activated = set;
}

void ButtonPanel::setHide(bool set)
{
	GETCMP2(this, Sprite)->setHide(set);
}

//----------------------------------------------------------------------------
void Button::init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen)
{
	id_ = imagen;
	SDL_Object::init(pos, ancho, alto, imagen, false);
	Sprite* s = addComponent<Sprite>(game_->getTextureMngr()->getTexture(src::Button_transition), 0, 0, 3);
	s->setHide(true);
	addComponent<ButtonCtrl>(this);
}

void Button::init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, bool animation)
{
	id_ = imagen;
	SDL_Object::init(pos, ancho, alto, imagen, animation);
	Sprite* s = addComponent<Sprite>(game_->getTextureMngr()->getTexture(src::Button_transition), 0, 0, 3);
	s->setHide(true);
	addComponent<ButtonCtrl>(this);
}


void Button::init(SDL_Rect dest, Resources::TextureId imagen)
{
	id_ = imagen;
	SDL_Object::init(POS(dest), dest.w, dest.h, imagen);
	Sprite* s = addComponent<Sprite>(game_->getTextureMngr()->getTexture(src::Button_transition), 0, 0, 3);
	s->setHide(true);
	addComponent<ButtonCtrl>(this);
}
void Button::toggleImage(Resources::TextureId imagen) //!
{
	id_ = imagen;
	Image* img = GETCMP2(this, Image);
	img->setTexture(game_->getTextureMngr()->getTexture(imagen));
}
;

//----------------------------------------------------------------------------

void ButtonSlott::init(SDL_Rect dest, Item* item)
{
	if (item != nullptr) {
		Button::init(dest, src::Slot);
		Texture* text = game_->getTextureMngr()->getTexture(getItemTxt(item));
		addComponent<Image>(text);
	}
	else {
		Button::init(dest, src::WeaponSlot);
	}
}
void ButtonSlott::init(Vector2D pos, uint ancho, uint alto, Item* item)
{
	init(RECT(pos.getX(), pos.getY(), ancho, alto), item);
};

//----------------------------------------------------------------------------

void ButtonWeaponAttack::init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, int attack) //¡
{
	app = TheElementalMaze::instance()->getComponent<Interfaz>(ecs::Interfaz);
	attack_ = attack;

	her = static_cast<Hero*>(GETCMP2(TheElementalMaze::instance(), CombatManager)->getCurrentCharacter());
	switch ((int)attack_)
	{
	case -2:
		hab = her->getLightAttack();
		break;
	case -3:
		hab = her->getHeavyAttack();
		break;
	default:
		hab = nullptr;
		break;
	}
	assert(hab != nullptr);
	affordable = her->getCharacterSheet()->manaPoints() >= hab->getMana();
	
	if (!affordable) imagen = (Resources::TextureId)((int)imagen + 38);
	Button::init(pos, ancho, alto, imagen);
}

void ButtonWeaponAttack::click() //<3
{
	callbacks::createFichaDescPan(false, hab, affordable);

	if (affordable) callbacks::set_hability((int)attack_);
	else game_->getAudioMngr()->playChannel(Resources::Error, 0, 0);
}

void ButtonWeaponAttack::pointerEntered() {
	callbacks::createFichaDescPan(true, hab, her->getCharacterSheet()->manaPoints() >= hab->getMana());
};

void ButtonWeaponAttack::pointerExited() {
	callbacks::createFichaDescPan(false, hab, her->getCharacterSheet()->manaPoints() >= hab->getMana());
};

//----

void ButtonInfoTienda::pointerEntered() {
	if (!isHero) {
		Item* ite = TheElementalMaze::instance()->getLobbyManager()->getLobbyStore()->items[id]->item;
		callbacks::createFichaDescObjPan(true, ite);
	}
};
void ButtonInfoTienda::pointerExited() {
	if (!isHero) {
		Item* ite = TheElementalMaze::instance()->getLobbyManager()->getLobbyStore()->items[id]->item;
		callbacks::createFichaDescObjPan(false, ite);
	}
};

//---

void ButtonHeroEquipment::pointerEntered() {
	if (accion == accionHeroEquipment::showUnequip)
	{
		Hero* her = TheElementalMaze::instance()->getPartyManager()->getHeroes()[heroid];
		Item* ite;
		if (isWeapon) ite = her->getWeapon();
		else ite = her->getArmor();
		callbacks::createFichaDescObjPan(true, ite);
	}

};
void ButtonHeroEquipment::pointerExited() {
	if (accion == accionHeroEquipment::showUnequip)
	{
		Hero* her = TheElementalMaze::instance()->getPartyManager()->getHeroes()[heroid];
		Item* ite;
		if (isWeapon) ite = her->getWeapon();
		else ite = her->getArmor();
		callbacks::createFichaDescObjPan(false, ite);
	}
};