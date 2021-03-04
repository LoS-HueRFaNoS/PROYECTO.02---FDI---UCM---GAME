// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
//

#include "Pacman.h"
#include "logic_game.h"
#include "logic_pacman.h"

#pragma region METODOS_PACMAN

// :::::::::::::::::: Uso de Ficheros: GUARDAR & CARGAR ::::::::::::::::::::::

const void Pacman::saveToFile(ofstream& file)
{
    GameCharacter::saveToFile(file);
    file << energia << ' ';
}

Pacman::Pacman(ifstream& file, Texture* t)
{
    file >> energia;
    if (energia < -1) throw FileFormatError("el valor 'energia' no esta bien definido");
}

// :::::::::::::::::: MOTOR DEL JUGADOR ::::::::::::::::::::::

void Pacman::update() {
    if (energia >= 0) { --energia; }

    Point2D newPos = Point2D();
    SDL_Rect rect = getDestRect();
    bool move = false;
    if (acedLogic().tryMove(rect, dir, VEL, newPos)) {
        pos = newPos;
        move = true;
    }
    if (sigDir != dir && acedLogic().tryMove(rect, sigDir, VEL, newPos)) {
        dir.set(sigDir);
        pos = newPos;
        move = true;
    }

    if (move) {
        Point2D pAct = centerPos(rect);
        efecto(pAct);
    }
    else { dir = Vector2D(); }
    acedLogPacman().collisionsPacman(rect);
    animation(direction(act(dir)));
}

bool Pacman::handleEvent(const SDL_Event& event) {
    bool keyPress = false;
	switch (event.key.keysym.sym) {
    // WASD o CRUCETA
    case SDLK_UP:
    case SDLK_w: sigDir.dir(N); 
        //keyPress = true;
        break;
    case SDLK_DOWN:
    case SDLK_s: sigDir.dir(S); 
        //keyPress = true;
        break;
    case SDLK_LEFT:
    case SDLK_a: sigDir.dir(O); 
        //keyPress = true;
        break;
    case SDLK_RIGHT:
    case SDLK_d: sigDir.dir(E); 
        //keyPress = true;
        break; 
    case SDLK_ESCAPE:
        keyPress = true;
        break;
	}
    return keyPress;
}

// :::::::::::::::::: MOTOR DE ANIMACION ::::::::::::::::::::::

void Pacman::animation(direction dir) {
    switch (dir) {
    case N: rowF = 3;
        break;
    case S: rowF = 1;
        break;
    case E: rowF = 0;
        break;
    case O: rowF = 2;
        break;
    default:
        break;
    }
    if (colF == 10) colF = 11;
    else if (colF == 11) colF = 10;
}

void Pacman::efecto(const Point2D pAct) {

    if (acedLogic().showCell(pAct) == Food) {
        acedLogic().clearCell(pAct);
        acedLogPacman().subsFood();
        acedLogic().addPoints(1);
    }
    else if (acedLogic().showCell(pAct) == Vitamins) {
        acedLogic().clearCell(pAct);
        acedLogic().addPoints(10);
        energia = ENERGY;
    }
}

















// @autor: Pedro Pablo Cubells Talavera (Acedpol, ACE D. POL) [https://github.com/Acedpol]
#pragma endregion