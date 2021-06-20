#pragma once
#include <vector>
#include <memory>
#include "SDL_rect.h"
#include "../../ecs/Manager.h"

class Entity;
class Tupple;
class ElementsResources
{
protected:
	enum class set_FirstElement
	{
		UP,
		DOWN
	}; using set_FE = set_FirstElement;
	set_FE way_;

protected:
	ElementsResources() : way_() {};
	virtual ~ElementsResources() {};
	void Init(set_FE way);

	// set the way in which elements will be move
	void setFE_way(set_FE selected) { way_ = selected; };
	set_FE way() { return way_; };

	// one way up or down
	void moveUp(Entity* e, double inc_h);
	void moveDown(Entity* e, double inc_h);

	// restores all elements in block
	void reset(const std::vector<std::unique_ptr<Entity>>& entities, SDL_Rect reference, Tupple limits);
	void resetToTop(const std::vector<std::unique_ptr<Entity>>& entities, SDL_Rect topElement, Tupple limits);
	void resetToBottom(const std::vector<std::unique_ptr<Entity>>& entities, SDL_Rect bottomElement, Tupple limits);

	// deletes all elements in the block
	void cleanALL(std::vector<std::unique_ptr<Entity>>& entities);

	// draw the given element, if it is inside the limits
	void drawElement(Entity* e, Tupple limits);

	// draw all given elements
	void draw(const std::vector<std::unique_ptr<Entity>>& entities, Tupple limits);

	// checks the block size, if it exceeds the limit, the first line inserted will be delete
	virtual void checkBlockSize(std::vector<std::unique_ptr<Entity>> &entities, int numElements);

	// checks if the element is inside the limits
	bool checkTopDownMax(double y, Tupple limits);

	// add element
	void add_element(Entity* e, SDL_Rect reference, double espace, EntityManager* mngr);
	void addTop_element(Entity* e, SDL_Rect topElement, double esp_h, EntityManager* mngr);
	void addBottom_element(Entity* e, SDL_Rect bottomElement, double esp_h, EntityManager* mngr);

};