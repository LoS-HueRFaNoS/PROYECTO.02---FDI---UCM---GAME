#pragma once
#include "../../ecs/ecs_interfaz.h"
#include "../../ecs/Entity.h"
#include "../../GameObjects/Button.h"
#include "../../Utilities/checkML.h"
#include <vector>

using namespace interfaz;

class PanelResources
{
protected:
	bool enable_;
	idPanel id_;
	vector<Entity*> list_;

public:
	PanelResources(idPanel idPan) : id_(idPan), enable_(true) {};
	virtual ~PanelResources() { removeElements(); }

	// main actions
	void addElement(Entity* b) { list_.push_back(b); }
	Entity* getElement(uint n) { return list_[n]; };

	void toggleEnable() {
		enable_ = !enable_;
		for (Entity* var : list_)
			var->toggleEnabled();
	}

	// GETTERS
	idPanel ID() { return id_; };
	bool enable() { return enable_; };
	int listSize() { return list_.size(); }

	// deleters
	void removeElements();
	void removeElement(uint n);

	// list actions
	void swapElementsList(vector<Entity*> savedHeroes);	

	// button panels needs
	ButtonPanel* getButtonActive();
	
};
