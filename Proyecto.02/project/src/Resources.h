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

		no_visitado,
		no_entrado,
		visitado,
		pared_N, // Pared norte minimapa
		pared_E, // Pared este minimapa
		pared_S, // Pared sur minimapa
		pared_O, // Pared oeste minimapa
		salidaMiniMap,
		texto_salida,
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
		Defensa,
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

		// Comodin
		Joker,

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

		//Armaduras
		Acolchada,
		CueroTachonado,
		CotaEscamas,
		Coraza,
		SemiPlacas,
		CotaMalla,
		Bandas,
		Placas,

		//Enemigos
		Zombie,
		Troll,
		Skeleton,
		Hellhound,
		Specter,
		Goblin,
		DeathKnight,
		Mimic,
		Pixie,
		Ghoul,
		Dracolich,
		GiantWorm,
		Banshee,
		Lich,
		Necrofago,
		Monster,
		Desconocido,

		//Ficha DD
		Pergamino
	};

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
		ARIAL16, ARIAL24, HERMAN, Fornite, Quake, KillerInst, Sega, Beaulieux, Triforce
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
