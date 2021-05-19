#include "PanelTurns.h"
#include "../GameObjects/Button.h"
#include "../Templates/Resources.h"
#include "../Utilities/textures_box.h"
#include "../Utilities/SDL_macros.h"
#include "../Managers/game/LobbyManager.h"
#include "../Managers/game/CombatManager.h"

using src = Resources;
using namespace textures_box;

void PanelTurns::init()
{
	// posicion en pixeles del 'fondo'
	double x_ = 1510;
	double y_ = 70;
	// tamano en pixeles del 'fondo'
	double w_ = 340;
	double h_ = 190;
	// tamano de los margenes
	double n = 20;

	// posicion y size del panel respecto a la ventana
	marco = RECT(
		game_->setHorizontalScale(x_),
		game_->setVerticalScale(y_),
		game_->setHorizontalScale(w_),
		game_->setVerticalScale(h_)
	);

	double espace = game_->setHorizontalScale(n); //

	// position and size first element
	firstElement = RECT(
		game_->setHorizontalScale(x_ + n),
		game_->setVerticalScale(y_ + n),
		game_->setHorizontalScale((w_ - n * 2) / 3),
		game_->setVerticalScale((h_ - n * 2) / 3)
	);

	// Character
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	character_ = c->getCurrentCharacter();
	turnsList_ = c->getCurrentTurnsList();
}

void PanelTurns::update()
{
}

void PanelTurns::draw()
{
	drawCharacterActual();
}

void PanelTurns::drawCharacterActual()
{
	Vector2D pos = Vector2D(firstElement.x + firstElement.w, firstElement.y + firstElement.h);

	// IMG pj actual
	src::TextureId img = size_t(character_->getType()) ? getEnemyTxt(character_) : getHeroTxt(character_);
	pan_->addButton(iManager_->addButton<SDL_Object>(pos, firstElement.w, firstElement.h, img));

	// VIDA y MANA:
	SDL_Color color = { 255,0,0,255 };
	CharacterSheet* character_sheet = character_->getCharacterSheet();
	pos = Vector2D(firstElement.x, firstElement.y + firstElement.h * 2);
	string text = to_string(character_sheet->maxHitPoints());	// Health
	pan_->addButton(iManager_->addButton<Line>(pos, firstElement.w, firstElement.h, text, Resources::Fornite64, color));
	color = { 0,0,255,255 };
	pos = Vector2D(firstElement.x + firstElement.w, firstElement.y + firstElement.h * 2);
	text = to_string(character_sheet->maxManaPoints());	// Mana
	pan_->addButton(iManager_->addButton<Line>(pos, firstElement.w, firstElement.h, text, Resources::Fornite64, color));
}
