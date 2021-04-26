#pragma once

class Interfaz;

// MENU
using namespace std;

class callbacks {
public:
	// pruebas (solo escriben por consola)
	static void pruebaGame0(Interfaz* app);
	static void pruebaGame1(Interfaz* app);
	static void pruebaGame2(Interfaz* app);
	static void pruebaGame3(Interfaz* app);
	// acceso a heroes
	static void heroType(int numberHeroe);
	// acceso a movimiento
	static void movCommand(int movType);
	// acceso a informacion
	static void inventario(Interfaz* app);
	static void chat(Interfaz* app);
	static void configuracion(Interfaz* app);
	static void potionType(int potionType_);
	// acceso a combate
	static void attackType(int attackType_);
	static void defendType(int attackType_);
	static void addTarget(int attackType_);
	static void set_hability(int attackType_);
	// habilitar/deshabilitar paneles
	static void createPanel(bool active, int panelType);
	static void ataqueNormal(Interfaz* app);
	static void ataqueMagico(Interfaz* app);
	static void defensa(Interfaz* app);
	static void huida(Interfaz* app);
	// acceso por menu
	static void startLobby(Interfaz* app);
	static void options(Interfaz* app);
	static void howToPlay(Interfaz* app);
	static void quit(Interfaz* app);
};