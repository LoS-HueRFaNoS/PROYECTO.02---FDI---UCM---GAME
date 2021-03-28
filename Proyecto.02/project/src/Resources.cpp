#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_ {
//
		{ ARIAL16, "resources/fonts/ARIAL.ttf", 16 }, //
		{ ARIAL24, "resources/fonts/ARIAL.ttf", 24 } //
};

vector<Resources::ImageInfo> Resources::images_ {
//
		{ Airplanes, "resources/images/airplanes.png" }, //
		{ Asteroid, "resources/images/asteroid.png" }, //
		{ Heart, "resources/images/heart.png" }, //
		{ WhiteRect, "resources/images/whiterect.png" }, //
		{ camino_izq, "resources/images/pasillos/camino_izq.png"}, //
		{ camino_der, "resources/images/pasillos/camino_der.png"}, //
		{ camino_del, "resources/images/pasillos/camino_del.png"}, //
		{ muro_izq, "resources/images/pasillos/muro_izq.png"}, //
		{ muro_der, "resources/images/pasillos/muro_der.png"}, //
		{ muro_del, "resources/images/pasillos/muro_del.png"}, //
		//{ Pasillo1, "resources/images/pasillos/Pasillo1.png"}, //
		//{ Pasillo2, "resources/images/pasillos/Pasillo2.png"}, //
		//{ Pasillo3, "resources/images/pasillos/Pasillo3.png"}, //
		//{ Pasillo4, "resources/images/pasillos/Pasillo4.png"}, //
		//{ Pasillo5, "resources/images/pasillos/Pasillo5.png"}, //
		//{ Pasillo6, "resources/images/pasillos/Pasillo6.png"}, //
		//{ Pasillo7, "resources/images/pasillos/Pasillo7.png"}, //
		{ Bardo, "resources/sprites/iconos personajes/bardo.png" },
		{ Brujo, "resources/sprites/iconos personajes/brujo.png" },
		{ Clerigo, "resources/sprites/iconos personajes/clerigo.png" },
		{ Guerrero, "resources/sprites/iconos personajes/guerrero.png" },
		{ Paladin, "resources/sprites/iconos personajes/paladin.png" },
		{ Barbaro, "resources/sprites/iconos personajes/barbaro.png" },
		{ Explorador, "resources/sprites/iconos personajes/explorador.png" },
		{ Picaro, "resources/sprites/iconos personajes/picaro.png" },
		{ Druida, "resources/sprites/iconos personajes/druida.png" },
		{ Bestia, "resources/sprites/iconos personajes/bestia.png" },
		{ GranArchimago, "resources/sprites/iconos personajes/heroe-mago.png" },
		
	{ Mouse, "resources/images/interfaz/cursor+sombras.png" },
	{Avanzar, "resources/sprites/iconos movimiento/movimientoAvanzar.png"},
	{RotarD, "resources/sprites/iconos movimiento/movimientoRotarDerecha.png"},
	{RotarI, "resources/sprites/iconos movimiento/movimientoRotarIzquierda.png"},
	{Interactuar,  "resources/sprites/iconos movimiento/movimientoInteractuar.png"},

	{Inventario,  "resources/sprites/iconos info/infoInventario.png"},
	{PocionVida,  "resources/sprites/iconos info/infoPocionVida.png"},
	{PocionMana,  "resources/sprites/iconos info/infoPocionMana.png"},
	{Chat,  "resources/sprites/iconos info/infoChat.png"},
	{Configuracion,  "resources/sprites/iconos info/infoConfiguracionAyuda.png"},
	
};

vector<Resources::TextMsgInfo> Resources::messages_ {
//
		{ HelloWorld, "Hello World", { COLOR(0xaaffffff) }, ARIAL16 }, //
		{ PressAnyKey, "Press Any Key to Start", { COLOR(0xaaffbbff) }, ARIAL24 }, //
		{ GameOverWon, "Game Over! You Won!", { COLOR(0xffffbbff) }, ARIAL24 }, //
		{ GameOverLost, "Game Over! You Lost!", { COLOR(0xffffbbff) }, ARIAL24 } //
};

vector<Resources::MusicInfo> Resources::musics_ {
//
		{ ImperialMarch, "resources/sound/imperial_march.wav" } //
};

vector<Resources::SoundInfo> Resources::sounds_ {
//
		{ Explosion, "resources/sound/explosion.wav" }, //
		{ GunShot, "resources/sound/GunShot.wav" } //
};


vector<Resources::JsonInfo> Resources::jsons_{
//
		{ Characters, "resources/jsons/characters.json" }, //
		{ Weapons, "resources/jsons/characters.json" }, //
		{ Armors, "resources/jsons/characters.json" } //
};

