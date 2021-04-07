#pragma once
#include "Button.h"
#include <list>
enum idPanel { Fight, Movement, Minimap, Heroes, Info, Inventory, HeroesStats, BigMap, Turns, Settings, Chat };

class Panel
{
protected:
	idPanel id;
	list<Button*> buttonList;
	
public:
	Panel(idPanel idPan) : id(idPan) {};

	~Panel(){
		//Hay que hacer que se destruya así pero por EntityManager

		/*for(Entity* b : buttonList){
			delete b; b = nullptr;
		}*/
		buttonList.clear();
	}

	void addButton(Button* b) {
		buttonList.push_back(b);
		//Faltaria el destructor
	}

	void toggleButtons() {
		for (Entity* var : buttonList) var->toggleEnabled();
	}

	idPanel GetID() { return id; };
};

