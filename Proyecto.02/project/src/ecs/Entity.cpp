#include "Entity.h"

Entity::Entity(SDLGame *game, EntityManager *mngr) :
		game_(game), //
		mngr_(mngr), //
		enabled(true), //
		active(true),
		pause(false)
{
}

Entity::~Entity() {
	components_.clear();
}

