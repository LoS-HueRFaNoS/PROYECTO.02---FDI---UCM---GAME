#pragma once
#include "../ecs/ecs_interfaz.h"
#include "../GameObjects/Button.h"
#include "../Utilities/checkML.h"
#include <vector>

using namespace interfaz;

class Panel
{
protected:
	bool enable;
	idPanel id;
	vector<Entity*> buttonList;
	
public:
	Panel(idPanel idPan) : id(idPan), enable(true) {};

	~Panel(){
		removeButtons();
	}

	void removeButtons();
	void removeButton(uint n);
	void swapButtonList(vector<Entity*> savedHeroes);
	Entity* getButton(uint n) {
		return buttonList[n];
	};
	int getButtonListSize() { return buttonList.size(); }
	void addButton(Entity* b) {
		buttonList.push_back(b);
	}

	void toggleEnable() {
		enable = !enable;
		for (Entity* var : buttonList) var->toggleEnabled();
	}

	ButtonPanel* getButtonActive();
	idPanel GetID() { return id; };
	bool getEnable() { return enable; };
};

