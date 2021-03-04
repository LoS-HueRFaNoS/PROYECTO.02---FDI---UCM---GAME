// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef OBJECTS_MOTOR_H_
#define OBJECTS_MOTOR_H_

#include "checkML.h"

#include <list>
#include "SDL_Object.h"
#include "EventHandler.h"
// inherits
#include "Singleton.h"

const uint FRAME_RATE = 60;										// tiempo m�nimo entre frames

class objectsMotor : public Singleton<objectsMotor>
{
	friend Singleton<objectsMotor>;
	objectsMotor();
	objectsMotor(SDL_Renderer* ren);
protected:
	list<SDL_Object*> stage;								// lista dinamica de GameObject's
	list<EventHandler*> handlers;
	list<list<SDL_Object*>::iterator> objectsToErase;		// lista dinamica de SDL_Objects (van a ser borrados en ejecucion)
	uint startTime;
public:
	virtual ~objectsMotor();

	virtual void run();										// bucle principal
	virtual void update();									// actualizador
	virtual void render();									// draw estado actual
	virtual bool handleEvent(const SDL_Event& event);		// manejo de eventos

	void clearStage();
	void clear_objectsToErase();

	void storeObject(SDL_Object* o);
	void eraseObject(list<SDL_Object*>::iterator it);
	void storeHandler(EventHandler* h);

	//template<typename A> void resetObjs();
	list<SDL_Object*> getStage() { return stage; };
};

inline objectsMotor& acedObjsMot() {
	return *objectsMotor::instance();
}














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif