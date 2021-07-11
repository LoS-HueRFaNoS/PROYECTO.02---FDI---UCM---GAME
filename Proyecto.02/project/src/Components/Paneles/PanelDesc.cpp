#include "PanelDesc.h"
#include "../../GameObjects/Button.h"
#include "../../Templates/Resources.h"
#include "../../Utilities/textures_box.h"
#include "../../Utilities/SDL_macros.h"

using namespace textures_box;

void PanelDesc::init()
{
	// valores responsive
	numLet_ = 53;
	anchoTexto_ = game_->setHorizontalScale(11.2); // game_->setHorizontalScale(590); // 425; // 425 para NUM_LET = 38
	altoTexto_ = game_->setVerticalScale(35); // 35;
	//---
	offsetMarcoX_ = game_->setHorizontalScale(15.0 + 10); // 15;
	offsetMarcoY_ = game_->setVerticalScale(10.0 + 10); // 10;

	// arreglo res.
	//if (game_->fullscr_) {
	//	numLet_ += 15;
	//	/*anchoTexto_ += 165;
	//	offsetMarcoX2_ += 140;*/
	//}

	// info
	//
	nombreHab_ = hab_->name();
	//
	generateDescriptionArray();
	//
	manaHab_ = (std::string)"Cost: " + to_string(hab_->getMana());
	//
	tipoHab_ = (std::string)"Type: ";
	switch (hab_->getHabilityType())
	{
	case HabilityType::ATTACK:
		tipoHab_ += (std::string)"Attack";
		break;
	case HabilityType::DEBUFF:
		tipoHab_ += (std::string)"Debuff";
		break;
	case HabilityType::HEAL:
		tipoHab_ += (std::string)"Cure";
		break;
	case HabilityType::BUFF:
		tipoHab_ += (std::string)"Buff";
		break;
	default:
		tipoHab_ += (std::string)"Attack";
		break;
	}
	//
	modificadorHab_ = (std::string)"Mod.: ";
	switch (hab_->getMod())
	{
	case mainStat::STR:
		modificadorHab_ += (std::string)"Strength";
		break;
	case mainStat::CON:
		modificadorHab_ += (std::string)"Const.";
		break;
	case mainStat::DEX:
		modificadorHab_ += (std::string)"Dext.";
		break;
	case mainStat::INT:
		modificadorHab_ += (std::string)"Intel.";
		break;
	default:
		modificadorHab_ += (std::string)"Strength";
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
		nombreHab_.size() * anchoTexto_, // anchoTexto_,
		altoTexto_
	);

	descripcion_ = RECT(
		titulo_.x,
		titulo_.y + titulo_.h,
		numLet_ * anchoTexto_,
		altoTexto_
	);

	mana_ = RECT(
		marco_.x + marco_.w - (manaHab_.size() * anchoTexto_) - offsetMarcoX_, // marco_.x + offsetMarcoX2_,
		marco_.y + offsetMarcoY_,
		manaHab_.size() * anchoTexto_,// anchoTexto_,
		altoTexto_
	);

	tipo_ = RECT(
		marco_.x + offsetMarcoX_,
		marco_.y + marco_.h - altoTexto_ - offsetMarcoY_,
		tipoHab_.size() * anchoTexto_, // anchoTexto_,
		altoTexto_
	);

	modificador_ = RECT(
		marco_.x + marco_.w - (modificadorHab_.size() * anchoTexto_) - offsetMarcoX_, // marco_.x + offsetMarcoX2_,
		marco_.y + marco_.h - altoTexto_ - offsetMarcoY_,
		modificadorHab_.size() * anchoTexto_, // anchoTexto_,
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
	pan_->addButton(iManager_->addButton<Line>(titulo_, /*checkLineSize(nombreHab_)*/nombreHab_, colorTextoTitulo_));
	for (int i = 0; i < descripcionHab_.size(); i++) {
		pan_->addButton(iManager_->addButton<Line>(descripcion_, checkLineSize(descripcionHab_[i]), colorTextoDescripcion_));
		descripcion_.y += descripcion_.h;
	}
	pan_->addButton(iManager_->addButton<Line>(mana_, /*checkLineSize(manaHab_)*/manaHab_, colorTextoMana_));
	pan_->addButton(iManager_->addButton<Line>(tipo_, /*checkLineSize(tipoHab_)*/tipoHab_, colorTextoTipo_));
	pan_->addButton(iManager_->addButton<Line>(modificador_, /*checkLineSize(modificadorHab_)*/modificadorHab_, colorTextoModificador_));
}

std::string PanelDesc::checkLineSize(std::string line)
{
	if (line.size() < numLet_) line.resize(numLet_, ' ');
	if (line.front() == ' ') line.erase(line.begin());
	return line;
}

void PanelDesc::generateDescriptionArray()
{
	string line = hab_->description();
	while (line.size() > 0) {
		string cut = "";
		size_t n = numLet_;

		if (line.size() > numLet_) {
			if (line.at(numLet_ - 2.0) != ' ' && line.at(numLet_ - 1.0) != ' ' || line.at(numLet_ - 1.0) != ' ' && line.at(numLet_) != ' ') {
				string aux = line.substr(0, numLet_);
				n = aux.rfind(' ', numLet_ - 1.0);
				cut = aux.substr(0, n);
			}
		}
		if (cut == "") {
			//cut.insert(0, d, 0, numLet_); es lo mismo
			cut = line.substr(0, numLet_);
		}

		line.erase(0, n);
		descripcionHab_.push_back(cut);
	}
}
