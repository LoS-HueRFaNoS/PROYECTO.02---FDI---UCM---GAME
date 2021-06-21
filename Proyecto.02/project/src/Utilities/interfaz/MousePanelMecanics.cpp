#include "MousePanelMecanics.h"
#include "../InputHandler.h"
#include "../../ecs/Entity.h"
#include "../../Components/Transform.h"

void MousePanelMecanics::Init(int exc, set_FE way)
{
	exceed = exc;
	ElementsResources::Init(way);
}

// Comprueba si el cursor esta dentro del area ocupado por el panel
bool MousePanelMecanics::isMouseIN(SDL_Rect marco)
{
	InputHandler* ih_ = InputHandler::instance();
	Vector2D pos_ = ih_->getMousePos();
	SDL_Point p_ = { (int)pos_.getX(), (int)pos_.getY() };
	return SDL_PointInRect(&p_, &marco);
}

// Hace el efecto de scroll si detecta MouseScrollEvent dentro del chat 
// atencion: los elementos deben colocarse de abajo a arriba!!
void MousePanelMecanics::scroll(SDL_Rect marco, Tupple limits, const std::vector<std::unique_ptr<Entity>> &entities, double cellSize_h, double padding_n_border_h)
{
	double y;
	double inc_h = cellSize_h + (padding_n_border_h * 2);
	InputHandler* ih_ = InputHandler::instance();
	if (ih_->mouseWheelEvent() && isMouseIN(marco))
	{
		// away from the user
		if (ih_->getMouseWheelState(InputHandler::UP))
		{
			Entity* e = nullptr;

			if (way() == set_FE::DOWN) {
				e = entities.begin()->get();
			}
			else if (way() == set_FE::UP) {
				e = entities.rbegin()->get();
			}

			Transform* tr_ = GETCMP2(e, Transform);
			y = tr_->getPos().getY();				// check first line

			if (y <= limits.getLeft() + inc_h * exceed) {
				for (auto it = entities.begin(); it != entities.end(); it++) {
					moveDown(it->get(), inc_h);		// move down
				}
			}
		}

		// toward the user
		else if (ih_->getMouseWheelState(InputHandler::DOWN))
		{
			Entity* e = nullptr;

			if (way() == set_FE::DOWN) {
				e = entities.rbegin()->get();
			}
			else if (way() == set_FE::UP) {
				e = entities.begin()->get();
			}

			Transform* tr_ = GETCMP2(e, Transform);
			y = tr_->getPos().getY();				// check last line

			if (y >= limits.getRight() - inc_h * exceed) {
				for (auto it = entities.begin(); it != entities.end(); it++) {
					moveUp(it->get(), inc_h);		// move up
				}
			}
		}
	}
}
