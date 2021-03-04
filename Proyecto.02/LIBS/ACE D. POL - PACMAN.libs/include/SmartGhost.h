// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#pragma once
#ifndef SMARTGHOST_H_
#define SMARTGHOST_H_

#include "checkML.h"

#include "FileFormatError.h"
#include "Ghost.h"

const int CUARENTENATIME = 160;			//tiempo de abstinencia de reproducirse
const int TIMETOGROW	 = 120;			//tiempo que tarda en convertirse en adulto
const int TIMETODIE		 = 640;			//tiempo que tarda en morir por tiempo max
const int TIMETOPERMADIE = 800;			//tiempo que tarda en morir definitivamente
const int MIN_DIST = 150;				//distancia minima para empezar a perseguir a pacman

class SmartGhost :	public Ghost 
{
private:
	bool adulto;
	bool deadBody;
	double distance;						// distancia hasta pacman
	uint cuarentenaTime, currentTime;		// valores para el manejo del tiempo / ciclos
public:
	SmartGhost() : Ghost(), adulto(false), deadBody(false), cuarentenaTime(0), currentTime(0), distance(200) {};			// contructor por defecto
	SmartGhost(	Point2D pIni,
				uint r,
				uint c,
				Texture* t,
				uint w,
				uint h,
				uint numGho, 
				bool adult	) 
				: Ghost(pIni, r, c, t, w, h, numGho), adulto(adult), deadBody(false), cuarentenaTime(0), currentTime(0), distance(200) {};
	virtual  ~SmartGhost() {};					// destructor

	bool getDeadBody() { return deadBody; };
	
	virtual const void saveToFile(ofstream& file);
	SmartGhost(ifstream& file, Texture* t);

	virtual void update();
	virtual void render();
	virtual void morir();

private:
	void checkDirs(SDL_Rect rect);
	void becomeAdult();
	void dieAndStay();
};














// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#endif