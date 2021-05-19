#include "Component.h"

Component::Component(ecs::CmpId id) :
		entity_(nullptr), //
		game_(nullptr), //
		id_(id), //
		active(true)
{
}

Component::~Component() {
}
