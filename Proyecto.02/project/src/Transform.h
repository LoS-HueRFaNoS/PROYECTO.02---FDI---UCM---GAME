#pragma once

#include "Vector2D.h"
#include "Component.h"

class Transform: public Component {
public:
	Transform(Vector2D pos,  double width, double height);
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

	void setSentido(int sentid)
	{
		sentido_ = sentid;
	}
	int getSentido()
	{
		return sentido_;
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
	double width_;
	double height_;
	MapCell sentido_;
	
};

