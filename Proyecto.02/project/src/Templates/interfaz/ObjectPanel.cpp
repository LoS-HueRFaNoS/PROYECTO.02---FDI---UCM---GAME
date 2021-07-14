#include "ObjectPanel.h"

void ObjectPanel::Init(SDL_Panel pan)
{
	marco_ = RECT(
		TheElementalMaze::instance()->getSDLGame()->setHorizontalScale(pan.x),
		TheElementalMaze::instance()->getSDLGame()->setVerticalScale(pan.y),
		pan.w,
		pan.h
	);

	topElement_ = RECT(pan.fcx, pan.fcy, pan.cw, pan.ch);
	bottomElement_ = RECT(pan.fcx, pan.lcy, pan.cw, pan.ch);
	
	tuppleLimits_ = Tupple(pan.fcy - 1, pan.lcy + 1);
	tuppleMargins_ = Tupple(pan.mw, pan.mh);
	tuppleEspaces_ = Tupple(pan.ew, pan.eh); // padding
	tuppleBorders_ = Tupple(pan.bw, pan.bh); // borders
}
