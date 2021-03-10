#pragma once
#include "./src/Component.h"
#include "./src/Transform.h"
#include "./src/Entity.h"
#include "./src/InputHandler.h"

class PlayerMotion : public Component
{
public:
	PlayerMotion(SDL_KeyCode avanzar, SDL_KeyCode izq, SDL_KeyCode der) :Component(ecs::PlayerMotion), //
		tr_(nullptr), avance(avanzar), giraIzq(izq),giraDer(der) //
	{

	}
	PlayerMotion() :Component(ecs::PlayerMotion), //
		tr_(nullptr), avance(SDLK_UP), giraIzq(SDLK_LEFT), giraDer(SDLK_DOWN) //
	{

	}
	virtual ~PlayerMotion() {
		tr_ = GETCMP2_(ecs::Transform, Transform);
	}
	void init() override
	{
		tr_ = GETCMP1_(Transform);
	}
	void update() override
	{
		int x = tr_->getPos().getX();
		int y = tr_->getPos().getY();
		InputHandler* ih = InputHandler::instance();
		if (ih->isKeyDown(avance)) {
			switch (tr_->getSentido())
			{
			case 0:
				tr_->setPos(Vector2D(x, y + 1));
				break;
			case 1:
				tr_->setPos(Vector2D(x + 1, y));
				break;
			case 2:
				tr_->setPos(Vector2D(x, y - 1));
				break;
			case 3:
				tr_->setPos(Vector2D(x - 1, y));
				break;
			}

		}
		else if (ih->isKeyDown(giraIzq)) {
			auto sent =tr_->getSentido();
			if (sent == MapCell::Norte)
				sent = MapCell::Oeste;
			else
				sent--;
			tr_->setSentido(sent);
		}
		else if (ih->isKeyDown(giraDer)) {
			int sent = tr_->getSentido();
			if (sent == MapCell::Oeste)
				sent = MapCell::Norte;
			else 
				sent++;
			tr_->setSentido(sent);
		}
	}
private:
	Transform* tr_;
	SDL_KeyCode avance, giraIzq, giraDer;
};

