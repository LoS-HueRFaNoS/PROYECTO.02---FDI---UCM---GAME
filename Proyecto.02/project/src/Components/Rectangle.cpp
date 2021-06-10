#include "Rectangle.h"
#include "../ecs/Entity.h"

Rectangle_cmpt::Rectangle_cmpt() :
		Rectangle_cmpt( { COLOR(0xFFFFFFFF) }) {
}

Rectangle_cmpt::Rectangle_cmpt(SDL_Color color) :
		Component(ecs::Rectangle_cmpt), //
		color_(color), //
		tr_(nullptr) {
}

Rectangle_cmpt::~Rectangle_cmpt() {
}

void Rectangle_cmpt::init() {
	tr_ = GETCMP1_(Transform);
}

void Rectangle_cmpt::draw() {
	SDL_Rect rect
			RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(),
					tr_->getH());

	SDL_SetRenderDrawColor(game_->getRenderer(), COLOREXP(color_));
	SDL_RenderFillRect(game_->getRenderer(), &rect);
}

void Rectangle_cmpt::setColor(SDL_Color color)
{
	color_ = color;
}

