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
	//list<ButtonType<T>*> buttonTypeList;
	
public:
	Panel(idPanel idPan) : id(idPan) {};

	~Panel(){
		for (auto it = buttonList.begin(); it != buttonList.end(); ++it)
		{
			delete (*it);
		}
		buttonList.clear();
	}

	void addButton(Button* b) {
		buttonList.push_back(b);
	}

	/*template<typename T>
	void addButtonType(ButtonType<T>* b) {
		buttonTypeList.push_back(b);
	}*/

	void toggleButtons() {
		for (Entity* var : buttonList) var->toggleEnabled();
	}

	idPanel GetID() { return id; };
};

