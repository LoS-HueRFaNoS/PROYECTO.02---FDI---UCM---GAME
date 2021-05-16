#define SDL_MAIN_HANDLED
#include <iostream>

#include "Game.h"
#include "Utilities/checkML.h"

using namespace std;

void start() {
	Game* g = Game::Init();
	g->start();
}


#if (defined _DEBUG) //|| !(defined _WIN64)
int main(int argc, char *args[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#include <windows.h>
int WINAPI
WinMain(HINSTANCE zHInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow) {
#endif
	try {
		start();
	}
	catch (std::string& e) { // catch errors thrown as strings
		cerr << e << endl;
	}
	catch (const std::exception& e) { // catch other exceptions
		cerr << e.what();
	}
	catch (...) {
		cerr << "Caught and exception of unknown type ..";
	}

	return 0;
}










