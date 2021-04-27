#pragma once
#include "Button.h"
#include "ecs_interfaz.h"
#include <list>

using namespace interfaz;

class Panel
{
protected:
	idPanel id;
	list<Button*> buttonList;
	
public:
	Panel(idPanel idPan) : id(idPan) {};

	~Panel(){
		removeButtons();
	}

	void removeButtons();

	void addButton(Button* b) {
		buttonList.push_back(b);
	}

	void toggleButtons() {
		for (Entity* var : buttonList) var->toggleEnabled();
	}

	Button* getButtonActive();
	idPanel GetID() { return id; };
};

