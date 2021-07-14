#include "Resources.h"
#include "../Utilities/SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_{
	{HERMAN, "project/resources/fonts/ARHERMANN.ttf", 64},
	{Fornite64, "project/resources/fonts/Fortnite.ttf", 64},
	{Beaulieux, "project/resources/fonts/t4cbeaulieux.ttf", 64},
	{Medieval, "project/resources/fonts/MedievalSharp-Regular.ttf", 32},	
	{Console, "project/resources/fonts/consola.ttf", 32},
	{ConsoleBO, "project/resources/fonts/consolab.ttf", 32}
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
	{fondo_vacio, "project/resources/images/pasillos/fondo/fondo_frente.png"},				//

	{no_visitado, "project/resources/images/pasillos/pasillo_no_visitado.png"}, //
	{no_entrado, "project/resources/images/pasillos/pasillo_no_entrado.png"},	//
	{visitado, "project/resources/images/pasillos/pasillo_visitado.png"},		//
	{pared_N, "project/resources/images/pasillos/pared_norte.png"},				//
	{pared_E, "project/resources/images/pasillos/pared_este.png"},				//
	{pared_S, "project/resources/images/pasillos/pared_sur.png"},				//
	{pared_O, "project/resources/images/pasillos/pared_oeste.png"},				//
	{salidaMiniMap, "project/resources/images/pasillos/salida.png"},			//
	{cofreMiniMap, "project/resources/images/pasillos/cofre.png"},			//
	{texto_salida, "project/resources/images/texto_salida.jpg"},				//
	{puerta, "project/resources/images/sprites/animaciones/door1finish.png"},				//

	// menu principal
	{start, "project/resources/images/interfaz/button icons/Menu/PlayButton.png"},
	{options, "project/resources/images/interfaz/button icons/Menu/OptionsButton.png"},
	{quit, "project/resources/images/interfaz/button icons/Menu/quit.png"},
	{mFondo, "project/resources/images/Menu/FondoMenuTituloFinal.png"},
	{close, "project/resources/images/Menu/close.png"},

	// heroes
	{Bardo, "project/resources/images/sprites/iconos personajes/bardo.png"},
	{Brujo, "project/resources/images/sprites/iconos personajes/brujo.png"},
	{Clerigo, "project/resources/images/sprites/iconos personajes/clerigo.png"},
	{Guerrero, "project/resources/images/sprites/iconos personajes/guerrero.png"},
	{Paladin, "project/resources/images/sprites/iconos personajes/paladin.png"},
	{Barbaro, "project/resources/images/sprites/iconos personajes/barbaro.png"},
	{Explorador, "project/resources/images/sprites/iconos personajes/explorador.png"},
	{Picaro, "project/resources/images/sprites/iconos personajes/picaro.png"},
	{Druida, "project/resources/images/sprites/iconos personajes/druida.png"},
	{Bestia, "project/resources/images/sprites/iconos personajes/bestia.png"},
	{GranArchimago, "project/resources/images/sprites/iconos personajes/heroe-mago.png"},
		//
	{Bardo_, "project/resources/images/sprites/iconos personajes/bardo_.png"},
	{Brujo_, "project/resources/images/sprites/iconos personajes/brujo_.png"},
	{Clerigo_, "project/resources/images/sprites/iconos personajes/clerigo_.png"},
	{Guerrero_, "project/resources/images/sprites/iconos personajes/guerrero_.png"},
	{Paladin_, "project/resources/images/sprites/iconos personajes/paladin_.png"},
	{Barbaro_, "project/resources/images/sprites/iconos personajes/barbaro_.png"},
	{Explorador_, "project/resources/images/sprites/iconos personajes/explorador_.png"},
	{Picaro_, "project/resources/images/sprites/iconos personajes/picaro_.png"},
	{Druida_, "project/resources/images/sprites/iconos personajes/druida_.png"},
	{Bestia_, "project/resources/images/sprites/iconos personajes/bestia_.png"},
	{GranArchimago_, "project/resources/images/sprites/iconos personajes/heroe-mago_.png"},
		//
	{Bardo__, "project/resources/images/sprites/iconos personajes/bardo__.png"},
	{Brujo__, "project/resources/images/sprites/iconos personajes/brujo__.png"},
	{Clerigo__, "project/resources/images/sprites/iconos personajes/clerigo__.png"},
	{Guerrero__, "project/resources/images/sprites/iconos personajes/guerrero__.png"},
	{Paladin__, "project/resources/images/sprites/iconos personajes/paladin__.png"},
	{Barbaro__, "project/resources/images/sprites/iconos personajes/barbaro__.png"},
	{Explorador__, "project/resources/images/sprites/iconos personajes/explorador__.png"},
	{Picaro__, "project/resources/images/sprites/iconos personajes/picaro__.png"},
	{Druida__, "project/resources/images/sprites/iconos personajes/druida__.png"},
	{Bestia__, "project/resources/images/sprites/iconos personajes/bestia__.png"},
	{GranArchimago__, "project/resources/images/sprites/iconos personajes/heroe-mago__.png"},

	// interfaz
	{Mouse, "project/resources/images/interfaz/cursor+sombras.png"},
	{Fondo, "project/resources/images/interfaz/Fondo_Interfaz_04.png"},
	{Fondo2, "project/resources/images/interfaz/Fondo_Interfaz_05.png"},
	{Button_transition, "project/resources/images/interfaz/button_transition.png"},
	{Cartel, "project/resources/images/interfaz/cartelito.png"},
	{VolumeBar, "project/resources/images/interfaz/volBar.png"},
	{VolumeBarBackground, "project/resources/images/interfaz/volBarBg.png"},
	{Change, "project/resources/images/interfaz/change.png"},
	{Change2, "project/resources/images/interfaz/change2.png"},
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
	{vibration, "project/resources/images/interfaz/peligro.png"},
	{fade, "project/resources/images/interfaz/FadeOutNegro.png"},
	{DiceRed, "project/resources/images/interfaz/dadoRojo.png"},
	{DiceGreen, "project/resources/images/interfaz/dadoVerde.png" },
	{marco_hero, "project/resources/images/interfaz/grids fondo/marco_heroe.png"},

	// movimiento
	{Avanzar, "project/resources/images/sprites/iconos movimiento/movimientoAvanzar.png"},
	{RotarD, "project/resources/images/sprites/iconos movimiento/movimientoRotarDerecha.png"},
	{RotarI, "project/resources/images/sprites/iconos movimiento/movimientoRotarIzquierda.png"},
	{RotarDAlt, "project/resources/images/sprites/iconos movimiento/movimientoRotarDerechaAlt.png"},
	{RotarIAlt, "project/resources/images/sprites/iconos movimiento/movimientoRotarIzquierdaAlt.png"},
	{Retroceder, "project/resources/images/sprites/iconos movimiento/movimientoRetroceder.png"},
	{AvanzarBloqueado, "project/resources/images/sprites/iconos movimiento/movimientoAvanzarBloqueado.png"},
	{RetrocederBloqueado, "project/resources/images/sprites/iconos movimiento/movimientoRetrocederBloqueado.png"},

	// inventario e info
	{Inventario, "project/resources/images/sprites/iconos info/infoInventario.png"},
	{CofreMenu, "project/resources/images/interfaz/grids fondo/cofre.png"},
	{PocionVida, "project/resources/images/sprites/iconos info/infoPocionVida.png"},
	{PocionVida_, "project/resources/images/sprites/iconos info/infoPocionVida_.png"},
	{PocionMana, "project/resources/images/sprites/iconos info/infoPocionMana.png"},
	{PocionMana_, "project/resources/images/sprites/iconos info/infoPocionMana_.png"},
	{Configuracion, "project/resources/images/sprites/iconos info/infoConfiguracionAyuda.png"},
	{Configuracion_, "project/resources/images/sprites/iconos info/infoConfiguracionAyuda_.png"},

	// combate
	{AtaqueNormal, "project/resources/images/sprites/iconos combate/ataque.png"},
	{AtaqueMagico, "project/resources/images/sprites/iconos combate/magic.png"},
	{Enter, "project/resources/images/sprites/iconos combate/enter.png"},
	{Huida, "project/resources/images/sprites/iconos combate/huir.png"},

	//Inventario
	{Slot, "project/resources/images/sprites/iconos inventario/inventorySlot.png"},
	{WeaponSlot, "project/resources/images/sprites/iconos inventario/weapon_slot.png"},
	{ArmorSlot, "project/resources/images/sprites/iconos inventario/armor_slot.png"},
	{inventory_slots, "project/resources/images/Menu/inventory_slots.png"},

	// Armas clasicas
	{Desarmado, "project/resources/images/sprites/iconos armas/desarmado.png"},
	{Baston, "project/resources/images/sprites/iconos armas/baston.png"},
	{Daga, "project/resources/images/sprites/iconos armas/daga.png"},
	{Clava, "project/resources/images/sprites/iconos armas/clava.png"},
	{HachaPequena, "project/resources/images/sprites/iconos armas/hacha.png"},
	{Hoz, "project/resources/images/sprites/iconos armas/hoz.png"},
	{Lanza, "project/resources/images/sprites/iconos armas/lanza.png"},
	{MartilloPequeno, "project/resources/images/sprites/iconos armas/martillo_peque.png"},
	{Maza, "project/resources/images/sprites/iconos armas/maza.png"},
	{ArcoPequeno, "project/resources/images/sprites/iconos armas/arco_ligero.png"},
	{BallestaLigera, "project/resources/images/sprites/iconos armas/ballesta_ligera.png"},

	// Armas marciales
	{Alabarda, "project/resources/images/sprites/iconos armas/alabarda.png"},
	{Atarraga, "project/resources/images/sprites/iconos armas/atarraga.png"},
	{EspadaCorta, "project/resources/images/sprites/iconos armas/espada_corta.png"},
	{EspadaLarga, "project/resources/images/sprites/iconos armas/espada_larga.png"},
	{Espadon, "project/resources/images/sprites/iconos armas/espadon.png"},
	{EspadaRopera, "project/resources/images/sprites/iconos armas/espada_ropera.png"},
	{HachaBatalla, "project/resources/images/sprites/iconos armas/hacha_batalla.png"},
	{Guja, "project/resources/images/sprites/iconos armas/guja.png"},
	{Latigo, "project/resources/images/sprites/iconos armas/latigo.png"},
	{LuceroAlba, "project/resources/images/sprites/iconos armas/lucero.png"},
	{MartilloGuerra, "project/resources/images/sprites/iconos armas/martillo.png"},
	{Pica, "project/resources/images/sprites/iconos armas/pica.png"},
	{Tridente, "project/resources/images/sprites/iconos armas/tridente.png"},
	{ArcoLargo, "project/resources/images/sprites/iconos armas/arco_largo.png"},
	{BallestaPesada, "project/resources/images/sprites/iconos armas/ballesta_pesada.png"},
	
	/// TODO: BORRAR
	{Joker, "project/resources/images/sprites/joker.png"},

	// Armaduras
	{Acolchada, "project/resources/images/sprites/iconos armaduras/acolchadaC.png"},
	{CueroTachonado, "project/resources/images/sprites/iconos armaduras/tachonada.png"},
	{CotaEscamas, "project/resources/images/sprites/iconos armaduras/cota_escamas.png"},
	{Coraza, "project/resources/images/sprites/iconos armaduras/corazaC.png"},
	{SemiPlacas, "project/resources/images/sprites/iconos armaduras/semiplacasC.png"},
	{CotaMalla, "project/resources/images/sprites/iconos armaduras/cota_mallas.png"},
	{Bandas, "project/resources/images/sprites/iconos armaduras/bandasC.png"},
	{Placas, "project/resources/images/sprites/iconos armaduras/placasC.png"},

	// Enemigos
	{Zombie, "project/resources/images/sprites/enemigos/spritesheets/idle/zombieIdle.png" },
	{Troll, "project/resources/images/sprites/enemigos/spritesheets/idle/trollIdle.png" },
	{Skeleton, "project/resources/images/sprites/enemigos/spritesheets/idle/skeletonIdle.png" },
	{Hellhound, "project/resources/images/sprites/enemigos/spritesheets/idle/hellhoundIdle.png" },
	{Specter, "project/resources/images/sprites/enemigos/spritesheets/idle/specterIdle.png" },
	{Goblin, "project/resources/images/sprites/enemigos/spritesheets/idle/goblinIdle.png" },
	{DeathKnight, "project/resources/images/sprites/enemigos/spritesheets/idle/deathknightIdle.png" },
	{Mimic, "project/resources/images/sprites/enemigos/spritesheets/idle/mimicIdle.png" },
	{Pixie, "project/resources/images/sprites/enemigos/spritesheets/idle/pixieIdle.png" },
	{Ghoul, "project/resources/images/sprites/enemigos/spritesheets/idle/ghoulIdle.png" },
	{Dracolich, "project/resources/images/sprites/enemigos/spritesheets/idle/dracolichIdle.png" },
	{GiantWorm, "project/resources/images/sprites/enemigos/spritesheets/idle/giantwormIdle.png" },
	{Banshee, "project/resources/images/sprites/enemigos/spritesheets/idle/bansheeIdle.png" },
	{Lich, "project/resources/images/sprites/enemigos/spritesheets/idle/lichIdle.PNG"},
	// Cofre
	{CofreCerrado, "project/resources/images/sprites/cofre/cofreCerrado.PNG" },
	{CofreVacio, "project/resources/images/sprites/cofre/cofreAbierto.PNG" },
	{CofreLleno, "project/resources/images/sprites/cofre/cofreLuz.PNG" },

	//Llaves
	{LlaveCofre, "project/resources/images/sprites/llaves/chestKey.png" },
	{LlaveNivel, "project/resources/images/sprites/llaves/levelKey.png" },
	{LlaveVacia, "project/resources/images/sprites/llaves/emptykey.png" },

	// Ficha DD
	{Pergamino, "project/resources/images/sprites/iconos ficha/pergamino.png"},
	// Panel Desc.
	{Cartelito, "project/resources/images/interfaz/cartelito_long.png"},

	//Habilidades
	{Aligerar, "project/resources/images/sprites/iconos habilidades/ALIGERAR.PNG"},
	{Bendicion, "project/resources/images/sprites/iconos habilidades/BENDICION.png"},
	{Bloody_strike, "project/resources/images/sprites/iconos habilidades/BLODDY_STRIKE.PNG"},
	{Bola_fuego, "project/resources/images/sprites/iconos habilidades/BOLA_DE_FUEGO.PNG"},
	{Congelar, "project/resources/images/sprites/iconos habilidades/CONGELAR.PNG"},
	{Cuchilla_aerea, "project/resources/images/sprites/iconos habilidades/CUCHILLA AEREA.png"},
	{Curacion_en_masa, "project/resources/images/sprites/iconos habilidades/CURACION EN MASA.png"},
	{Curacion, "project/resources/images/sprites/iconos habilidades/CURACION.PNG"},
	{Destello, "project/resources/images/sprites/iconos habilidades/DESTELLO.png"},
	{Determinacion, "project/resources/images/sprites/iconos habilidades/DETERMINACION.png"},	
	{DisparoDoble, "project/resources/images/sprites/iconos habilidades/DISPARO DOBLE.PNG"},
	{Endurecer, "project/resources/images/sprites/iconos habilidades/ENDURECER.png"},
	{Espinas, "project/resources/images/sprites/iconos habilidades/ESPINAS.png"},
	{FlechaDeFuego, "project/resources/images/sprites/iconos habilidades/FLECHA DE FUEGO.png"},
	{FlechaDeHumo, "project/resources/images/sprites/iconos habilidades/FLECHA DE HUMO.png"},
	{Fortalecer, "project/resources/images/sprites/iconos habilidades/FORTALECER.png"},
	{GolpeDuro, "project/resources/images/sprites/iconos habilidades/GOLPE DURO.png"},
	{HachaArrojadiza, "project/resources/images/sprites/iconos habilidades/HACHA ARROJADIZA.PNG"},
	{LightAttack, "project/resources/images/sprites/iconos habilidades/LightAttack.PNG"},
	{LluviaDeDagas, "project/resources/images/sprites/iconos habilidades/LLUVIA DE DAGAS.png"},
	{Meditacion, "project/resources/images/sprites/iconos habilidades/MEDITACION.png"},
	{OdaDeLosGladiadores, "project/resources/images/sprites/iconos habilidades/ODA DE LOS GLADIADORES.png"},
	{OdaDeViento, "project/resources/images/sprites/iconos habilidades/ODA DE VIENTO.png"},
	{PilarDeTierra, "project/resources/images/sprites/iconos habilidades/PILAR DE TIERRA.png"},
	{ProyectilesDeRoca, "project/resources/images/sprites/iconos habilidades/PROYECTILES DE ROCA.png"},
	{RafagaDeViento, "project/resources/images/sprites/iconos habilidades/RAFAGA DE VIENTO.png"},
	{RayoLuminoso, "project/resources/images/sprites/iconos habilidades/RAYO LUMINOSO.PNG"},
	{Sacrificio, "project/resources/images/sprites/iconos habilidades/SACRIFICIO.PNG"},
	{SedDeSangre, "project/resources/images/sprites/iconos habilidades/SED DE SANGRE.png"},
	{SelfHeal, "project/resources/images/sprites/iconos habilidades/SELF HEAL.png"},
	{Sombra_toxica, "project/resources/images/sprites/iconos habilidades/SOMBRA TOXICA.png"},
	{Proteccion_divina, "project/resources/images/sprites/iconos habilidades/PROTECCION DIVINA.png"},
	{TorrenteAcuatico, "project/resources/images/sprites/iconos habilidades/TORRENTE ACUATICO.PNG"},
	{Trickshot, "project/resources/images/sprites/iconos habilidades/TRICKSHOT.png"},
	{Tsunami, "project/resources/images/sprites/iconos habilidades/TSUNAMI.png"},
	{VorticeDeOscuridad, "project/resources/images/sprites/iconos habilidades/VORTICE DE OSCURIDAD.PNG"},
	{Morph, "project/resources/images/sprites/iconos habilidades/MORPH.png"},
	{ReverseMorph, "project/resources/images/sprites/iconos habilidades/REVERSEMORPH.png"},
		//
	{ Aligerar_, "project/resources/images/sprites/iconos habilidades/ALIGERAR_.PNG" },
	{ Bendicion_, "project/resources/images/sprites/iconos habilidades/BENDICION_.png" },
	{ Bloody_strike_, "project/resources/images/sprites/iconos habilidades/BLODDY_STRIKE_.PNG" },
	{ Bola_fuego_, "project/resources/images/sprites/iconos habilidades/BOLA_DE_FUEGO_.PNG" },
	{ Congelar_, "project/resources/images/sprites/iconos habilidades/CONGELAR_.PNG" },
	{ Cuchilla_aerea_, "project/resources/images/sprites/iconos habilidades/CUCHILLA AEREA_.png" },
	{ Curacion_en_masa_, "project/resources/images/sprites/iconos habilidades/CURACION EN MASA_.png" },
	{ Curacion_, "project/resources/images/sprites/iconos habilidades/CURACION_.PNG" },
	{ Destello_, "project/resources/images/sprites/iconos habilidades/DESTELLO_.png" },
	{ Determinacion_, "project/resources/images/sprites/iconos habilidades/DETERMINACION_.png" },
	{ DisparoDoble_, "project/resources/images/sprites/iconos habilidades/DISPARO DOBLE_.PNG" },
	{ Endurecer_, "project/resources/images/sprites/iconos habilidades/ENDURECER_.png" },
	{ Espinas_, "project/resources/images/sprites/iconos habilidades/ESPINAS_.png" },
	{ FlechaDeFuego_, "project/resources/images/sprites/iconos habilidades/FLECHA DE FUEGO_.png" },
	{ FlechaDeHumo_, "project/resources/images/sprites/iconos habilidades/FLECHA DE HUMO_.png" },
	{ Fortalecer_, "project/resources/images/sprites/iconos habilidades/FORTALECER_.png" },
	{ GolpeDuro_, "project/resources/images/sprites/iconos habilidades/GOLPE DURO_.png" },
	{ HachaArrojadiza_, "project/resources/images/sprites/iconos habilidades/HACHA ARROJADIZA_.PNG" },
	{ LightAttack_, "project/resources/images/sprites/iconos habilidades/LightAttack_.PNG" },
	{ LluviaDeDagas_, "project/resources/images/sprites/iconos habilidades/LLUVIA DE DAGAS_.png" },
	{ Meditacion_, "project/resources/images/sprites/iconos habilidades/MEDITACION_.png" },
	{ OdaDeLosGladiadores_, "project/resources/images/sprites/iconos habilidades/ODA DE LOS GLADIADORES_.png" },
	{ OdaDeViento_, "project/resources/images/sprites/iconos habilidades/ODA DE VIENTO_.png" },
	{ PilarDeTierra_, "project/resources/images/sprites/iconos habilidades/PILAR DE TIERRA_.png" },
	{ ProyectilesDeRoca_, "project/resources/images/sprites/iconos habilidades/PROYECTILES DE ROCA_.png" },
	{ RafagaDeViento_, "project/resources/images/sprites/iconos habilidades/RAFAGA DE VIENTO_.png" },
	{ RayoLuminoso_, "project/resources/images/sprites/iconos habilidades/RAYO LUMINOSO_.PNG" },
	{ Sacrificio_, "project/resources/images/sprites/iconos habilidades/SACRIFICIO_.PNG" },
	{ SedDeSangre_, "project/resources/images/sprites/iconos habilidades/SED DE SANGRE_.png" },
	{ SelfHeal_, "project/resources/images/sprites/iconos habilidades/SELF HEAL_.png" },
	{ Sombra_toxica_, "project/resources/images/sprites/iconos habilidades/SOMBRA TOXICA_.png" },
	{ Proteccion_divina_, "project/resources/images/sprites/iconos habilidades/PROTECCION DIVINA_.png" },
	{ TorrenteAcuatico_, "project/resources/images/sprites/iconos habilidades/TORRENTE ACUATICO_.PNG" },
	{ Trickshot_, "project/resources/images/sprites/iconos habilidades/TRICKSHOT_.png" },
	{ Tsunami_, "project/resources/images/sprites/iconos habilidades/TSUNAMI_.png" },
	{ VorticeDeOscuridad_, "project/resources/images/sprites/iconos habilidades/VORTICE DE OSCURIDAD_.PNG" },
	{ Morph_, "project/resources/images/sprites/iconos habilidades/MORPH_.png" },
	{ ReverseMorph_, "project/resources/images/sprites/iconos habilidades/REVERSEMORPH_.png" },

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
	{ cinematica, "project/resources/images/interfaz/focos/cinematica.png" },
	//Danyo
	{ slash, "project/resources/images/sprites/animaciones/heroes danyo/slashSheet.png" },
	//Taberna
	{ tabernaLobby, "project/resources/images/interfaz/lobby/TabernaLobby.jpg" },
	{ tabernaShop, "project/resources/images/interfaz/lobby/TabernaShop.jpg" },
	{ tabernaStash, "project/resources/images/interfaz/lobby/TabernaStash.jpg" },
	{ bartender, "project/resources/images/sprites/animaciones/taberneroSheet.png" }
};

