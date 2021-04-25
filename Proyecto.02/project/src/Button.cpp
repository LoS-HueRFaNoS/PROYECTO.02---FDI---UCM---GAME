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