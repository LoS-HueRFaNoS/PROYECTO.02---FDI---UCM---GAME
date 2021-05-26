#pragma once
#include "../ecs/Component.h"
#include "Interfaz.h"
#include "../GameObjects/Character.h"

class BorrarAlMorir : public Component {
private:
	Interfaz* interfaz_;
	int indice;
	Enemy* enemy_;

public:
	BorrarAlMorir(Interfaz* inter, int i, Enemy* en);
	virtual ~BorrarAlMorir() {};

	void init() override;
	void update() override;
	void draw() override;
};


