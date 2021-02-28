#pragma once

#include "Vector2D.h"

/*
 *
 */
class Collisions {
public:
	virtual ~Collisions();
	static bool collides(const Vector2D o1Pos, double o1Width, double o1Height, const Vector2D o2Pos, double o2Width, double o2Height);
	static bool collidesWithRotation(const Vector2D o1Pos, double o1Width, double o1Height, double o1Rot, const Vector2D o2Pos, double o2Width, double o2Height, double o2Rot);
private:
	Collisions();
	static bool PointInTriangle(const Vector2D A, const Vector2D B, const Vector2D C, const Vector2D P);
	static bool PointInRectangle(const Vector2D X, const Vector2D Y, const Vector2D Z, const Vector2D W,
			Vector2D P);

};
