#include "Component.h"

Component::Component(ecs::CmpId id) :
		entity_(nullptr), //
		game_(nullptr), //
		id_(id) //
{
}

Component::~Component() {
}
