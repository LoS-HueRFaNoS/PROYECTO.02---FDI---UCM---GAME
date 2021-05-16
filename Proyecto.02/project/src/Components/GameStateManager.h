#pragma once
#include "../ecs/Component.h"

class TheElementalMaze;

enum class GameState;

class GameStateManager : public Component {
private:
	GameState state_;
	TheElementalMaze* tem_;
public:
	GameStateManager();
	virtual ~GameStateManager() {};

	GameState gameState() { return state_; }
	void changeState(GameState state)
	{
		if (state_ != state) {
			state_ = state;
		}
	}

	void init() override;
	void update() override;
};