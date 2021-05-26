#include "BorrarAlMorir.h"

BorrarAlMorir::BorrarAlMorir(Interfaz* inter, int i, Enemy* en) : Component(ecs::BorrarAlMorir)
{
	interfaz_ = inter;
	indice = i;
	enemy_ = en;
}

void BorrarAlMorir::init()
{

}

void BorrarAlMorir::update()
{
	if (enemy_->isDead()) {
		interfaz_->enemyDead(indice);
	}
}

void BorrarAlMorir::draw()
{
}
