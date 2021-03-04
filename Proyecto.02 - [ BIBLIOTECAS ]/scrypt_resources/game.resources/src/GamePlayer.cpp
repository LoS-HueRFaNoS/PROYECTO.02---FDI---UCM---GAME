// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "GamePlayer.h"
#include "logic_game.h"

#pragma region METODOS_GAME_PLAYER

void GamePlayer::morir()
{
    acedLogic().subsLives();
    sigDir.set(Vector2D());
    dir = sigDir;
    pos.set(posIni);
    rowF = 0;
}

















// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion