#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"

class Rectangle: public Component {
public:
	Rectangle();
	Rectangle(SDL_Color color);
	virtual ~Rectangle();
	void init() override;
	void draw() override;
private:
	SDL_Color color_;
	Transform *tr_;
};

