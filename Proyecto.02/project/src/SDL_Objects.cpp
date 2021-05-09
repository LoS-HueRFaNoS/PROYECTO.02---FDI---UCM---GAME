#pragma once
#include "SDL_Objects.h"
#include "Transform.h"
#include "Image.h"

void SDL_Object::initComponents(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen)
{
	addComponent<Transform>(pos, Vector2D(), ancho, alto, 0);
	addComponent<Image>(game_->getTextureMngr()->getTexture(imagen));
}

void SDL_Object::initComponents(Vector2D pos, uint ancho, uint alto, Texture* imagen)
{
	addComponent<Transform>(pos, Vector2D(), ancho, alto, 0);
	addComponent<Image>(imagen);
}

void Fondo::init(Vector2D pos, uint ancho, uint alto, Resources::TextureId imagen)
{
	addComponent<Transform>(pos, Vector2D(), ancho, alto, 0);
	addComponent<Image>(game_->getTextureMngr()->getTexture(Resources::Fondo));
}

void Line::init(Vector2D pos, uint ancho, uint alto, string line, Resources::FontId font, const SDL_Color& color = { (0),(0),(0),(255) })
{
	Texture* text = new Texture();
	if (text->loadFromText(game_->getRenderer(), line, game_->getFontMngr()->getFont(font), color))
		SDL_Object::init(pos, ancho, alto, text);
}
