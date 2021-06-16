#include "PanelDescObj.h"
#include "../../GameObjects/Button.h"
#include "../../Templates/Resources.h"
#include "../../Utilities/textures_box.h"
#include "../../Utilities/SDL_macros.h"

using namespace textures_box;

void PanelDescObj::init()
{
	// info
	//
	nombreItem_ = ite_->getName();
	//
	string d = ite_->getDescription();
	while (d.size() > 0) {
		string aux = "";
		aux.insert(0, d, 0, numLet_);
		d.erase(0, numLet_);
		descripcionItem_.push_back(aux);
	}
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
	afinidadItem_ = (std::string)"Affinity: ";
	rpgLogic::Weaknesses wea = ite_->getElementalAfinity();
	for (int i = 0; i < (int)damTy::_lastDamageTypeId_; i++) { // damTy::_lastDamageTypeId_ es el .size()
		afinidadItem_ += to_string(wea.getWeakness((rpgLogic::damageType)i));
		afinidadItem_ += (std::string)";";
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
		anchoTexto_,
		altoTexto_
	);

	descripcion_ = RECT(
		titulo_.x,
		titulo_.y + titulo_.h,
		anchoTexto_,
		altoTexto_
	);

	tipo_ = RECT(
		marco_.x + offsetMarcoX2_,
		marco_.y + offsetMarcoY_,
		anchoTexto_,
		altoTexto_
	);

	afinidad_ = RECT(
		marco_.x + offsetMarcoX_,
		marco_.y + marco_.h - altoTexto_ - offsetMarcoY_,
		anchoTexto_,
		altoTexto_
	);

	coste_ = RECT(
		marco_.x + offsetMarcoX2_,
		marco_.y + marco_.h - altoTexto_ - offsetMarcoY_,
		anchoTexto_,
		altoTexto_
	);

	valor_ = RECT(
		marco_.x + offsetMarcoX2_,
		marco_.y + marco_.h - altoTexto_ - offsetMarcoY_,
		anchoTexto_,
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
	pan_->addButton(iManager_->addButton<Line>(titulo_, checkLineSize(nombreItem_), colorTextoTitulo_));
	for (int i = 0; i < descripcionItem_.size(); i++) {
		pan_->addButton(iManager_->addButton<Line>(descripcion_, checkLineSize(descripcionItem_[i]), colorTextoDescripcion_));
		descripcion_.y += descripcion_.h;
	}
	pan_->addButton(iManager_->addButton<Line>(tipo_, checkLineSize(tipoItem_), colorTextoTipo_));
	pan_->addButton(iManager_->addButton<Line>(afinidad_, checkLineSize(afinidadItem_), colorTextoAfinidad_));
	pan_->addButton(iManager_->addButton<Line>(coste_, checkLineSize(costeItem_), colorTextoCoste_));
	pan_->addButton(iManager_->addButton<Line>(valor_, checkLineSize(valorItem_), colorTextoValor_));
}

std::string PanelDescObj::checkLineSize(std::string line)
{
	if (line.size() < numLet_) line.resize(numLet_, ' ');
	return line;
}