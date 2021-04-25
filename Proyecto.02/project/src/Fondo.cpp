#pragma once
#include "Fondo.h"
#include "Transform.h"
#include "Image.h"

void Fondo::init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen)
{
	addComponent<Transform>(pos, Vector2D(), ancho, alto, 0);
	addComponent<Image>(game_->getTextureMngr()->getTexture(Resources::Fondo));
}
