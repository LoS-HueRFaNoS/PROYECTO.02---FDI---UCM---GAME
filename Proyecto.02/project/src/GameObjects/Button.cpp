#include "Button.h"
#include "../Managers/SDLGame.h"
#include "../Components/Interfaz.h"
#include "../Components/Transform.h"
#include "../Components/Image.h"
#include "../Components/Sprite.h"
#include "../Components/ButtonCtrl.h"

// todo el juego se une mediante GameMngr(entity_)


// ----------------------------------------------------

#pragma region ButtonPanelResources

void ButtonPanelCte::click()
{
	pan_->toggleEnable();
}

#include "../Components/Interfaz.h"
void ButtonHero::click()
{
	Interfaz* i_ = TheElementalMaze::instance()->getComponent<Interfaz>(ecs::Interfaz);
	i_->checkActiveHeroButton(heroType_);
	callbacks::createDDPan(activated, (uint)heroType_);
	if (!activated) 
		turnON();
	else 
		turnOFF();
}

#pragma endregion

#pragma region ButtonCombateResources
#include "../Managers/TheElementalMaze.h"
#include "../Managers/game/CombatManager.h"
#include "../ecs/ecs.h"
#include "../ecs/ecs_interfaz.h"
void ButtonHability::init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, uint attack)
{
	hability_ = attack;
	Button::init(pos, ancho, alto, imagen);
}

void ButtonHability::click()
{
	callbacks::set_hability((int)hability_);	
}

#pragma endregion



void ButtonPanel::setActive(bool set)
{
	activated = set;
}

void ButtonPanel::setHide(bool set)
{
	GETCMP2(this, Sprite)->setHide(set);
}

void Button::init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen)
{
	SDL_Object::init(pos, ancho, alto, imagen);
	addComponent<ButtonCtrl>(this);
};