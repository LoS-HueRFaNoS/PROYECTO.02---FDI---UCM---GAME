#pragma once
#include "../../Utilities/SDL_macros.h"
#include "../../Managers/TheElementalMaze.h"

class ObjectPanel {
protected:
	SDL_Rect topElement_;			// top element rectangle
	SDL_Rect bottomElement_;		// bottom element rectangle
	SDL_Rect marco_;				// size of the background
	Tupple tuppleLimits_;			// high and low limits
	Tupple tuppleMargins_;			// horizontal and vertical margins
	Tupple tuppleEspaces_;			// espaces between elements (padding)
	Tupple tuppleBorders_;			// espaces between elements (border)

public:
	ObjectPanel() : topElement_(), bottomElement_(), marco_() {};
	void Init(SDL_Panel pan);
	virtual ~ObjectPanel() {};

	// GETTERS
	SDL_Rect topElement() { return topElement_; };
	SDL_Rect bottomElement() { return bottomElement_; };
	SDL_Rect marco() { return marco_; };
	Tupple tuppleLimits() { return tuppleLimits_; };
	Tupple tuppleMargins() { return tuppleMargins_; };
	Tupple tuppleEspaces() { return tuppleEspaces_; };
	Tupple tuppleBorders() { return tuppleBorders_; };

	// SETTERS
	void set_topElement(SDL_Rect top_elem) { topElement_ = top_elem; };
	void set_bottomElement(SDL_Rect bottom_elem) { bottomElement_ = bottom_elem; };
	void set_marco(SDL_Rect size) { marco_ = size; };
	void set_tuppleLimits(Tupple tupple_limits) { tuppleLimits_ = tupple_limits; };
	void set_tuppleMargins(Tupple tupple_margins) { tuppleMargins_ = tupple_margins; };
	void set_tuppleEspaces(Tupple tupple_espaces) { tuppleEspaces_ = tupple_espaces; };
	void set_tuppleBorders(Tupple tupple_borders) { tuppleBorders_ = tupple_borders; };

};