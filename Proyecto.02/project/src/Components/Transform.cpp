#include "Transform.h"
#include "../Utilities/SDL_macros.h"

Transform::Transform() :
		Component(ecs::Transform), position_(), //
		velocity_(), //
		width_(), //
		height_(), //
		rotation_() //
{
}

Transform::Transform(SDL_Rect dest, Vector2D vel, double rotation) :
	Component(ecs::Transform), 
	position_(POS(dest)), //
	velocity_(vel), //
	width_(dest.w), //
	height_(dest.h), //
	rotation_(rotation) //
{
}

Transform::Transform(Vector2D pos, Vector2D vel, double width,
		double height, double rotation) :
		Component(ecs::Transform), position_(pos), //
		velocity_(vel), //
		width_(width), //
		height_(height), //
		rotation_(0.0) //
{
}

Transform::~Transform() {
}

