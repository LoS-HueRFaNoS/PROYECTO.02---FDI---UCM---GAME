#pragma once
#include "Cursor.h"
#include "../Components/Transform.h"
#include "../Components/Sprite.h"
#include "../Components/MouseCtrl.h"
#include "../Components/Interfaz.h"

void Cursor::init(SDLGame* game, Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen)
{
	addComponent<Transform>(pos, Vector2D(), ancho, alto, 0);
	addComponent<Sprite>(game->getTextureMngr()->getTexture(imagen), 0, 0);
	addComponent<MouseCtrl>();
}