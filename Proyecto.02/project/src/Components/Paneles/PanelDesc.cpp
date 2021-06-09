#include "PanelDesc.h"
#include "../../GameObjects/Button.h"
#include "../../Templates/Resources.h"
#include "../../Utilities/textures_box.h"
#include "../../Utilities/SDL_macros.h"

using namespace textures_box;

void PanelDesc::init()
{
	// info
	nombreHab_ = hab_->name();
	descripcionHab_ = hab_->description();
	manaHab_ = to_string(hab_->getMana());
	// string tipoHab_ = hab_->getHabilityType();
	// string modificadorHab_ = hab_->getMod();
	
	// aspecto
	marco_ = RECT(
				game_->setHorizontalScale(670), //posX
				game_->setVerticalScale(750),	//posY
				game_->setHorizontalScale(620),	//ancho
				game_->setVerticalScale(272)	//alto
				);

	titulo_ = RECT(
				marco_.x + offsetMarcoX_,
				marco_.y + offsetMarcoY_,
				tamTextoGrande_.first,
				tamTextoGrande_.second
				);

	descripcion_ = RECT(
				titulo_.x,
				titulo_.y + titulo_.h,
				tamTextoPequenyo_.first,
				tamTextoPequenyo_.second
				);

	mana_ = RECT(
				marco_.x + offsetMarcoX_,
				marco_.y + marco_.h - tamTextoGrande_.second - offsetMarcoY_,
				tamTextoGrande_.first,
				tamTextoGrande_.second
				);

	drawPanel();
}
void PanelDesc::update() {}
void PanelDesc::draw() {}

void PanelDesc::drawPanel()
{
	// Fondo:
	pan_->addButton(iManager_->addButton<SDL_Object>(marco_, src::Cartelito));

	//Texto:
	//string nom = "A" + (std::string)"mogus en pamplona";
	pan_->addButton(iManager_->addButton<Line>(titulo_, checkLineSize(nombreHab_), colorTextoTitulo_));
	//string des = "Ah, " + (std::string)"este es un ejemplo de descripcion muy larga pare el texto - Es porello que queda mal";
	pan_->addButton(iManager_->addButton<Line>(descripcion_, checkLineSize(descripcionHab_), colorTextoDescripcion_));
	//string man = "Mana: " + (std::string)"134";
	pan_->addButton(iManager_->addButton<Line>(mana_, checkLineSize(manaHab_), colorTextoMana_));
}

std::string PanelDesc::checkLineSize(std::string line)
{
	if (line.size() < NUM_LET) line.resize(NUM_LET, ' ');
	return line;
}