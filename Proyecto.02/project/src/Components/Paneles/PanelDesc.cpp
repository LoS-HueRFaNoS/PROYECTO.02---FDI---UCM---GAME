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
	SDL_Panel pan = game_->relativePanel(880, 790, (1410 - 880), (980 - 790), 1, 1, 10, 10, 5, 5); //pos,tam,elemMatr,marg,elemSep
	primElem = RECT(pan.fcx, pan.fcy, pan.cw, pan.ch);
	uint mcw = game_->setHorizontalScale(50);
	uint mch = game_->setVerticalScale(50);
	marco = RECT(pan.x + mcw, pan.y + mch, pan.w - mcw * 2, pan.h - mch * 2);

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