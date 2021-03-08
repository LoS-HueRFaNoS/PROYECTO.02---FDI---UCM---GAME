#ifndef _HERO_
#define _HERO_

#include "Entity.h"
#include "Character.h"


class Hero {
	void init(){
		character_ = entity_->addComponent<Character>();
	
	}

private:
	Entity* entity_;
	Character* character_;
	// Equipamiento* equipo;
};


#endif // !_HERO_

