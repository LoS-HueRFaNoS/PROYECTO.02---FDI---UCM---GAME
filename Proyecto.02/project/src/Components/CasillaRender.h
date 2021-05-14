#pragma once

#include <SDL_rect.h>
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../Utilities/SDL_macros.h"
#include "../Structures/Vector2D.h"
#include "../Structures/Texture.h"
#include "Transform.h"
const static enum MapCell { Norte, Este, Sur, Oeste };
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
		SDL_Rect dest
			RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH());
		Texture* texturaCasilla;
		int izquierda;
		if (look == Norte) izquierda = Oeste;
		else izquierda = look-1;
		int derecha;
		if (look == Oeste) derecha = Norte;
		else izquierda = look+1;
		auto manager = game_->getTextureMngr();
		if (direcciones[look] && direcciones[izquierda] && direcciones[derecha]) // <-^->
			texturaCasilla = manager->getTexture(Resources::Pasillo1);
		else if (direcciones[look] && direcciones[izquierda] && !direcciones[derecha]) // <-^
			texturaCasilla = manager->getTexture(Resources::Pasillo2);
		else if (!direcciones[look] && direcciones[izquierda] && !direcciones[derecha]) // <-
			texturaCasilla = manager->getTexture(Resources::Pasillo3);
		else if (direcciones[look] && !direcciones[izquierda] && !direcciones[derecha]) // ^
			texturaCasilla = manager->getTexture(Resources::Pasillo4);
		else if (!direcciones[look] && direcciones[izquierda] && direcciones[derecha]) // <- ->
			texturaCasilla = manager->getTexture(Resources::Pasillo5);
		else if (direcciones[look] && !direcciones[izquierda] && direcciones[derecha]) // ^->
			texturaCasilla = manager->getTexture(Resources::Pasillo6);
		else if (!direcciones[look] && !direcciones[izquierda] && direcciones[derecha]) // ->
			texturaCasilla = manager->getTexture(Resources::Pasillo7);
		else if (!direcciones[look] && !direcciones[izquierda] && !direcciones[derecha]) //
			texturaCasilla = manager->getTexture(Resources::Pasillo8);
		texturaCasilla->render(dest,tr_->getRot(),clip_);
	}
private:
	Transform* tr_;
	SDL_Rect clip_;
};

