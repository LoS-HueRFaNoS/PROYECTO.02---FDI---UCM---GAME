
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif
#include "SDL.h"
#include <string>
using namespace std;
typedef unsigned int uint;
typedef const char* word;

// Agrega checkML.h al proyecto e inclúyelo en todos los módulos del proyecto 
// Escribe el siguiente comando al inicio de la función main
// _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 
