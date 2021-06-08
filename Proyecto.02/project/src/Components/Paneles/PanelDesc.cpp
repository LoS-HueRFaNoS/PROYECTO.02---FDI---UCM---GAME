#include "PanelDesc.h"
#include "../../GameObjects/Button.h"
#include "../../Templates/Resources.h"
#include "../../Utilities/textures_box.h"
#include "../../Utilities/SDL_macros.h"

using namespace textures_box;

void PanelDesc::init()
{
	// info
	//...

	// aspecto
	marco = RECT(
				game_->setHorizontalScale(670), //posX
				game_->setVerticalScale(750),	//posY
				game_->setHorizontalScale(620),	//ancho
				game_->setVerticalScale(272)	//alto
				);

	titulo = RECT(
				marco.x + offsetMarcoX,
				marco.y + offsetMarcoY,
				tamTextoGrande_.first,
				tamTextoGrande_.second
				);

	descripcion = RECT(
				titulo.x,
				titulo.y + titulo.h,
				tamTextoPequenyo_.first,
				tamTextoPequenyo_.second
				);

	mana = RECT(
				marco.x + offsetMarcoX,
				marco.y + marco.h - tamTextoGrande_.second - offsetMarcoY,
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
	pan_->addButton(iManager_->addButton<SDL_Object>(marco, src::Cartelito));

	//Texto:
	string nom = "A" + (std::string)"mogus en pamplona"; //to_string()
	pan_->addButton(iManager_->addButton<Line>(titulo, checkLineSize(nom), colorTextoTitulo_));
	string des = "Ah, " + (std::string)"este es un ejemplo de descripcion muy larga pare el texto - Es porello que queda mal"; //to_string()
	pan_->addButton(iManager_->addButton<Line>(descripcion, checkLineSize(des), colorTextoDescripcion_));
	string man = "Mana: " + (std::string)"134"; //to_string()
	pan_->addButton(iManager_->addButton<Line>(mana, checkLineSize(man), colorTextoMana_));
}

std::string PanelDesc::checkLineSize(std::string line)
{
	if (line.size() < NUM_LET) line.resize(NUM_LET, ' ');
	return line;
}