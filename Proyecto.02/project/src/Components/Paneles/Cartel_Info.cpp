#include "Cartel_Info.h"

void CartelInfo::init()
{
}

void CartelInfo::update()
{
}

void CartelInfo::draw()
{
}

void CartelInfo::drawCartelActual()
{
	// Fondo:
	pan_->addButton(iManager_->addButton<SDL_Object>(marco, src::Pergamino));

	// TITLE:
	addTitleName();
}

void CartelInfo::addTitleName()
{
	switch (type)
	{
	default:
		break;
	}
}

void CartelInfo::addTemplate()
{
}

std::string CartelInfo::checkLineSize(std::string line)
{
    return std::string();
}
