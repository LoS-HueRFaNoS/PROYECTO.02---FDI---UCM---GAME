#include "PanelDnD.h"
#include "../../GameObjects/Button.h"
#include "../../Templates/Resources.h"
#include "../../Utilities/textures_box.h"
#include "../../Utilities/SDL_macros.h"

using namespace textures_box;

void PanelDnD::init()
{
	// character info
	character_sheet = character_->getCharacterSheet();

	// panel divisions sizes
	SDL_Panel pan = game_->relativePanel(70, 70, 1340, 620, 3, 3, 250, 100, 5, 5);
	firstElement = RECT(pan.fcx, pan.fcy, pan.cw, pan.ch);
	uint mcw = game_->setHorizontalScale(50);
	uint mch = game_->setHorizontalScale(50);
	marco = RECT(
		pan.x + mcw, 
		pan.y + mch, 
		pan.w - mcw * 2, 
		pan.h - mch * 2
	);

	drawPanelDnDActual();
	//addTemplate();
}

void PanelDnD::update()
{
}

void PanelDnD::draw()
{
}

void PanelDnD::drawPanelDnDActual()
{
	// Fondo:
	pan_->addButton(iManager_->addButton<SDL_Object>(marco, src::Pergamino));

	// TITLE:
	addTitleName();

	// MAIN STATS:
	addMainStats();	

	// RESISTENCIAS:
	addWeaknesses();

	// ARMOR & WEAPON:
	addArmorWeapon();

	// CHARACTER:
	addCharacter();
}

void PanelDnD::addTitleName()
{
	SDL_Rect slottSize = RECT(
		firstElement.x,
		firstElement.y,
		firstElement.w * 3,
		firstElement.h
	);	uint k = 0;

	pan_->addButton(iManager_->addButton<Line>(slottSize, character_->name(), hex2sdlcolor("0x000000FF")));
}

void PanelDnD::addWeaknesses()
{
	SDL_Rect lineSize = RECT(
		firstElement.x + 2 * firstElement.w,
		firstElement.y + firstElement.h,
		firstElement.w,
		firstElement.h * 2.0 / NUM_WEAKNESSES
	);	uint k = 0;

	// RESISTENCIAS:
	std::string line = PERCENTAGE(character_sheet->getResistance(damTy::FIRE));		// Fire
	//lineSize.y += lineSize.h;
	std::string text = "Fire = " + line;	
	pan_->addButton(iManager_->addButton<Line>(lineSize, text, hex2sdlcolor("0xFF0000FF")));

	line = PERCENTAGE(character_sheet->getResistance(damTy::WATER));				// Water
	lineSize.y += lineSize.h;
	text = "Water = " + line;	
	pan_->addButton(iManager_->addButton<Line>(lineSize, text, hex2sdlcolor("0x0000FFFF")));

	line = PERCENTAGE(character_sheet->getResistance(damTy::ICE));					// Ice
	lineSize.y += lineSize.h;
	text = "Ice = " + line;		
	pan_->addButton(iManager_->addButton<Line>(lineSize, text, hex2sdlcolor("0x9B9BFFFF")));

	line = PERCENTAGE(character_sheet->getResistance(damTy::EARTH));				// Earth
	lineSize.y += lineSize.h;
	text = "Earth = " + line;	
	pan_->addButton(iManager_->addButton<Line>(lineSize, text, hex2sdlcolor("0x9B5014FF")));

	line = PERCENTAGE(character_sheet->getResistance(damTy::WIND));					// Wind
	lineSize.y += lineSize.h;
	text = "Wind = " + line;	
	pan_->addButton(iManager_->addButton<Line>(lineSize, text, hex2sdlcolor("0x009B00FF")));

	line = PERCENTAGE(character_sheet->getResistance(damTy::LIGHT));				// Light
	lineSize.y += lineSize.h;
	text = "Light = " + line;	
	pan_->addButton(iManager_->addButton<Line>(lineSize, text, hex2sdlcolor("0xFFFF9BFF")));

	line = PERCENTAGE(character_sheet->getResistance(damTy::DARK));					// Dark
	lineSize.y += lineSize.h;
	text = "Dark = " + line;	
	pan_->addButton(iManager_->addButton<Line>(lineSize, text, hex2sdlcolor("0x323232FF")));
}

