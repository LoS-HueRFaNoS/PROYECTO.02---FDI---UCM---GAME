#include "Button.h"
#include "SDLGame.h"
#include "Interfaz.h"
#include "Transform.h"
#include "Image.h"
#include "Sprite.h"
#include "ButtonCtrl.h"

// todo el juego se une mediante GameMngr(entity_)
void Button::initComponents(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen)
{
	addComponent<Transform>(pos, Vector2D(), ancho, alto, 0);
	addComponent<Image>(game_->getTextureMngr()->getTexture(imagen));
	addComponent<ButtonCtrl>(this);
}

// ----------------------------------------------------

#pragma region ButtonPanelResources

void ButtonPanelCte::click()
{
	pan_->toggleEnable();
}

#include "Interfaz.h"
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
#include "../TheElementalMaze.h"
#include "CombatManager.h"
#include "ecs.h"
#include "ecs_interfaz.h"
void ButtonHability::init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, HbltType attack)
{
	hability_ = attack;
	Button::init(pos, ancho, alto, imagen);
}

void ButtonHability::click()
{
	callbacks::set_hability((int)hability_);	
}

#pragma endregion

void ButtonLine::init(Vector2D pos, uint ancho, uint alto, string line, Resources::FontId font, const SDL_Color& color = {(0),(0),(0),(255)})
{
	addComponent<Transform>(pos, Vector2D(), ancho, alto, 0);
	Texture* t = new Texture(); 
	if (t->loadFromText(game_->getRenderer(), line, game_->getFontMngr()->getFont(font), color))
		addComponent<Image>(t);
	addComponent<ButtonCtrl>(this);
}

void ButtonPanel::setActive(bool set)
{
	activated = set;
}

void ButtonPanel::setHide(bool set)
{
	GETCMP2(this, Sprite)->setHide(set);
}