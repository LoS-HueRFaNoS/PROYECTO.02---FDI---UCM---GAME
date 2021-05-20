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
		texto_salida,

		lobFondo,
		mFondo,
		close,

		start,
		options,
		howToPlay,
		quit,

		cargando,

		// text
		HelloWorld,
		PressAnyKey,
		GameOverWon,
		GameOverLost,

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

		// UI
		Mouse,
		Fondo,
		Fondo2,
		Change,
		Selected,

		// movement
		Avanzar,
		RotarD,
		RotarI,
		Interactuar,

		//Info
		Inventario,
		PocionVida,
		PocionMana,
		PocionRess,
		Chat,
		Configuracion,

		//Combate
		AtaqueNormal,
		AtaqueMagico,
		Enter,
		Huida,
		Marco,
		Target,
		Hability,

//Inventario
		Slot,
		EmptySword,
		EmptyArmor,
		WeaponSlot,
		ArmorSlot,

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
		Necrofago,
		Monster,
		Desconocido,

		//Ficha DD
		Pergamino,

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
	}; using txtID = TextureId;

	enum AudioId : std::size_t {
		// music
		ImperialMarch,
		Mystery,
		Tension,

		// sound effects
		Explosion,
		Notification,
		GameOver
	};

	enum FontId : std::size_t {
		ARIAL16, ARIAL24, HERMAN, Fornite64, Fornite14, Quake, KillerInst, Sega, Beaulieux, Triforce
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
