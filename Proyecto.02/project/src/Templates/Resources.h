#pragma once

#include <SDL.h>
#include <string>
#include <vector>

using namespace std;

class Resources {
public:

	enum TextureId {
		// images
		posMiniMap = 0,
		camino_izq,
		camino_der,
		camino_fr,
		muro_izq,
		muro_der,
		muro_fr,
		muro_fr_izq,
		muro_fr_der,
		muro_del,
		// Imagenes de la casilla siguiente a la actual
		camino_fondo_izq,
		camino_fondo_der,
		camino_fondo_fr,
		muro_fondo_izq,
		muro_fondo_der,
		muro_fondo_fr,
		muro_fondo_fr_izq,
		muro_fondo_fr_der,
		fondo_vacio,
		no_visitado,
		no_entrado,
		visitado,
		pared_N, // Pared norte minimapa
		pared_E, // Pared este minimapa
		pared_S, // Pared sur minimapa
		pared_O, // Pared oeste minimapa
		salidaMiniMap,
		cofreMiniMap,
		texto_salida,
		puerta,

		start,
		options,
		quit,
		mFondo,
		close,

		// heroes
		_firstHeroRId_,
		Guerrero,
		Brujo,
		Explorador,
		Bardo,
		Clerigo,
		Paladin,
		Barbaro,
		Picaro,
		Druida,
		Bestia,
		GranArchimago,
			//
		Guerrero_,
		Brujo_,
		Explorador_,
		Bardo_,
		Clerigo_,
		Paladin_,
		Barbaro_,
		Picaro_,
		Druida_,
		Bestia_,
		GranArchimago_,
			//
		Guerrero__,
		Brujo__,
		Explorador__,
		Bardo__,
		Clerigo__,
		Paladin__,
		Barbaro__,
		Picaro__,
		Druida__,
		Bestia__,
		GranArchimago__,

		// UI
		Mouse,
		Fondo,
		Fondo2,
		Change,
		Change2,
		Button_transition,
		Cartel,
		VolumeBar,
		VolumeBarBackground,
		BuyButton,
		EquipButton,
		FireButton,
		RecruitButton,
		SellButton,
		StoreItemButton,
		lobby_button,
		stash_button,
		inventory_button,
		take, 
		vibration,
		fade,
		DiceRed,
		DiceGreen,
		marco_hero,

		// carteles tutorial
		_firstCartelId_,
		cartel_combate,
		cartel_movimiento,
		cartel_inventario,
		cartel_support, // chat/feed
		cartel_heroes,
		cartel_minimapa,
		cartel_configuracion,
		cartel_bienvenida_pt1,
		cartel_bienvenida_pt2,

		// paneles focalizados
		_firstFocoId_,
		foco_combate, // comparte con movimiento, habilidades y objetivos
		foco_inventario, // comparte con configuracion
		foco_support, // chat/feed
		foco_heroes,
		foco_minimapa,
		cinematica,

		// movement
		Avanzar,
		RotarD,
		RotarI,
		RotarDAlt,
		RotarIAlt,
		Retroceder,
		AvanzarBloqueado,
		RetrocederBloqueado,
		
		//Info
		Inventario,
		CofreMenu,
		PocionVida,
		PocionVida_,
		PocionMana,
		PocionMana_,
		Configuracion,
		Configuracion_,

		//Combate
		AtaqueNormal,
		AtaqueMagico,
		Enter,
		Huida,

		//Inventario
		Slot,
		WeaponSlot,
		ArmorSlot,
		inventory_slots,

		//Objetos
		_firstWeaponId_,
		Desarmado,
		Baston,
		Daga,
		Clava,
		HachaPequena,
		Hoz,
		Lanza,
		MartilloPequeno,
		Maza,
		ArcoPequeno,
		BallestaLigera,

		//Armas Marciales
		Alabarda,
		Atarraga,
		EspadaCorta,
		EspadaLarga,
		Espadon,
		EspadaRopera,
		HachaBatalla,
		Guja,
		Latigo,
		LuceroAlba,
		MartilloGuerra,
		Pica,
		Tridente,
		ArcoLargo,
		BallestaPesada,
		
		// Comodin
		Joker,
		
		//Armaduras
		_firstArmorId_,
		Acolchada,
		CueroTachonado,
		CotaEscamas,
		Coraza,
		SemiPlacas,
		CotaMalla,
		Bandas,
		Placas,

