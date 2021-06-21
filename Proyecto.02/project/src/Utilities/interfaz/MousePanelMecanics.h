#pragma once
#include "ElementsResources.h"
#include <vector>
#include <memory>
class Entity;
class Tupple;
struct SDL_Rect;

class MousePanelMecanics : public ElementsResources
{
protected:
	int exceed;

public:
	MousePanelMecanics() : ElementsResources(), exceed() {};
	virtual ~MousePanelMecanics() {};
	void Init(int exc, set_FE way);

	void set_exceed(int n) { exceed = n; };

	// mouse inside of area
	bool isMouseIN(SDL_Rect marco);	

	// scroll double way sensitive
	void scroll(SDL_Rect marco, Tupple limits, const std::vector<std::unique_ptr<Entity>> &entities, double cellSize_h, double padding_n_border_h = 0.0);

	// moves the block/panel and all the element it contains
	// void moveBlock(SDL_Rect marco, const std::vector<std::unique_ptr<Entity>>& entities, SDL_Point newPos);

}; 
