#pragma once

#include "../Structures/Vector2D.h"
#include "../ecs/Component.h"
class MazePos : public Component {
public:
	MazePos(Vector2D pos) :
		Component(ecs::MazePos), mazePosition_(pos), look(Norte) {}
	MazePos() :
		Component(ecs::MazePos), mazePosition_(Vector2D(0, 0)), look(Norte) {}
	virtual ~MazePos() {};

	// position
	const Vector2D& getPos() const {
		return mazePosition_;
	}
	void setPos(const Vector2D& pos) {
		mazePosition_.set(pos);
	}
	void setPos(double x, double y) {
		mazePosition_.set(x, y);
	}
	void setPosX(double x) {
		mazePosition_.setX(x);
	}
	void setPosY(double y) {
		mazePosition_.setY(y);
	}
	// look
	const int getLook() const {
		return look;
	}
	void setLook(int look_) {
		look = look_;
	}

	void reset() {
		mazePosition_ = Vector2D(0, 0);
		look = Norte;
	}
private:
	Vector2D mazePosition_;
	int look;
};
