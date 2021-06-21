#include "Component.h"

Component::Component(ecs::CmpId id) :
		entity_(nullptr), //
		game_(nullptr), //
		id_(id), //
		active(true)
{
}

Component::Component(ecs::CmpId id, SDLGame* g) :
		entity_(nullptr), //
		game_(g), //
		id_(id), //
		active(true)
{
}

Component::~Component() {
}
