#include "ElementsResources.h"
#include "../../Components/Transform.h"
#include "../../Structures/Vector2D.h"
#include "../../ecs/Entity.h"

//--- MOVE VERTICAL SIDE ------------------------------------------

void ElementsResources::Init(set_FE way)
{
	way_ = way;
}

// Mueve una fila hacia arriba (inc_h = alto de una linea)
void ElementsResources::moveUp(Entity* e, double inc_h)
{
	Transform* tr_ = GETCMP2(e, Transform);
	tr_->setPosY(tr_->getPos().getY() - inc_h);
}

// Mueve una fila hacia abajo (inc_h = alto de una linea)
void ElementsResources::moveDown(Entity* e, double inc_h)
{
	Transform* tr_ = GETCMP2(e, Transform);
	tr_->setPosY(tr_->getPos().getY() + inc_h);
}

//--- RESET SCROLL ------------------------------------------------

// restores initial position
void ElementsResources::reset(const std::vector<std::unique_ptr<Entity>>& entities, SDL_Rect reference, Tupple limits)
{
	if (way_ == set_FE::UP) {
		resetToTop(entities, reference, limits);
	}
	else if (way_ == set_FE::DOWN) {
		resetToBottom(entities, reference, limits);
	}
}

// restores initial position (scroll hacia arriba completo)
void ElementsResources::resetToTop(const std::vector<std::unique_ptr<Entity>>& entities, SDL_Rect topElement, Tupple limits)
{
	Transform* tr_ = GETCMP2(entities.rbegin()->get(), Transform);
	double y = tr_->getPos().getY();					// check last line

	while (y != topElement.y && (y + topElement.h) <= limits.getLeft()) {
		for (auto it = entities.begin(); it != entities.end(); it++) {
			moveUp(it->get(), topElement.h);			// move up
		}
		y = tr_->getPos().getY();
	}
}

// restores initial position (scroll hacia abajo completo)
void ElementsResources::resetToBottom(const std::vector<std::unique_ptr<Entity>>& entities, SDL_Rect bottomElement, Tupple limits)
{
	Transform* tr_ = GETCMP2(entities.rbegin()->get(), Transform);
	double y = tr_->getPos().getY();					// check last line

	while (y != bottomElement.y && (y + bottomElement.h) <= limits.getRight()) {
		for (auto it = entities.begin(); it != entities.end(); it++) {
			moveDown(it->get(), bottomElement.h);		// move down
		}
		y = tr_->getPos().getY();
	}
}

//--- CLEAN -------------------------------------------------------

// cleans all the elements in the block
void ElementsResources::cleanALL(std::vector<std::unique_ptr<Entity>>& entities)
{
	for (auto it = entities.rbegin(); it != entities.rend(); it++) {
		(*it)->disable();
	}
	entities.clear();
}

//--- CHECK INSIDE ------------------------------------------------

// comprueba si el elemento se encuentra dentro de la zona visible
bool ElementsResources::checkTopDownMax(double y, Tupple limits)
{
	if (y >= limits.getLeft() && y <= limits.getRight())
	{
		return true;
	}
	else return false;
}

// comprueba si sobrepasa el limite de elementos en el bloque, si es asi borrar el primero en entrar
void ElementsResources::checkBlockSize(std::vector<std::unique_ptr<Entity>>& entities, int numElements)
{
	if (entities.size() > numElements) {
		entities.begin()->get()->disable();
	}
}

//--- ADD ELEMENT -------------------------------------------------

// espace must have in mind the padding and the borders
void ElementsResources::add_element(Entity* e, SDL_Rect reference, double espace, EntityManager* mngr)
{
	if (way_ == set_FE::UP) {
		addTop_element(e, reference, espace * 2, mngr);
	}
	else if (way_ == set_FE::DOWN) {
		addBottom_element(e, reference, espace * 2, mngr);
	}
}

void ElementsResources::addTop_element(Entity* e, SDL_Rect topElement, double esp_h, EntityManager* mngr)
{
	for (auto it = mngr->entities_().begin(); it != mngr->entities_().end(); it++) {
		moveDown(it->get(), topElement.h + esp_h);
	}
	mngr->addEntity(e);
}

void ElementsResources::addBottom_element(Entity* e, SDL_Rect bottomElement, double esp_h, EntityManager* mngr)
{
	for (auto it = mngr->entities_().begin(); it != mngr->entities_().end(); it++) {
		moveUp(it->get(), bottomElement.h + esp_h);
	}
	mngr->addEntity(e);
}

//--- DRAW --------------------------------------------------------

// lo pinta si se encuentra en la zona visible
void ElementsResources::drawElement(Entity* e, Tupple limits)
{
	Transform* tr_ = GETCMP2(e, Transform);
	double y = tr_->getPos().getY();
	if (checkTopDownMax(y, limits)) {
		e->draw();
	};
}

// muestra todos los elementos
void ElementsResources::draw(const std::vector<std::unique_ptr<Entity>>& entities, Tupple limits)
{
	for (auto it = entities.begin(); it != entities.end(); it++) {
		drawElement(it->get(), limits);
	}
}
