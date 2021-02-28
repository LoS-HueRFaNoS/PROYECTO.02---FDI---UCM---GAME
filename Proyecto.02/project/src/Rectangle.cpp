#include "Rectangle.h"
#include "Entity.h"

Rectangle::Rectangle() :
		Rectangle( { COLOR(0xFFFFFFFF) }) {
}

Rectangle::Rectangle(SDL_Color color) :
		Component(ecs::Rectangle), //
		color_(color), //
		tr_(nullptr) {
}

Rectangle::~Rectangle() {
}

void Rectangle::init() {
	tr_ = GETCMP1_(Transform);
}

void Rectangle::draw() {
	SDL_Rect rect
			RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(),
					tr_->getH());

	SDL_SetRenderDrawColor(game_->getRenderer(), COLOREXP(color_));
	SDL_RenderFillRect(game_->getRenderer(), &rect);
}

