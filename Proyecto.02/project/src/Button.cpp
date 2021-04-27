#include "Button.h"
#include "SDLGame.h"
#include "Interfaz.h"
#include "Transform.h"
#include "Image.h"
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
	pan_->toggleButtons();
}

#include "Interfaz.h"
void ButtonHero::click()
{
	Interfaz* i_ = TheElementalMaze::instance()->getComponent<Interfaz>(ecs::Interfaz);
	i_->checkActiveHeroButton();
	callbacks::createDDPan((uint)heroType_);
	activated = !activated;
}

#pragma endregion

#pragma region ButtonCombateResources

void ButtonHability::init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen, HbltType attack, idPanel panId, bool active, Panel* p_)
{
	hability_ = attack;
	activated = active;
	pan_ = panId;
	p_->toggleButtons();
	Button::init(pos, ancho, alto, imagen);
}
#pragma endregion

void ButtonLine::init(Vector2D pos, uint ancho, uint alto, string line, Resources::FontId font)
{
	addComponent<Transform>(pos, Vector2D(), ancho, alto, 0);
	Texture* t = new Texture(); 
	if (t->loadFromText(game_->getRenderer(), line, game_->getFontMngr()->getFont(font), { 0,0,255,255 }))
		addComponent<Image>(t);
	addComponent<ButtonCtrl>(this);
}


