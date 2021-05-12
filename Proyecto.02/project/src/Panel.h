#pragma once
#include "Button.h"
#include "ecs_interfaz.h"
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

