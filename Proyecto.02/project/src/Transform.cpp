#include "Transform.h"

Transform::Transform() :
		Component(ecs::Transform), position_(), //
		width_(), //
		height_() //
{
}

Transform::Transform(Vector2D pos, double width,
		double height) :
		Component(ecs::Transform), position_(pos), //
		width_(width), //
		height_(height),//
	sentido_()
{
}

Transform::~Transform() {
}

