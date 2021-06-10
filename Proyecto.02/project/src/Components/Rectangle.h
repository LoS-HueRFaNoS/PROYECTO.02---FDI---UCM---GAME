#pragma once

#include <SDL_rect.h>
#include "../ecs/Component.h"
#include "../Utilities/SDL_macros.h"
#include "../Components/Transform.h"

class Rectangle_cmpt: public Component {
public:
	Rectangle_cmpt();
	Rectangle_cmpt(SDL_Color color);
	virtual ~Rectangle_cmpt();
	void init() override;
	void draw() override;
	void setColor(SDL_Color color);
private:
	SDL_Color color_;
	Transform *tr_;
};