		//Enemigos
		_firstEnemyId_,
		Goblin,
		Pixie,
		Zombie,
		Skeleton,
		Specter,
		Troll,
		Hellhound,
		Mimic,
		Ghoul,
		GiantWorm,
		Banshee,
		DeathKnight,
		Dracolich,
		Lich,

		//Cofre
		CofreCerrado,
		CofreVacio,
		CofreLleno,

		//Llaves
		LlaveCofre,
		LlaveNivel,
		LlaveVacia,

		//Ficha DD
		Pergamino,
		//Panel Desc.
		Cartelito,

		//Habilidades
		_firstSkillId_,
		LightAttack,
		Bola_fuego,
		Bloody_strike,
		Curacion,
		Curacion_en_masa,
		SelfHeal,
		RafagaDeViento,
		Cuchilla_aerea,
		PilarDeTierra,
		Sombra_toxica,
		Tsunami,
		Proteccion_divina,
		Destello,
		Congelar,
		TorrenteAcuatico,
		RayoLuminoso,
		VorticeDeOscuridad,
		FlechaDeFuego,
		Meditacion,
		Aligerar,
		Fortalecer,
		Endurecer,
		SedDeSangre,
		Sacrificio,
		DisparoDoble,
		HachaArrojadiza,
		Morph,
		ReverseMorph,
		GolpeDuro,
		FlechaDeHumo,
		LluviaDeDagas,
		ProyectilesDeRoca,
		Trickshot,
		OdaDeLosGladiadores,
		OdaDeViento,
		Determinacion,
		Bendicion,
		Espinas,
			//
		LightAttack_,
		Bola_fuego_,
		Bloody_strike_,
		Curacion_,
		Curacion_en_masa_,
		SelfHeal_,
		RafagaDeViento_,
		Cuchilla_aerea_,
		PilarDeTierra_,
		Sombra_toxica_,
		Tsunami_,
		Proteccion_divina_,
		Destello_,
		Congelar_,
		TorrenteAcuatico_,
		RayoLuminoso_,
		VorticeDeOscuridad_,
		FlechaDeFuego_,
		Meditacion_,
		Aligerar_,
		Fortalecer_,
		Endurecer_,
		SedDeSangre_,
		Sacrificio_,
		DisparoDoble_,
		HachaArrojadiza_,
		Morph_,
		ReverseMorph_,
		GolpeDuro_,
		FlechaDeHumo_,
		LluviaDeDagas_,
		ProyectilesDeRoca_,
		Trickshot_,
		OdaDeLosGladiadores_,
		OdaDeViento_,
		Determinacion_,
		Bendicion_,
		Espinas_,
		//Danyo
		slash,
		//Taberna
		tabernaLobby,
		tabernaShop,
		tabernaStash,
		bartender,
	}; using txtID = TextureId;

	enum AudioId : std::size_t {
		// music
		MenuInicial,
		Lobby,
		Exploracion,
		Combate,
		Derrota,
		Creditos,
		CombateBoss,

		// sound effects
		AtaqueAgua,
		AtaqueFuego,
		AtaqueLuz, 
		AtaqueViento,
		Boton1,
		Boton2,
		Error,
		//CofreSound,
	};

	enum FontId : std::size_t {
		HERMAN,
		Fornite64,
		Beaulieux,
		Medieval,
		Console,
		ConsoleBO
	};

	enum JsonId : std::size_t {
		Heroes,
		Enemies,
		Weapons,
		Armors
	};

	struct FontInfo {
		FontId id;
		string fileName;
		int size;
	};

	struct ImageInfo {
		TextureId id;
		string fileName;
	};

	struct TextMsgInfo {
		TextureId id;
		string msg;
		SDL_Color color;
		FontId fontId;
	};

	struct MusicInfo {
		AudioId id;
		string fileName;
	};

	struct SoundInfo {
		AudioId id;
		string fileName;

	};

	struct JsonInfo {
		JsonId id;
		string filename;
	};

	static vector<FontInfo> fonts_; // initialized in .cpp
	static vector<ImageInfo> images_; // initialized in .cpp
	static vector<TextMsgInfo> messages_; // initialized in .cpp
	static vector<MusicInfo> musics_; // initialized in .cpp
	static vector<SoundInfo> sounds_; // initialized in .cpp
	static vector<JsonInfo> jsons_; // initialized in .cpp
	//static vector<ClassTemplates> classTemplates_;

};

using src = Resources;
