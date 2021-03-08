#pragma once

#include "Vector2D.h"
#include "Component.h"
#include <SDL_rect.h>
#include "Entity.h"
#include "SDL_macros.h"
#include "Texture.h"
#include "Transform.h"

class CasillaRender : public Component {
public:
	CasillaRender(SDL_Rect clip) : Component(ecs::CasillaRender),
		clip(clip),
		tr_(nullptr){}
	virtual ~CasillaRender() {};
	void dibujaCasilla()
	{
		/*SDL_Rect dest
			RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH());
		Texture* texturaCasilla;
		texturaCasilla = game_->getTextureMngr()->getTexture(Resources::Pasillo1);
		texturaCasilla->render(dest,tr_->getRot(),clip_);*/
	}
private:
	Transform* tr_;
	SDL_Rect clip_;
};

