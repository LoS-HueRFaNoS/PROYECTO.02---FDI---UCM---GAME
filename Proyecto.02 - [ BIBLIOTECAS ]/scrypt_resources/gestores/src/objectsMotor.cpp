// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "objectsMotor.h"
#include "windowAPP.h"

#pragma region METODOS_WINDOW_APP

// :::::::::::::::::: CONSTRUCTOR ::::::::::::::::::::::

objectsMotor::objectsMotor()
{
	startTime = SDL_GetTicks();
}

objectsMotor::~objectsMotor()
{
	clearStage();
}

void objectsMotor::run()
{
	bool exit = false;
	SDL_Event event;
	uint frameTime;
	while (!exit) {
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE) {
			update();
			SDL_RenderClear(acedWinApp().getRenderer());
			render();
			SDL_RenderPresent(acedWinApp().getRenderer());
			startTime = SDL_GetTicks();
		}
		if (SDL_PollEvent(&event)) { exit = handleEvent(event); };
	}
}

void objectsMotor::update()
{
	for (SDL_Object* o : stage) o->update();
	clear_objectsToErase();
}

void objectsMotor::render()
{
	for (SDL_Object* o : stage) o->render();
}

bool objectsMotor::handleEvent(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_QUIT: return true;
		break;
	default:
		for (EventHandler* h : handlers) if (h->handleEvent(event)) return true; // return = break -> TPV RULES
		break;
	}
	return false;
}

// :::::::::::::::::: GESTION DE MEMORIA ::::::::::::::::::::::

void objectsMotor::clearStage()
{
	for (auto it = stage.begin(); it != stage.end(); ++it)
	{
		delete (*it);
	}
	stage.clear();
	handlers.clear();
}

void objectsMotor::clear_objectsToErase()
{
	for (auto it : objectsToErase) {
		delete* it;
		stage.erase(it);	// complejidad cte
	}
	objectsToErase.clear();
}

void objectsMotor::storeObject(SDL_Object* o)
{
	auto it = stage.insert(stage.end(), o);
	o->setItList(it);
}

void objectsMotor::eraseObject(list<SDL_Object*>::iterator it)
{
	objectsToErase.push_back(it);
}

void objectsMotor::storeHandler(EventHandler* h)
{
	handlers.push_back(h);
}

//template<typename A> 
//void objectsMotor::resetObjs()
//{
//	for (SDL_Object* o : stage) {
//		A* g = dynamic_cast<A*>(o);
//		if (g != nullptr)
//			if (!g->getIsDie())
//				g->morir();
//	};
//}

















// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion