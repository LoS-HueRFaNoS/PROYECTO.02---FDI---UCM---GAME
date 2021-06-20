#include "TextBlock.h"
#include "../Components/Transform.h"
#include "../Components/Rectangle.h"

void TextBlock::Init(SDL_Panel pan)
{
	ObjectPanel::Init(pan);
	TextBlockResources::Init(bottomElement(), this);

	// fondo oscuro
	fondo_ = new Entity(game_, this);
	SDL_Rect dest = RECT(pan.x, pan.y, pan.w, pan.h);
	fondo_->addComponent<Transform>(dest);
	fondo_->addComponent<Rectangle_cmpt>(hex2sdlcolor("#000000FF"));
}

void TextBlock::update()
{
	ElementsResources::checkBlockSize(entities, numLines_);
}

void TextBlock::draw()
{
	fondo_->draw();
	ElementsResources::draw(entities, tuppleLimits());
}
