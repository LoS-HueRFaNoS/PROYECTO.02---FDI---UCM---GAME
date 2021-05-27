#pragma once
#include "../ecs/Component.h"

class TheElementalMaze;

enum class GameState;

class GameStateManager : public Component {
private:
	GameState state_;
	TheElementalMaze* tem_;
	bool stateChanged = false;
public:
	GameStateManager();
	virtual ~GameStateManager() {};

	GameState gameState() { return state_; }
	void changeState(GameState state)
	{
		if (state_ != state) {
			state_ = state;
			stateChanged = true;
		}
	}

	void init() override;
	void update() override;
};