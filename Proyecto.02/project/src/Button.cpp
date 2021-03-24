#include "Button.h"
#include "Transform.h"
#include "Image.h"
#include "ButtonCtrl.h"
#include "Game.h"

Button::Button(SDLGame* game, Game* g, EntityManager* mngr, Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen) : Entity(game, mngr)
{
	Entity* button = mngr->addEntity();
	button->addComponent<Transform>(pos, Vector2D(), ancho, alto, 0);
	button->addComponent<Image>(game->getTextureMngr()->getTexture(imagen));
	button->addComponent<ButtonCtrl>(g);
}