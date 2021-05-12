#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_{
	{ARIAL16, "resources/fonts/ARIAL.ttf", 16}, //
	{ARIAL24, "resources/fonts/ARIAL.ttf", 24},	//
	{HERMAN, "resources/fonts/ARHERMANN.ttf", 64},
	{Fornite, "resources/fonts/Fortnite.ttf", 64},
	{Quake, "resources/fonts/dpquake_.ttf", 64},
	{KillerInst, "resources/fonts/kinifed_.ttf", 64},
	{Sega, "resources/fonts/SEGA.ttf", 64},
	{Beaulieux, "resources/fonts/t4cbeaulieux.ttf", 64},
	{Triforce, "resources/fonts/Triforce.ttf", 64}
};

vector<Resources::ImageInfo> Resources::images_{
	{posMiniMap, "resources/images/pasillos/posJugador.png"},			//
	{camino_izq, "resources/images/pasillos/frente/giro_izquierda/frente_giro_izquierda_suelo.png"},			//
	{camino_der, "resources/images/pasillos/frente/giro_derecha/frente_giro_derecha_suelo.png"},			//
	{camino_fr, "resources/images/pasillos/frente/frente_suelo.png"},			//
	{muro_izq, "resources/images/pasillos/frente/frente_pared_izquierda.png"},				//
	{muro_der, "resources/images/pasillos/frente/frente_pared_derecha.png"},				//
	{muro_fr, "resources/images/pasillos/frente/frente_pared.png"},				//
	{muro_fr_izq, "resources/images/pasillos/frente/giro_izquierda/frente_giro_izquierda_pared.png"},				//
	{muro_fr_der, "resources/images/pasillos/frente/giro_derecha/frente_giro_derecha_pared.png"},				//
	{muro_del, "resources/images/pasillos/frente/muro_frontal.png"},				//



	{camino_fondo_izq, "resources/images/pasillos/fondo/giro_izquierda/fondo_giro_izquierda_suelo.png"},			//
	{camino_fondo_der, "resources/images/pasillos/fondo/giro_derecha/fondo_giro_derecha_suelo.png"},			//
	{camino_fondo_fr, "resources/images/pasillos/fondo/fondo_suelo.png"},			//
	{muro_fondo_izq, "resources/images/pasillos/fondo/fondo_pared_izquierda.png"},				//
	{muro_fondo_der, "resources/images/pasillos/fondo/fondo_pared_derecha.png"},				//
	{muro_fondo_fr, "resources/images/pasillos/fondo/fondo_pared.png"},				//
	{muro_fondo_fr_izq, "resources/images/pasillos/fondo/giro_izquierda/fondo_giro_izquierda_pared.png"},				//
	{muro_fondo_fr_der, "resources/images/pasillos/fondo/giro_derecha/fondo_giro_derecha_pared.png"},				//


	{no_visitado, "resources/images/pasillos/pasillo_no_visitado.png"}, //
	{no_entrado, "resources/images/pasillos/pasillo_no_entrado.png"},	//
	{visitado, "resources/images/pasillos/pasillo_visitado.png"},		//
	{pared_N, "resources/images/pasillos/pared_norte.png"},				//
	{pared_E, "resources/images/pasillos/pared_este.png"},				//
	{pared_S, "resources/images/pasillos/pared_sur.png"},				//
	{pared_O, "resources/images/pasillos/pared_oeste.png"},				//
	{salidaMiniMap, "resources/images/pasillos/salida.png"},				//
	{texto_salida, "resources/images/texto_salida.png"},				//

	{start, "resources/images/Menu/StartBoton.png"},
	{options, "resources/images/Menu/options.png"},
	{quit, "resources/images/Menu/quit.png"},
	{howToPlay, "resources/images/Menu/howtoplay.png"},

	{mFondo, "resources/images/Menu/menufondo.jpg"},
	{close, "resources/images/Menu/close.png"},

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
	{Fondo, "resources/sprites/fondos y marcos/Fondo_Interfaz_02.png"},
	{Selected, "resources/sprites/fondos y marcos/selected.png"},
	{Avanzar, "resources/sprites/iconos movimiento/movimientoAvanzar.png"},
	{RotarD, "resources/sprites/iconos movimiento/movimientoRotarDerecha.png"},
	{RotarI, "resources/sprites/iconos movimiento/movimientoRotarIzquierda.png"},
	{Interactuar, "resources/sprites/iconos movimiento/movimientoInteractuar.png"},

	{Inventario, "resources/sprites/iconos info/infoInventario.png"},
	{PocionVida, "resources/sprites/iconos info/infoPocionVida.png"},
	{PocionMana, "resources/sprites/iconos info/infoPocionMana.png"},
	{PocionRess, "resources/sprites/iconos info/infoPocionRess.png"},
	{Chat, "resources/sprites/iconos info/infoChat.png"},
	{Configuracion, "resources/sprites/iconos info/infoConfiguracionAyuda.png"},

	{AtaqueNormal, "resources/sprites/iconos combate/ataque.png"},
	{AtaqueMagico, "resources/sprites/iconos combate/magic.png"},
	{Defensa, "resources/sprites/iconos combate/defensa.png"},
	{Huida, "resources/sprites/iconos combate/huir.png"},
	{Marco, "resources/sprites/iconos combate/marco.png"},
	{Target, "resources/sprites/iconos combate/target.png"},
	{Hability, "resources/sprites/iconos combate/hability.png"},

	//Inventario
	{Slot, "resources/sprites/iconos inventario/inventorySlot.png"},
	{EmptySword, "resources/sprites/iconos inventario/inventorySword.png"},
	{EmptyArmor, "resources/sprites/iconos inventario/inventoryArmor.png"},
	{WeaponSlot, "resources/sprites/iconos inventario/weapon_slot.png"},
	{ArmorSlot, "resources/sprites/iconos inventario/armor_slot.png"},

	// Armas clasicas
	{Joker, "resources/sprites/iconos armas/joker.png"}, ///TODO
	{Desarmado, "resources/sprites/iconos armas/desarmado.png"},
	{Baston, "resources/sprites/iconos armas/baston.png"},
	{Daga, "resources/sprites/iconos armas/daga.png"},
	{Clava, "resources/sprites/iconos armas/clava.png"},
	{HachaPequena, "resources/sprites/iconos armas/hacha.png"},
	{Hoz, "resources/sprites/iconos armas/hoz.png"},
	{Lanza, "resources/sprites/iconos armas/lanza.png"},
	{MartilloPequeno, "resources/sprites/iconos armas/martillo_peque.png"},
	{Maza, "resources/sprites/iconos armas/maza.png"},
	{ArcoPequeno, "resources/sprites/iconos armas/arco_ligero.png"},
	{BallestaLigera, "resources/sprites/iconos armas/ballesta_ligera.png"},

	// Armas marciales
	{Alabarda, "resources/sprites/iconos armas/alabarda.png"},
	{Atarraga, "resources/sprites/iconos armas/atarraga.png"},
	{EspadaCorta, "resources/sprites/iconos armas/espada_corta.png"},
	{EspadaLarga, "resources/sprites/iconos armas/espada_larga.png"},
	{Espadon, "resources/sprites/iconos armas/espadon.png"},
	{EspadaRopera, "resources/sprites/iconos armas/espada_ropera.png"},
	{HachaBatalla, "resources/sprites/iconos armas/hacha_batalla.png"},
	{Guja, "resources/sprites/iconos armas/guja.png"},
	{Latigo, "resources/sprites/iconos armas/latigo.png"},
	{LuceroAlba, "resources/sprites/iconos armas/lucero.png"},
	{MartilloGuerra, "resources/sprites/iconos armas/martillo.png"},
	{Pica, "resources/sprites/iconos armas/pica.png"},
	{Tridente, "resources/sprites/iconos armas/tridente.png"},
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
	{Placas, "resources/sprites/iconos armaduras/joker.png"},

	// Enemigos
	{Zombie, "resources/sprites/enemigos/zombie.png" },
	{Troll, "resources/sprites/enemigos/troll.png" },
	{Skeleton, "resources/sprites/enemigos/skeleton.png" },
	{Hellhound, "resources/sprites/enemigos/hellhound.png" },
	{Specter, "resources/sprites/enemigos/specter.png" },
	{Goblin, "resources/sprites/enemigos/goblin.png" },
	{DeathKnight, "resources/sprites/enemigos/deathknight.png" },
	{Mimic, "resources/sprites/enemigos/mimic.png" },
	{Pixie, "resources/sprites/enemigos/pixie.png" },
	{Ghoul, "resources/sprites/enemigos/ghoul.png" },
	{Dracolich, "resources/sprites/enemigos/dracolich.png" },
	{GiantWorm, "resources/sprites/enemigos/giantworm.png" },
	{Banshee, "resources/sprites/enemigos/banshee.png" },
	{Lich, "resources/sprites/iconos personajes/lich.PNG"},
	{Necrofago, "resources/sprites/iconos personajes/necrofago.png" },
	{ Monster, "resources/images/monster.png" },
	{ Desconocido, "resources/images/desconocido.png" },

	// Ficha DD
	{Pergamino, "resources/sprites/iconos ficha/pergamino.png"},

	//Habilidades
	{Aligerar, "resources/sprites/iconos habilidades/ALIGERAR.PNG"},
	{Bendicion, "resources/sprites/iconos habilidades/BENDICION.png"},
	{Bloody_strike, "resources/sprites/iconos habilidades/BLODDY_STRIKE.PNG"},
	{Bola_fuego, "resources/sprites/iconos habilidades/BOLA_DE_FUEGO.PNG"},
	{Congelar, "resources/sprites/iconos habilidades/CONGELAR.PNG"},
	{Cuchilla_aerea, "resources/sprites/iconos habilidades/CUCHILLA AEREA.png"},
	{Curacion_en_masa, "resources/sprites/iconos habilidades/CURACION EN MASA.png"},
	{Curacion, "resources/sprites/iconos habilidades/CURACION.PNG"},
	{Destello, "resources/sprites/iconos habilidades/DESTELLO.png"},
	{Determinacion, "resources/sprites/iconos habilidades/DETERMINACION.png"},	
	{DisparoDoble, "resources/sprites/iconos habilidades/DISPARO DOBLE.PNG"},
	{Endurecer, "resources/sprites/iconos habilidades/ENDURECER.png"},
	{Espinas, "resources/sprites/iconos habilidades/ESPINAS.png"},
	{FlechaDeFuego, "resources/sprites/iconos habilidades/FLECHA DE FUEGO.png"},
	{FlechaDeHumo, "resources/sprites/iconos habilidades/FLECHA DE HUMO.png"},
	{Fortalecer, "resources/sprites/iconos habilidades/FORTALECER.png"},
	{GolpeDuro, "resources/sprites/iconos habilidades/GOLPE DURO.png"},
	{HachaArrojadiza, "resources/sprites/iconos habilidades/HACHA ARROJADIZA.PNG"},
	{LightAttack, "resources/sprites/iconos habilidades/LightAttack.PNG"},
	{LluviaDeDagas, "resources/sprites/iconos habilidades/LLUVIA DE DAGAS.png"},
	{Meditacion, "resources/sprites/iconos habilidades/MEDITACION.png"},
	{OdaDeLosGladiadores, "resources/sprites/iconos habilidades/ODA DE LOS GLADIADORES.png"},
	{OdaDeViento, "resources/sprites/iconos habilidades/ODA DE VIENTO.png"},
	{PilarDeTierra, "resources/sprites/iconos habilidades/PILAR DE TIERRA.png"},
	{ProyectilesDeRoca, "resources/sprites/iconos habilidades/PROYECTILES DE ROCA.png"},
	{RafagaDeViento, "resources/sprites/iconos habilidades/RAFAGA DE VIENTO.png"},
	{RayoLuminoso, "resources/sprites/iconos habilidades/RAYO LUMINOSO.PNG"},
	{Sacrificio, "resources/sprites/iconos habilidades/SACRIFICIO.PNG"},
	{SedDeSangre, "resources/sprites/iconos habilidades/SED DE SANGRE.png"},
	{SelfHeal, "resources/sprites/iconos habilidades/SELF HEAL.png"},
	{Sombra_toxica, "resources/sprites/iconos habilidades/SOMBRA TOXICA.png"},
	{Proteccion_divina, "resources/sprites/iconos habilidades/PROTECCION DIVINA.png"},
	{TorrenteAcuatico, "resources/sprites/iconos habilidades/TORRENTE ACUATICO.PNG"},
	{Trickshot, "resources/sprites/iconos habilidades/TRICKSHOT.png"},
	{Tsunami, "resources/sprites/iconos habilidades/TSUNAMI.png"},
	{VorticeDeOscuridad, "resources/sprites/iconos habilidades/VORTICE DE OSCURIDAD.PNG"},
	{Morph, "resources/sprites/iconos habilidades/MORPH.png"}
};

