#pragma once

#include "Vector2D.h"
#include "Component.h"

class Transform: public Component {
public:
	Transform(Vector2D pos, Vector2D vel, double width, double height, double rotation);
	Transform();
	virtual ~Transform();

	// position
	const Vector2D& getPos() const {
		return position_;
	}
	void setPos(const Vector2D &pos) {
		position_.set(pos);
	}
	void setPos(double x, double y) {
		position_.set(x, y);
	}
	void setPosX(double x) {
		position_.setX(x);
	}
	void setPosY(double y) {
		position_.setY(y);
	}

	// rotation
	double getRot() const {
		return rotation_;
	}
	void setRot(double angle) {
		rotation_ = angle;
	}

	// velocity
	const Vector2D& getVel() const {
		return velocity_;
	}
	void setVel(const Vector2D &vel) {
		velocity_.set(vel);
	}
	void setVel(double x, double y) {
		velocity_.set(x, y);
	}
	void setVelX(double x) {
		velocity_.setX(x);
	}
	void setVelY(double y) {
		velocity_.setY(y);
	}

	// width && height
	double getW() const {
		return width_;
	}
	void setW(double width) {
		width_ = width;
	}

	double getH() const {
		return height_;
	}
	void setH(double height) {
		height_ = height;
	}

	void setWH(double width, double height) {
		width_ = width;
		height_ = height;
	}

private:
	Vector2D position_;
	Vector2D velocity_;
	double width_;
	double height_;
	double rotation_;
};

