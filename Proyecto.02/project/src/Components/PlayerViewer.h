#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../Utilities/InputHandler.h"
#include "../Components/Transform.h"
#include "../Components/Laberinto.h"
#include "../Components/MazePos.h"

class PlayerViewer : public Component
{
public:
	PlayerViewer():Component(ecs::PlayerViewer), //
		pos(nullptr),lab(nullptr),cas(nullptr), casSig(nullptr),manager(nullptr)//
	{	}

	PlayerViewer(Laberinto* lab_) :Component(ecs::PlayerViewer), //
		pos(nullptr) ,lab(lab_), cas(nullptr), casSig(nullptr),manager(nullptr) //
	{	}

	virtual ~PlayerViewer() {
		
	}
	void init() override
	{
		pos = GETCMP1_(MazePos);
		manager = game_->getTextureMngr();
	}
	void update() override;

	virtual void draw();


private:
	MazePos* pos;
	Laberinto* lab;
	vector<bool> casillaActual;
	vector<bool> casillaSig;
	vector<bool> casillaSigSig;
	int sentido = Norte;
	Casilla* cas;
	Casilla* casSig;
	Casilla* casSigSig;
	TexturesManager* manager;
	/*void renderEnemyActual();		
	void enemyViewer(enemyTemplate temp, int x, int y, int w, int h);*/	
};