vector<Resources::TextMsgInfo> Resources::messages_{
	//
	{HelloWorld, "Hello World", {COLOR(0xaaffffff)}, ARIAL16},			   //
	{PressAnyKey, "Press Any Key to Start", {COLOR(0xaaffbbff)}, ARIAL24}, //
	{GameOverWon, "Game Over! You Won!", {COLOR(0xffffbbff)}, ARIAL24},	   //
	{GameOverLost, "Game Over! You Lost!", {COLOR(0xffffbbff)}, ARIAL24}   //
};

vector<Resources::MusicInfo> Resources::musics_{
	//
	{ImperialMarch, "resources/sound/imperial_march.wav"}, //
	{Mystery, "resources/sound/mystery.mp3"}, //
	{Tension, "resources/sound/tension.mp3"} //
};

vector<Resources::SoundInfo> Resources::sounds_{
	//
	{Explosion, "resources/sound/explosion.wav"}, //
	{Notification, "resources/sound/notification.wav"},	  //
	{GameOver, "resources/sound/gameover.wav"}	  //
};

vector<Resources::JsonInfo> Resources::jsons_{
	//
	{Heroes, "resources/jsons/heroes.json"},		  //
	{Enemies, "resources/jsons/enemies.json"},		  //
	{Weapons, "resources/jsons/pruebasArmas.json"},	  //
	{Armors, "resources/jsons/pruebasArmaduras.json"} //
};
