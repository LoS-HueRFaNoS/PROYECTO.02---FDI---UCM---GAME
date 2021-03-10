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
		clip_(clip),
		tr_(nullptr){}
	CasillaRender() : Component(ecs::CasillaRender),
		clip_({ 0,0,0,0 }),
		tr_(nullptr) {}
	virtual ~CasillaRender() {};
	void draw()
	{
		//SDL_Rect dest
		//	RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH());
		//Texture* texturaCasilla;
		//
		//




		//int izquierda = look-1; 
		//int derecha = look+1;
		//if (izquierda == -1) izquierda = 3;
		//if (derecha == 4) derecha = 0;
		//if (direcciones[look] && direcciones[izquierda] && direcciones[derecha]) // <-^->
		//texturaCasilla = game_->getTextureMngr()->getTexture(Resources::Pasillo1);
		//else if (direcciones[look] && direcciones[izquierda] && !direcciones[derecha]) // <-^
		//else if (!direcciones[look] && direcciones[izquierda] && !direcciones[derecha]) // <-
		//else if (direcciones[look] && !direcciones[izquierda] && !direcciones[derecha]) // ^
		//else if (!direcciones[look] && direcciones[izquierda] && direcciones[derecha]) // <- ->
		//else if (direcciones[look] && !direcciones[izquierda] && direcciones[derecha]) // ^->
		//else if (!direcciones[look] && !direcciones[izquierda] && direcciones[derecha]) // ->
		//else if (!direcciones[look] && !direcciones[izquierda] && !direcciones[derecha]) // 
		//texturaCasilla->render(dest,tr_->getRot(),clip_);
	}
private:
	Transform* tr_;
	SDL_Rect clip_;
};

