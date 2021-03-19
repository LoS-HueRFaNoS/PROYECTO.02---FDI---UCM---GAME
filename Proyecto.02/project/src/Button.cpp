#include "Button.h"
#include "Transform.h"
#include "Image.h"
#include "ButtonCtrl.h"

Button::Button(SDLGame* g, EntityManager* mngr, Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen) : Entity(g, mngr)
{
	Entity* button = mngr->addEntity();
	button->addComponent<Transform>(pos, Vector2D(), ancho, alto, 0);
	button->addComponent<Image>(g->getTextureMngr()->getTexture(imagen));
	button->addComponent<ButtonCtrl>();
}