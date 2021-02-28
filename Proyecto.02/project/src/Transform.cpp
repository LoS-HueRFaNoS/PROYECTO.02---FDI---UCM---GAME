#include "Transform.h"

Transform::Transform() :
		Component(ecs::Transform), position_(), //
		velocity_(), //
		width_(), //
		height_(), //
		rotation_() //
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

