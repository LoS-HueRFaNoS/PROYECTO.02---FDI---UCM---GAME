#pragma once
#include "Button.h"
#include "ecs_interfaz.h"
#include <list>

using namespace interfaz;

class Panel
{
protected:
	bool enable;
	idPanel id;
	list<Button*> buttonList;
	
public:
	Panel(idPanel idPan) : id(idPan), enable(true) {};

	~Panel(){
		removeButtons();
	}

	void removeButtons();

	void addButton(Button* b) {
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

