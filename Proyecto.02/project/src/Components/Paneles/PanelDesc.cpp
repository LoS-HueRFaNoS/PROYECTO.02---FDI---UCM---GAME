#include "PanelDesc.h"
#include "../../GameObjects/Button.h"
#include "../../Templates/Resources.h"
#include "../../Utilities/textures_box.h"
#include "../../Utilities/SDL_macros.h"

using namespace textures_box;

void PanelDesc::init()
{
	// info
	//
	nombreHab_ = hab_->name();
	//
	string d = hab_->description();
	while (d.size() > 0) {
		string aux = "";
		aux.insert(0, d, 0, numLet_);
		d.erase(0, numLet_);
		descripcionHab_.push_back(aux);
	}
	//
	manaHab_ = (std::string)"Coste: " + to_string(hab_->getMana());
	//
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
	//
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
		anchoTexto_,
		altoTexto_
		);

	descripcion_ = RECT(
		titulo_.x,
		titulo_.y + titulo_.h,
		anchoTexto_,
		altoTexto_
		);

	mana_ = RECT(
		marco_.x + offsetMarcoX2_,
		marco_.y + offsetMarcoY_,
		anchoTexto_,
		altoTexto_
		);

	tipo_ = RECT(
		marco_.x + offsetMarcoX_,
		marco_.y + marco_.h - altoTexto_ - offsetMarcoY_,
		anchoTexto_,
		altoTexto_
		);

	modificador_ = RECT(
		marco_.x + offsetMarcoX2_,
		marco_.y + marco_.h - altoTexto_ - offsetMarcoY_,
		anchoTexto_,
		altoTexto_
		);

	//colores
	if (affordable_) {
		colorTextoTitulo_ = hex2sdlcolor("0xFFD700FF");
		colorTextoDescripcion_ = hex2sdlcolor("0xFFFFFFFF");
		colorTextoMana_ = hex2sdlcolor("0x0055FFFF");
		colorTextoTipo_ = hex2sdlcolor("0xE20066FF");
		colorTextoModificador_ = hex2sdlcolor("0x22B7ABFF");
	}
	else {
		colorTextoTitulo_ = hex2sdlcolor("0xCBCBCBFF");
		colorTextoDescripcion_ = hex2sdlcolor("0x6F6F6FFF");
		colorTextoMana_ = hex2sdlcolor("0xFF0F00FF");
		colorTextoTipo_ = hex2sdlcolor("0x4F4F4FFF");
		colorTextoModificador_ = hex2sdlcolor("0x898989FF");
	}

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
	for (int i = 0; i < descripcionHab_.size(); i++) {
		pan_->addButton(iManager_->addButton<Line>(descripcion_, checkLineSize(descripcionHab_[i]), colorTextoDescripcion_));
		descripcion_.y += descripcion_.h;
	}
	pan_->addButton(iManager_->addButton<Line>(mana_, checkLineSize(manaHab_), colorTextoMana_));
	pan_->addButton(iManager_->addButton<Line>(tipo_, checkLineSize(tipoHab_), colorTextoTipo_));
	pan_->addButton(iManager_->addButton<Line>(modificador_, checkLineSize(modificadorHab_), colorTextoModificador_));
}

std::string PanelDesc::checkLineSize(std::string line)
{
	if (line.size() < numLet_) line.resize(numLet_, ' ');
	return line;
}