void PanelDnD::addMainStats()
{
	SDL_Rect lineSize = RECT(
		firstElement.x,
		firstElement.y + firstElement.h,
		firstElement.w,
		firstElement.h * 2.0 / NUM_WEAKNESSES
	);	uint k = 0;

	// VIDA y MANA:
	string text = "Health = " + to_string(character_sheet->maxHitPoints());			// Health
	//lineSize.y += lineSize.h;
	pan_->addButton(iManager_->addButton<Line>(lineSize, text, hex2sdlcolor("0x000000FF")));
	
	text = "Mana = " + to_string(character_sheet->maxManaPoints());					// Mana
	lineSize.y += lineSize.h;
	pan_->addButton(iManager_->addButton<Line>(lineSize, text, hex2sdlcolor("0x000000FF")));

	// Espaciado
	lineSize.y += lineSize.h;

	// MAIN STATS:
	text = "Strength = " + to_string(character_sheet->getStat(ms::STR).value);		// Fuerza
	lineSize.y += lineSize.h;
	pan_->addButton(iManager_->addButton<Line>(lineSize, text, hex2sdlcolor("0x000000FF")));
	
	text = "Constitution = " + to_string(character_sheet->getStat(ms::CON).value);	// Constitution
	lineSize.y += lineSize.h;
	pan_->addButton(iManager_->addButton<Line>(lineSize, text, hex2sdlcolor("0x000000FF")));
	
	text = "Dexterity = " + to_string(character_sheet->getStat(ms::DEX).value);		// Destreza
	lineSize.y += lineSize.h;
	pan_->addButton(iManager_->addButton<Line>(lineSize, text, hex2sdlcolor("0x000000FF")));
	
	text = "Intelect = " + to_string(character_sheet->getStat(ms::INT).value);		// Intelecto
	lineSize.y += lineSize.h;
	pan_->addButton(iManager_->addButton<Line>(lineSize, text, hex2sdlcolor("0x000000FF")));
}

void PanelDnD::addArmorWeapon()
{
	double L = 2.0 / NUM_WEAKNESSES;
	SDL_Rect slottSize = RECT(
		firstElement.x + firstElement.w * (6 + 1) / 6,
		firstElement.y + firstElement.h * (12 + 0) / 6 + L * firstElement.h,
		firstElement.w * 2 / 6,
		firstElement.h * 2 / 6
	);	uint k = 0;

	// ARMA:
	pan_->addButton(iManager_->addButton<ButtonSlott>(slottSize, character_->getWeapon()));

	slottSize.x += slottSize.w;

	// ARMOR:
	Hero* hero_ = dynamic_cast<Hero*>(character_);
	if (hero_ != nullptr) {

		pan_->addButton(iManager_->addButton<ButtonSlott>(slottSize, hero_->getArmor()));

		// HABILITIES:
		addHabilities(hero_);
	}

}

void PanelDnD::addCharacter()
{
	double L = 2.0 / NUM_WEAKNESSES;
	SDL_Rect slottSize = RECT(
		firstElement.x + firstElement.w * 9 / 8,
		firstElement.y + firstElement.h * 9 / 8 + L * firstElement.h,
		firstElement.w * 6 / 8,
		firstElement.h * 6 / 8
	);	uint k = 0;

	// CHARACTER:
	pan_->addButton(iManager_->addButton<SDL_Object>(slottSize, getCharacterTxt(character_)));
}

void PanelDnD::addHabilities(Hero* hero)
{
	double L = 2.0 / NUM_WEAKNESSES;
	SDL_Rect slottSize = RECT(
		firstElement.x + firstElement.w * (8 + 4) / 8,
		firstElement.y + firstElement.h * 3 - firstElement.h * L,
		firstElement.w * L,
		firstElement.h * L
	);	uint k = 0;

	vector<Hability*> habilities = hero->getHabilities();
	int size = habilities.size();

	slottSize.x = slottSize.x - slottSize.w * (size / 2);

	for (int i = 0; i < size; ++i)
	{
		pan_->addButton(iManager_->addButton<SDL_Object>(slottSize, getHabilityTxt(habilities[i])));
		slottSize.x += slottSize.w;
	}
}

void PanelDnD::addTemplate()
{
	SDL_Rect slottSize = RECT(
		firstElement.x,
		firstElement.y,
		firstElement.w,
		firstElement.h
	);	uint k = 3;

	pan_->addButton(iManager_->addButton<SDL_Object>(marco, src::Pergamino));

	for (uint f = 0; f < k; f++) {		
		for (uint c = 0; c < k; c++) {
			pan_->addButton(iManager_->addButton<SDL_Object>(slottSize, src::txtID::Joker));
			slottSize.x += slottSize.w;
		}
		slottSize.y += slottSize.h;
		slottSize.x = firstElement.x;
	}
	
}
