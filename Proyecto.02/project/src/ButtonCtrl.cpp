#include "ButtonCtrl.h"

void ButtonCtrl::init()
{
    tr_ = GETCMP1_(Transform);
    assert(tr_ != nullptr);
    ih_ = InputHandler::instance();
}
