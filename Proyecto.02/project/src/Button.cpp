#include "Button.h"
#include "Transform.h"
#include "Image.h"
#include "ButtonCtrl.h"
#include "Game.h"

void Button::init(SDLGame* game, Game* g, Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen)
{
	addComponent<Transform>(pos, Vector2D(), ancho, alto, 0);
	addComponent<Image>(game->getTextureMngr()->getTexture(imagen));
	addComponent<ButtonCtrl>(g);
}