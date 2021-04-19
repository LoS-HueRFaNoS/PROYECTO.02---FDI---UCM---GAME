#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_{
	{ARIAL16, "resources/fonts/ARIAL.ttf", 16}, //
	{ARIAL24, "resources/fonts/ARIAL.ttf", 24}	//
};

vector<Resources::ImageInfo> Resources::images_{
	{posMiniMap, "resources/images/pasillos/posJugador.png"},			//
	{camino_izq, "resources/images/pasillos/camino_izq.png"},			//
	{camino_der, "resources/images/pasillos/camino_der.png"},			//
	{camino_del, "resources/images/pasillos/camino_del.png"},			//
	{muro_izq, "resources/images/pasillos/muro_izq.png"},				//
	{muro_der, "resources/images/pasillos/muro_der.png"},				//
	{muro_del, "resources/images/pasillos/muro_del.png"},				//
	{no_visitado, "resources/images/pasillos/pasillo_no_visitado.png"}, //
	{no_entrado, "resources/images/pasillos/pasillo_no_entrado.png"},	//
	{visitado, "resources/images/pasillos/pasillo_visitado.png"},		//
	{pared_N, "resources/images/pasillos/pared_norte.png"},				//
	{pared_E, "resources/images/pasillos/pared_este.png"},				//
	{pared_S, "resources/images/pasillos/pared_sur.png"},				//
	{pared_O, "resources/images/pasillos/pared_oeste.png"},				//

	{Bardo, "resources/sprites/iconos personajes/bardo.png"},
	{Brujo, "resources/sprites/iconos personajes/brujo.png"},
	{Clerigo, "resources/sprites/iconos personajes/clerigo.png"},
	{Guerrero, "resources/sprites/iconos personajes/guerrero.png"},
	{Paladin, "resources/sprites/iconos personajes/paladin.png"},
	{Barbaro, "resources/sprites/iconos personajes/barbaro.png"},
	{Explorador, "resources/sprites/iconos personajes/explorador.png"},
	{Picaro, "resources/sprites/iconos personajes/picaro.png"},
	{Druida, "resources/sprites/iconos personajes/druida.png"},
	{Bestia, "resources/sprites/iconos personajes/bestia.png"},
	{GranArchimago, "resources/sprites/iconos personajes/heroe-mago.png"},

	{Mouse, "resources/images/interfaz/cursor+sombras.png"},
	{Avanzar, "resources/sprites/iconos movimiento/movimientoAvanzar.png"},
	{RotarD, "resources/sprites/iconos movimiento/movimientoRotarDerecha.png"},
	{RotarI, "resources/sprites/iconos movimiento/movimientoRotarIzquierda.png"},
	{Interactuar, "resources/sprites/iconos movimiento/movimientoInteractuar.png"},

	{Inventario, "resources/sprites/iconos info/infoInventario.png"},
	{PocionVida, "resources/sprites/iconos info/infoPocionVida.png"},
	{PocionMana, "resources/sprites/iconos info/infoPocionMana.png"},
	{Chat, "resources/sprites/iconos info/infoChat.png"},
	{Configuracion, "resources/sprites/iconos info/infoConfiguracionAyuda.png"},

	{AtaqueNormal, "resources/sprites/iconos combate/ataque.png"},
	{AtaqueMagico, "resources/sprites/iconos combate/magic.png"},
	{Defensa, "resources/sprites/iconos combate/defensa.png"},
	{Huida, "resources/sprites/iconos combate/huir.png"},

	//Inventario
	{Slot, "resources/sprites/iconos inventario/inventorySlot.png"},
	{ EmptySword, "resources/sprites/iconos inventario/inventorySword.png" },
	{ EmptyArmor, "resources/sprites/iconos inventario/inventoryArmor.png" },

	// Armas clasicas �?
	{Desarmado, "resources/sprites/iconos armas/joker.png"}, ///TODO
	{Baston, "resources/sprites/iconos armas/baston.png"},
	{Daga, "resources/sprites/iconos armas/daga.png"},
	{Clava, "resources/sprites/iconos armas/clava.png"},
	{HachaPequena, "resources/sprites/iconos armas/hacha.png"},
	{Hoz, "resources/sprites/iconos armas/joker.png"}, ///TODO
	{Lanza, "resources/sprites/iconos armas/lanza.png"},
	{MartilloPequeno, "resources/sprites/iconos armas/joker.png"}, ///TODO
	{Maza, "resources/sprites/iconos armas/maza.png"},
	{ArcoPequeno, "resources/sprites/iconos armas/arco_ligero.png"},
	{BallestaLigera, "resources/sprites/iconos armas/ballesta_ligera.png"},

	// Armas marciales
	{Alabarda, "resources/sprites/iconos armas/alabarda.png"},
	{Atarraga, "resources/sprites/iconos armas/joker.png"}, ///TODO
	{EspadaCorta, "resources/sprites/iconos armas/espada_corta.png"},
	{EspadaLarga, "resources/sprites/iconos armas/espada_larga.png"},
	{Espadon, "resources/sprites/iconos armas/joker.png"},		///TODO
	{EspadaRopera, "resources/sprites/iconos armas/joker.png"}, ///TODO
	{HachaBatalla, "resources/sprites/iconos armas/joker.png"}, ///TODO
	{Guja, "resources/sprites/iconos armas/joker.png"},			///TODO
	{Latigo, "resources/sprites/iconos armas/joker.png"},		///TODO
	{LuceroAlba, "resources/sprites/iconos armas/lucero.png"},	///TODO
	{MartilloGuerra, "resources/sprites/iconos armas/martillo.png"},
	{Pica, "resources/sprites/iconos armas/joker.png"},		///TODO
	{Tridente, "resources/sprites/iconos armas/joker.png"}, ///TODO
	{ArcoLargo, "resources/sprites/iconos armas/arco_largo.png"},
	{BallestaPesada, "resources/sprites/iconos armas/ballesta_pesada.png"},

	// Armaduras
	{Acolchada, "resources/sprites/iconos armaduras/joker.png"},
	{CueroTachonado, "resources/sprites/iconos armaduras/joker.png"},
	{CotaEscamas, "resources/sprites/iconos armaduras/cota_escamas.png"},
	{Coraza, "resources/sprites/iconos armaduras/joker.png"},
	{SemiPlacas, "resources/sprites/iconos armaduras/joker.png"},
	{CotaMalla, "resources/sprites/iconos armaduras/cota_mallas.png"},
	{Bandas, "resources/sprites/iconos armaduras/joker.png"},
	{Placas, "resources/sprites/iconos armaduras/joker.png"}};

vector<Resources::TextMsgInfo> Resources::messages_{
	//
	{HelloWorld, "Hello World", {COLOR(0xaaffffff)}, ARIAL16},			   //
	{PressAnyKey, "Press Any Key to Start", {COLOR(0xaaffbbff)}, ARIAL24}, //
	{GameOverWon, "Game Over! You Won!", {COLOR(0xffffbbff)}, ARIAL24},	   //
	{GameOverLost, "Game Over! You Lost!", {COLOR(0xffffbbff)}, ARIAL24}   //
};

vector<Resources::MusicInfo> Resources::musics_{
	//
	{ImperialMarch, "resources/sound/imperial_march.wav"} //
};

vector<Resources::SoundInfo> Resources::sounds_{
	//
	{Explosion, "resources/sound/explosion.wav"}, //
	{GunShot, "resources/sound/GunShot.wav"}	  //
};

vector<Resources::JsonInfo> Resources::jsons_{
	//
	{Heroes, "resources/jsons/heroes.json"},		  //
	{Enemies, "resources/jsons/enemies.json"},		  //
	{Weapons, "resources/jsons/pruebasArmas.json"},	  //
	{Armors, "resources/jsons/pruebasArmaduras.json"} //
};
