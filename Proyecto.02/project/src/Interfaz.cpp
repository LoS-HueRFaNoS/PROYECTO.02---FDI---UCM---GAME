#include "Interfaz.h"

void Interfaz::createMovement()
{
	Panel* p = new Panel();
	allPanels.push_back(p);
	p->addButton(new Button(Vector2D(0,0), ANCHO, ALTO, IMAGEN, CALLBACK));
	p->addButton(new Button(Vector2D(0, 0), ANCHO, ALTO, IMAGEN, CALLBACK));
	p->addButton(new Button(Vector2D(0, 0), ANCHO, ALTO, IMAGEN, CALLBACK));
	p->addButton(new Button(Vector2D(0, 0), ANCHO, ALTO, IMAGEN, CALLBACK));
}

Interfaz::Interfaz(Game* juego)
{
	game_ = juego;
}

Interfaz::~Interfaz()
{
}

void Interfaz::createPanel(idPanel panelID)
{
	switch (panelID) {
	case Fight:
		createFight();
		break;
	case Movement:
		createMovement();
		break;
	case Minimap:
		createMinimap();
		break;
	case Heroes:
		createHeroes();
		break;
	case Info:
		createInfo();
		break;
	case Inventory:
		createInventory();
		break;
	case HeroesStats:
		createHeroesStats();
		break;
	case BigMap:
		createBigMap();
		break;
	case Turns:
		createTurns();
		break;
	case Settings:
		createSettings();
		break;
	case Chat:
		createChat(); 
		break;
	}
}


void Interfaz::destroyPanel(idPanel panelID)
{
	bool encontrado = false;
	int i = 0;
	while (!encontrado && i < contador) {
		encontrado = allPanels->GetID() == panelID;

		++i;
	}

	if (encontrado) delete allPanels[i];
}

