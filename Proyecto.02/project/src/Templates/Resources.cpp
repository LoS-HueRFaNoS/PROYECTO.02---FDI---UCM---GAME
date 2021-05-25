#include "Resources.h"
#include "../Utilities/SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_{
	{ARIAL16, "project/resources/fonts/ARIAL.ttf", 16}, //
	{ARIAL24, "project/resources/fonts/ARIAL.ttf", 24},	//
	{HERMAN, "project/resources/fonts/ARHERMANN.ttf", 64},
	{Fornite64, "project/resources/fonts/Fortnite.ttf", 64},
	{Fornite14, "project/resources/fonts/Fortnite.ttf", 14},
	{Quake, "project/resources/fonts/dpquake_.ttf", 64},
	{KillerInst, "project/resources/fonts/kinifed_.ttf", 64},
	{Sega, "project/resources/fonts/SEGA.ttf", 64},
	{Beaulieux, "project/resources/fonts/t4cbeaulieux.ttf", 64},
	{Triforce, "project/resources/fonts/Triforce.ttf", 64}	
};

vector<Resources::ImageInfo> Resources::images_{
	// laberinto y minimapa
	{posMiniMap, "project/resources/images/pasillos/posJugador.png"},			//
	{camino_izq, "project/resources/images/pasillos/frente/giro_izquierda/frente_giro_izquierda_suelo.png"},			//
	{camino_der, "project/resources/images/pasillos/frente/giro_derecha/frente_giro_derecha_suelo.png"},			//
	{camino_fr, "project/resources/images/pasillos/frente/frente_suelo.png"},			//
	{muro_izq, "project/resources/images/pasillos/frente/frente_pared_izquierda.png"},				//
	{muro_der, "project/resources/images/pasillos/frente/frente_pared_derecha.png"},				//
	{muro_fr, "project/resources/images/pasillos/frente/frente_pared.png"},				//
	{muro_fr_izq, "project/resources/images/pasillos/frente/giro_izquierda/frente_giro_izquierda_pared.png"},				//
	{muro_fr_der, "project/resources/images/pasillos/frente/giro_derecha/frente_giro_derecha_pared.png"},				//
	{muro_del, "project/resources/images/pasillos/frente/muro_frontal.png"},				//

	{camino_fondo_izq, "project/resources/images/pasillos/fondo/giro_izquierda/fondo_giro_izquierda_suelo.png"},			//
	{camino_fondo_der, "project/resources/images/pasillos/fondo/giro_derecha/fondo_giro_derecha_suelo.png"},			//
	{camino_fondo_fr, "project/resources/images/pasillos/fondo/fondo_suelo.png"},			//
	{muro_fondo_izq, "project/resources/images/pasillos/fondo/fondo_pared_izquierda.png"},				//
	{muro_fondo_der, "project/resources/images/pasillos/fondo/fondo_pared_derecha.png"},				//
	{muro_fondo_fr, "project/resources/images/pasillos/fondo/fondo_pared.png"},				//
	{muro_fondo_fr_izq, "project/resources/images/pasillos/fondo/giro_izquierda/fondo_giro_izquierda_pared.png"},				//
	{muro_fondo_fr_der, "project/resources/images/pasillos/fondo/giro_derecha/fondo_giro_derecha_pared.png"},				//
	//{fondo_vacio, "resources/images/pasillos/frente/fondo_frente.png"},				//

	{no_visitado, "project/resources/images/pasillos/pasillo_no_visitado.png"}, //
	{no_entrado, "project/resources/images/pasillos/pasillo_no_entrado.png"},	//
	{visitado, "project/resources/images/pasillos/pasillo_visitado.png"},		//
	{pared_N, "project/resources/images/pasillos/pared_norte.png"},				//
	{pared_E, "project/resources/images/pasillos/pared_este.png"},				//
	{pared_S, "project/resources/images/pasillos/pared_sur.png"},				//
	{pared_O, "project/resources/images/pasillos/pared_oeste.png"},				//
	{salidaMiniMap, "project/resources/images/pasillos/salida.png"},			//
	{texto_salida, "project/resources/images/texto_salida.jpg"},				//

	// menu principal
	{start, "project/resources/images/interfaz/button icons/Menu/PlayButton.png"},
	{options, "project/resources/images/interfaz/button icons/Menu/OptionsButton.png"},
	{quit, "project/resources/images/interfaz/button icons/Menu/quit.png"},
	{howToPlay, "project/resources/images/interfaz/button icons/Menu/HowToPlayButton.png"},
	//{mFondo, "project/resources/images/Menu/menufondo.jpg"},
	{mFondo, "project/resources/images/Menu/FondoMenuTituloFinal.png"},
	{close, "project/resources/images/Menu/close.png"},

	// heroes
	{Bardo, "project/resources/sprites/iconos personajes/bardo.png"},
	{Brujo, "project/resources/sprites/iconos personajes/brujo.png"},
	{Clerigo, "project/resources/sprites/iconos personajes/clerigo.png"},
	{Guerrero, "project/resources/sprites/iconos personajes/guerrero.png"},
	{Paladin, "project/resources/sprites/iconos personajes/paladin.png"},
	{Barbaro, "project/resources/sprites/iconos personajes/barbaro.png"},
	{Explorador, "project/resources/sprites/iconos personajes/explorador.png"},
	{Picaro, "project/resources/sprites/iconos personajes/picaro.png"},
	{Druida, "project/resources/sprites/iconos personajes/druida.png"},
	{Bestia, "project/resources/sprites/iconos personajes/bestia.png"},
	{GranArchimago, "project/resources/sprites/iconos personajes/heroe-mago.png"},

	// interfaz
	{Mouse, "project/resources/images/interfaz/cursor+sombras.png"},
	{Fondo, "project/resources/images/interfaz/Fondo_Interfaz_04.png"},
	{Fondo2, "project/resources/images/interfaz/Fondo_Interfaz_05.png"},
	{Button_transition, "project/resources/images/interfaz/button_transition.png"},
	{Cartel, "project/resources/images/interfaz/cartelito.png"},
	{Change, "project/resources/images/interfaz/change.png"},
	{Selected, "project/resources/images/interfaz/selected.png"},
	{BuyButton, "project/resources/images/interfaz/button icons/Tienda/BuyButton.png"},
	{EquipButton, "project/resources/images/interfaz/button icons/Tienda/EquipButton.png"},
	{FireButton, "project/resources/images/interfaz/button icons/Tienda/FireButton.png"},
	{RecruitButton, "project/resources/images/interfaz/button icons/Tienda/RecruitButton.png"},
	{SellButton, "project/resources/images/interfaz/button icons/Tienda/SellButton.png"},
	{StoreItemButton, "project/resources/images/interfaz/button icons/Tienda/StoreItemButton.png"},
	{lobby_button, "project/resources/images/interfaz/button icons/Tienda/lobby_button.png"},
	{inventory_button, "project/resources/images/interfaz/button icons/Tienda/InventoryButton.png"},
	{stash_button, "project/resources/images/interfaz/button icons/Tienda/StashButton.png"},
	{take, "project/resources/images/interfaz/button icons/Tienda/TakeButton.png"},

	// movimiento
	{Avanzar, "project/resources/sprites/iconos movimiento/movimientoAvanzar.png"},
	{RotarD, "project/resources/sprites/iconos movimiento/movimientoRotarDerecha.png"},
	{RotarI, "project/resources/sprites/iconos movimiento/movimientoRotarIzquierda.png"},
	{Interactuar, "project/resources/sprites/iconos movimiento/movimientoInteractuar.png"},
	{Retroceder, "project/resources/sprites/iconos movimiento/movimientoRetroceder.png"},
	{AvanzarBloqueado, "project/resources/sprites/iconos movimiento/movimientoAvanzarBloqueado.png"},
	{RetrocederBloqueado, "project/resources/sprites/iconos movimiento/movimientoRetrocederBloqueado.png"},

	// inventario e info
	{Inventario, "project/resources/sprites/iconos info/infoInventario.png"},
	{PocionVida, "project/resources/sprites/iconos info/infoPocionVida.png"},
	{PocionMana, "project/resources/sprites/iconos info/infoPocionMana.png"},
	{PocionRess, "project/resources/sprites/iconos info/infoPocionRess.png"},
	{Chat, "project/resources/sprites/iconos info/infoChat.png"},
	{Configuracion, "project/resources/sprites/iconos info/infoConfiguracionAyuda.png"},

	// combate
	{AtaqueNormal, "project/resources/sprites/iconos combate/ataque.png"},
	{AtaqueMagico, "project/resources/sprites/iconos combate/magic.png"},
	{Enter, "project/resources/sprites/iconos combate/enter.png"},
	{Huida, "project/resources/sprites/iconos combate/huir.png"},
	{Marco, "project/resources/sprites/iconos combate/marco.png"},
	{Target, "project/resources/sprites/iconos combate/target.png"},
	{Hability, "project/resources/sprites/iconos combate/hability.png"},

	//Inventario
	{Slot, "project/resources/sprites/iconos inventario/inventorySlot.png"},
	{EmptySword, "project/resources/sprites/iconos inventario/inventorySword.png"},
	{EmptyArmor, "project/resources/sprites/iconos inventario/inventoryArmor.png"},
	{WeaponSlot, "project/resources/sprites/iconos inventario/weapon_slot.png"},
	{ArmorSlot, "project/resources/sprites/iconos inventario/armor_slot.png"},
	{inventory_slots, "project/resources/images/Menu/inventory_slots.png"},

	// Armas clasicas
	{Joker, "project/resources/sprites/iconos armas/joker.png"}, ///TODO
	{Desarmado, "project/resources/sprites/iconos armas/desarmado.png"},
	{Baston, "project/resources/sprites/iconos armas/baston.png"},
	{Daga, "project/resources/sprites/iconos armas/daga.png"},
	{Clava, "project/resources/sprites/iconos armas/clava.png"},
	{HachaPequena, "project/resources/sprites/iconos armas/hacha.png"},
	{Hoz, "project/resources/sprites/iconos armas/hoz.png"},
	{Lanza, "project/resources/sprites/iconos armas/lanza.png"},
	{MartilloPequeno, "project/resources/sprites/iconos armas/martillo_peque.png"},
	{Maza, "project/resources/sprites/iconos armas/maza.png"},
	{ArcoPequeno, "project/resources/sprites/iconos armas/arco_ligero.png"},
	{BallestaLigera, "project/resources/sprites/iconos armas/ballesta_ligera.png"},

	// Armas marciales
	{Alabarda, "project/resources/sprites/iconos armas/alabarda.png"},
	{Atarraga, "project/resources/sprites/iconos armas/atarraga.png"},
	{EspadaCorta, "project/resources/sprites/iconos armas/espada_corta.png"},
	{EspadaLarga, "project/resources/sprites/iconos armas/espada_larga.png"},
	{Espadon, "project/resources/sprites/iconos armas/espadon.png"},
	{EspadaRopera, "project/resources/sprites/iconos armas/espada_ropera.png"},
	{HachaBatalla, "project/resources/sprites/iconos armas/hacha_batalla.png"},
	{Guja, "project/resources/sprites/iconos armas/guja.png"},
	{Latigo, "project/resources/sprites/iconos armas/latigo.png"},
	{LuceroAlba, "project/resources/sprites/iconos armas/lucero.png"},
	{MartilloGuerra, "project/resources/sprites/iconos armas/martillo.png"},
	{Pica, "project/resources/sprites/iconos armas/pica.png"},
	{Tridente, "project/resources/sprites/iconos armas/tridente.png"},
	{ArcoLargo, "project/resources/sprites/iconos armas/arco_largo.png"},
	{BallestaPesada, "project/resources/sprites/iconos armas/ballesta_pesada.png"},

	// Armaduras
	{Acolchada, "project/resources/sprites/iconos armaduras/acolchadaC.png"},
	{CueroTachonado, "project/resources/sprites/iconos armaduras/tachonada.png"},
	{CotaEscamas, "project/resources/sprites/iconos armaduras/cota_escamas.png"},
	{Coraza, "project/resources/sprites/iconos armaduras/corazaC.png"},
	{SemiPlacas, "project/resources/sprites/iconos armaduras/semiplacasC.png"},
	{CotaMalla, "project/resources/sprites/iconos armaduras/cota_mallas.png"},
	{Bandas, "project/resources/sprites/iconos armaduras/bandasC.png"},
	{Placas, "project/resources/sprites/iconos armaduras/placasC.png"},

	// Enemigos
	{Zombie, "project/resources/sprites/enemigos/zombie.png" },
	{Troll, "project/resources/sprites/enemigos/troll.png" },
	{Skeleton, "project/resources/sprites/enemigos/skeleton.png" },
	{Hellhound, "project/resources/sprites/enemigos/hellhound.png" },
	{Specter, "project/resources/sprites/enemigos/specter.png" },
	{Goblin, "project/resources/sprites/enemigos/goblin.png" },
	{DeathKnight, "project/resources/sprites/enemigos/deathknight.png" },
	{Mimic, "project/resources/sprites/enemigos/mimic.png" },
	{Pixie, "project/resources/sprites/enemigos/pixie.png" },
	{Ghoul, "project/resources/sprites/enemigos/ghoul.png" },
	{Dracolich, "project/resources/sprites/enemigos/dracolich.png" },
	{GiantWorm, "project/resources/sprites/enemigos/giantworm.png" },
	{Banshee, "project/resources/sprites/enemigos/banshee.png" },
	{Lich, "project/resources/sprites/iconos personajes/lich.PNG"},
	{Necrofago, "project/resources/sprites/iconos personajes/necrofago.png" },
	//{ Monster, "project/resources/images/monster.png" },
	//{ Desconocido, "project/resources/images/desconocido.png" },

	// Ficha DD
	{Pergamino, "project/resources/sprites/iconos ficha/pergamino.png"},

	//Habilidades
	{Aligerar, "project/resources/sprites/iconos habilidades/ALIGERAR.PNG"},
	{Bendicion, "project/resources/sprites/iconos habilidades/BENDICION.png"},
	{Bloody_strike, "project/resources/sprites/iconos habilidades/BLODDY_STRIKE.PNG"},
	{Bola_fuego, "project/resources/sprites/iconos habilidades/BOLA_DE_FUEGO.PNG"},
	{Congelar, "project/resources/sprites/iconos habilidades/CONGELAR.PNG"},
	{Cuchilla_aerea, "project/resources/sprites/iconos habilidades/CUCHILLA AEREA.png"},
	{Curacion_en_masa, "project/resources/sprites/iconos habilidades/CURACION EN MASA.png"},
	{Curacion, "project/resources/sprites/iconos habilidades/CURACION.PNG"},
	{Destello, "project/resources/sprites/iconos habilidades/DESTELLO.png"},
	{Determinacion, "project/resources/sprites/iconos habilidades/DETERMINACION.png"},	
	{DisparoDoble, "project/resources/sprites/iconos habilidades/DISPARO DOBLE.PNG"},
	{Endurecer, "project/resources/sprites/iconos habilidades/ENDURECER.png"},
	{Espinas, "project/resources/sprites/iconos habilidades/ESPINAS.png"},
	{FlechaDeFuego, "project/resources/sprites/iconos habilidades/FLECHA DE FUEGO.png"},
	{FlechaDeHumo, "project/resources/sprites/iconos habilidades/FLECHA DE HUMO.png"},
	{Fortalecer, "project/resources/sprites/iconos habilidades/FORTALECER.png"},
	{GolpeDuro, "project/resources/sprites/iconos habilidades/GOLPE DURO.png"},
	{HachaArrojadiza, "project/resources/sprites/iconos habilidades/HACHA ARROJADIZA.PNG"},
	{LightAttack, "project/resources/sprites/iconos habilidades/LightAttack.PNG"},
	{LluviaDeDagas, "project/resources/sprites/iconos habilidades/LLUVIA DE DAGAS.png"},
	{Meditacion, "project/resources/sprites/iconos habilidades/MEDITACION.png"},
	{OdaDeLosGladiadores, "project/resources/sprites/iconos habilidades/ODA DE LOS GLADIADORES.png"},
	{OdaDeViento, "project/resources/sprites/iconos habilidades/ODA DE VIENTO.png"},
	{PilarDeTierra, "project/resources/sprites/iconos habilidades/PILAR DE TIERRA.png"},
	{ProyectilesDeRoca, "project/resources/sprites/iconos habilidades/PROYECTILES DE ROCA.png"},
	{RafagaDeViento, "project/resources/sprites/iconos habilidades/RAFAGA DE VIENTO.png"},
	{RayoLuminoso, "project/resources/sprites/iconos habilidades/RAYO LUMINOSO.PNG"},
	{Sacrificio, "project/resources/sprites/iconos habilidades/SACRIFICIO.PNG"},
	{SedDeSangre, "project/resources/sprites/iconos habilidades/SED DE SANGRE.png"},
	{SelfHeal, "project/resources/sprites/iconos habilidades/SELF HEAL.png"},
	{Sombra_toxica, "project/resources/sprites/iconos habilidades/SOMBRA TOXICA.png"},
	{Proteccion_divina, "project/resources/sprites/iconos habilidades/PROTECCION DIVINA.png"},
	{TorrenteAcuatico, "project/resources/sprites/iconos habilidades/TORRENTE ACUATICO.PNG"},
	{Trickshot, "project/resources/sprites/iconos habilidades/TRICKSHOT.png"},
	{Tsunami, "project/resources/sprites/iconos habilidades/TSUNAMI.png"},
	{VorticeDeOscuridad, "project/resources/sprites/iconos habilidades/VORTICE DE OSCURIDAD.PNG"},
	{Morph, "project/resources/sprites/iconos habilidades/MORPH.png"},
	{ReverseMorph, "project/resources/sprites/iconos habilidades/MORPH.png"},

	// carteles tutorial
	{ cartel_combate, "project/resources/images/interfaz/carteles/cartel_combate.png" },
	{ cartel_movimiento, "project/resources/images/interfaz/carteles/cartel_movimiento.png" },
	{ cartel_inventario, "project/resources/images/interfaz/carteles/cartel_inventario.png" },
	{ cartel_support, "project/resources/images/interfaz/carteles/cartel_support.png" },
	{ cartel_heroes, "project/resources/images/interfaz/carteles/cartel_heroes.png" },
	{ cartel_minimapa, "project/resources/images/interfaz/carteles/cartel_minimapa.png" },
	{ cartel_configuracion, "project/resources/images/interfaz/carteles/cartel_configuracion.png" },
	{ cartel_bienvenida_pt1, "project/resources/images/interfaz/carteles/cartel_bienvenida_pt1.png" },
	{ cartel_bienvenida_pt2, "project/resources/images/interfaz/carteles/cartel_bienvenida_pt2.png" },

	// paneles focalizados
	{ foco_combate, "project/resources/images/interfaz/focos/foco_combate.png" },
	{ foco_inventario, "project/resources/images/interfaz/focos/foco_inventario.png" },
	{ foco_support, "project/resources/images/interfaz/focos/foco_support.png" },
	{ foco_heroes, "project/resources/images/interfaz/focos/foco_heroes.png" },
	{ foco_minimapa, "project/resources/images/interfaz/focos/foco_minimapa.png" },
	{ cinematica, "project/resources/images/interfaz/focos/cinematica.png" }
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
	//{MenuInicial, "project/resources/sound/Musica/Menu principal.wav"}, //
	//{Lobby, "project/resources/sound/Musica/Lobby.wav"}, //
	//{Exploracion, "project/resources/sound/Musica/Exploracion.wav"}, //
	//{Derrota, "project/resources/sound/Musica/Derrota.wav"}, //
	//{Creditos, "project/resources/sound/Musica/Creditos.wav"}, //
	//{CombateLich, "project/resources/sound/Musica/Combate Lich.wav"} //
};

vector<Resources::SoundInfo> Resources::sounds_{
	//
	{AtaqueAgua, "project/resources/sound/Sonidos/ataque agua.mp3"}, //
	{AtaqueFuego, "project/resources/sound/Sonidos/ataque fuego.mp3"}, //
	{AtaqueLuz, "project/resources/sound/Sonidos/ataque luz.mp3"}, //
	{AtaqueViento, "project/resources/sound/Sonidos/ataque viento.mp3"}, //
	{Boton1, "project/resources/sound/Sonidos/boton 1.mp3"}, //
	{Boton2, "project/resources/sound/Sonidos/boton 2.mp3"}, //
};

vector<Resources::JsonInfo> Resources::jsons_{
	//
	{Heroes, "project/resources/jsons/heroes.json"},		  //
	{Enemies, "project/resources/jsons/enemies.json"},		  //
	{Weapons, "project/resources/jsons/pruebasArmas.json"},	  //
	{Armors, "project/resources/jsons/pruebasArmaduras.json"} //
};
