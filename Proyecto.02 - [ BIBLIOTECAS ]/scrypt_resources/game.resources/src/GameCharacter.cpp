// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "GameCharacter.h"
#include "logic_game.h"

#pragma region METODOS_GAME_CHARACTER

void const GameCharacter::saveToFile(ofstream& file)
{
	SDL_Object::saveToFile(file);
	file << posIni << ' '; 
	file << rowF << ' ' << colF << ' '; 
	file << dir << ' ';
}

GameCharacter::GameCharacter(ifstream& file, Texture* t)
{
	text = t;
	file >> pos;
	file >> posIni;
	file >> width >> height;
	file >> rowF >> colF;
	file >> dir;
	if (pos == Point2D()) throw FileFormatError("el valor 'pos' no esta definido");
	if (posIni == Point2D()) throw FileFormatError("el valor 'posIni' no esta definido");
}

Point2D const GameCharacter::centerPos(const SDL_Rect rect)
{
	return acedLogic().SDLPointToMapCoords(Point2D(pos.getX() + (rect.w / 2), pos.getY() + (rect.h / 2)));
}

void GameCharacter::render() {
	SDL_Rect rect = getDestRect();
	text->renderFrame(rect, rowF, colF);
}

















// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion