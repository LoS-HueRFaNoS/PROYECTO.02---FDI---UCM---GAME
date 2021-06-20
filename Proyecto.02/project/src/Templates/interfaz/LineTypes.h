#pragma once
#include <SDL.h>
#include <map>

enum class LineColor {
	White,
	Yellow,
	Green,
	Red,
	Blue
}; using linCol = LineColor;

class LineTypes
{
public:
	std::map<LineColor, SDL_Color> lineTypesMap_;
	LineTypes() : lineTypesMap_() {};

	void Init()
	{
		// color messages
		lineTypesMap_[linCol::White] = hex2sdlcolor("#FFFFFFFF");
		lineTypesMap_[linCol::Yellow] = hex2sdlcolor("#FFD700FF");
		lineTypesMap_[linCol::Green] = hex2sdlcolor("#00FF00FF");
		lineTypesMap_[linCol::Red] = hex2sdlcolor("#FF0000FF");
		lineTypesMap_[linCol::Blue] = hex2sdlcolor("#0055FFFF");
	};

};
