#pragma once
#include "../Managers/game/ElementManager.h"

class Entity;
class Character;
typedef unsigned int uint;
class PanelTurnos : public ElementManager
{
private:
	SDL_Panel pan;
	Entity* fondo_ = nullptr;
	Entity* turns_ = nullptr;
	Entity* next_ = nullptr;
	Entity* nextTurn_ = nullptr;

	SDL_Rect icono;
	SDL_Rect number;
	SDL_Rect bar;
	SDL_Rect first;
	SDL_Rect first_bar;

	SDL_Rect fondo_rect;
	SDL_Rect next_rect;
	SDL_Rect nextTurn_rect;
	SDL_Rect turns_rect;

	bool refresh_done = false;
	uint last_state = 2;

	uint offset = 0;

public:
	PanelTurnos(SDLGame* game) : ElementManager(game) {
		pan = game_->relativePanel(1510, 70, 340, 190, 3, 3, 15, 15, 10, 10);
	};
	virtual ~PanelTurnos() {
		delete fondo_;
		fondo_ = nullptr;
	};

	void Init();
	void update();
	void draw();

private:
	Character* character_;
	std::vector<Character*> turnsList_;

	void drawCurrentCharacter();
	void drawCurrentTurnList();
	void drawFondo();

};
