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
	manaHab_ = (std::string)"Coste: " + to_string(hab_->getMana());
	tipoHab_ = (std::string)"Tipo: ";
	switch (hab_->getHabilityType())
	{
	case HabilityType::ATTACK:
		tipoHab_ += (std::string)"Ataque";
		break;
	case HabilityType::DEBUFF:
		tipoHab_ += (std::string)"Malus";
		break;
	case HabilityType::HEAL:
		tipoHab_ += (std::string)"Cura";
		break;
	case HabilityType::BUFF:
		tipoHab_ += (std::string)"Bonus";
		break;
	default:
		tipoHab_ += (std::string)"Ataque";
		break;
	}
	modificadorHab_ = (std::string)"Mod.: ";
	switch (hab_->getMod())
	{
	case mainStat::STR:
		modificadorHab_ += (std::string)"Fuerza";
		break;
	case mainStat::CON:
		modificadorHab_ += (std::string)"Const.";
		break;
	case mainStat::DEX:
		modificadorHab_ += (std::string)"Destr.";
		break;
	case mainStat::INT:
		modificadorHab_ += (std::string)"Intel.";
		break;
	default:
		modificadorHab_ += (std::string)"Fuerza";
		break;
	}
	
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
		marco_.x + offsetMarcoX2_,
		marco_.y + offsetMarcoY_,
		tamTextoGrande_.first,
		tamTextoGrande_.second
		);

	tipo_ = RECT(
		marco_.x + offsetMarcoX_,
		marco_.y + marco_.h - tamTextoGrande_.second - offsetMarcoY_,
		tamTextoGrande_.first,
		tamTextoGrande_.second
		);

	modificador_ = RECT(
		marco_.x + offsetMarcoX2_,
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
	pan_->addButton(iManager_->addButton<Line>(titulo_, checkLineSize(nombreHab_), colorTextoTitulo_));
	pan_->addButton(iManager_->addButton<Line>(descripcion_, checkLineSize(descripcionHab_), colorTextoDescripcion_));
	pan_->addButton(iManager_->addButton<Line>(mana_, checkLineSize(manaHab_), colorTextoMana_));
	pan_->addButton(iManager_->addButton<Line>(tipo_, checkLineSize(tipoHab_), colorTextoTipo_));
	pan_->addButton(iManager_->addButton<Line>(modificador_, checkLineSize(modificadorHab_), colorTextoModificador_));
}

std::string PanelDesc::checkLineSize(std::string line)
{
	if (line.size() < NUM_LET) line.resize(NUM_LET, ' ');
	return line;
}