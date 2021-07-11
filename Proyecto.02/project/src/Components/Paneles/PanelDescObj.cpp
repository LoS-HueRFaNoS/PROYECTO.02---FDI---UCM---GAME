#include "PanelDescObj.h"
#include "../../GameObjects/Button.h"
#include "../../Templates/Resources.h"
#include "../../Utilities/textures_box.h"
#include "../../Utilities/SDL_macros.h"

using namespace textures_box;

void PanelDescObj::init()
{
	// valores responsive
	numLet_ = 53;
	anchoTexto_ = game_->setHorizontalScale(11.2); // game_->setHorizontalScale(590); // 425; // 425 para NUM_LET = 38
	altoTexto_ = game_->setVerticalScale(35); // 35;
	//---
	offsetMarcoX_ = game_->setHorizontalScale(15.0 + 10); // 15;
	offsetMarcoY_ = game_->setVerticalScale(10.0 + 10); // 10;

	// arreglo res.
	/*if (game_->fullscr_) {
		numLet_ += 15;
		anchoTexto_ += 165;
		offsetMarcoX2_ += 140;
	}*/

	// info
	//
	nombreItem_ = ite_->getName();
	//
	generateDescriptionArray();
	//
	tipoItem_ = (std::string)"Type: ";
	switch (ite_->getItemType())
	{
	case ItemType::WEAPON:
		tipoItem_ += (std::string)"Weapon";
		break;
	case ItemType::ARMOR:
		tipoItem_ += (std::string)"Armor";
		break;
	default:
		tipoItem_ += (std::string)"Weapon";
		break;
	}
	//
	vector<string> prefs = { "B", "P", "S", "F", "W", "I", "E", "A", "L", "D"}; // /!\ ojo al tamaño
	afinidadItem_ = (std::string)"Aff.: ";
	rpgLogic::Weaknesses wea = ite_->getElementalAfinity();
	for (int i = 0; i < (int)damTy::_lastDamageTypeId_; i++) { // damTy::_lastDamageTypeId_ es el .size()
		int numWeak = wea.getWeakness((rpgLogic::damageType)i) * 100;
		afinidadItem_ += (std::string)prefs[i];
		afinidadItem_ += (std::string)":";
		afinidadItem_ += to_string(numWeak);
		afinidadItem_ += (std::string)"%;";
	}
	//
	costeItem_ = (std::string)"Cost: " + to_string(ite_->getBuyValue());
	//
	valorItem_ = (std::string)"Value: " + to_string(ite_->getSellValue());

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
		nombreItem_.size() * anchoTexto_, // anchoTexto_,
		altoTexto_
	);

	descripcion_ = RECT(
		titulo_.x,
		titulo_.y + titulo_.h,
		numLet_ * anchoTexto_,
		altoTexto_
	);

	tipo_ = RECT(
		marco_.x + marco_.w - (tipoItem_.size() * anchoTexto_) - offsetMarcoX_, // marco_.x + offsetMarcoX2_,
		marco_.y + offsetMarcoY_,
		tipoItem_.size() * anchoTexto_,// anchoTexto_,
		altoTexto_
	);

	afinidad_ = RECT(
		marco_.x + offsetMarcoX_,
		marco_.y + marco_.h - altoTexto_ * 2 - offsetMarcoY_,
		numLet_ * anchoTexto_,
		altoTexto_
	);

	coste_ = RECT(
		marco_.x + offsetMarcoX_,
		marco_.y + marco_.h - altoTexto_ - offsetMarcoY_,
		costeItem_.size() * anchoTexto_, // anchoTexto_,
		altoTexto_
	);

	valor_ = RECT(
		marco_.x + marco_.w - (valorItem_.size() * anchoTexto_) - offsetMarcoX_, // marco_.x + offsetMarcoX2_,
		marco_.y + marco_.h - altoTexto_ - offsetMarcoY_,
		valorItem_.size() * anchoTexto_, // anchoTexto_,
		altoTexto_
	);

	//colores
	colorTextoTitulo_ = hex2sdlcolor("0xFFD700FF");
	colorTextoDescripcion_ = hex2sdlcolor("0xFFFFFFFF");
	colorTextoTipo_ = hex2sdlcolor("0xFF5D00FF");
	colorTextoAfinidad_ = hex2sdlcolor("0xD559F8FF");
	colorTextoCoste_ = hex2sdlcolor("0x4EDB68FF");
	colorTextoValor_ = hex2sdlcolor("0xCDDB68FF");

	drawPanel();
}
void PanelDescObj::update() {}
void PanelDescObj::draw() {}

void PanelDescObj::drawPanel()
{
	// Fondo:
	pan_->addButton(iManager_->addButton<SDL_Object>(marco_, src::Cartelito));

	//Texto:
	pan_->addButton(iManager_->addButton<Line>(titulo_, /*checkLineSize(nombreItem_)*/nombreItem_, colorTextoTitulo_));
	for (int i = 0; i < descripcionItem_.size(); i++) {
		pan_->addButton(iManager_->addButton<Line>(descripcion_, checkLineSize(descripcionItem_[i]), colorTextoDescripcion_));
		descripcion_.y += descripcion_.h;
	}
	pan_->addButton(iManager_->addButton<Line>(tipo_, /*checkLineSize(tipoItem_)*/tipoItem_, colorTextoTipo_));
	pan_->addButton(iManager_->addButton<Line>(afinidad_, /*checkLineSize(afinidadItem_)*/afinidadItem_, colorTextoAfinidad_));
	pan_->addButton(iManager_->addButton<Line>(coste_, /*checkLineSize(costeItem_)*/costeItem_, colorTextoCoste_));
	pan_->addButton(iManager_->addButton<Line>(valor_, /*checkLineSize(valorItem_)*/valorItem_, colorTextoValor_));
}

std::string PanelDescObj::checkLineSize(std::string line)
{
	if (line.size() < numLet_) line.resize(numLet_, ' ');
	if (line.front() == ' ') line.erase(line.begin());
	return line;
}

void PanelDescObj::generateDescriptionArray()
{
	string line = ite_->getDescription();
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
		descripcionItem_.push_back(cut);
	}
}
