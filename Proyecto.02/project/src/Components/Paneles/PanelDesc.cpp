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
	SDL_Panel pan = game_->relativePanel(670, 750, 620, 272, 1, 1, 10, 10, 5, 5); //pos,tam,elemMatr,marg,elemSep
	primElem = RECT(pan.fcx, pan.fcy, pan.cw, pan.ch);
	marco = RECT(pan.x, pan.y, pan.w, pan.h);

	drawPanel();
}
void PanelDesc::update() {}
void PanelDesc::draw() {}

void PanelDesc::drawPanel()
{
	// Fondo:
	pan_->addButton(iManager_->addButton<SDL_Object>(marco, src::Cartelito));
}

std::string PanelDesc::checkLineSize(std::string line)
{
	if (line.size() < NUM_LET) line.resize(NUM_LET, ' ');
	return line;
}