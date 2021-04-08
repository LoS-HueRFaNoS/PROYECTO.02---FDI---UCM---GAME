#include "Entity.h"

Entity::Entity(SDLGame *game, EntityManager *mngr) :
		game_(game), //
		mngr_(mngr), //
		enabled(true) //
{
}

Entity::~Entity() {
}

