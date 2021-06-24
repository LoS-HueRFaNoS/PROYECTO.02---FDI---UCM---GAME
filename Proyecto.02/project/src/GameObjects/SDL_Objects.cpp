#pragma once
#include "SDL_Objects.h"
#include "../Components/Transform.h"
#include "../Components/Image.h"
#include "../Utilities/SDL_macros.h"

void SDL_Object::init(SDL_Rect dest, Texture* image)
{
	Vector2D pos = POS(dest);
	addComponent<Transform>(pos, Vector2D(), dest.w, dest.h, 0);
	addComponent<Image>(image);
}

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

void Fondo::init(Vector2D pos, uint ancho, uint alto)
{
	image = Resources::Fondo;
	addComponent<Transform>(pos, Vector2D(), ancho, alto, 0);
	addComponent<Image>(game_->getTextureMngr()->getTexture(image));
}

void Fondo::changeTheme()
{
	Image* img = GETCMP2(this, Image);
	if (image == Resources::Fondo) image = Resources::Fondo2;
	else image = Resources::Fondo;
	img->setTexture(game_->getTextureMngr()->getTexture(image));
}

void Line::init(Vector2D pos, uint ancho, uint alto, string line, Resources::FontId font, const SDL_Color& color = { (0),(0),(0),(255) })
{
	texto = line;
	Texture* text = new Texture();
	if (text->loadFromText(game_->getRenderer(), line, game_->getFontMngr()->getFont(font), color)) {
		tex_ = text;
		SDL_Object::init(pos, ancho, alto, text);
	}
	else
		delete text;
}

void Line::init(SDL_Rect size, string line, Resources::FontId font, const SDL_Color& color)
{
	texto = line;
	Texture* text = new Texture();
	if (text->loadFromText(game_->getRenderer(), line, game_->getFontMngr()->getFont(font), color)) { //src::Beaulieux
		tex_ = text;
		SDL_Object::init(size, text);
	}
	else
		delete text;
}

void Line::setLine(string line, Resources::FontId font, const SDL_Color& color)
{	
	texto = line;
	Texture* text = new Texture();
	if (text->loadFromText(game_->getRenderer(), line, game_->getFontMngr()->getFont(font), color)) { //src::Beaulieux
		tex_ = text;
		getComponent<Image>(ecs::Image)->setTexture(tex_);
	}
	else
		delete text;
}

void Line::init(SDL_Rect size, string line, const SDL_Color& color, bool isTitle)
{
	texto = line;
	Texture* text = new Texture();
	if (text->loadFromText(game_->getRenderer(), line, game_->getFontMngr()->getFont(src::ConsoleBO), color, isTitle)) { //src::Beaulieux
		tex_ = text;
		SDL_Object::init(POS(size), size.w, size.h, text);
	}
	else
		delete text;
}