vector<Resources::TextMsgInfo> Resources::messages_{
	//
};

vector<Resources::MusicInfo> Resources::musics_{
	//
	{MenuInicial, "project/resources/music/Menu principal.mp3"}, //
	{Lobby, "project/resources/music/Lobby.wav"}, //
	{Exploracion, "project/resources/music/Exploracion.mp3"}, //
	{Combate, "project/resources/music/Combate.mp3"}, //
	{Derrota, "project/resources/music/Derrota.mp3"}, //
	{Creditos, "project/resources/music/Creditos.mp3"}, //
	{CombateBoss, "project/resources/music/CombateBoss.mp3"} //
};

vector<Resources::SoundInfo> Resources::sounds_{
	//
	{AtaqueAgua, "project/resources/sound/ataque agua.mp3"}, //
	{AtaqueFuego, "project/resources/sound/ataque fuego.mp3"}, //
	{AtaqueLuz, "project/resources/sound/ataque luz.mp3"}, //
	{AtaqueViento, "project/resources/sound/ataque viento.mp3"}, //
	{Boton1, "project/resources/sound/boton 1.mp3"}, //
	{Boton2, "project/resources/sound/boton 2.mp3"}, //
	{Error, "project/resources/sound/error.mp3"}, //
	//{CofreSound, "project/resources/sound/cofre.mp3"}, //
};

vector<Resources::JsonInfo> Resources::jsons_{
	//
	{Heroes, "project/resources/jsons/heroes.json"},		  //
	{Enemies, "project/resources/jsons/enemies.json"},		  //
	{Weapons, "project/resources/jsons/pruebasArmas.json"},	  //
	{Armors, "project/resources/jsons/pruebasArmaduras.json"} //
};
