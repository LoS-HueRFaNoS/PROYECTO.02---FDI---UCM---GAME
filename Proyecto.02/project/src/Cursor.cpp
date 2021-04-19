#pragma once
#include "Cursor.h"
#include "Transform.h"
#include "Sprite.h"
#include "MouseCtrl.h"
#include "Interfaz.h"

void Cursor::init(SDLGame* game, Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen)
{
	addComponent<Transform>(pos, Vector2D(), ancho, alto, 0);
	addComponent<Sprite>(game->getTextureMngr()->getTexture(imagen), 0, 0);
	addComponent<MouseCtrl>();
}